#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Food.h" // Eredita da Food

// Rappresenta un ristorante, un tipo di posto Food
class Restaurant : public Food {
private:
    QString cuisineType; // Tipo di cucina
    bool reservation; // Possibile prenotare
    QString specialDish; // Piatto speciale

public:
    // Costruttore
    Restaurant(const QString& name,
               const QString& city,
               const QString& description,
               double rating,
               const weeklyOpenings& hours,
               double cost,
               bool takeAway,
               const QTime& avgWaitingTime,
               bool veganMenu,
               const QString& cuisineType,
               bool reservation,
               const QString& specialDish);

    virtual ~Restaurant() = default; // Distruttore

    // Riassunto cibo
    QString getFoodSummary() const override;

    // Dice la categoria
    QString getCategory() const override;

    // Per il Visitor
    virtual void acceptVisitor(PlaceVisitorInterface& visitor) const override;

    // Getter
    QString getCuisineType() const;
    bool hasReservation() const;
    QString getSpecialDish() const;
};

#endif // RESTAURANT_H
