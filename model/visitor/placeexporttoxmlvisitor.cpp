#include "placeexporttoxmlvisitor.h"
#include <stdexcept>

// Costruttore
PlaceExportToXmlVisitor::PlaceExportToXmlVisitor(QDomDocument& document)
    : doc(document) {}

// Ritorna l'elemento XML creato
QDomElement PlaceExportToXmlVisitor::getResult() const {
    return result;
}

// Crea elemento XML per gli orari
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
        }
        else if (f.alwaysOpen) {
            dayElem.setAttribute("alwaysOpen", "1");
        }
        else {
            QDomElement slot = doc.createElement("slot");
            slot.setAttribute("from", f.opening.toString("HH:mm"));
            slot.setAttribute("to", f.closing.toString("HH:mm"));
            dayElem.appendChild(slot);
        }
        openingsElem.appendChild(dayElem);
    }
    return openingsElem;
}

// Crea elemento XML per i dati base di Place
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

// Crea elemento XML per i dati specifici di Food
QDomElement PlaceExportToXmlVisitor::exportFoodData(const Food& f) const {
    QDomElement e = doc.createElement("foodData");
    e.setAttribute("hasTakeAway", f.hasTakeAway());
    e.setAttribute("avgWaitingTime", f.getAvgWaitingTime().toString("HH:mm"));
    e.setAttribute("hasVeganMenu", f.hasVeganMenu());
    return e;
}

// Crea elemento XML per i dati specifici di Shopping
QDomElement PlaceExportToXmlVisitor::exportShoppingData(const Shopping& s) const {
    QDomElement e = doc.createElement("shoppingData");
    e.setAttribute("isOutdoor", s.isOutdoor());
    e.setAttribute("foodAreaPresent", s.foodAreaPresent());
    e.setAttribute("standNumber", s.getStandNumber());
    return e;
}

// Crea elemento XML per i dati specifici di Entertainment
QDomElement PlaceExportToXmlVisitor::exportEntertainmentData(const Entertainment& ent) const {
    QDomElement e = doc.createElement("entertainmentData");
    e.setAttribute("avgStayDuration", ent.getAvgStayDuration().toString("HH:mm"));
    e.setAttribute("minimumAge", ent.getMinAge());
    e.setAttribute("restrictedEntry", ent.getRestrictedEntry());
    return e;
}

// Crea elemento XML per i dati specifici di Culture
QDomElement PlaceExportToXmlVisitor::exportCultureData(const Culture& c) const {
    QDomElement e = doc.createElement("cultureData");
    e.setAttribute("studentDiscount", c.getStudentDiscount());
    e.setAttribute("guidedTour",      c.hasGuidedTour());
    e.setAttribute("culturalFocus",   c.getCulturalFocus());
    return e;
}

// Implementazione visit per Place
void PlaceExportToXmlVisitor::visit(const Place&) {
    throw std::runtime_error("Unsupported: cannot export abstract Place to XML");
}

// Implementazioni dei metodi visit per le classi concrete
void PlaceExportToXmlVisitor::visit(const Cafe& cafe) {
    QDomElement e = basePlaceToXml(cafe, "Cafe");
    e.appendChild(exportFoodData(cafe));
    e.setAttribute("hasTerrace", cafe.hasTerrace());
    e.setAttribute("famousDrink", cafe.getSpecialDrink());
    result = e;
}

void PlaceExportToXmlVisitor::visit(const Restaurant& restaurant) {
    QDomElement e = basePlaceToXml(restaurant, "Restaurant");
    e.appendChild(exportFoodData(restaurant));
    e.setAttribute("cuisineType", restaurant.getCuisineType());
    e.setAttribute("reservation", restaurant.hasReservation());
    e.setAttribute("specialDish", restaurant.getSpecialDish());
    result = e;
}

void PlaceExportToXmlVisitor::visit(const Disco& disco) {
    QDomElement e = basePlaceToXml(disco, "Disco");
    e.appendChild(exportEntertainmentData(disco));
    e.setAttribute("musicGenre", disco.getMusicGenre());
    e.setAttribute("hasPrive", disco.hasPriveAccess());
    e.setAttribute("dressCode", disco.getDressCode());
    result = e;
}

void PlaceExportToXmlVisitor::visit(const PanoramicPoint& point) {
    QDomElement e = basePlaceToXml(point, "PanoramicPoint");
    e.appendChild(exportEntertainmentData(point));
    e.setAttribute("altitude", point.getAltitude());
    e.setAttribute("hasBinocular", point.hasBinoculars());
    e.setAttribute("nightLighting", point.isNightLit());
    result = e;
}

void PlaceExportToXmlVisitor::visit(const LocalMarket& localMarket) {
    QDomElement e = basePlaceToXml(localMarket, "LocalMarket");
    e.appendChild(exportShoppingData(localMarket));
    e.setAttribute("artisans", localMarket.hasArtisans());
    e.setAttribute("seasonal", localMarket.isSeasonal());
    e.setAttribute("period", localMarket.getPeriod());
    result = e;
}

void PlaceExportToXmlVisitor::visit(const Mall& mall) {
    QDomElement e = basePlaceToXml(mall, "Mall");
    e.appendChild(exportShoppingData(mall));
    e.setAttribute("shopCount", mall.getShopCount());
    e.setAttribute("cinema", mall.hasCinema());
    e.setAttribute("freeParking", mall.hasFreeParking());
    result = e;
}

void PlaceExportToXmlVisitor::visit(const Museum& museum) {
    QDomElement e = basePlaceToXml(museum, "Museum");
    e.appendChild(exportCultureData(museum));
    e.setAttribute("hasAudioGuide", museum.hasAudioGuideAvailable());
    result = e;
}

void PlaceExportToXmlVisitor::visit(const Monument& monument) {
    QDomElement e = basePlaceToXml(monument, "Monument");
    e.appendChild(exportCultureData(monument));
    e.setAttribute("isUnesco", monument.isUnesco());
    e.setAttribute("conservationStatus", monument.getConservationStatus());
    e.setAttribute("openToPublic", monument.isOpenToPublic());
    result = e;
}
