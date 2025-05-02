#include "Museum.h"
#include "visitor/placevisitorinterface.h"

Museum::Museum(const QString& name, const QString& city, const QString& description,
               double rating, const weeklyOpenings& open, double cost,
               double studentDiscount, bool guidedTour,
               const QString& culturalFocus, const QString& hasGuidedTour,
               bool hasAudioGuide)
    : Culture(name, city, description, rating, open, cost,
              studentDiscount, guidedTour, culturalFocus, hasGuidedTour),
      hasAudioGuide(hasAudioGuide) {}

QString Museum::getCategory() const {
    return "Museum";
}

void Museum::acceptVisitor(PlaceVisitorInterface& visitor) const{
    visitor.visit(*this);
}
bool Museum::hasAudioGuideAvailable() const {
    return hasAudioGuide;
}
