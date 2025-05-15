#ifndef SHOPPING_H
#define SHOPPING_H

#include "Place.h" // Eredita da Place

// Base per posti legati allo shopping
class Shopping : public Place {
private:
    bool outdoor; // All'aperto
    bool foodArea; // Area cibo presente
    int standNumber; // Numero di stand/negozi

public:
    // Costruttore
    Shopping(const QString& name,
             const QString& city,
             const QString& description,
             double rating,
             const weeklyOpenings& hours,
             double cost,
             bool outdoor,
             bool foodArea,
             int standNumber);

    virtual ~Shopping() = default; // Distruttore

    // Riassunto shopping
    virtual QString getShoppingSummary() const = 0;

    // Dice la categoria
    QString getCategory() const override;

    // Getter
    bool isOutdoor() const;
    bool foodAreaPresent() const;
    int getStandNumber() const;
};

#endif // SHOPPING_H
