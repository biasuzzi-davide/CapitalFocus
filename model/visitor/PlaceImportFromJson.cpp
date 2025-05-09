#include "PlaceImportFromJson.h"
#include "model/Cafe.h"
#include "model/Disco.h"
#include "model/Restaurant.h"
#include "model/LocalMarket.h"
#include "model/Mall.h"
#include "model/Museum.h"
#include "model/Monument.h"
#include "model/PanoramicPoints.h"
#include "model/import_errors.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>


weeklyOpenings PlaceImportFromJson::parseOpenings(const QJsonArray& array) const{
    weeklyOpenings week;

    for (const QJsonValue& v : array) {
        QJsonObject o = v.toObject();
        Weekday day   = weeklyOpenings::weekdayFromString(o["day"].toString());

        // Se "closed" imposta il weekday a chiuso
        if (o.contains("closed") && o["closed"].toBool()) {
            week.setClosed(day);
            continue;
        }

        if (o.contains("alwaysOpen") && o["alwaysOpen"].toBool()) {
            week.setAlwaysOpen(day);
            continue;
        }

        //Altrimenti estrai gli orari
        QString fromStr = o["from"].toString();
        QString toStr   = o["to"].toString();
        QTime from = QTime::fromString(fromStr,"HH:mm");
        QTime to   = QTime::fromString(toStr,"HH:mm");

        //Check sugli orari
        if (!from.isValid() || !to.isValid() || from >= to)
            throw std::invalid_argument("Invalid time frame");

        week.setOpening(day, from, to);
    }
    return week;
}

std::vector<std::shared_ptr<Place>> PlaceImportFromJson::importFromJson(const QString& filePath) const{
    std::vector<std::shared_ptr<Place>> imported;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw FileOpenError(filePath);

    QJsonParseError jErr;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &jErr);
    file.close();

    if (jErr.error != QJsonParseError::NoError)
        throw JsonParseError(jErr.errorString());

    if (!doc.isArray())
        throw JsonParseError("Root must be a JSON array");

    QJsonArray placeArray = doc.array();

    for(const QJsonValue& val: placeArray){
        QJsonObject obj = val.toObject();

        QString type=obj["type"].toString();
        QString name=obj["name"].toString();
        QString city=obj["city"].toString();
        QString description=obj["description"].toString();
        double rating=obj["rating"].toDouble();
        double cost=obj["cost"].toDouble();
        QJsonArray openingsArray=obj["openings"].toArray();
        weeklyOpenings openings=parseOpenings(openingsArray);

        if (type.isEmpty())
            throw std::invalid_argument("JSON element without type");
        if (name.isEmpty())
            throw std::invalid_argument("JSON element without name");
        if (city.isEmpty())
            throw std::invalid_argument("JSON element without city");
        if (rating < 0.0 || rating > 5.0)
            throw std::invalid_argument("rating out of range [0‑5]");

        if (type == "Cafe") {
            bool takeAway = obj["takeAway"].toBool();
            QTime avgWait = QTime::fromString(obj["avgWaitingTime"].toString(), "HH:mm");
            bool veganMenu = obj["veganMenu"].toBool();

            bool terrace = obj["hasTerrace"].toBool();
            QString drink = obj["famousDrink"].toString();
            imported.push_back(std::make_shared<Cafe>(name, city, description, rating, openings, cost,
                                        takeAway, avgWait, veganMenu, terrace, drink));
        }
        else if (type == "Disco") {
            QTime avgStay = QTime::fromString(obj["avgStayDuration"].toString(), "HH:mm");
            int minAge = obj["minimumAge"].toInt();
            QString restricted = obj["restrictedEntry"].toString();

            QString genre = obj["musicGenre"].toString();
            bool prive = obj["hasPrive"].toBool();
            QString dressCode = obj["dressCode"].toString();
            imported.push_back(std::make_shared<Disco>(name, city, description, rating, openings, cost,
                                         avgStay, minAge, restricted, genre, prive, dressCode));
        }
        else if (type == "Restaurant") {
            bool takeAway = obj["takeAway"].toBool();
            QTime avgWait = QTime::fromString(obj["avgWaitingTime"].toString(), "HH:mm");
            bool veganMenu = obj["veganMenu"].toBool();

            QString cuisine = obj["cuisineType"].toString();
            bool res = obj["reservation"].toBool();
            QString special = obj["specialDish"].toString();
            imported.push_back(std::make_shared<Restaurant>(name, city, description, rating, openings, cost,
                                              takeAway, avgWait, veganMenu, cuisine, res, special));
        }
        else if (type == "LocalMarket") {
            bool outdoor = obj["isOutdoor"].toBool();
            bool foodArea = obj["foodAreaPresent"].toBool();
            int stands = obj["standNumber"].toInt();

            bool artisans = obj["artisans"].toBool();
            bool seasonal = obj["seasonal"].toBool();
            QString period = obj["period"].toString();
            imported.push_back(std::make_shared<LocalMarket>(name, city, description, rating, openings, cost,
                                               outdoor, foodArea, stands, artisans, seasonal, period));
        }
        else if (type == "Mall") {
            bool outdoor = obj["isOutdoor"].toBool();
            bool foodArea = obj["foodAreaPresent"].toBool();
            int stands = obj["standNumber"].toInt();

            int shopCount = obj["shopCount"].toInt();
            bool cinema = obj["cinema"].toBool();
            bool parking = obj["freeParking"].toBool();
            imported.push_back(std::make_shared<Mall>(name, city, description, rating, openings, cost,
                                        outdoor, foodArea, stands, shopCount, cinema, parking));
        }
        else if (type == "PanoramicPoints") {
            QTime avgStay = QTime::fromString(obj["avgStayDuration"].toString(), "HH:mm");
            int minAge = obj["minimumAge"].toInt();
            QString restricted = obj["restrictedEntry"].toString();

            double altitude = obj["altitude"].toDouble();
            bool binocular = obj["hasBinocular"].toBool();
            bool night = obj["nightLighting"].toBool();
            imported.push_back(std::make_shared<PanoramicPoints>(name, city, description, rating, openings, cost,
                                                   avgStay, minAge, restricted, altitude, binocular, night));
        }
        else if (type == "Museum") {
            double studentDiscount = obj["studentDiscount"].toDouble();
            bool guidedTour = obj["guidedTour"].toBool();
            QString focus = obj["culturalFocus"].toString();

            bool guide = obj["hasAudioGuide"].toBool();
            imported.push_back(std::make_shared<Museum>(name, city, description, rating, openings, cost,
                                          studentDiscount, guidedTour, focus, guide));
        }
        else if (type == "Monument") {
            double studentDiscount = obj["studentDiscount"].toDouble();
            bool guidedTour = obj["guidedTour"].toBool();
            QString focus = obj["culturalFocus"].toString();

            bool unesco = obj["isUnesco"].toBool();
            QString state = obj["conservationStatus"].toString();
            bool openTo = obj["openToPublic"].toBool();
            imported.push_back(std::make_shared<Monument>(name, city, description, rating, openings, cost,
                                            studentDiscount, guidedTour, focus, unesco, state, openTo));
        }
        else throw std::invalid_argument("Unknown type: " + type.toStdString());
    }

    return imported;
}

