#include "Culture.h"

Culture::Culture(const QString& name, const QString& city, const QString& description,
                 double rating, const weeklyOpenings& open, double cost,
                 double studentDiscount, bool guidedTour,
                 const QString& culturalFocus, const QString& hasGuidedTour)
    : Place(name, city, description, rating, open, cost),
      studentDiscount(studentDiscount), guidedTour(guidedTour),
      culturalFocus(culturalFocus), hasGuidedTour(hasGuidedTour) {}
