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

#include <QFile>
#include <QDomElement>
#include <QDomNodeList>
#include <QDebug>

weeklyOpenings PlaceImportFromXml::parseOpenings(const QDomElement& parent) const {
    weeklyOpenings week;

    QDomElement openingsElem = parent.firstChildElement("openings");

    QDomNodeList days = openingsElem.elementsByTagName("day");
    for (int i = 0; i < days.count(); ++i) {
        QDomElement d   = days.at(i).toElement();
        Weekday day     = weeklyOpenings::weekdayFromString(d.attribute("name"));

        //Se "closed" imposta il weekday a chiuso
        if (d.hasAttribute("closed") && d.attribute("closed").toInt()) {
            week.setClosed(day);
            continue;
        }

        //Altrimenti estrai gli orari
        QDomElement slot = d.firstChildElement("slot");
        QTime from = QTime::fromString(slot.attribute("from"), "HH:mm");
        QTime to   = QTime::fromString(slot.attribute("to"),   "HH:mm");

        //Check sugli orari
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
        double cost = el.attribute("cost").toDouble();

        if (type.isEmpty())
            throw std::invalid_argument("XML element without type");
        if (name.isEmpty())
            throw std::invalid_argument("XML element without name");
        if (city.isEmpty())
            throw std::invalid_argument("XML element without city");
        if (rating < 0.0 || rating > 5.0)
            throw std::invalid_argument("Rating out of range [0‑5]");

        weeklyOpenings open = parseOpenings(el);

        if (type == "Cafe") {
            bool terrace = el.attribute("hasTerrace").toInt();
            QString drink = el.attribute("famousDrink");
            imported.push_back(std::make_shared<Cafe>(name, city, desc, rating, open, cost,
                                        true, QTime(0,5), true, terrace, drink));
        }
        else if (type == "Disco") {
            QString genre = el.attribute("musicGenre");
            bool prive = el.attribute("hasPrive").toInt();
            QString dressCode = el.attribute("dressCode");
            imported.push_back(std::make_shared<Disco>(name, city, desc, rating, open, cost,
                                         2.5, 18, "VIP", genre, prive, dressCode));
        }
        else if (type == "Restaurant") {
            QString cuisine = el.attribute("cuisineType");
            bool res = el.attribute("reservation").toInt();
            QString special = el.attribute("specialDish");
            imported.push_back(std::make_shared<Restaurant>(name, city, desc, rating, open, cost,
                                              true, QTime(0, 10), true, cuisine, res, special));
        }
        else if (type == "LocalMarket") {
            bool artisans = el.attribute("artisans").toInt();
            bool seasonal = el.attribute("seasonal").toInt();
            QString period = el.attribute("period");
            imported.push_back(std::make_shared<LocalMarket>(name, city, desc, rating, open, cost,
                                               true, true, 10, artisans, seasonal, period));
        }
        else if (type == "Mall") {
            int shopCount = el.attribute("shopCount").toInt();
            bool cinema = el.attribute("cinema").toInt();
            bool parking = el.attribute("freeParking").toInt();
            imported.push_back(std::make_shared<Mall>(name, city, desc, rating, open, cost,
                                        true, true, 20, shopCount, cinema, parking));
        }
        else if (type == "PanoramicPoints") {
            double altitude = el.attribute("altitude").toDouble();
            bool binocular = el.attribute("hasBinocular").toInt();
            bool night = el.attribute("nightLighting").toInt();
            imported.push_back(std::make_shared<PanoramicPoints>(name, city, desc, rating, open, cost,
                                                   1.0, 0, "nessuna", altitude, binocular, night));
        }
        else if (type == "Museum") {
            bool guide = el.attribute("hasAudioGuide").toInt();
            imported.push_back(std::make_shared<Museum>(name, city, desc, rating, open, cost,
                                          1.0, true, "Cultura", "Sì", guide));
        }
        else if (type == "Monument") {
            bool unesco = el.attribute("isUnesco").toInt();
            QString state = el.attribute("conservationStatus");
            bool openTo = el.attribute("openToPublic").toInt();
            imported.push_back(std::make_shared<Monument>(name, city, desc, rating, open, cost,
                                            1.0, true, "Cultura", "Sì", unesco, state, openTo));
        }
        else throw std::invalid_argument("Unknown type: " + type.toStdString());

    }
    qDebug() << "Totale oggetti importati:" << imported.size();
    return imported;
}
