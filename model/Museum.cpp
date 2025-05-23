#include "Museum.h"
#include "visitor/placevisitorinterface.h"

// Costruttore
Museum::Museum(const QString& name, const QString& city, const QString& description,
               double rating, const weeklyOpenings& open, double cost,
               double studentDiscount, bool guidedTour,
               const QString& culturalFocus,
               bool hasAudioGuide)
    : Culture(name, city, description, rating, open, cost,
              studentDiscount, guidedTour, culturalFocus),
    hasAudioGuide(hasAudioGuide) {}

// Dice la categoria
QString Museum::getCategory() const {
    return "Museum";
}

// Riassunto culturale
QString Museum::getCultureSummary() const {
    return QString("This museum offers %1")
        .arg(hasAudioGuide ? "an audio guide" : "no audio guide");
}

// Implementazione per il Visitor
void Museum::acceptVisitor(PlaceVisitorInterface& visitor) const{
    visitor.visit(*this);
}

// Getter
bool Museum::hasAudioGuideAvailable() const {
    return hasAudioGuide;
}
