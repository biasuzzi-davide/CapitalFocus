#ifndef PLACECONTROLLER_H
#define PLACECONTROLLER_H

#include "../model/placerepository.h"
#include "../../model/visitor/placeimportfromxml.h"
#include "../../model/visitor/PlaceImportFromJson.h"
#include "view/mainwindow.h"
#include <memory>
#include <QObject>
#include <QString>
#include <vector>

class QListWidgetItem;
class MainWindow;
class Place;

class PlaceController : public QObject{
    Q_OBJECT

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

        void printAllPlaces() const;
        bool setWidgetSafe(const QString& name);
        void showCreditsPage();
        std::map<QString, std::vector<std::shared_ptr<Place>>> groupedSearchResults(const QString& keyword, const QString& city) const;
        bool anyWidgetIsEditing() const;

        // import/export
        void importFromFile();
        void importPlacesFromXml(const QString& filePath);
        void importPlacesFromJson(const QString& filePath);
        void promptExportToXml();
        void promptExportToJson();
        void exportToFile();
        void exportToJson(const QString& filePath) const;
        void exportToXml(const QString& filePath) const;

        void setWidgetCreate();
        void setWidgetMain();
        void setWidgetCredits();
        void showStatistics();
        void goBack();
        void promptAndSetWidget();
        void onCreateTypeChanged(int index);

        void findPlaces();
        void resetSearchFields();
        void onPlaceSelected(QListWidgetItem* item);

        void toggleDebug();
    public slots:
        void createNewPlace();
        void editCurrentPlace();
        void deleteCurrentPlace();

    };

#endif // PLACECONTROLLER_H
