#ifndef STATISTICSRESULT_H
#define STATISTICSRESULT_H

#include <map>
#include <QString>

// Struttura per i risultati delle statistiche
struct StatisticsResult {
    int     totalPlaces = 0; // Totale posti
    double  averageRating = 0.0; // Rating medio
    double  averageCost = 0.0; // Costo medio
    std::map<QString,int> countByCity; // Conteggio per città
};

#endif // STATISTICSRESULT_H
