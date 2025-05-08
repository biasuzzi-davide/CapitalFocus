#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#include "Place.h"

class Entertainment : public Place {
protected:
    QTime avgStayDuration;
    int minimumAge;
    QString restrictedEntry;

public:
    Entertainment(const QString& name, const QString& city, const QString& description,
                  double rating, const weeklyOpenings& open, double cost,
                  QTime avgStayDuration, int minimumAge, const QString& restrictedEntry);
    virtual ~Entertainment() = default;
    QTime getAvgStayDuration() const;
    int getMinAge() const;
    QString getRestrictedEntry() const;
    virtual QString getEntertainmentSummary() const = 0;
};

#endif // ENTERTAINMENT_H
