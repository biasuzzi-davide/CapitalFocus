#ifndef CAFE_H
#define CAFE_H

#include "Food.h" // Eredita da Food
#include "weeklyOpenings.h"

// Rappresenta un cafe, un tipo di posto Food
class Cafe : public Food {
private:
    bool terrace; // Ha una terrazza
    QString specialDrink; // Bevanda speciale

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

    virtual ~Cafe() = default; // Distruttore

    // Controlla se apre per colazione in un dato giorno
    bool servesBreakfast(Weekday day) const;

    // Riassunto specifico per Cafe
    QString getFoodSummary() const override;

    // Dice la categoria
    QString getCategory() const override;

    // Per il Visitor
    void acceptVisitor(PlaceVisitorInterface& visitor) const override;

    // Getter
    bool hasTerrace() const;
    QString getSpecialDrink() const;
};

#endif // CAFE_H
