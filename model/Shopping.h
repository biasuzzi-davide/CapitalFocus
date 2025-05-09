#ifndef SHOPPING_H
#define SHOPPING_H

#include "Place.h"

class Shopping : public Place {
private:
    bool outdoor;
    bool foodArea;
    int standNumber;

public:
    Shopping(const QString& name,
             const QString& city,
             const QString& description,
             double rating,
             const weeklyOpenings& hours,
             double cost,
             bool outdoor,
             bool foodArea,
             int standNumber);

    bool isOutdoor() const;
    bool foodAreaPresent() const;
    int getStandNumber() const;
    virtual QString getShoppingSummary() const = 0;
    QString getCategory() const override;

    virtual ~Shopping() = default;
};

#endif // SHOPPING_H
