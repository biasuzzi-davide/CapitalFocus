#ifndef STATISTICSVISITOR_H
#define STATISTICSVISITOR_H

#include "PlaceVisitorInterface.h"
#include <vector>
#include <map>

class StatisticsVisitor : public PlaceVisitorInterface {
public:
    StatisticsVisitor();

    // chiamato per ogni Place*
    void visit(const Place& p) override;

    // getters per i valori finali
    int totalPlaces() const;
    double averageRating() const;
    double averageCost() const;
    const std::map<QString,int>& countByCity() const;

    virtual void visit(const Cafe& cafe) override;
    virtual void visit(const Disco& disco) override;
    virtual void visit(const Mall& mall) override;
    virtual void visit(const LocalMarket& market) override;
    virtual void visit(const Restaurant& restaurant) override;
    virtual void visit(const PanoramicPoints& point) override;
    virtual void visit(const Museum& museum) override;
    virtual void visit(const Monument& monument) override;

private:
    int count;
    double sumRatings;
    double sumCost;
    std::map<QString,int> cityCounts;
};

#endif // STATISTICSVISITOR_H
