#include "placeimportfromxml.h"

// Includiamo gli header delle classi concrete per poterle creare
#include "model/Cafe.h"
#include "model/Disco.h"
#include "model/Restaurant.h"
#include "model/LocalMarket.h"
#include "model/Mall.h"
#include "model/Museum.h"
#include "model/Monument.h"
#include "model/PanoramicPoint.h"
#include "model/import_errors.h"
#include "model/debugconfig.h"

#include <QFile>
#include <QDomElement>
#include <QDomNodeList>
#include <QTime>
#include <QDebug>

// Parsa gli orari di apertura da un elemento XML
weeklyOpenings PlaceImportFromXml::parseOpenings(const QDomElement& parent) const {
    weeklyOpenings week; // Crea un oggetto weeklyOpenings

    // Trova l'elemento 'openings' figlio
    QDomElement openingsElem = parent.firstChildElement("openings");

    // Trova tutti gli elementi 'day' all'interno di 'openings'
    QDomNodeList days = openingsElem.elementsByTagName("day");

    // Itera su ogni giorno
    for (int i = 0; i < days.count(); ++i) {
        QDomElement d = days.at(i).toElement();
        Weekday day = weeklyOpenings::weekdayFromString(d.attribute("name"));

        // Controlla se il giorno è segnato come chiuso
        if (d.hasAttribute("closed") && d.attribute("closed").toInt()) {
            week.setClosed(day);
            continue;
        }

        // Controlla se il giorno è segnato come sempre aperto
        if (d.hasAttribute("alwaysOpen") && d.attribute("alwaysOpen").toInt()) {
            week.setAlwaysOpen(day);
            continue;
        }

        // Se non è chiuso o sempre aperto, parsa l'orario specifico
        QDomElement slot = d.firstChildElement("slot");
        QTime from = QTime::fromString(slot.attribute("from"), "HH:mm");
        QTime to   = QTime::fromString(slot.attribute("to"),   "HH:mm");

        if (!from.isValid() || !to.isValid() || from >= to)
            throw std::invalid_argument("Invalid time frame"); // Lancia eccezione se orari non validi

        week.setOpening(day, from, to);
    }
    return week;
}

