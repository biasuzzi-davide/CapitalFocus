#include "Disco.h"
#include "visitor/placevisitorinterface.h"

// Costruttore
Disco::Disco(const QString& name, const QString& city, const QString& description,
             double rating, const weeklyOpenings& open, double cost,
             QTime avgStayDuration, int minimumAge, const QString& restrictedEntry,
             const QString& musicGenre, bool hasPrive, const QString& dressCode)
    : Entertainment(name, city, description, rating, open, cost,
                    avgStayDuration, minimumAge, restrictedEntry),
    musicGenre(musicGenre), hasPrive(hasPrive), dressCode(dressCode) {}

// Dice la categoria
QString Disco::getCategory() const {
    return "Disco";
}

// Riassunto specifico per Disco
QString Disco::getEntertainmentSummary() const {
    return QString("Music genre: %1, %2, dress code: %3.")
    .arg(musicGenre)
    .arg(hasPrive ? "has private area" : "no private area")
    .arg(dressCode.isEmpty() ? "none" : dressCode);
}

// Implementazione per il Visitor
void Disco::acceptVisitor(PlaceVisitorInterface& visitor) const {
    visitor.visit(*this);
}

// Getter
QString Disco::getMusicGenre() const {
    return musicGenre;
}

bool Disco::hasPriveAccess() const {
    return hasPrive;
}

QString Disco::getDressCode() const {
    return dressCode;
}
