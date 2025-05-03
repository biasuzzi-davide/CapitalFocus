#ifndef PLACECONTROLLER_H
#define PLACECONTROLLER_H

#include "../Model/PlaceRepository.h"
#include "../Model/Visitor/placeimportfromxml.h"
#include "../Model/Visitor/PlaceImportFromJson.h"
#include "../../mainwindow.h"
#include "../model/import_errors.h"
#include <memory>
#include <QString>
#include <vector>

class PlaceController : public QObject{
private:
    MainWindow* view;
    PlaceRepository& repository;  // riferimento al model

    PlaceImportFromXml xmlImporter;
    PlaceImportFromJson jsonImporter;


public:
    explicit PlaceController(MainWindow* view, PlaceRepository& repo);

    // Interfacce logiche
    void addPlace(const std::shared_ptr<Place>& place);
    void removePlace(int index);
    std::vector<std::shared_ptr<Place>> search(const QString& keyword, const QString& city = "All") const;
    const std::vector<std::shared_ptr<Place>>& getAll() const;
    void importPlacesFromXml(const QString& filePath);
    void importPlacesFromJson(const QString& filePath);
    void importFromFile();

    void exportToJson(const QString& filePath) const;
    void exportToXml (const QString& filePath) const;
    void printAllPlaces() const;

public slots: // pubblici perchè devono essere visibili quando faccio il connect
    void findPlaces();
    void resetSearchFields();
    void exportToFile();

    void showCreditsPage();
    void setWidgetCredits();
    void setWidgetMain();
    void showStatistics();
    std::map<QString, std::vector<std::shared_ptr<Place>>> groupedSearchResults(const QString& keyword, const QString& city) const;
};

#endif // PLACECONTROLLER_H
