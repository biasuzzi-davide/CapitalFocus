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

// Ritorna il numero di negozi
int Mall::getShopCount() const {
    return shopCount;
}
QString Mall::getShoppingSummary() const {
    return QString("This mall has %1 shops, %2, and %3.")
    .arg(shopCount)
        .arg(cinema ? "a cinema" : "no cinema")
        .arg(freeParking ? "free parking" : "no free parking");
}

// True se è presente un cinema
bool Mall::hasCinema() const {
    return cinema;
}

// True se è presente un parcheggio gratuito
bool Mall::hasFreeParking() const {
    return freeParking;
}

// Ritorna la categoria del luogo
QString Mall::getCategory() const {
    return "Mall";
}

void Mall::acceptVisitor(PlaceVisitorInterface& visitor) const {
    visitor.visit(*this);
}
