#ifndef PLACECONTROLLER_H
#define PLACECONTROLLER_H

#include "../model/placerepository.h"
#include "../../model/visitor/placeimportfromxml.h"
#include "../../model/visitor/PlaceImportFromJson.h"
#include "../../mainwindow.h"
#include <memory>
#include <QString>
#include <vector>

class PlaceController : public QObject{
private:
    MainWindow* view;
    PlaceRepository& repository;
    PlaceImportFromXml xmlImporter;
    PlaceImportFromJson jsonImporter;
    Place* currentPlace = nullptr;
public:
    explicit PlaceController(MainWindow* view, PlaceRepository& repo);
    Place* getCurrentPlace() const;      // restituisce il Place corrente o nullptr
    void   resetCurrentPlace();          // azzera la variabile
    void addPlace(const std::shared_ptr<Place>& place);
    void removePlace(int index);
    std::vector<std::shared_ptr<Place>> search(const QString& keyword, const QString& city = "All") const;
    const std::vector<std::shared_ptr<Place>>& getAll() const;
    void importPlacesFromXml(const QString& filePath);
    void importPlacesFromJson(const QString& filePath);
    void importFromFile();
    void promptAndSetWidget(); // METODO DI DEBUG
    void exportToJson(const QString& filePath) const;
    void exportToXml (const QString& filePath) const;
    void printAllPlaces() const;
    bool setWidgetSafe(const QString& name);
    void findPlaces();
    void resetSearchFields();
    void exportToFile();
    void onPlaceSelected(QListWidgetItem* item);
    void showCreditsPage();
    void setWidgetCredits();
    void setWidgetMain();
    void showStatistics();
    void goBack();
    void editCurrentPlace();
    void deleteCurrentPlace();
    std::map<QString, std::vector<std::shared_ptr<Place>>> groupedSearchResults(const QString& keyword, const QString& city) const;
    void promptExportToXml();
    void promptExportToJson();
    bool anyWidgetIsEditing() const;
    void toggleDebug();
    void createNewPlace();
    void setWidgetCreate();
    void onCreateTypeChanged(int index);
};

#endif // PLACECONTROLLER_H
