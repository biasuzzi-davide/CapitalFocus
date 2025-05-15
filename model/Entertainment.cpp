#include "Entertainment.h"

// Costruttore
Entertainment::Entertainment(const QString& name, const QString& city, const QString& description,
                             double rating, const weeklyOpenings& open, double cost,
                             QTime avgStayDuration, int minimumAge, const QString& restrictedEntry)
    : Place(name, city, description, rating, open, cost),
    avgStayDuration(avgStayDuration), minimumAge(minimumAge), restrictedEntry(restrictedEntry) {}

// Getter
QTime Entertainment::getAvgStayDuration() const {
    return avgStayDuration;
}

int Entertainment::getMinAge() const {
    return minimumAge;
}

QString Entertainment::getRestrictedEntry() const {
    return restrictedEntry;
}
