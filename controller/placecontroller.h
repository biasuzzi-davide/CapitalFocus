#ifndef PLACECONTROLLER_H
#define PLACECONTROLLER_H

#include "../model/placerepository.h"
#include "../model/visitor/placeimportfromxml.h"
#include "../model/visitor/PlaceImportFromJson.h"
#include "view/mainwindow.h"
#include <memory>
#include <QObject>
#include <QString>
#include <vector>

// Dichiarazioni forward
class QListWidgetItem;
class MainWindow;
class Place;

// Il Controller, gestisce la logica e coordina Model e View
class PlaceController : public QObject{
    Q_OBJECT

private:
    MainWindow* view; // Puntatore alla View
    PlaceRepository& repository; // Riferimento al Model
    PlaceImportFromXml xmlImporter; // Importatore XML
    PlaceImportFromJson jsonImporter; // Importatore JSON
    Place* currentPlace = nullptr; // Il posto attualmente selezionato
    bool unsavedChanges = false; // Flag per modifiche non salvate

public:
    // Costruttore
    explicit PlaceController(MainWindow* view, PlaceRepository& repo);

    // Metodi per interagire con il Model
    void addPlace(const std::shared_ptr<Place>& place);
    void removePlace(int index);
    std::vector<std::shared_ptr<Place>> search(const QString& keyword, const QString& city = "All") const;

    // Metodi per interagire con la View
    bool setWidgetSafe(const QString& name); // Cambia widget in modo sicuro
    void showCreditsPage(); // Mostra pagina credits
    std::map<QString, std::vector<std::shared_ptr<Place>>> groupedSearchResults(const QString& keyword, const QString& city) const; // Raggruppa risultati ricerca
    bool anyWidgetIsEditing() const; // Controlla se qualche widget è in modalità modifica

    // Import/Export
    void importFromFile(); // Avvia processo import da file
    void importPlacesFromXml(const QString& filePath); // Importa da XML
    void importPlacesFromJson(const QString& filePath); // Importa da JSON
    void promptExportToXml(); // Chiede dove esportare in XML
    void promptExportToJson(); // Chiede dove esportare in JSON
    void exportToFile(); // Avvia processo export
    void exportToJson(const QString& filePath); // Esporta in JSON
    void exportToXml(const QString& filePath); // Esporta in XML

    // Navigazione e gestione widget
    void setWidgetCreate(); // Va alla pagina creazione
    void setWidgetMain(); // Va alla pagina principale
    void setWidgetCredits(); // Va alla pagina credits
    void showStatistics(); // Mostra pagina statistiche
    void goBack(); // Torna indietro
    void promptAndSetWidget(); // Chiede di salvare e poi cambia widget
    void onCreateTypeChanged(int index); // Gestisce cambio tipo in pagina creazione

    // Ricerca e selezione
    void findPlaces(); // Esegue la ricerca e aggiorna la lista
    void resetSearchFields(); // Azzera i campi di ricerca
    void onPlaceSelected(QListWidgetItem* item); // Gestisce selezione Place nella lista

    // Altre azioni GUI
    void toggleDarkMode(); // Attiva/disattiva dark mode
    void toggleDebug(); // Attiva/disattiva debug

    // Gestione stato
    bool canClose(); // Controlla se l'applicazione può chiudere
    bool hasUnsavedChanges() const; // Controlla se ci sono modifiche non salvate
    void setUnsavedChanges(bool value); // Imposta lo stato delle modifiche non salvate

    // Getter
    Place* getCurrentPlace() const; // Ritorna il Place corrente
    void resetCurrentPlace(); // Azzera il Place corrente
    const std::vector<std::shared_ptr<Place>>& getAll() const; // Ritorna tutti i Place dal repository

public slots:
    // Slot per azioni attivate dalla View
    void createNewPlace(); // Crea un nuovo Place
    void editCurrentPlace(); // Modifica il Place corrente
    void deleteCurrentPlace(); // Elimina il Place corrente
};

#endif // PLACECONTROLLER_H
