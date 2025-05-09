#include "placeimportfromxml.h"
#include "model/Cafe.h"
#include "model/Disco.h"
#include "model/Restaurant.h"
#include "model/LocalMarket.h"
#include "model/Mall.h"
#include "model/Museum.h"
#include "model/Monument.h"
#include "model/PanoramicPoints.h"
#include "model/import_errors.h"
#include "model/debugconfig.h"

#include <QFile>
#include <QDomElement>
#include <QDomNodeList>
#include <QTime>
#include <QDebug>

weeklyOpenings PlaceImportFromXml::parseOpenings(const QDomElement& parent) const {
    weeklyOpenings week;

    QDomElement openingsElem = parent.firstChildElement("openings");
    QDomNodeList days = openingsElem.elementsByTagName("day");
    for (int i = 0; i < days.count(); ++i) {
        QDomElement d = days.at(i).toElement();
        Weekday day = weeklyOpenings::weekdayFromString(d.attribute("name"));

        if (d.hasAttribute("closed") && d.attribute("closed").toInt()) {
            week.setClosed(day);
            continue;
        }

        if (d.hasAttribute("alwaysOpen") && d.attribute("alwaysOpen").toInt()) {
            week.setAlwaysOpen(day);
            continue;
        }

        QDomElement slot = d.firstChildElement("slot");
        QTime from = QTime::fromString(slot.attribute("from"), "HH:mm");
        QTime to   = QTime::fromString(slot.attribute("to"),   "HH:mm");
        if (!from.isValid() || !to.isValid() || from >= to)
            throw std::invalid_argument("Invalid time frame");
        week.setOpening(day, from, to);
    }
    return week;
}

std::vector<std::shared_ptr<Place>> PlaceImportFromXml::importFromFile(const QString& filePath) const {
    std::vector<std::shared_ptr<Place>> imported;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw FileOpenError(filePath);

    QDomDocument doc;
    QString errMsg; int line = 0, col = 0;
    if (!doc.setContent(&file, false, &errMsg, &line, &col)) {
        throw XmlParseError(QString("%1 (%2:%3)")
                                .arg(errMsg).arg(line).arg(col));
    }
    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != "places")
        throw XmlParseError("Root element must be <places>");

    QDomNodeList nodes = root.childNodes();
    for (int i = 0; i < nodes.count(); ++i) {
        QDomElement el = nodes.at(i).toElement();
        QString type = el.tagName();

        QString name = el.attribute("name");
        QString city = el.attribute("city");
        QString desc = el.attribute("description");
        double rating = el.attribute("rating").toDouble();
        double cost   = el.attribute("cost").toDouble();
        if (type.isEmpty() || name.isEmpty() || city.isEmpty())
            throw std::invalid_argument("Missing required attributes");
        if (rating < 0.0 || rating > 5.0)
            throw std::invalid_argument("Rating out of range [0-5]");

        weeklyOpenings open = parseOpenings(el);

        if (type == "Cafe") {
            // Intermediary Food data
            QDomElement fd = el.firstChildElement("foodData");
            bool takeAway = fd.attribute("hasTakeAway").toInt();
            QTime avgWait = QTime::fromString(fd.attribute("avgWaitingTime"), "HH:mm");
            bool veganMenu = fd.attribute("hasVeganMenu").toInt();
            // Specific Cafe data
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
            QTime avgStay = QTime::fromString(ed.attribute("avgWaitingTime"), "HH:mm");
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
        else if (type == "PanoramicPoints") {
            QDomElement ed = el.firstChildElement("entertainmentData");
            QTime avgStay = QTime::fromString(ed.attribute("avgWaitingTime"), "HH:mm");
            int minAge = ed.attribute("minimumAge").toInt();
            QString restrict = ed.attribute("restrictedEntry");
            double altitude = el.attribute("altitude").toDouble();
            bool binocular = el.attribute("hasBinocular").toInt();
            bool night = el.attribute("nightLighting").toInt();
            imported.push_back(std::make_shared<PanoramicPoints>(
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
            bool guided = el.attribute("hasGuidedTour").toInt();
            QString focus = el.attribute("culturalFocus");
            bool audio = el.attribute("hasAudioGuide").toInt();
            double discount = el.attribute("studentDiscount").toDouble();
            imported.push_back(std::make_shared<Museum>(
                name, city, desc, rating, open, cost,
                discount, guided, focus, audio
                ));
        }
        else if (type == "Monument") {
            bool guided = el.attribute("hasGuidedTour").toInt();
            QString focus = el.attribute("culturalFocus");
            bool unesco = el.attribute("isUnesco").toInt();
            QString state = el.attribute("conservationStatus");
            bool openTo = el.attribute("openToPublic").toInt();
            double discount = el.attribute("studentDiscount").toDouble();
            imported.push_back(std::make_shared<Monument>(
                name, city, desc, rating, open, cost,
                discount, guided, focus,
                unesco, state, openTo
                ));
        }
        else throw std::invalid_argument("Unknown type: " + type.toStdString());
    }

    DEBUG_LOG("XML IMPORTER: IMPORTATI OGGETTI #" << imported.size());
    return imported;
}
