#include "PlaceController.h"

PlaceController::PlaceController(PlaceRepository& repo)
    : repository(repo) {}

void PlaceController::addPlace(const std::shared_ptr<Place>& place) {
    repository.addPlace(place);
}

void PlaceController::removePlace(int index) {
    repository.removePlace(index);
}

std::vector<std::shared_ptr<Place>> PlaceController::search(const QString& keyword, const QString& city) const {
    return repository.search(keyword, city);
}

const std::vector<std::shared_ptr<Place>>& PlaceController::getAll() const {
    return repository.getAllPlaces();
}

void PlaceController::importPlacesFromXml(const QString& filePath) {
    std::vector<Place*> rawPlaces = importer.importFromFile(filePath);

    for (Place* p : rawPlaces) {
        repository.addPlace(std::shared_ptr<Place>(p));  // conversione sicura
    }

    qDebug() << "Importati" << rawPlaces.size() << "luoghi da XML.";
}
