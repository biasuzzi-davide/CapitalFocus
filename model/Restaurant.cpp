#include "Restaurant.h"
#include "visitor/placevisitorinterface.h"

// Costruttore
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

// Riassunto cibo
QString Restaurant::getFoodSummary() const {
    return QString("Cuisine: %1 | Reservation %2 | Special dish: %3")
    .arg(cuisineType)
    .arg(reservation ? "available" : "not available")
    .arg(specialDish);
}

// Dice la categoria
QString Restaurant::getCategory() const{
    return "Restaurant";
}

// Implementazione per il Visitor
void Restaurant::acceptVisitor(PlaceVisitorInterface& visitor) const{
    visitor.visit(*this);
}

// Getter
QString Restaurant::getCuisineType() const{
    return cuisineType;
}

bool Restaurant::hasReservation() const{
    return reservation;
}

QString Restaurant::getSpecialDish() const{
    return specialDish;
}
