#ifndef FOOD_H
#define FOOD_H

#include "Place.h" // Eredita da Place
#include <QTime>

// Base per posti legati al cibo
class Food: public Place{
private:
    bool takeAway; // Possibilità di take away
    QTime avgWaitingTime; // Tempo medio di attesa
    bool veganMenu; // Opzioni vegane

public:
    // Costruttore
    Food(const QString& name,
         const QString& city,
         const QString& description,
         double rating,
         const weeklyOpenings& hours,
         double cost,
         bool takeAway,
         const QTime& avgWaitingTime,
         bool veganMenu);

    virtual ~Food()=default; // Distruttore

    // Riassunto cibo
    virtual QString getFoodSummary() const = 0;

    // Dice la categoria
    QString getCategory() const override;

    // Getter
    bool hasTakeAway() const;
    QTime getAvgWaitingTime() const;
    bool hasVeganMenu() const;
};
#endif // FOOD_H
