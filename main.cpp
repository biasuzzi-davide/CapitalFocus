#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QDir>
#include <QDebug>

#include "model/Cafe.h"
#include "model/Disco.h"
#include "model/Restaurant.h"
#include "model/LocalMarket.h"
#include "model/Mall.h"
#include "model/PanoramicPoints.h"
#include "model/Museum.h"
#include "model/Monument.h"
#include "model/visitor/placeexporttoxmlvisitor.h"
#include "model/visitor/placeimportfromxml.h".h"

QString weekdayToString(Weekday day) {
    switch (day) {
    case Weekday::Monday: return "Monday";
    case Weekday::Tuesday: return "Tuesday";
    case Weekday::Wednesday: return "Wednesday";
    case Weekday::Thursday: return "Thursday";
    case Weekday::Friday: return "Friday";
    case Weekday::Saturday: return "Saturday";
    case Weekday::Sunday: return "Sunday";
    default: return "Unknown";
    }
}

void printPlaceDetails(const Place* p) {
    qDebug() << "\n📌 Tipo:" << p->getCategory();
    qDebug() << "Nome:" << p->getName();
    qDebug() << "Città:" << p->getCity();
    qDebug() << "Descrizione:" << p->getDescription();
    qDebug() << "Rating:" << p->getRating();
    qDebug() << "Costo:" << p->getCost();

    for (int i = 0; i < 7; ++i) {
        Weekday day = static_cast<Weekday>(i);
        QString slot = p->getOpen().getOpeningFrameString(day);
        if (!slot.isEmpty()) {
            qDebug() << "Orario " << weekdayToString(day) << ":" << slot;
        }
    }

    // Specifici per tipo
    if (auto c = dynamic_cast<const Cafe*>(p)) {
        qDebug() << " - Terrazza:" << (c->hasTerrace() ? "Sì" : "No");
        qDebug() << " - Specialità:" << c->getSpecialDrink();
    }
    else if (auto d = dynamic_cast<const Disco*>(p)) {
        qDebug() << " - Genere musicale:" << d->getMusicGenre();
        qDebug() << " - Prive:" << (d->hasPriveAccess() ? "Sì" : "No");
        qDebug() << " - Dress code:" << d->getDressCode();
    }
    else if (auto r = dynamic_cast<const Restaurant*>(p)) {
        qDebug() << " - Cucina:" << r->getCuisineType();
        qDebug() << " - Prenotazione:" << (r->hasReservation() ? "Sì" : "No");
        qDebug() << " - Piatto speciale:" << r->getSpecialDish();
    }
    else if (auto mkt = dynamic_cast<const LocalMarket*>(p)) {
        qDebug() << " - Artigiani:" << (mkt->hasArtisans() ? "Sì" : "No");
        qDebug() << " - Stagionale:" << (mkt->isSeasonal() ? "Sì" : "No");
        qDebug() << " - Periodo:" << mkt->getPeriod();
    }
    else if (auto mall = dynamic_cast<const Mall*>(p)) {
        qDebug() << " - Negozi:" << mall->getShopCount();
        qDebug() << " - Cinema:" << (mall->hasCinema() ? "Sì" : "No");
        qDebug() << " - Parcheggio gratis:" << (mall->hasFreeParking() ? "Sì" : "No");
    }
    else if (auto pano = dynamic_cast<const PanoramicPoints*>(p)) {
        qDebug() << " - Altitudine:" << pano->getAltitude();
        qDebug() << " - Binocolo:" << (pano->hasBinoculars() ? "Sì" : "No");
        qDebug() << " - Illuminazione notturna:" << (pano->isNightLit() ? "Sì" : "No");
    }
    else if (auto mus = dynamic_cast<const Museum*>(p)) {
        qDebug() << " - Audioguida:" << (mus->hasAudioGuideAvailable() ? "Sì" : "No");
    }
    else if (auto mon = dynamic_cast<const Monument*>(p)) {
        qDebug() << " - Patrimonio UNESCO:" << (mon->isUnesco() ? "Sì" : "No");
        qDebug() << " - Conservazione:" << mon->getConservationStatus();
        qDebug() << " - Visitabile:" << (mon->isOpenToPublic() ? "Sì" : "No");
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    qDebug() << "=== Inizio export completo ===";

    weeklyOpenings commonOpenings;
    commonOpenings.setOpening(Weekday::Monday, QTime(9, 0), QTime(18, 0));

    QDomDocument doc("places");
    QDomElement root = doc.createElement("places");
    doc.appendChild(root);
    PlaceExportToXmlVisitor visitor(doc);

    // 1. Cafe
    for (int i = 1; i <= 3; ++i) {
        Cafe obj("Cafe " + QString::number(i), "Città", "Descrizione cafe",
                 4.0 + i * 0.1, commonOpenings, 2.5 + i,
                 true, QTime(0, 5 + i), i % 2, true, "Drink " + QString::number(i));
        obj.acceptVisitor(visitor);
        root.appendChild(visitor.getResult());
    }

    // 2. Disco
    for (int i = 1; i <= 3; ++i) {
        Disco obj("Disco " + QString::number(i), "Città", "Descrizione disco",
                  4.0 + i * 0.2, commonOpenings, 10 + i,
                  2.0, 18 + i, "Accesso " + QString::number(i),
                  "Genere " + QString::number(i), i % 2, "DressCode " + QString::number(i));
        obj.acceptVisitor(visitor);
        root.appendChild(visitor.getResult());
    }

    // 3. Restaurant
    for (int i = 1; i <= 3; ++i) {
        Restaurant obj("Ristorante " + QString::number(i), "Città", "Descrizione ristorante",
                       4.0 + i * 0.2, commonOpenings, 15 + i,
                       i % 2, QTime(0, 10 + i), true,
                       "Cucina " + QString::number(i), true, "Piatto " + QString::number(i));
        obj.acceptVisitor(visitor);
        root.appendChild(visitor.getResult());
    }

    // 4. LocalMarket
    for (int i = 1; i <= 3; ++i) {
        LocalMarket obj("Mercato " + QString::number(i), "Città", "Descrizione mercato",
                        3.5 + i * 0.2, commonOpenings, 0,
                        true, i % 2, 10 + i,
                        i % 2, i % 2, "Periodo " + QString::number(i));
        obj.acceptVisitor(visitor);
        root.appendChild(visitor.getResult());
    }

    // 5. Mall
    for (int i = 1; i <= 3; ++i) {
        Mall obj("Mall " + QString::number(i), "Città", "Descrizione mall",
                 3.5 + i * 0.3, commonOpenings, 0,
                 true, true, 20 + i,
                 100 + i, i % 2, i % 2);
        obj.acceptVisitor(visitor);
        root.appendChild(visitor.getResult());
    }

    // 6. PanoramicPoints
    for (int i = 1; i <= 3; ++i) {
        PanoramicPoints obj("Panorama " + QString::number(i), "Città", "Punto panoramico",
                            4.0 + i * 0.1, commonOpenings, 5 + i,
                            1.0, 0, "Aperto",
                            300 + i * 10, i % 2, i % 2);
        obj.acceptVisitor(visitor);
        root.appendChild(visitor.getResult());
    }

    // 7. Museum
    for (int i = 1; i <= 3; ++i) {
        Museum obj("Museo " + QString::number(i), "Città", "Descrizione museo",
                   4.5, commonOpenings, 10 + i,
                   2.0, true, "Arte " + QString::number(i), "Sì", i % 2);
        obj.acceptVisitor(visitor);
        root.appendChild(visitor.getResult());
    }

    // 8. Monument
    for (int i = 1; i <= 3; ++i) {
        Monument obj("Monumento " + QString::number(i), "Città", "LLALALAL",
                     5.0, commonOpenings, 8.0,
                     1.0, false, "Storia " + QString::number(i), "Sì", i % 2,
                     "Stato " + QString::number(i), i % 2);
        obj.acceptVisitor(visitor);
        root.appendChild(visitor.getResult());
    }

    // 9. Salvataggio
    QString exportPath = QDir("../../../../../export").absoluteFilePath("export.xml");
    QDir exportDir = QFileInfo(exportPath).absoluteDir();
    if (!exportDir.exists()) exportDir.mkpath(".");

    QFile file(exportPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "❌ Errore: impossibile scrivere su export.xml";
        return 1;
    }

    QTextStream stream(&file);
    stream << doc.toString(4);
    file.close();

    qDebug() << "✅ Export completato! File salvato in:" << exportPath;


    qDebug() << "Ora inizio con l'import";
        // === IMPORT XML E STAMPA RISULTATO ===
        qDebug() << "\n=== Lettura da XML ===";

    PlaceImportFromXml importer;
    std::vector<Place*> importedPlaces = importer.importFromFile("../../../../../export/export.xml");

    for (const auto& p : importedPlaces)
        printPlaceDetails(p);

    // (Opzionale) liberazione memoria, se non usi smart pointer
    for (auto p : importedPlaces)
        delete p;
}
