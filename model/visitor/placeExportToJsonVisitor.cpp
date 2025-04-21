#include "placeExportToJsonVisitor.h"
#include "placevisitorinterface.h"
#include <QDomDocument>
#include <QDomElement>
#include "../Cafe.h"
#include "../Disco.h"
#include "../Mall.h"
#include "../LocalMarket.h"
#include "../Restaurant.h"
#include "../PanoramicPoints.h"
#include "../Museum.h"
#include "../Monument.h"

QJsonObject PlaceExportToJsonVisitor::getResult() const{return result;}

QJsonArray PlaceExportToJsonVisitor::exportWeeklyOpenings(const weeklyOpenings& w) const{
    QJsonArray openingsArray;
    const auto& schedule= w.getSchedule();

    for(auto it=schedule.cbegin(); it!=schedule.cend(); ++it){
        const openingFrames& f=it.value();

        QJsonObject dayObj;
        dayObj["day"]=weeklyOpenings::weekdayToString(it.key());
        dayObj["from"]=f.getStartAsString();
        dayObj["to"]=f.getEndAsString();

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

void PlaceExportToJsonVisitor::visit(const Cafe& cafe){
    QJsonObject obj=basePlaceToJson(cafe, "Cafe");

    obj["hasTerrace"]=cafe.hasTerrace();
    obj["famousDrink"]=cafe.getSpecialDrink();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const Restaurant& restaurant){
    QJsonObject obj=basePlaceToJson(restaurant, "Restaurant");

    obj["cuisineType"]=restaurant.getCuisineType();
    obj["reservation"]=restaurant.hasReservation();
    obj["specialDish"]=restaurant.getSpecialDish();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const Disco& disco){
    QJsonObject obj=basePlaceToJson(disco, "Disco");

    obj["musicGenre"]=disco.getMusicGenre();
    obj["hasPrive"]=disco.hasPriveAccess();
    obj["dressCode"]=disco.getDressCode();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const LocalMarket& localMarket){
    QJsonObject obj=basePlaceToJson(localMarket, "LocalMarket");

    obj["artisans"]= localMarket.hasArtisans();
    obj["seasonal"]= localMarket.isSeasonal();
    obj["period"]= localMarket.getPeriod();


    result=obj;
}

void PlaceExportToJsonVisitor::visit(const PanoramicPoints& panoramicPoints){
    QJsonObject obj=basePlaceToJson(panoramicPoints, "PanoramicPoints");

    obj["altitude"]= panoramicPoints.getAltitude();
    obj["hasBinocular"]= panoramicPoints.hasBinoculars();
    obj["nightLighting"]= panoramicPoints.isNightLit();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const Mall& mall){
    QJsonObject obj=basePlaceToJson(mall, "Mall");

    obj["shopCount"]= mall.getShopCount();
    obj["cinema"]= mall.hasCinema();
    obj["freeParking"]= mall.hasFreeParking();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const  &){
    QJsonObject obj=basePlaceToJson(museum, "Museum");

    obj["hasAudioGuide"]=museum.hasAudioGuideAvailable();

    result=obj;
}

void PlaceExportToJsonVisitor::visit(const Monument& monument){
    QJsonObject obj=basePlaceToJson(monument, "Monument");

    obj["isUnesco"]= monument.isUnesco();
    obj["conservationStatus"]= monument.getConservationStatus();
    obj["openToPublic"]= monument.isOpenToPublic();

    result=obj;
}
