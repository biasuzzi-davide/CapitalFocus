#include "Museum.h"
#include "visitor/placevisitorinterface.h"

Museum::Museum(const QString& name, const QString& city, const QString& description,
               double rating, const weeklyOpenings& open, double cost,
               double studentDiscount, bool guidedTour,
               const QString& culturalFocus,
               bool hasAudioGuide)
    : Culture(name, city, description, rating, open, cost,
              studentDiscount, guidedTour, culturalFocus),
      hasAudioGuide(hasAudioGuide) {}

QString Museum::getCategory() const {
    return "Museum";
}
QString Museum::getCultureSummary() const {
    return QString("This museum offers %1, with a student discount of %2% and a cultural focus on %3.")
    .arg(hasAudioGuide ? "an audio guide" : "no audio guide")
        .arg(QString::number(studentDiscount, 'f', 1))
        .arg(culturalFocus);
}

void Museum::acceptVisitor(PlaceVisitorInterface& visitor) const{
    visitor.visit(*this);
}
bool Museum::hasAudioGuideAvailable() const {
    return hasAudioGuide;
}
