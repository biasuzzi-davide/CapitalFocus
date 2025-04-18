#ifndef DISCO_H
#define DISCO_H

#include "Entertainment.h"

class Disco : public Entertainment {
private:
    bool musicGenre;
    bool hasPrive;
    QString dressCode;

public:
    Disco(const QString& name, const QString& city, const QString& description,
          float rating, const weeklyOpenings& open, double cost,
          double avgStayDuration, int minimumAge, const QString& restrictedEntry,
          bool musicGenre, bool hasPrive, const QString& dressCode);

    QString getCategory() const override;
    void acceptVisitor(PlaceVisitorInterface& visitor) const override;

};

#endif // DISCO_H
