#ifndef PLACEREPOSITORY_H
#define PLACEREPOSITORY_H

#include <vector>
#include <memory>
#include <QString>
#include "Place.h"

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
    std::vector<std::shared_ptr<Place>> search(const QString& nameKeyword, const QString& cityFilter = "Tutte") const;

    // Pulisce tutti i Place
    void clear();
};

#endif // PLACEREPOSITORY_H
