#ifndef STATISTICSVISITOR_H
#define STATISTICSVISITOR_H

#include "placevisitorinterface.h"
#include <map>
#include <QString>

// Un Visitor per calcolare statistiche sui Place
class StatisticsVisitor : public PlaceVisitorInterface {
private:
    int count; // Conteggio dei posti
    double sumRatings; // Somma dei rating
    double sumCost; // Somma dei costi
    std::map<QString,int> cityCounts; // Conteggio per città

public:
    // Costruttore
    StatisticsVisitor();

    // Implementazioni dei metodi visit per i vari tipi di Place
    void visit(const Place& p) override;
    void visit(const Cafe& cafe) override;
    void visit(const Disco& disco) override;
    void visit(const Mall& mall) override;
    void visit(const LocalMarket& market) override;
    void visit(const Restaurant& restaurant) override;
    void visit(const PanoramicPoints& point) override;
    void visit(const Museum& museum) override;
    void visit(const Monument& monument) override;

    // Ritorna il conteggio totale dei posti visitati
    int totalPlaces() const;

    // Ritorna il rating medio
    double averageRating() const;

    // Ritorna il costo medio
    double averageCost() const;

    // Ritorna il conteggio dei posti per città
    const std::map<QString,int>& countByCity() const;
};

#endif // STATISTICSVISITOR_H
