#ifndef PLACECONTROLLER_H
#define PLACECONTROLLER_H

#include "../Model/PlaceRepository.h"
#include "../Model/Visitor/placeimportfromxml.h"
#include "../../mainwindow.h"
#include <memory>
#include <QString>
#include <vector>

class PlaceController : public QObject{
private:
    MainWindow* view;
    PlaceRepository& repository;  // riferimento al model
    PlaceImportFromXml importer;


public:
    explicit PlaceController(MainWindow* view, PlaceRepository& repo);

    // Interfacce logiche
    void addPlace(const std::shared_ptr<Place>& place);
    void removePlace(int index);
    std::vector<std::shared_ptr<Place>> search(const QString& keyword, const QString& city = "Tutte") const;

    const std::vector<std::shared_ptr<Place>>& getAll() const;
    void importPlacesFromXml(const QString& filePath);
    void printAllPlaces() const;
public slots: // pubblici perchè devono essere visibili quando faccio il connect
    void findPlaces();
    void importFromXml();
    void resetSearchFields();
};

#endif // PLACECONTROLLER_H
