#include "Culture.h"

// Costruttore
Culture::Culture(const QString& name, const QString& city, const QString& description,
                 double rating, const weeklyOpenings& open, double cost,
                 double studentDiscount, bool guidedTour,
                 const QString& culturalFocus)
    : Place(name, city, description, rating, open, cost),
    guidedTour(guidedTour), studentDiscount(studentDiscount),
    culturalFocus(culturalFocus){}

// Getter sconto studenti
double Culture::getStudentDiscount() const {
    return studentDiscount;
}

// Getter tour guidato
bool Culture::hasGuidedTour() const {
    return guidedTour;
}

// Getter focus culturale
QString Culture::getCulturalFocus() const {
    return culturalFocus;
}
