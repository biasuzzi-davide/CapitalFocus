#include "PanoramicPoints.h"
#include "visitor/placevisitorinterface.h"


PanoramicPoints::PanoramicPoints(const QString& name, const QString& city, const QString& description,
                                 float rating, const weeklyOpenings& open, double cost,
                                 double avgStayDuration, int minimumAge, const QString& restrictedEntry,
                                 double altitude, bool hasBinocular, bool nightLighting)
    : Entertainment(name, city, description, rating, open, cost,
                    avgStayDuration, minimumAge, restrictedEntry),
      altitude(altitude), hasBinocular(hasBinocular), nightLighting(nightLighting) {}

QString PanoramicPoints::getCategory() const {
    return "Panoramic Point";
}

void PanoramicPoints::acceptVisitor(PlaceVisitorInterface& visitor) const{
    visitor.visit(*this);
}
double PanoramicPoints::getAltitude() const {
    return altitude;
}

bool PanoramicPoints::hasBinoculars() const {
    return hasBinocular;
}

bool PanoramicPoints::isNightLit() const {
    return nightLighting;
}
