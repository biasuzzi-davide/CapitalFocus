#include "Entertainment.h"

Entertainment::Entertainment(const QString& name, const QString& city, const QString& description,
                             double rating, const weeklyOpenings& open, double cost,
                             double avgStayDuration, int minimumAge, const QString& restrictedEntry)
    : Place(name, city, description, rating, open, cost),
      avgStayDuration(avgStayDuration), minimumAge(minimumAge), restrictedEntry(restrictedEntry) {}

double Entertainment::getAvgStayDuration() const {
    return avgStayDuration;
}

int Entertainment::getMinAge() const {
    return minimumAge;
}

QString Entertainment::getRestrictedEntry() const {
    return restrictedEntry;
}
