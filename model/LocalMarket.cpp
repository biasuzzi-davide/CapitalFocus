#include "LocalMarket.h"
#include "visitor/placevisitorinterface.h"

// Costruttore
LocalMarket::LocalMarket(   const QString& name, 
                            const QString& city, 
                            const QString& description, 
                            double rating,
                            const weeklyOpenings& hours,
                            double cost, 
                            bool outdoor, 
                            bool foodArea, 
                            int standNumber,
                            bool artisans,
                            bool seasonal,
                            const QString& period)
                        :   Shopping(name, city, description, rating, hours, cost, outdoor, foodArea, standNumber),
                            artisans(artisans),
                            seasonal(seasonal),
                            period(period) {}

// True se presenti artigiani
bool LocalMarket::hasArtisans() const {
    return artisans;
}
QString LocalMarket::getShoppingSummary() const {
    return QString("This market is %1, %2, and takes place in %3.")
    .arg(artisans ? "artisan-friendly" : "not artisan-friendly")
        .arg(seasonal ? "seasonal" : "permanent")
        .arg(period);
}

// True se organizzato in precise stagioni
bool LocalMarket::isSeasonal() const {
    return seasonal;
}

// Ritorna il periodo di apertura
QString LocalMarket::getPeriod() const {
    return seasonal ? period : "Open all year round";
}

// Ritorna la categoria del luogo
QString LocalMarket::getCategory() const {
    return "Local Market";
}

void LocalMarket::acceptVisitor(PlaceVisitorInterface& visitor) const {
    visitor.visit(*this);
}
