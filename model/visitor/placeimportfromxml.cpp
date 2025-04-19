#include "placeimportfromxml.h"
#include "model/Cafe.h"
#include "model/Disco.h"
#include "model/Restaurant.h"
#include "model/LocalMarket.h"
#include "model/Mall.h"
#include "model/Museum.h"
#include "model/Monument.h"
#include "model/PanoramicPoints.h"

#include <QFile>
#include <QDomElement>
#include <QDomNodeList>
#include <QDebug>

weeklyOpenings PlaceImportFromXml::parseOpenings(const QDomElement& parent) const {
    weeklyOpenings openings;
    QDomElement openingsElem = parent.firstChildElement("openings");

    QDomNodeList days = openingsElem.elementsByTagName("day");
    for (int i = 0; i < days.count(); ++i) {
        QDomElement dayElem = days.at(i).toElement();
        QString dayStr = dayElem.attribute("name");
        Weekday day;

        if (dayStr == "Monday") day = Weekday::Monday;
        else if (dayStr == "Tuesday") day = Weekday::Tuesday;
        else if (dayStr == "Wednesday") day = Weekday::Wednesday;
        else if (dayStr == "Thursday") day = Weekday::Thursday;
        else if (dayStr == "Friday") day = Weekday::Friday;
        else if (dayStr == "Saturday") day = Weekday::Saturday;
        else if (dayStr == "Sunday") day = Weekday::Sunday;

        QDomElement slot = dayElem.firstChildElement("slot");
        QTime from = QTime::fromString(slot.attribute("from"), "hh:mm");
        QTime to = QTime::fromString(slot.attribute("to"), "hh:mm");

        openings.setOpening(day, from, to);
    }

    return openings;
}

std::vector<Place*> PlaceImportFromXml::importFromFile(const QString& filePath) const {
    std::vector<Place*> imported;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Errore apertura file:" << filePath;
        return imported;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qCritical() << "Errore parsing XML.";
        file.close();
        return imported;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList nodes = root.childNodes();

    for (int i = 0; i < nodes.count(); ++i) {
        QDomElement el = nodes.at(i).toElement();
        QString type = el.tagName();

        QString name = el.attribute("name");
        QString city = el.attribute("city");
        QString desc = el.attribute("description");
        float rating = el.attribute("rating").toFloat();
        double cost = el.attribute("cost").remove("€").toDouble();

        weeklyOpenings open = parseOpenings(el);

        if (type == "Cafe") {
            bool terrace = el.attribute("hasTerrace").toInt();
            QString drink = el.attribute("famousDrink");
            imported.push_back(new Cafe(name, city, desc, rating, open, cost,
                                        true, QTime(0,5), true, terrace, drink));
        }
        else if (type == "Disco") {
            QString genre = el.attribute("musicGenre");
            bool prive = el.attribute("hasPrive").toInt();
            QString dressCode = el.attribute("dressCode");
            imported.push_back(new Disco(name, city, desc, rating, open, cost,
                                         2.5, 18, "VIP", genre, prive, dressCode));
        }
        else if (type == "Restaurant") {
            QString cuisine = el.attribute("cuisineType");
            bool res = el.attribute("reservation").toInt();
            QString special = el.attribute("specialDish");
            imported.push_back(new Restaurant(name, city, desc, rating, open, cost,
                                              true, QTime(0, 10), true, cuisine, res, special));
        }
        else if (type == "LocalMarket") {
            bool artisans = el.attribute("artisans").toInt();
            bool seasonal = el.attribute("seasonal").toInt();
            QString period = el.attribute("period");
            imported.push_back(new LocalMarket(name, city, desc, rating, open, cost,
                                               true, true, 10, artisans, seasonal, period));
        }
        else if (type == "Mall") {
            int shopCount = el.attribute("shopCount").toInt();
            bool cinema = el.attribute("cinema").toInt();
            bool parking = el.attribute("freeParking").toInt();
            imported.push_back(new Mall(name, city, desc, rating, open, cost,
                                        true, true, 20, shopCount, cinema, parking));
        }
        else if (type == "PanoramicPoints") {
            double altitude = el.attribute("altitude").toDouble();
            bool binocular = el.attribute("hasBinocular").toInt();
            bool night = el.attribute("nightLighting").toInt();
            imported.push_back(new PanoramicPoints(name, city, desc, rating, open, cost,
                                                   1.0, 0, "nessuna", altitude, binocular, night));
        }
        else if (type == "Museum") {
            bool guide = el.attribute("hasAudioGuide").toInt();
            imported.push_back(new Museum(name, city, desc, rating, open, cost,
                                          1.0, true, "Cultura", "Sì", guide));
        }
        else if (type == "Monument") {
            bool unesco = el.attribute("isUnesco").toInt();
            QString state = el.attribute("conservationStatus");
            bool openTo = el.attribute("openToPublic").toInt();
            imported.push_back(new Monument(name, city, desc, rating, open, cost,
                                            1.0, true, "Cultura", "Sì", unesco, state, openTo));
        }
    }

    return imported;
}
