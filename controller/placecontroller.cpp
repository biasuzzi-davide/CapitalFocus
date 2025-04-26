#include "PlaceController.h"
#include <QFileDialog>

PlaceController::PlaceController(MainWindow* v, PlaceRepository& repo)
    : view(v), repository(repo) {};

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
    printAllPlaces();
}
void PlaceController::printAllPlaces() const {
    const auto& all = repository.getAllPlaces();

    qDebug() << "=== Elenco luoghi attualmente presenti ===";

    for (const auto& place : all) {
        // Se hai un metodo getCategory(), lo puoi includere
        qDebug() << "- " << place->getName()
                 << "(" << place->getCity() << ")";
    }

    qDebug() << "Totale:" << all.size() << "luoghi.";
}
void PlaceController::importFromXml() {
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Seleziona file XML", "", "File XML (*.xml)");
    if (!filePath.isEmpty()) {
        std::vector<Place*> rawPlaces = importer.importFromFile(filePath);

        for (Place* p : rawPlaces) {
            repository.addPlace(std::shared_ptr<Place>(p));  // ✅ conversione sicura
        }
        view->populateCityComboBox(repository.getAllPlaces());  // 👈 chiamata qui
        qDebug() << "Luoghi totali in repository:" << repository.getAllPlaces().size();
        //findPlaces();  // chiama subito per aggiornare la view
    }
}
void PlaceController::resetSearchFields() {
    view->clearSearchFields();  // se la view ha questo metodo
}

void PlaceController::findPlaces() {
    QString keyword = view->getSearchText();
    QString city = view->getSelectedCity();

    auto results = repository.search(keyword, city);  // qui city può essere "Tutte"
    qDebug() << "KW: " << keyword << " CTY: " << city << " N: " << results.size();

    view->updateResults(results);
}
