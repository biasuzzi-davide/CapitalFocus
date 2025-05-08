#include "placeexporttoxmlvisitor.h"
#include <stdexcept>
#include "../weeklyOpenings.h"
#include "../Place.h"
#include "../Food.h"
#include "../Shopping.h"
#include "../Entertainment.h"
#include "../Cafe.h"
#include "../Restaurant.h"
#include "../Disco.h"
#include "../PanoramicPoints.h"
#include "../LocalMarket.h"
#include "../Mall.h"
#include "../Museum.h"
#include "../Monument.h"

PlaceExportToXmlVisitor::PlaceExportToXmlVisitor(QDomDocument& document)
    : doc(document) {}

QDomElement PlaceExportToXmlVisitor::getResult() const {
    return result;
}

QDomElement PlaceExportToXmlVisitor::exportWeeklyOpenings(const weeklyOpenings& w) const {
    QDomElement openingsElem = doc.createElement("openings");
    const auto& schedule = w.getSchedule();
    for (auto it = schedule.constBegin(); it != schedule.constEnd(); ++it) {
        Weekday day = it.key();
        const openingFrames& f = it.value();
        QDomElement dayElem = doc.createElement("day");
        dayElem.setAttribute("name", weeklyOpenings::weekdayToString(day));
        if (f.closed) {
            dayElem.setAttribute("closed", "1");
        } else {
            QDomElement slot = doc.createElement("slot");
            slot.setAttribute("from", f.opening.toString("HH:mm"));
            slot.setAttribute("to", f.closing.toString("HH:mm"));
            dayElem.appendChild(slot);
        }
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

QDomElement PlaceExportToXmlVisitor::exportFoodData(const Food& f) const {
    QDomElement e = doc.createElement("foodData");
    e.setAttribute("hasTakeAway", f.hasTakeAway());
    e.setAttribute("avgWaitingTime", f.getAvgWaitingTime().toString("HH:mm"));
    e.setAttribute("hasVeganMenu", f.hasVeganMenu());
    return e;
}

QDomElement PlaceExportToXmlVisitor::exportShoppingData(const Shopping& s) const {
    QDomElement e = doc.createElement("shoppingData");
    e.setAttribute("isOutdoor", s.isOutdoor());
    e.setAttribute("foodAreaPresent", s.foodAreaPresent());
    e.setAttribute("standNumber", s.getStandNumber());
    return e;
}

QDomElement PlaceExportToXmlVisitor::exportEntertainmentData(const Entertainment& ent) const {
    QDomElement e = doc.createElement("entertainmentData");
    e.setAttribute("avgStayDuration", ent.getAvgStayDuration());
    e.setAttribute("minimumAge", ent.getMinAge());
    e.setAttribute("restrictedEntry", ent.getRestrictedEntry());
    return e;
}

void PlaceExportToXmlVisitor::visit(const Place&) {
    throw std::runtime_error("Unsupported: cannot export abstract Place to XML");
}

void PlaceExportToXmlVisitor::visit(const Cafe& cafe) {
    QDomElement e = basePlaceToXml(cafe, "Cafe");
    e.setAttribute("hasTerrace", cafe.hasTerrace());
    e.setAttribute("famousDrink", cafe.getSpecialDrink());
    e.appendChild(exportFoodData(cafe));
    result = e;
}

void PlaceExportToXmlVisitor::visit(const Restaurant& restaurant) {
    QDomElement e = basePlaceToXml(restaurant, "Restaurant");
    e.setAttribute("cuisineType", restaurant.getCuisineType());
    e.setAttribute("reservation", restaurant.hasReservation());
    e.setAttribute("specialDish", restaurant.getSpecialDish());
    e.appendChild(exportFoodData(restaurant));
    result = e;
}

void PlaceExportToXmlVisitor::visit(const Disco& disco) {
    QDomElement e = basePlaceToXml(disco, "Disco");
    e.setAttribute("musicGenre", disco.getMusicGenre());
    e.setAttribute("hasPrive", disco.hasPriveAccess());
    e.setAttribute("dressCode", disco.getDressCode());
    e.appendChild(exportEntertainmentData(disco));
    result = e;
}

void PlaceExportToXmlVisitor::visit(const PanoramicPoints& point) {
    QDomElement e = basePlaceToXml(point, "PanoramicPoints");
    e.setAttribute("altitude", point.getAltitude());
    e.setAttribute("hasBinocular", point.hasBinoculars());
    e.setAttribute("nightLighting", point.isNightLit());
    e.appendChild(exportEntertainmentData(point));
    result = e;
}

void PlaceExportToXmlVisitor::visit(const LocalMarket& localMarket) {
    QDomElement e = basePlaceToXml(localMarket, "LocalMarket");
    e.setAttribute("artisans", localMarket.hasArtisans());
    e.setAttribute("seasonal", localMarket.isSeasonal());
    e.setAttribute("period", localMarket.getPeriod());
    e.appendChild(exportShoppingData(localMarket));
    result = e;
}

void PlaceExportToXmlVisitor::visit(const Mall& mall) {
    QDomElement e = basePlaceToXml(mall, "Mall");
    e.setAttribute("shopCount", mall.getShopCount());
    e.setAttribute("cinema", mall.hasCinema());
    e.setAttribute("freeParking", mall.hasFreeParking());
    e.appendChild(exportShoppingData(mall));
    result = e;
}

void PlaceExportToXmlVisitor::visit(const Museum& museum) {
    QDomElement e = basePlaceToXml(museum, "Museum");
    e.setAttribute("studentDiscount", museum.getStudentDiscount());
    e.setAttribute("guidedTour", museum.hasGuidedTour());
    e.setAttribute("culturalFocus", museum.getCulturalFocus());
    e.setAttribute("hasAudioGuide", museum.hasAudioGuideAvailable());
    result = e;
}

void PlaceExportToXmlVisitor::visit(const Monument& monument) {
    QDomElement e = basePlaceToXml(monument, "Monument");
    e.setAttribute("studentDiscount", monument.getStudentDiscount());
    e.setAttribute("guidedTour", monument.hasGuidedTour());
    e.setAttribute("culturalFocus", monument.getCulturalFocus());
    e.setAttribute("isUnesco", monument.isUnesco());
    e.setAttribute("conservationStatus", monument.getConservationStatus());
    e.setAttribute("openToPublic", monument.isOpenToPublic());
    result = e;
}
