#include "Monument.h"
#include "visitor/placevisitorinterface.h"


Monument::Monument(const QString& name, const QString& city, const QString& description,
                   float rating, const weeklyOpenings& open, double cost,
                   double studentDiscount, bool guidedTour,
                   const QString& culturalFocus, const QString& hasGuidedTour,
                   bool isUnescoHeritage, const QString& conservationStatus, bool openToPublic)
    : Culture(name, city, description, rating, open, cost,
              studentDiscount, guidedTour, culturalFocus, hasGuidedTour),
      isUnescoHeritage(isUnescoHeritage), conservationStatus(conservationStatus), openToPublic(openToPublic) {}

QString Monument::getCategory() const {
    return "Monument";
}

void Monument::acceptVisitor(PlaceVisitorInterface& visitor) const{
    visitor.visit(*this);
}
bool Monument::isUnesco() const {
    return isUnescoHeritage;
}

QString Monument::getConservationStatus() const {
    return conservationStatus;
}

bool Monument::isOpenToPublic() const {
    return openToPublic;
}
