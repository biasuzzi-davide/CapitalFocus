#include "placerepository.h"
#include "visitor/statisticsvisitor.h"
#include <algorithm>

// Aggiunge un Place
void PlaceRepository::addPlace(const std::shared_ptr<Place>& place) {
    places.push_back(place);
}

// Rimuove un Place per indice
void PlaceRepository::removePlace(int index) {
    // Controlla se l'indice è valido
    if (index >= 0 && index < static_cast<int>(places.size())) {
        places.erase(places.begin() + index); // Rimuove l'elemento all'indice specificato
    }
}

// Ricerca Place per nome, città o descrizione
std::vector<std::shared_ptr<Place>> PlaceRepository::search(const QString& nameKeyword, const QString& cityFilter) const {
    std::vector<std::shared_ptr<Place>> results;

    for (const auto& place : places) {
        QString name = place->getName();
        QString city = place->getCity();
        QString desc = place->getDescription(); // Include descrizione nella ricerca

        // Controlla se nome, città o descrizione contengono la keyword (ignora maiuscole/minuscole)
        bool keywordMatch =
            nameKeyword.isEmpty() || // Se keyword vuota, match sempre
            name.contains(nameKeyword, Qt::CaseInsensitive) ||
            city.contains(nameKeyword, Qt::CaseInsensitive) ||
            desc.contains(nameKeyword, Qt::CaseInsensitive);

        // Controlla se la città corrisponde al filtro, se non è impostato "All"
        bool cityMatch = cityFilter == "All" || city == cityFilter;

        // Aggiunge il posto ai risultati se matchano keyword e città
        if (keywordMatch && cityMatch) {
            results.push_back(place);
        }
    }

    return results;
}

// Pulisce tutti i Place
void PlaceRepository::clear() {
    places.clear();
}

// Fa le statistiche usando il Visitor
StatisticsResult PlaceRepository::computeStatistics() const {
    StatisticsVisitor visitor;
    // Visita ogni posto per raccogliere dati
    for (const auto& p : places) {
        p->acceptVisitor(visitor);
    }

    // Raccoglie i risultati dal visitor
    StatisticsResult res;
    res.totalPlaces     = visitor.totalPlaces();
    res.averageRating = visitor.averageRating();
    res.averageCost     = visitor.averageCost();
    res.countByCity     = visitor.countByCity();
    return res;
}

// Sostituisce un Place esistente con uno nuovo
void PlaceRepository::replacePlace(Place* oldPtr,
                                   const std::shared_ptr<Place>& newPlace)
{
    // Trova il posto da sostituire usando il puntatore grezzo
    auto it = std::find_if(places.begin(), places.end(),
                           [oldPtr](const std::shared_ptr<Place>& p){
                               return p.get() == oldPtr; // Confronta i puntatori grezzi
                           });

    // Se trovato, sostituisce lo shared_ptr
    if (it != places.end())
        *it = newPlace; // Sovrascrive lo shared_ptr esistente con il nuovo
}

// Ritorna tutti i Place
const std::vector<std::shared_ptr<Place>>& PlaceRepository::getAllPlaces() const {
    return places;
}
