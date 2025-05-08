#include "Restaurant.h"
#include "visitor/placevisitorinterface.h"

// Costruttore classe concreta
Restaurant::Restaurant( const QString& name,
                        const QString& city,
                        const QString& description,
                        double rating,
                        const weeklyOpenings& hours,
                        double cost,
                        bool takeAway,
                        const QTime& avgWaitingTime,
                        bool veganMenu,
                        const QString& cuisineType,
                        bool reservation,
                        const QString& specialDish)
                    :   Food(name, city, description, rating, hours, cost, takeAway, avgWaitingTime, veganMenu),
                        cuisineType(cuisineType),
                        reservation(reservation),
                        specialDish(specialDish) {}

// Ritorna una stringa che indica il tipo di cucina
QString Restaurant::getCuisineType() const{
    return cuisineType;
}

// True se possibile prenotare
bool Restaurant::hasReservation() const{
    return reservation;
}

// Stringa che indica il piatto speciale
QString Restaurant::getSpecialDish() const{
    return specialDish;
}

QString Restaurant::getCategory() const{
    return "Restaurant";
}
QString Restaurant::getFoodSummary() const {
    return QString("Cuisine: %1. Reservation %2. Special dish: %3.")
    .arg(cuisineType)
        .arg(reservation ? "available" : "not available")
        .arg(specialDish);
}

void Restaurant::acceptVisitor(PlaceVisitorInterface& visitor) const{
    visitor.visit(*this);
}
