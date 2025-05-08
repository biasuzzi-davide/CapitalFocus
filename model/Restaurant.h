#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Food.h"

// Classe concreta ristorante
class Restaurant : public Food {
private:
    QString cuisineType;    // Stringa che indica il tipo di cucina
    bool reservation;       // True se possibile prenotare
    QString specialDish;    // Stringa che indica il piatto speciale

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

    // Getter
    QString getCuisineType() const;
    bool hasReservation() const;
    QString getSpecialDish() const;

    // Override del metodo polimorfo della classe base
    QString getCategory() const override;
    QString getFoodSummary() const override;
    virtual ~Restaurant() = default;

    virtual void acceptVisitor(PlaceVisitorInterface& visitor) const override;
};

#endif // RESTAURANT_H
