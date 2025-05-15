#include "Shopping.h"

// Costruttore
Shopping::Shopping( const QString &name,
                   const QString& city,
                   const QString& description,
                   double rating,
                   const weeklyOpenings& hours,
                   double cost,
                   bool outdoor,
                   bool foodArea,
                   int standNumber)
    :   Place(name, city, description, rating, hours, cost),
    outdoor(outdoor),
    foodArea(foodArea),
    standNumber(standNumber) {}

// Getter
bool Shopping::isOutdoor() const {
    return outdoor;
}

bool Shopping::foodAreaPresent() const {
    return foodArea;
}

int Shopping::getStandNumber() const{
    return standNumber;
}

// Dice la categoria
QString Shopping::getCategory() const {
    return "Shopping";
}
