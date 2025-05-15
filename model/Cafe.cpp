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

//Se apre prima delle 10:30 si assume serva la colazione
bool Cafe::servesBreakfast(Weekday day) const{
    return open.opensBefore(day, QTime(10,30));
}

// Riassunto specifico per Cafe
QString Cafe::getFoodSummary() const {
    return QString("This café has %1 and its special drink is %2.")
    .arg(terrace ? "a terrace" : "no terrace")
    .arg(specialDrink);
}

// Getter
bool Cafe::hasTerrace() const{
    return terrace;
}

QString Cafe::getSpecialDrink() const{
    return specialDrink;
}

// Dice la categoria
QString Cafe::getCategory() const{
    return "Cafe";
}

// Implementazione per il Visitor
void Cafe::acceptVisitor(PlaceVisitorInterface& visitor) const {
    visitor.visit(*this);
}
