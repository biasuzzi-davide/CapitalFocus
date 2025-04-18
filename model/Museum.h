#ifndef MUSEUM_H
#define MUSEUM_H

#include "Culture.h"

class Museum : public Culture {
private:
    bool hasAudioGuide;

public:
    Museum(const QString& name, const QString& city, const QString& description,
           float rating, const weeklyOpenings& open, double cost,
           double studentDiscount, bool guidedTour,
           const QString& culturalFocus, const QString& hasGuidedTour,
           bool hasAudioGuide);

    QString getCategory() const override;

    virtual void acceptVisitor(PlaceVisitorInterface& visitor) const override;
};

#endif // MUSEUM_H
