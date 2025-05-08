#ifndef MUSEUM_H
#define MUSEUM_H

#include "Culture.h"

class Museum : public Culture {
private:
    bool hasAudioGuide;

public:
    Museum(const QString& name, const QString& city, const QString& description,
           double rating, const weeklyOpenings& open, double cost,
           double studentDiscount, bool guidedTour,
           const QString& culturalFocus,
           bool hasAudioGuide);

    QString getCategory() const override;

    virtual void acceptVisitor(PlaceVisitorInterface& visitor) const override;
    bool hasAudioGuideAvailable() const;
    QString getCultureSummary() const override;
};

#endif // MUSEUM_H
