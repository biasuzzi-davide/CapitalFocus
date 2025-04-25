#ifndef PLACECONTROLLER_H
#define PLACECONTROLLER_H

#include "../Model/PlaceRepository.h"
#include "../Model/Visitor/placeimportfromxml.h"
#include <memory>
#include <QString>
#include <vector>

class PlaceController {
private:
    PlaceRepository& repository;  // riferimento al model
    PlaceImportFromXml importer;


public:
    explicit PlaceController(PlaceRepository& repo);

    // Interfacce logiche
    void addPlace(const std::shared_ptr<Place>& place);
    void removePlace(int index);
    std::vector<std::shared_ptr<Place>> search(const QString& keyword, const QString& city = "Tutte") const;

    const std::vector<std::shared_ptr<Place>>& getAll() const;
    void importPlacesFromXml(const QString& filePath);

};

#endif // PLACECONTROLLER_H
