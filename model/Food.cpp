#include "Food.h"

Food::Food( const QString& name,
            const QString& city,
            const QString& description,
            double rating,
            const weeklyOpenings& hours,
            double cost,
            bool takeAway,
            const QTime& avgWaitingTime,
            bool veganMenu)
        :   Place(name, city, description, rating, hours, cost),
            takeAway(takeAway),
            avgWaitingTime(avgWaitingTime),
            veganMenu(veganMenu) {}

bool Food::hasTakeAway() const {
    return takeAway;
}

QTime Food::getAvgWaitingTime() const{
    return avgWaitingTime;
}

bool Food::hasVeganMenu() const{
    return veganMenu;
}

QString Food::getCategory() const{
    return "Food";
}
