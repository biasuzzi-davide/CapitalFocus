#include "PlaceRepository.h"

void PlaceRepository::addPlace(const std::shared_ptr<Place>& place) {
    places.push_back(place);
}

// Uso sharedptr perchè fanno gestione automatica della memoria e più oggetti possono usare lo stesso place
void PlaceRepository::removePlace(int index) {
    if (index >= 0 && index < static_cast<int>(places.size())) {
        places.erase(places.begin() + index);
    }
}

const std::vector<std::shared_ptr<Place>>& PlaceRepository::getAllPlaces() const {
    return places;
}

std::vector<std::shared_ptr<Place>> PlaceRepository::search(const QString& nameKeyword, const QString& cityFilter) const {
    std::vector<std::shared_ptr<Place>> results;
    for (const auto& place : places) {
        bool nameMatch = nameKeyword.isEmpty() || place->getName().contains(nameKeyword, Qt::CaseInsensitive);
        bool cityMatch = cityFilter == "All" || place->getCity() == cityFilter;

        if (nameMatch && cityMatch) {
            results.push_back(place);
        }
    }
    return results;
}

void PlaceRepository::clear() {
    places.clear();
}