// Legge i Place da un file XML
std::vector<std::shared_ptr<Place>> PlaceImportFromXml::importFromFile(const QString& filePath) const {
    std::vector<std::shared_ptr<Place>> imported; // Lista per i Place importati

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw FileOpenError(filePath); // Lancia eccezione se non si riesce ad aprire il file

    QDomDocument doc;
    QString errMsg; int line = 0, col = 0;

    // Parsa il contenuto del file in un documento XML
    if (!doc.setContent(&file, false, &errMsg, &line, &col)) {
        // Lancia eccezione se parsing fallisce
        throw XmlParseError(QString("%1 (%2:%3)")
                                .arg(errMsg).arg(line).arg(col));
    }
    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != "places")
        throw XmlParseError("Root element must be <places>");

    QDomNodeList nodes = root.childNodes();

    // Itera su ogni nodo figlio
    for (int i = 0; i < nodes.count(); ++i) {
        QDomElement el = nodes.at(i).toElement(); // Converte il nodo in elemento
        QString type = el.tagName(); // Ottiene il tipo del Place dal nome del tag

        // Legge gli attributi comuni a tutti i Place
        QString name = el.attribute("name");
        QString city = el.attribute("city");
        QString desc = el.attribute("description");
        double rating = el.attribute("rating").toDouble();
        double cost   = el.attribute("cost").toDouble();

        // Valida gli attributi comuni minimi, lanciando un'eccezione se inadeguati
        if (type.isEmpty() || name.isEmpty() || city.isEmpty())
            throw std::invalid_argument("Missing required attributes");
        if (rating < 0.0 || rating > 5.0)
            throw std::invalid_argument("Rating out of range [0-5]");

        // Parsa gli orari di apertura specifici per questo Place
        weeklyOpenings open = parseOpenings(el);

        // Crea l'oggetto Place corretto in base al tipo
        if (type == "Cafe") {
            QDomElement fd = el.firstChildElement("foodData");
            bool takeAway = fd.attribute("hasTakeAway").toInt();
            QTime avgWait = QTime::fromString(fd.attribute("avgWaitingTime"), "HH:mm");
            bool veganMenu = fd.attribute("hasVeganMenu").toInt();
            bool terrace = el.attribute("hasTerrace").toInt();
            QString drink = el.attribute("famousDrink");
            imported.push_back(std::make_shared<Cafe>(
                name, city, desc, rating, open, cost,
                takeAway, avgWait, veganMenu,
                terrace, drink
                ));
        }
        else if (type == "Restaurant") {
            QDomElement fd = el.firstChildElement("foodData");
            bool takeAway = fd.attribute("hasTakeAway").toInt();
            QTime avgWait = QTime::fromString(fd.attribute("avgWaitingTime"), "HH:mm");
            bool veganMenu = fd.attribute("hasVeganMenu").toInt();
            QString cuisine = el.attribute("cuisineType");
            bool res = el.attribute("reservation").toInt();
            QString special = el.attribute("specialDish");
            imported.push_back(std::make_shared<Restaurant>(
                name, city, desc, rating, open, cost,
                takeAway, avgWait, veganMenu,
                cuisine, res, special
                ));
        }
        else if (type == "Disco") {
            QDomElement ed = el.firstChildElement("entertainmentData");
            QTime avgStay = QTime::fromString(ed.attribute("avgStayDuration"), "HH:mm");
            int minAge = ed.attribute("minimumAge").toInt();
            QString restrict = ed.attribute("restrictedEntry");
            QString genre = el.attribute("musicGenre");
            bool prive = el.attribute("hasPrive").toInt();
            QString dressCode = el.attribute("dressCode");
            imported.push_back(std::make_shared<Disco>(
                name, city, desc, rating, open, cost,
                avgStay, minAge, restrict,
                genre, prive, dressCode
                ));
        }
        else if (type == "PanoramicPoint") {
            QDomElement ed = el.firstChildElement("entertainmentData");
            QTime avgStay = QTime::fromString(ed.attribute("avgStayDuration"), "HH:mm");
            int minAge = ed.attribute("minimumAge").toInt();
            QString restrict = ed.attribute("restrictedEntry");
            double altitude = el.attribute("altitude").toDouble();
            bool binocular = el.attribute("hasBinocular").toInt();
            bool night = el.attribute("nightLighting").toInt();
            imported.push_back(std::make_shared<PanoramicPoint>(
                name, city, desc, rating, open, cost,
                avgStay, minAge, restrict,
                altitude, binocular, night
                ));
        }
        else if (type == "LocalMarket") {
            QDomElement sd = el.firstChildElement("shoppingData");
            bool outdoor = sd.attribute("isOutdoor").toInt();
            bool foodArea = sd.attribute("foodAreaPresent").toInt();
            int stands = sd.attribute("standNumber").toInt();
            bool artisans = el.attribute("artisans").toInt();
            bool seasonal = el.attribute("seasonal").toInt();
            QString period = el.attribute("period");
            imported.push_back(std::make_shared<LocalMarket>(
                name, city, desc, rating, open, cost,
                outdoor, foodArea, stands,
                artisans, seasonal, period
                ));
        }
        else if (type == "Mall") {
            QDomElement sd = el.firstChildElement("shoppingData");
            bool outdoor = sd.attribute("isOutdoor").toInt();
            bool foodArea = sd.attribute("foodAreaPresent").toInt();
            int stands = sd.attribute("standNumber").toInt();
            int shopCount = el.attribute("shopCount").toInt();
            bool cinema = el.attribute("cinema").toInt();
            bool parking = el.attribute("freeParking").toInt();
            imported.push_back(std::make_shared<Mall>(
                name, city, desc, rating, open, cost,
                outdoor, foodArea, stands,
                shopCount, cinema, parking
                ));
        }
        else if (type == "Museum") {
            QDomElement cd = el.firstChildElement("cultureData");
            double studentDiscount = cd.attribute("studentDiscount").toDouble();
            bool guidedTour = cd.attribute("guidedTour").toInt();
            QString focus = cd.attribute("culturalFocus");
            bool audio = el.attribute("hasAudioGuide").toInt();
            imported.push_back(std::make_shared<Museum>(
                name, city, desc, rating, open, cost,
                studentDiscount, guidedTour, focus, audio
                ));
        }
        else if (type == "Monument") {
            QDomElement cd = el.firstChildElement("cultureData");
            double studentDiscount = cd.attribute("studentDiscount").toDouble();
            bool guidedTour = cd.attribute("guidedTour").toInt();
            QString focus = cd.attribute("culturalFocus");
            bool unesco = el.attribute("isUnesco").toInt();
            QString state = el.attribute("conservationStatus");
            bool openTo = el.attribute("openToPublic").toInt();
            imported.push_back(std::make_shared<Monument>(
                name, city, desc, rating, open, cost,
                studentDiscount, guidedTour, focus,
                unesco, state, openTo
                ));
        }
        else throw std::invalid_argument("Unknown type: " + type.toStdString()); // Lancia eccezione per tipo sconosciuto
    }

    DEBUG_LOG("XML IMPORTER: IMPORTATI OGGETTI #" << imported.size()); // Log di debug
    return imported; // Ritorna la lista dei Place importati
}
