#ifndef PLACEREPOSITORY_H
#define PLACEREPOSITORY_H

#include <vector>
#include <memory>
#include <QString>
#include "Place.h"
#include "statisticsResult.h"


class PlaceRepository {
private:
    std::vector<std::shared_ptr<Place>> places;

public:
    // Aggiunge un nuovo Place
    void addPlace(const std::shared_ptr<Place>& place);

    // Rimuove un Place per indice (se valido)
    void removePlace(int index);

    // Ritorna tutti i Place
    const std::vector<std::shared_ptr<Place>>& getAllPlaces() const;

    // Ricerca Place per nome e/o città
    std::vector<std::shared_ptr<Place>> search(const QString& nameKeyword, const QString& cityFilter = "All") const;

    // Pulisce tutti i Place
    void clear();

    // Fa le statistiche
    StatisticsResult computeStatistics() const;

    void replacePlace(Place* oldPtr, const std::shared_ptr<Place>& newPlace);

};

#endif // PLACEREPOSITORY_H
