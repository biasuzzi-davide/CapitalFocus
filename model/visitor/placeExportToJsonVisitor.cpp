#include "placeExportToJsonVisitor.h"
#include <QDomDocument>
#include <QDomElement>
#include <stdexcept>
#include "../Cafe.h"
#include "../Disco.h"
#include "../Mall.h"
#include "../LocalMarket.h"
#include "../Restaurant.h"
#include "../PanoramicPoints.h"
#include "../Museum.h"
#include "../Monument.h"

QJsonObject PlaceExportToJsonVisitor::getResult() const{return result;}

QJsonArray PlaceExportToJsonVisitor::exportWeeklyOpenings(const weeklyOpenings& w) const {
    QJsonArray openingsArray;
    const auto& schedule = w.getSchedule();

    for (auto it = schedule.cbegin(); it != schedule.cend(); ++it) {
        Weekday day = it.key();
        const openingFrames& f = it.value();

        QJsonObject dayObj;
        dayObj["day"] = weeklyOpenings::weekdayToString(day);

        if (f.closed) {
            dayObj["closed"] = true;
        }
        else if (f.alwaysOpen) {
            dayObj["alwaysOpen"] = true;
        }
        else {
            dayObj["from"] = f.opening.toString("HH:mm");
            dayObj["to"]   = f.closing.toString("HH:mm");
        }

        openingsArray.append(dayObj);
    }

    return openingsArray;
}


QJsonObject PlaceExportToJsonVisitor::basePlaceToJson(const Place& place,const QString& type) const{
    QJsonObject obj;

    obj["type"]=type;
    obj["name"]=place.getName();
    obj["city"]=place.getCity();
    obj["description"]=place.getDescription();
    obj["rating"]=place.getRating();
    obj["cost"]=place.getCost();
    obj["openings"]=exportWeeklyOpenings(place.getOpen());

    return obj;
}

void PlaceExportToJsonVisitor::visit(const Place&) {
    throw std::runtime_error("Unsupported: cannot export abstract Place to JSON");
}

void PlaceExportToJsonVisitor::visit(const Cafe& cafe){
    QJsonObject obj=basePlaceToJson(cafe, "Cafe");

    obj["takeAway"]        = cafe.hasTakeAway();
    obj["avgWaitingTime"]  = cafe.getAvgWaitingTime().toString("HH:mm");
    obj["veganMenu"]       = cafe.hasVeganMenu();

    obj["hasTerrace"]=cafe.hasTerrace();
    obj["famousDrink"]=cafe.getSpecialDrink();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const Restaurant& restaurant){
    QJsonObject obj=basePlaceToJson(restaurant, "Restaurant");

    obj["takeAway"]        = restaurant.hasTakeAway();
    obj["avgWaitingTime"]  = restaurant.getAvgWaitingTime().toString("HH:mm");
    obj["veganMenu"]       = restaurant.hasVeganMenu();

    obj["cuisineType"]=restaurant.getCuisineType();
    obj["reservation"]=restaurant.hasReservation();
    obj["specialDish"]=restaurant.getSpecialDish();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const Disco& disco){
    QJsonObject obj=basePlaceToJson(disco, "Disco");

    obj["avgStayDuration"]=disco.getAvgStayDuration().toString("HH:mm");
    obj["minimumAge"]=QString::number(disco.getMinAge());
    obj["restrictedEntry"]=disco.getRestrictedEntry();

    obj["musicGenre"]=disco.getMusicGenre();
    obj["hasPrive"]=disco.hasPriveAccess();
    obj["dressCode"]=disco.getDressCode();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const LocalMarket& localMarket){
    QJsonObject obj=basePlaceToJson(localMarket, "LocalMarket");

    obj["outdoor"] = localMarket.isOutdoor();
    obj["foodArea"] = localMarket.foodAreaPresent();
    obj["standNumber"] = localMarket.getStandNumber();

    obj["artisans"]= localMarket.hasArtisans();
    obj["seasonal"]= localMarket.isSeasonal();
    obj["period"]= localMarket.getPeriod();


    result=obj;
}

void PlaceExportToJsonVisitor::visit(const PanoramicPoints& panoramicPoints){
    QJsonObject obj=basePlaceToJson(panoramicPoints, "PanoramicPoints");

    obj["avgStayDuration"]=panoramicPoints.getAvgStayDuration().toString("HH:mm");
    obj["minimumAge"]=QString::number(panoramicPoints.getMinAge());
    obj["restrictedEntry"]=panoramicPoints.getRestrictedEntry();

    obj["altitude"]= panoramicPoints.getAltitude();
    obj["hasBinocular"]= panoramicPoints.hasBinoculars();
    obj["nightLighting"]= panoramicPoints.isNightLit();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const Mall& mall){
    QJsonObject obj=basePlaceToJson(mall, "Mall");

    obj["outdoor"] = mall.isOutdoor();
    obj["foodArea"] = mall.foodAreaPresent();
    obj["standNumber"] = mall.getStandNumber();

    obj["shopCount"]= mall.getShopCount();
    obj["cinema"]= mall.hasCinema();
    obj["freeParking"]= mall.hasFreeParking();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const Museum& museum){
    QJsonObject obj=basePlaceToJson(museum, "Museum");

    obj["studentDiscount"] = museum.getStudentDiscount();
    obj["guidedTour"]      = museum.hasGuidedTour();
    obj["culturalFocus"]   = museum.getCulturalFocus();

    obj["hasAudioGuide"]=museum.hasAudioGuideAvailable();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const Monument& monument){
    QJsonObject obj=basePlaceToJson(monument, "Monument");

    obj["studentDiscount"] = monument.getStudentDiscount();
    obj["guidedTour"]      = monument.hasGuidedTour();
    obj["culturalFocus"]   = monument.getCulturalFocus();

    obj["isUnesco"]= monument.isUnesco();
    obj["conservationStatus"]= monument.getConservationStatus();
    obj["openToPublic"]= monument.isOpenToPublic();

    result=obj;
}
