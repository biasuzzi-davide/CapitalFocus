#include "Entertainment.h"

Entertainment::Entertainment(const QString& name, const QString& city, const QString& description,
                             float rating, const weeklyOpenings& open, double cost,
                             double avgStayDuration, int minimumAge, const QString& restrictedEntry)
    : Place(name, city, description, rating, open, cost),
      avgStayDuration(avgStayDuration), minimumAge(minimumAge), restrictedEntry(restrictedEntry) {}
