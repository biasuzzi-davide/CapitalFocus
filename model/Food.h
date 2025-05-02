#ifndef FOOD_H
#define FOOD_H

#include "Place.h"

class Food: public Place{
    private:
        bool takeAway;
        QTime avgWaitingTime;
        bool veganMenu;
    
    public:
        Food(   const QString& name,
                const QString& city,
                const QString& description,
                double rating,
                const weeklyOpenings& hours,
                double cost,
                bool takeAway,
                const QTime& avgWaitingTime,
                bool veganMenu);

        bool hasTakeAway() const;
        QTime getAvgWaitingTime() const;
        bool hasVeganMenu() const;

        QString getCategory() const override;

        virtual ~Food()=default;
};
#endif // FOOD_H
