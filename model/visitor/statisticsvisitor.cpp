#include "statisticsvisitor.h"

// Costruttore, inizializza i contatori a zero
StatisticsVisitor::StatisticsVisitor()
    : count(0), sumRatings(0.0), sumCost(0.0)
{}

// Metodo visit per la classe base Place, dove avviene il calcolo delle statistiche in comune
void StatisticsVisitor::visit(const Place& p) {
    ++count; // Incrementa il conteggio totale
    sumRatings += p.getRating(); // Aggiunge il rating
    sumCost += p.getCost(); // Aggiunge il costo
    cityCounts[p.getCity()]++; // Incrementa il conteggio per la città del posto
}

// Implementazioni dei metodi visit per le classi derivate
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
void StatisticsVisitor::visit(const PanoramicPoint& r) {
    visit(static_cast<const Place&>(r));
}

// Ritorna il conteggio totale
int StatisticsVisitor::totalPlaces() const { return count; }

// Ritorna il rating medio (gestisce divisione per zero)
double StatisticsVisitor::averageRating() const { return count ? sumRatings/count : 0; }

// Ritorna il costo medio (gestisce divisione per zero)
double StatisticsVisitor::averageCost()    const { return count ? sumCost/count : 0; }

// Ritorna il conteggio per città
const std::map<QString,int>& StatisticsVisitor::countByCity() const { return cityCounts; }
