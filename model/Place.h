#ifndef PLACE_H
#define PLACE_H

#include <QString>
#include "weeklyOpenings.h"

class PlaceVisitorInterface; // Serve per acceptVisitor

// Base per tutti i luoghi
class Place {
private:
    QString name; // Nome
    QString city; // Città
    QString description; // Descrizione
    double rating; // Valutazione
    double cost; // Costo

protected:
    weeklyOpenings open; // Orari

public:
    // Costruttore
    Place(const QString& name, const QString& city, const QString& description,
          double rating, const weeklyOpenings& open, double cost);

    virtual ~Place() = default; // Distruttore

    // Per il Visitor
    virtual void acceptVisitor(PlaceVisitorInterface& visitor) const = 0;

    // Dice la categoria
    virtual QString getCategory() const = 0;

    // Getter
    double getCost() const;
    QString getName() const;
    QString getCity() const;
    QString getDescription() const;
    double getRating() const;
    const weeklyOpenings& getOpen() const;
};

#endif // PLACE_H
