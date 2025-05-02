#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#include "Place.h"

class Entertainment : public Place {
protected:
    double avgStayDuration;
    int minimumAge;
    QString restrictedEntry;

public:
    Entertainment(const QString& name, const QString& city, const QString& description,
                  double rating, const weeklyOpenings& open, double cost,
                  double avgStayDuration, int minimumAge, const QString& restrictedEntry);
    virtual ~Entertainment() = default;
};

#endif // ENTERTAINMENT_H
