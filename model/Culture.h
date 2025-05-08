#ifndef CULTURE_H
#define CULTURE_H

#include "Place.h"

class Culture : public Place {
protected:
    double studentDiscount;
    bool guidedTour;
    QString culturalFocus;

public:
    Culture(const QString& name, const QString& city, const QString& description,
            double rating, const weeklyOpenings& open, double cost,
            double studentDiscount, bool guidedTour,
            const QString& culturalFocus);
    virtual ~Culture() = default;
    double getStudentDiscount() const;
    bool hasGuidedTour() const;
    QString getCulturalFocus() const;
    virtual QString getCultureSummary() const = 0;
};

#endif // CULTURE_H
