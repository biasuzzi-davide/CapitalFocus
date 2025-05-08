#include "Culture.h"

Culture::Culture(const QString& name, const QString& city, const QString& description,
                 double rating, const weeklyOpenings& open, double cost,
                 double studentDiscount, bool guidedTour,
                 const QString& culturalFocus)
    : Place(name, city, description, rating, open, cost),
      studentDiscount(studentDiscount), guidedTour(guidedTour),
      culturalFocus(culturalFocus){}

double Culture::getStudentDiscount() const {
    return studentDiscount;
}

bool Culture::hasGuidedTour() const {
    return guidedTour;
}

QString Culture::getCulturalFocus() const {
    return culturalFocus;
}
