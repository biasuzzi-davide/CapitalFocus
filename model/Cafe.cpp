#include "Cafe.h"
// Costruttore
Cafe::Cafe( const QString& name,
           const QString& city,
           const QString& description,
           float rating,
           const weeklyOpenings& hours,
           double cost,
           bool takeAway,
           const QTime& avgWaitingTime,
           bool veganMenu,
           bool terrace,
           const QString& specialDrink)
    :   Food(name, city, description, rating, hours, cost, takeAway, avgWaitingTime, veganMenu),
    terrace(terrace),
    specialDrink(specialDrink) {}

// Metodo che ritorna true se il posto apre per colazione
bool Cafe::servesBreakfast(Weekday day) const{
    return open.opensBefore(day, QTime(10,30));
}

// getter
bool Cafe::hasTerrace() const{
    return terrace;
}

QString Cafe::getSpecialDrink() const{
    return specialDrink;
}

// Override del metodo polimorfo della classe base
QString Cafe::getCategory() const{
    return "Cafe";
}

#include "placevisitorinterface.h"

void Cafe::acceptVisitor(PlaceVisitorInterface& visitor) const {
    visitor.visit(*this);
}
