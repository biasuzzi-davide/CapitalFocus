#include "Place.h"

Place::Place(const QString& name, const QString& city, const QString& description,
             float rating, const weeklyOpenings& op, double cost)
    : name(name), city(city), description(description),
      rating(rating), open(op), cost(cost) {}

QString Place::getName() const{return name;}
QString Place::getCity() const{return city;}
QString Place::getDescription() const{return description;}
float Place::getRating() const{return rating;}
QString Place::getCost() const {return QString::number(cost, 'f', 2) + "€";}
const weeklyOpenings& Place::getOpen() const{return open;}
