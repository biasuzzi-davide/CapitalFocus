#include "Cafe.h"
#include "visitor/placevisitorinterface.h"

// Costruttore
Cafe::Cafe( const QString& name,
           const QString& city,
           const QString& description,
           double rating,
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
QString Cafe::getFoodSummary() const {
    return QString("This café has %1 and its special drink is %2.")
        .arg(terrace ? "a terrace" : "no terrace")
        .arg(specialDrink);
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

void Cafe::acceptVisitor(PlaceVisitorInterface& visitor) const {
    visitor.visit(*this);
}
