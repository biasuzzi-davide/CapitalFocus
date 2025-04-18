#include "placeexporttoxmlvisitor.h"
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


PlaceExportToXmlVisitor::PlaceExportToXmlVisitor(QDomDocument& document): doc(document) {}

QDomElement PlaceExportToXmlVisitor::getResult() const {return result;}

QString PlaceExportToXmlVisitor::weekdayToString(Weekday day) const {
    switch (day) {
    case Weekday::Monday:    return "Monday";
    case Weekday::Tuesday:   return "Tuesday";
    case Weekday::Wednesday: return "Wednesday";
    case Weekday::Thursday:  return "Thursday";
    case Weekday::Friday:    return "Friday";
    case Weekday::Saturday:  return "Saturday";
    case Weekday::Sunday:    return "Sunday";
    }

    return "ERROREEE"; // fallback
}

QDomElement PlaceExportToXmlVisitor::exportWeeklyOpenings(const weeklyOpenings& w) const {
    QDomElement openingsElem = doc.createElement("openings");
    const auto& openingsMap = w.getSchedule();

    for (auto it = openingsMap.constBegin(); it != openingsMap.constEnd(); ++it) {
        Weekday day = it.key();
        const openingFrames& f = it.value();

        QDomElement dayElem = doc.createElement("day");
        dayElem.setAttribute("name", weekdayToString(day));

        QDomElement slot = doc.createElement("slot");
        slot.setAttribute("from", f.getStartAsString());
        slot.setAttribute("to", f.getEndAsString());
        dayElem.appendChild(slot);

        openingsElem.appendChild(dayElem);
    }

    return openingsElem;
}

QDomElement PlaceExportToXmlVisitor::basePlaceToXml(const Place& place, const QString& type) const {
    QDomElement e = doc.createElement(type);

    e.setAttribute("name", place.getName());
    e.setAttribute("city", place.getCity());
    e.setAttribute("description", place.getDescription());
    e.setAttribute("rating", place.getRating());
    e.setAttribute("cost", place.getCost());
    e.appendChild(exportWeeklyOpenings(place.getOpen()));

    return e;
}


void PlaceExportToXmlVisitor::visit(const Cafe& cafe) {
    QDomElement e = basePlaceToXml(cafe,"Cafe");

    e.setAttribute("hasTerrace", cafe.hasTerrace());
    e.setAttribute("famousDrink", cafe.getSpecialDrink());
    result = e;
}
void PlaceExportToXmlVisitor::visit(const Disco& disco) {
    QDomElement e = basePlaceToXml(disco, "Disco");

    e.setAttribute("musicGenre", disco.getMusicGenre());
    e.setAttribute("hasPrive", disco.hasPriveAccess());
    e.setAttribute("dressCode", disco.getDressCode());
    result = e;
}
void PlaceExportToXmlVisitor::visit(const LocalMarket& localMarket) {
    QDomElement e = basePlaceToXml(localMarket, "LocalMarket");

    e.setAttribute("artisans", localMarket.hasArtisans());
    e.setAttribute("seasonal", localMarket.isSeasonal());
    e.setAttribute("period", localMarket.getPeriod());

    result = e;
}
void PlaceExportToXmlVisitor::visit(const Mall& mall) {
    QDomElement e = basePlaceToXml(mall, "Mall");

    e.setAttribute("shopCount", mall.getShopCount());
    e.setAttribute("cinema", mall.hasCinema());
    e.setAttribute("freeParking", mall.hasFreeParking());

    result = e;
}
void PlaceExportToXmlVisitor::visit(const Restaurant& restaurant) {
    QDomElement e = basePlaceToXml(restaurant, "Restaurant");

    e.setAttribute("cuisineType", restaurant.getCuisineType());
    e.setAttribute("reservation", restaurant.hasReservation());
    e.setAttribute("specialDish", restaurant.getSpecialDish());

    result = e;
}
void PlaceExportToXmlVisitor::visit(const PanoramicPoints& point) {
    QDomElement e = basePlaceToXml(point, "PanoramicPoints");

    e.setAttribute("altitude", point.getAltitude());
    e.setAttribute("hasBinocular", point.hasBinoculars());
    e.setAttribute("nightLighting", point.isNightLit());

    result = e;
}
void PlaceExportToXmlVisitor::visit(const Museum& museum) {
    QDomElement e = basePlaceToXml(museum, "Museum");

    e.setAttribute("hasAudioGuide", museum.hasAudioGuideAvailable());

    result = e;
}
void PlaceExportToXmlVisitor::visit(const Monument& monument) {
    QDomElement e = basePlaceToXml(monument, "Monument");

    e.setAttribute("isUnesco", monument.isUnesco());
    e.setAttribute("conservationStatus", monument.getConservationStatus());
    e.setAttribute("openToPublic", monument.isOpenToPublic());

    result = e;
}
