#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QDir>

#include "model/Cafe.h"
#include "model/Disco.h"
#include "model/Restaurant.h"
#include "model/LocalMarket.h"
#include "model/Mall.h"
#include "model/PanoramicPoints.h"
#include "model/Museum.h"
#include "model/Monument.h"
#include "model/visitor/PlaceExportToJsonVisitor.h"
#include "model/visitor/PlaceImportFromJson.h"

// Funzione di stampa base (puoi aggiungere dynamic_cast come nel tuo esempio XML)
void printPlaceDetails(const Place* p) {
    qDebug() << "\n📌 Tipo:" << p->getCategory();
    qDebug() << "Nome:" << p->getName();
    qDebug() << "Città:" << p->getCity();
    qDebug() << "Descrizione:" << p->getDescription();
    qDebug() << "Rating:" << p->getRating();
    qDebug() << "Costo:" << p->getCost();
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    qDebug() << "=== Export JSON ===";

    // Orari comuni
    weeklyOpenings openings;
    openings.setOpening(Weekday::Monday, QTime(9, 0), QTime(18, 0));

    // Export JSON
    QJsonArray placesArray;
    PlaceExportToJsonVisitor visitor;

    for (int i = 1; i <= 2; ++i) {
        Cafe obj("Cafe " + QString::number(i), "Roma", "Descrizione",
                 4.5, openings, 3.0 + i,
                 true, QTime(0, 5 + i), true, true, "Cappuccino");

        obj.acceptVisitor(visitor);
        placesArray.append(visitor.getResult());
    }

    QJsonDocument doc(placesArray);

    QString path = QDir("../../../../../export").absoluteFilePath("export.json");
    QDir dir = QFileInfo(path).absoluteDir();
    if (!dir.exists()) dir.mkpath(".");

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        qCritical() << "❌ Errore apertura file JSON per scrittura.";
        return 1;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "✅ File esportato in:" << path;

    // === Import JSON ===
    qDebug() << "\n=== Import JSON ===";
    PlaceImportFromJson importer;
    std::vector<Place*> imported = importer.importFromJson(path);

    for (const Place* p : imported)
        printPlaceDetails(p);

    for (Place* p : imported)
        delete p;

    return 0;
}
