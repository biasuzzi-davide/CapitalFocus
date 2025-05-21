#include "Monument.h"
#include "visitor/placevisitorinterface.h"

// Costruttore
Monument::Monument(const QString& name, const QString& city, const QString& description,
                   double rating, const weeklyOpenings& open, double cost,
                   double studentDiscount, bool guidedTour,
                   const QString& culturalFocus,
                   bool isUnescoHeritage, const QString& conservationStatus, bool openToPublic)
    : Culture(name, city, description, rating, open, cost,
              studentDiscount, guidedTour, culturalFocus),
    isUnescoHeritage(isUnescoHeritage), conservationStatus(conservationStatus), openToPublic(openToPublic) {}

// Dice la categoria
QString Monument::getCategory() const {
    return "Monument";
}

// Implementazione per il Visitor
void Monument::acceptVisitor(PlaceVisitorInterface& visitor) const{
    visitor.visit(*this);
}

// Riassunto culturale
QString Monument::getCultureSummary() const {
    return QString("This monument is %1, %2 and currently %3.")
    .arg(isUnescoHeritage ? "a UNESCO heritage site" : "not a UNESCO heritage site")
    .arg(openToPublic ? "open to the public" : "not open to the public")
    .arg(conservationStatus);
}

// Getter
bool Monument::isUnesco() const {
    return isUnescoHeritage;
}

QString Monument::getConservationStatus() const {
    return conservationStatus;
}

bool Monument::isOpenToPublic() const {
    return openToPublic;
}
