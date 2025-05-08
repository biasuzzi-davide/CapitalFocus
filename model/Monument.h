#ifndef MONUMENT_H
#define MONUMENT_H

#include "Culture.h"

class Monument : public Culture {
private:
    bool isUnescoHeritage;
    QString conservationStatus;
    bool openToPublic;

public:
    Monument(const QString& name, const QString& city, const QString& description,
             double rating, const weeklyOpenings& open, double cost,
             double studentDiscount, bool guidedTour,
             const QString& culturalFocus,
             bool isUnescoHeritage, const QString& conservationStatus, bool openToPublic);

    QString getCategory() const override;

    virtual void acceptVisitor(PlaceVisitorInterface& visitor) const override;
    bool isUnesco() const;
    QString getConservationStatus() const;
    bool isOpenToPublic() const;
    QString getCultureSummary() const override;
};

#endif // MONUMENT_H
