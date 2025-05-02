#ifndef CAFE_H
#define CAFE_H

#include "Food.h"
#include "weeklyOpenings.h"

class Cafe : public Food {
private:
    bool terrace;           // True se presente una terrazza
    QString specialDrink;   // Stringa rappresentante il cocktail specialità

public:
    // Costruttore
    Cafe(const QString& name,
         const QString& city,
         const QString& description,
         double rating,
         const weeklyOpenings& hours,
         double cost,
         bool takeAway,
         const QTime& avgWaitingTime,
         bool veganMenu,
         bool terrace,
         const QString& specialDrink);

    // Metodo che ritorna true se il posto apre per colazione
    bool servesBreakfast(Weekday day) const;

    // Getter
    bool hasTerrace() const;
    QString getSpecialDrink() const;

    // Override del metodo polimorfo della classe base
    QString getCategory() const override;

    virtual ~Cafe() = default;

    void acceptVisitor(PlaceVisitorInterface& visitor) const override;

};

#endif // CAFE_H
