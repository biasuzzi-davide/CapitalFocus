#ifndef PLACEREPOSITORY_H
#define PLACEREPOSITORY_H

#include <vector>
#include <memory>
#include <QString>
#include "Place.h"
#include "statisticsResult.h"

// Gestisce la collezione di Place
class PlaceRepository {
private:
    std::vector<std::shared_ptr<Place>> places; // La lista dei posti

public:
    // Aggiunge un Place
    void addPlace(const std::shared_ptr<Place>& place);

    // Rimuove un Place per indice
    void removePlace(int index);

    // Ricerca Place per nome, città o descrizione
    std::vector<std::shared_ptr<Place>> search(const QString& nameKeyword, const QString& cityFilter = "All") const;

    // Pulisce tutti i Place
    void clear();

    // Fa le statistiche
    StatisticsResult computeStatistics() const;

    // Sostituisce un Place esistente
    void replacePlace(Place* oldPtr, const std::shared_ptr<Place>& newPlace);

    // Getter
    const std::vector<std::shared_ptr<Place>>& getAllPlaces() const;
};

#endif // PLACEREPOSITORY_H
