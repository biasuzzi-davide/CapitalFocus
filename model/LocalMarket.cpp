#include "LocalMarket.h"

// Costruttore
LocalMarket::LocalMarket(   const QString& name, 
                            const QString& city, 
                            const QString& description, 
                            float rating,
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
