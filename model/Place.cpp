#include "Place.h"

// Costruttore
Place::Place(const QString& name, const QString& city, const QString& description,
             double rating, const weeklyOpenings& op, double cost)
    : name(name), city(city), description(description),
    rating(rating), open(op), cost(cost) {}

// Getter
QString Place::getName() const{return name;}
QString Place::getCity() const{return city;}
QString Place::getDescription() const{return description;}
double Place::getRating() const{return rating;}
double Place::getCost() const {return cost;}
const weeklyOpenings& Place::getOpen() const{return open;}
