#ifndef PLACE_H
#define PLACE_H

#include <QString>
#include "weeklyOpenings.h"
class PlaceVisitorInterface;

class Place {
protected:
    QString name;
    QString city;
    QString description;
    float rating;
    weeklyOpenings open;
    double cost;

public:
    Place(const QString& name, const QString& city, const QString& description,
          float rating, const weeklyOpenings& open, double cost);
    virtual ~Place() = default;
    virtual void acceptVisitor(PlaceVisitorInterface& visitor) const = 0;


    virtual QString getCategory() const = 0;
    QString getCost() const;
    QString getName() const;
    QString getCity() const;
    QString getDescription() const;
    float getRating() const;
    const weeklyOpenings& getOpen() const;

};

#endif // PLACE_H
