#ifndef CULTURE_H
#define CULTURE_H

#include "Place.h"

class Culture : public Place {
protected:
    double studentDiscount;
    bool guidedTour;
    QString culturalFocus;
    QString hasGuidedTour;

public:
    Culture(const QString& name, const QString& city, const QString& description,
            double rating, const weeklyOpenings& open, double cost,
            double studentDiscount, bool guidedTour,
            const QString& culturalFocus, const QString& hasGuidedTour);
    virtual ~Culture() = default;
};

#endif // CULTURE_H
