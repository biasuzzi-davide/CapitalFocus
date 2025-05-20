#include "PanoramicPoint.h"
#include "visitor/placevisitorinterface.h"

// Costruttore
PanoramicPoint::PanoramicPoint(const QString& name, const QString& city, const QString& description,
                                 double rating, const weeklyOpenings& open, double cost,
                                 QTime avgStayDuration, int minimumAge, const QString& restrictedEntry,
                                 double altitude, bool hasBinocular, bool nightLighting)
    : Entertainment(name, city, description, rating, open, cost,
                    avgStayDuration, minimumAge, restrictedEntry),
    altitude(altitude), hasBinocular(hasBinocular), nightLighting(nightLighting) {}

// Dice la categoria
QString PanoramicPoint::getCategory() const {
    return "Panoramic Point";
}

// Implementazione per il Visitor
void PanoramicPoint::acceptVisitor(PlaceVisitorInterface& visitor) const{
    visitor.visit(*this);
}

// Riassunto intrattenimento
QString PanoramicPoint::getEntertainmentSummary() const {
    return QString("Altitude: %1 m | %2 | %3")
    .arg(altitude)
    .arg(hasBinocular ? "Binoculars available" : "No binoculars")
    .arg(nightLighting ? "Night lighting available" : "No night lighting");
}

// Getter
double PanoramicPoint::getAltitude() const {
    return altitude;
}

bool PanoramicPoint::hasBinoculars() const {
    return hasBinocular;
}

bool PanoramicPoint::isNightLit() const {
    return nightLighting;
}
