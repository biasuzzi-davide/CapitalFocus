#include "statisticsvisitor.h"
#include "../Place.h"

StatisticsVisitor::StatisticsVisitor()
    : count(0), sumRatings(0.0), sumCost(0.0)
{}

void StatisticsVisitor::visit(const Place& p) {
    ++count;
    sumRatings += p.getRating();
    sumCost += p.getCost();
    cityCounts[p.getCity()]++;
}

int StatisticsVisitor::totalPlaces() const { return count; }
double StatisticsVisitor::averageRating() const { return count ? sumRatings/count : 0; }
double StatisticsVisitor::averageCost()   const { return count ? sumCost/count : 0; }
const std::map<QString,int>& StatisticsVisitor::countByCity() const { return cityCounts; }

void StatisticsVisitor::visit(const Restaurant& r) {
    visit(static_cast<const Place&>(r));
}
void StatisticsVisitor::visit(const Cafe& r) {
    visit(static_cast<const Place&>(r));
}
void StatisticsVisitor::visit(const Mall& r) {
    visit(static_cast<const Place&>(r));
}
void StatisticsVisitor::visit(const Disco& r) {
    visit(static_cast<const Place&>(r));
}
void StatisticsVisitor::visit(const Monument& r) {
    visit(static_cast<const Place&>(r));
}
void StatisticsVisitor::visit(const Museum& r) {
    visit(static_cast<const Place&>(r));
}
void StatisticsVisitor::visit(const LocalMarket& r) {
    visit(static_cast<const Place&>(r));
}
void StatisticsVisitor::visit(const PanoramicPoints& r) {
    visit(static_cast<const Place&>(r));
}

