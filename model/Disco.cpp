#include "Disco.h"

Disco::Disco(const QString& name, const QString& city, const QString& description,
             float rating, const weeklyOpenings& open, double cost,
             double avgStayDuration, int minimumAge, const QString& restrictedEntry,
             bool musicGenre, bool hasPrive, const QString& dressCode)
    : Entertainment(name, city, description, rating, open, cost,
                    avgStayDuration, minimumAge, restrictedEntry),
      musicGenre(musicGenre), hasPrive(hasPrive), dressCode(dressCode) {}

QString Disco::getCategory() const {
    return "Disco";
}
