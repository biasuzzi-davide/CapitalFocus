#include "Place.h"

Place::Place(const QString& name, const QString& city, const QString& description,
             float rating, const weeklyOpenings& op, double cost)
    : name(name), city(city), description(description),
      rating(rating), open(open), cost(cost) {}

QString Place::getCost() const {
    return QString::number(cost, 'f', 2) + "€";
}
// prova
