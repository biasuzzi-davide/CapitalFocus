#include "Mall.h"
#include "visitor/placevisitorinterface.h"

// Costruttore
Mall::Mall( const QString& name,
           const QString& city,
           const QString& description,
           double rating,
           const weeklyOpenings& hours,
           double cost,
           bool outdoor,
           bool foodArea,
           int standNumber,
           int shopCount,
           bool cinema,
           bool freeParking)
    :   Shopping(name, city, description, rating, hours, cost, outdoor, foodArea, standNumber),
    shopCount(shopCount),
    cinema(cinema),
    freeParking(freeParking) {}

// Riassunto shopping
QString Mall::getShoppingSummary() const {
    return QString("This mall has %1 shops, %2, and %3.")
    .arg(shopCount)
    .arg(cinema ? "a cinema" : "no cinema")
    .arg(freeParking ? "free parking" : "no free parking");
}

// Dice la categoria
QString Mall::getCategory() const {
    return "Mall";
}

// Implementazione per il Visitor
void Mall::acceptVisitor(PlaceVisitorInterface& visitor) const {
    visitor.visit(*this);
}

// Getter
int Mall::getShopCount() const {
    return shopCount;
}

bool Mall::hasCinema() const {
    return cinema;
}

bool Mall::hasFreeParking() const {
    return freeParking;
}
