#ifndef DISCO_H
#define DISCO_H

#include "Entertainment.h"

class Disco : public Entertainment {
private:
    QString musicGenre;
    bool hasPrive;
    QString dressCode;

public:
    Disco(const QString& name, const QString& city, const QString& description,
          double rating, const weeklyOpenings& open, double cost,
          double avgStayDuration, int minimumAge, const QString& restrictedEntry,
          const QString& musicGenre, bool hasPrive, const QString& dressCode);

    QString getCategory() const override;
    void acceptVisitor(PlaceVisitorInterface& visitor) const override;

    // Getters
    QString getMusicGenre() const;
    bool hasPriveAccess() const;
    QString getDressCode() const;

};

#endif // DISCO_H
