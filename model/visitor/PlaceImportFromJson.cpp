#include "PlaceImportFromJson.h"
#include "model/Cafe.h"
#include "model/Disco.h"
#include "model/Restaurant.h"
#include "model/LocalMarket.h"
#include "model/Mall.h"
#include "model/Museum.h"
#include "model/Monument.h"
#include "model/PanoramicPoints.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>


weeklyOpenings PlaceImportFromJson::parseOpenings(const QJsonArray& array) const{
    weeklyOpenings w;

    for(const QJsonValue& val : array){
        QJsonObject obj=val.toObject();

        QString dayStr=obj["day"].toString();
        QString fromStr=obj["from"].toString();
        QString toStr=obj["to"].toString();

        Weekday day=weeklyOpenings::weekdayFromString(dayStr);
        QTime from=QTime::fromString(fromStr, "hh:mm");
        QTime to=QTime::fromString(toStr, "hh:mm");

        w.setOpening(day,from,to);
    }
    return w;
}

std::vector<Place*> PlaceImportFromJson::importFromJson(const QString& filePath) const{
    std::vector<Place*> imported;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Errore apertura file JSON";
        return {};
    }

    QJsonDocument doc= QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) {
        qCritical() << "Il file JSON non è un array valido.";
        return {};
    }

    QJsonArray placeArray = doc.array();

    for(const QJsonValue& val: placeArray){
        QJsonObject obj = val.toObject();

        QString type=obj["type"].toString();
        QString name=obj["name"].toString();
        QString city=obj["city"].toString();
        QString description=obj["description"].toString();
        float rating=obj["rating"].toDouble();
        double cost=obj["cost"].toDouble();
        QJsonArray openingsArray=obj["openings"].toArray();
        weeklyOpenings openings=parseOpenings(openingsArray);

        if (type == "Cafe") {
            bool terrace = obj["hasTerrace"].toBool();
            QString drink = obj["famousDrink"].toString();
            imported.push_back(new Cafe(name, city, description, rating, openings, cost,
                                        true, QTime(0,5), true, terrace, drink));
        }
        else if (type == "Disco") {
            QString genre = obj["musicGenre"].toString();
            bool prive = obj["hasPrive"].toBool();
            QString dressCode = obj["dressCode"].toString();
            imported.push_back(new Disco(name, city, description, rating, openings, cost,
                                         2.5, 18, "VIP", genre, prive, dressCode));
        }
        else if (type == "Restaurant") {
            QString cuisine = obj["cuisineType"].toString();
            bool res = obj["reservation"].toBool();
            QString special = obj["specialDish"].toString();
            imported.push_back(new Restaurant(name, city, description, rating, openings, cost,
                                              true, QTime(0, 10), true, cuisine, res, special));
        }
        else if (type == "LocalMarket") {
            bool artisans = obj["artisans"].toBool();
            bool seasonal = obj["seasonal"].toBool();
            QString period = obj["period"].toString();
            imported.push_back(new LocalMarket(name, city, description, rating, openings, cost,
                                               true, true, 10, artisans, seasonal, period));
        }
        else if (type == "Mall") {
            int shopCount = obj["shopCount"].toInt();
            bool cinema = obj["cinema"].toBool();
            bool parking = obj["freeParking"].toBool();
            imported.push_back(new Mall(name, city, description, rating, openings, cost,
                                        true, true, 20, shopCount, cinema, parking));
        }
        else if (type == "PanoramicPoints") {
            double altitude = obj["altitude"].toDouble();
            bool binocular = obj["hasBinocular"].toBool();
            bool night = obj["nightLighting"].toBool();
            imported.push_back(new PanoramicPoints(name, city, description, rating, openings, cost,
                                                   1.0, 0, "nessuna", altitude, binocular, night));
        }
        else if (type == "Museum") {
            bool guide = obj["hasAudioGuide"].toBool();
            imported.push_back(new Museum(name, city, description, rating, openings, cost,
                                          1.0, true, "Cultura", "Sì", guide));
        }
        else if (type == "Monument") {
            bool unesco = obj["isUnesco"].toBool();
            QString state = obj["conservationStatus"].toString();
            bool openTo = obj["openToPublic"].toBool();
            imported.push_back(new Monument(name, city, description, rating, openings, cost,
                                            1.0, true, "Cultura", "Sì", unesco, state, openTo));
        }
    }

    return imported;
}

