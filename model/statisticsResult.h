// StatisticsResult.h
#ifndef STATISTICSRESULT_H
#define STATISTICSRESULT_H

#include <map>
#include <QString>

struct StatisticsResult {
    int    totalPlaces    = 0;
    double averageRating  = 0.0;
    double averageCost    = 0.0;
    std::map<QString,int> countByCity;
};

#endif // STATISTICSRESULT_H
