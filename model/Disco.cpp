#include "Disco.h"
#include "visitor/placevisitorinterface.h"

Disco::Disco(const QString& name, const QString& city, const QString& description,
             float rating, const weeklyOpenings& open, double cost,
             double avgStayDuration, int minimumAge, const QString& restrictedEntry,
             const QString& musicGenre, bool hasPrive, const QString& dressCode)
    : Entertainment(name, city, description, rating, open, cost,
                    avgStayDuration, minimumAge, restrictedEntry),
      musicGenre(musicGenre), hasPrive(hasPrive), dressCode(dressCode) {}

QString Disco::getCategory() const {
    return "Disco";
}

void Disco::acceptVisitor(PlaceVisitorInterface& visitor) const {
    visitor.visit(*this);
}
QString Disco::getMusicGenre() const {
    return musicGenre;
}

bool Disco::hasPriveAccess() const {
    return hasPrive;
}

QString Disco::getDressCode() const {
    return dressCode;
}
