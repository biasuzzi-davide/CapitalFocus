#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QDebug>
#include <QDir>

#include "model/Cafe.h"
#include "model/visitor/placeexporttoxmlvisitor.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    qDebug() << "=== Inizio esportazione XML ===";

    // 1. Crea un oggetto Cafe di test
    weeklyOpenings openings;
    openings.setOpening(Weekday::Monday, QTime(9, 0), QTime(18, 0));

    Cafe cafe("Bar Centrale", "Padova", "Il miglior caffè in centro",
              4.5, openings, 2.50,
              true, QTime(0, 5), true, true, "Cappuccino");

    qDebug() << "Oggetto Cafe creato correttamente.";

    // 2. Crea documento XML
    QDomDocument doc("places");
    PlaceExportToXmlVisitor visitor(doc);
    cafe.acceptVisitor(visitor);

    QDomElement root = doc.createElement("places");
    root.appendChild(visitor.getResult());
    doc.appendChild(root);

    qDebug() << "Documento XML generato.";

    // 3. Percorso statico hardcoded alla cartella progetto
    QString exportPath = QDir("../../../../../export").absoluteFilePath("export.xml");

    QDir exportDir = QFileInfo(exportPath).absoluteDir();
    if (!exportDir.exists()) {
        if (!exportDir.mkpath(".")) {
            qCritical() << "❌ Errore nella creazione della cartella export!";
            return 1;
        }
    }

    qDebug() << "Tentativo di scrittura su file:" << exportPath;

    // 4. Salva su file
    QFile file(exportPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "❌ Errore nell'apertura del file di output!";
        return 1;
    }

    QTextStream stream(&file);
    stream << doc.toString(4);
    file.close();

    qDebug() << "✅ Export completato!";
    qDebug() << "📁 File generato in:" << exportPath;

    return 0;
}
