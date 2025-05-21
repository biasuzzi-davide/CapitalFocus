#include "placecontroller.h"
#include "../model/visitor/placeexporttoxmlvisitor.h"
#include "../model/visitor/placeExportToJsonVisitor.h"
#include <QFileInfo>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDomDocument>
#include <QInputDialog>
#include "../model/debugconfig.h"
#include "../model/import_errors.h"
#include "../model/uicommon.h"
#include <view/foodwidget.h>
#include <view/entertainmentwidget.h>
#include <view/shoppingwidget.h>
#include <view/culturewidget.h>
#include <view/createplacewidget.h>

// Funzione helper per ottenere stringa stelle da rating
QString getStarRating(double rating) {
    const QString full = "★";
    const QString empty = "☆";
    QString result;

    int fullStars = static_cast<int>(std::floor(rating));
    int emptyStars = 5 - fullStars;

    result += full.repeated(fullStars); // Aggiunge stelle piene
    result += empty.repeated(emptyStars); // Aggiunge stelle vuote

    return result;
}

// Imposta flag modifiche non salvate
void PlaceController::setUnsavedChanges(bool value) {
    unsavedChanges = value;
}

// Costruttore
PlaceController::PlaceController(MainWindow* v, PlaceRepository& repo)
    : view(v), repository(repo), currentPlace(nullptr) {};

// Aggiunge Place al repository
void PlaceController::addPlace(const std::shared_ptr<Place>& place) {
    repository.addPlace(place);
}

// Rimuove Place dal repository per indice
void PlaceController::removePlace(int index) {
    repository.removePlace(index);
}

// Ritorna Place corrente
Place* PlaceController::getCurrentPlace() const {
    return currentPlace;
}

// Azzera Place corrente
void PlaceController::resetCurrentPlace() {
    currentPlace = nullptr;
}

// Cerca Place nel repository
std::vector<std::shared_ptr<Place>> PlaceController::search(const QString& keyword, const QString& city) const {
    return repository.search(keyword, city);
}

// Ritorna tutti i Place dal repository
const std::vector<std::shared_ptr<Place>>& PlaceController::getAll() const {
    return repository.getAllPlaces();
}

// Importa Place da file XML
void PlaceController::importPlacesFromXml(const QString& filePath){
    try {
        // Importa i Place dal file
        std::vector<std::shared_ptr<Place>> newXmlPlaces = xmlImporter.importFromFile(filePath);

        // Svuota il repository e aggiunge i Place importati
        repository.clear();
        for (const auto& sp : newXmlPlaces)
            repository.addPlace(sp);

        // Aggiorna la View
        view->populateCityComboBox(repository.getAllPlaces());
        auto grouped = groupedSearchResults("", "All");
        view->updateResults(grouped);

        // Gestione eccezioni specifiche di importazione XML
    } catch (const FileOpenError& e) {
        view->showMessage(UiCommon::MsgIcon::Critical,
                          tr("File opening error"),
                          e.what());
    } catch (const XmlParseError& e) {
        view->showMessage(UiCommon::MsgIcon::Critical,
                          tr("XML parsing error"),
                          e.what());
    } catch (const std::exception& e) { // Cattura altre eccezioni generiche
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Invalid data"),
                          e.what());
    }
    setUnsavedChanges(false); // Resetta flag modifiche non salvate dopo import
}

// Importa Place da file JSON
void PlaceController::importPlacesFromJson(const QString& filePath){
    try {
        // Importa i Place dal file
        std::vector<std::shared_ptr<Place>> newJsonPlaces = jsonImporter.importFromJson(filePath);

        // Svuota il repository e aggiunge i Place importati
        repository.clear();
        for (const auto& sp : newJsonPlaces)
            repository.addPlace(sp);

        // Aggiorna la View
        view->populateCityComboBox(repository.getAllPlaces());
        auto grouped = groupedSearchResults("", "All");
        view->updateResults(grouped);

        // Gestione eccezioni specifiche di importazione JSON
    } catch (const FileOpenError& e) {
        view->showMessage(UiCommon::MsgIcon::Critical,
                          tr("File opening error"),
                          e.what());
    } catch (const JsonParseError& e) {
        view->showMessage(UiCommon::MsgIcon::Critical,
                          tr("JSON parsing error"),
                          e.what());
    } catch (const std::exception& e) { // Cattura altre eccezioni generiche
        view->showMessage(UiCommon::MsgIcon::Critical,
                          tr("Invalid data"),
                          e.what());
    }
    setUnsavedChanges(false); // Resetta flag modifiche non salvate dopo import
}

// Gestisce selezione Place nella lista
void PlaceController::onPlaceSelected(QListWidgetItem* item) {
    // Controlla se item è valido e ha dati associati
    if (!item) return;
    QVariant data = item->data(Qt::UserRole);
    if (!data.isValid()) return;

    // Recupera il puntatore al Place dall'item
    auto* place = static_cast<Place*>(data.value<void*>());
    if (!place) return;

    currentPlace = place; // Aggiorna il Place corrente selezionato

    // Determina il tipo di Place e aggiorna il widget di dettaglio appropriato
    if (auto s = dynamic_cast<Shopping*>(place)) {
        DEBUG_LOG("CONTROLLER: APERTURA WIDGET SHOPPING");
        // Ottiene il widget Shopping dalla View e lo aggiorna con i dati
        shoppingwidget* shopping = qobject_cast<shoppingwidget*>(view->getWidgetByName("shopping"));
        if (shopping) {
            shopping->setValues(
                s->getName(), s->getCity(), s->getDescription(),
                getStarRating(s->getRating()) + " (" + QString::number(s->getRating(), 'f', 1) + " / 5)",
                QString::number(s->getCost(), 'f', 1),
                (s->getOpen()).toQStringMultiline(),
                s->isOutdoor() ? "Yes" : "No",
                s->foodAreaPresent() ? "Yes" : "No",
                QString::number(s->getStandNumber())+" stands",
                s->getShoppingSummary());
            setWidgetSafe("shopping"); // Cambia pagina al widget Shopping
        }

    } else if (auto f = dynamic_cast<Food*>(place)) {
        DEBUG_LOG("CONTROLLER: APERTURA WIDGET FOOD");
        // Ottiene il widget Food dalla View e lo aggiorna con i dati
        foodwidget* food = qobject_cast<foodwidget*>(view->getWidgetByName("food"));
        if (food) {
            food->setValues(
                f->getName(), f->getCity(), f->getDescription(),
                getStarRating(f->getRating()) + " (" + QString::number(f->getRating(), 'f', 1) + " / 5)",
                QString::number(f->getCost(), 'f', 1),
                (f->getOpen()).toQStringMultiline(),
                f->hasTakeAway() ? "Yes" : "No",
                f->getAvgWaitingTime().toString("hh:mm"),
                f->hasVeganMenu() ? "Yes" : "No",
                f->getFoodSummary());
            setWidgetSafe("food"); // Cambia pagina al widget Food
        }

    } else if (auto e = dynamic_cast<Entertainment*>(place)) {
        DEBUG_LOG("CONTROLLER: APERTURA WIDGET ENTERTAINMENT");
        // Ottiene il widget Entertainment dalla View e lo aggiorna con i dati
        entertainmentwidget* entertainment = qobject_cast<entertainmentwidget*>(view->getWidgetByName("entertainment"));
        if (entertainment) {
            entertainment->setValues(
                e->getName(), e->getCity(), e->getDescription(),
                getStarRating(e->getRating()) + " (" + QString::number(e->getRating(), 'f', 1) + " / 5)",
                QString::number(e->getCost(), 'f', 1),
                (e->getOpen()).toQStringMultiline(),
                e->getAvgStayDuration().toString("hh:mm"),
                QString::number(e->getMinAge(), 'f', 1), e->getRestrictedEntry(),
                e->getEntertainmentSummary());
            setWidgetSafe("entertainment"); // Cambia pagina al widget Entertainment
        }
    } else if (auto c = dynamic_cast<Culture*>(place)) {
        DEBUG_LOG("CONTROLLER: APERTURA WIDGET CULTURE");
        // Ottiene il widget Culture dalla View e lo aggiorna con i dati
        culturewidget* culture = qobject_cast<culturewidget*>(view->getWidgetByName("culture"));
        if (culture) {
            culture->setValues(
                c->getName(), c->getCity(), c->getDescription(),
                getStarRating(c->getRating()) + " (" + QString::number(c->getRating(), 'f', 1) + " / 5)",
                QString::number(c->getCost(), 'f', 1),
                (c->getOpen()).toQStringMultiline(),
                QString::number(c->getStudentDiscount(), 'f', 1),
                c->hasGuidedTour() ? "Yes" : "No",
                c->getCulturalFocus(),
                c->getCultureSummary());
            setWidgetSafe("culture"); // Cambia pagina al widget Culture
        }
    }
}

// Controlla se ci sono modifiche non salvate
bool PlaceController::hasUnsavedChanges() const {
    return unsavedChanges;
}

// Avvia processo import da file
void PlaceController::importFromFile()
{
    // Chiede conferma se ci sono già Place nel repository
    if (!repository.getAllPlaces().empty()) {
        bool confirmed = view->askConfirmation(
            tr("Import Confirmation"),
            tr("Importing a new file will overwrite all existing places. Do you want to continue?")
            );
        if (!confirmed) {
            // Utente ha annullato
            view->showStatusBarMsg(tr("Import cancelled."), 3000);
            return; // Esce senza importare
        }
    }

    // Chiede all'utente di selezionare un file
    QString path = view->askOpenFile(
        tr("Select file"),
        tr("JSON or XML file (*.json *.xml)")
        );

    // Se l'utente non ha selezionato nessun file, esce
    if (path.isEmpty()) return;

    // Determina il tipo di file dall'estensione e chiama l'importatore corretto
    QString ext = QFileInfo(path).suffix().toLower();
    if (ext == "json")
        importPlacesFromJson(path);
    else if (ext == "xml")
        importPlacesFromXml(path);
    else
        // Mostra messaggio se il formato non è supportato
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Unsupported format"),
                          tr("Select a .json or .xml file"));

    // Aggiorna le statistiche dopo l'importazione
    view->setStats(repository.computeStatistics());
}

// Esporta Place in formato JSON
void PlaceController::exportToJson(const QString& filePath) {
    QJsonArray placesArray;

    for (const auto& place : repository.getAllPlaces()) {
        PlaceExportToJsonVisitor v;
        place->acceptVisitor(v);
        placesArray.append(v.getResult()); // Aggiunge l'oggetto JSON all'array
    }

    QJsonDocument doc(placesArray); // Crea un documento JSON dall'array

    QFile file(filePath); // Apre il file per scrivere
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Mostra errore se non riesce ad aprire il file
        view->showMessage(UiCommon::MsgIcon::Critical,
                          tr("File writing error"),
                          tr("Cannot open file for writing:\n%1").arg(filePath));
        return;
    }
    file.write(doc.toJson(QJsonDocument::Indented)); // Scrive il JSON formattato nel file
    file.close();

    // Mostra messaggi di successo
    view->showStatusBarMsg(
        tr("Exported %1 places to %2")
            .arg(placesArray.size())
            .arg(filePath),8000);
    view->showMessage(UiCommon::MsgIcon::Info,
                      tr("Export completed"),
                      tr("Exported %1 places to\n%2")
                          .arg(placesArray.size())
                          .arg(filePath));
    setUnsavedChanges(false); // Resetta flag modifiche non salvate dopo export
}

// Esporta Place in formato XML
void PlaceController::exportToXml (const QString& filePath) {
    QDomDocument doc("placesDoc"); // Crea un documento XML
    QDomElement root = doc.createElement("places");
    doc.appendChild(root);

    // Itera su tutti i Place nel repository
    for (const auto& place : repository.getAllPlaces()) {
        PlaceExportToXmlVisitor v(doc); // Crea un visitor per ogni Place, passando il documento
        place->acceptVisitor(v); // Fa visitare il Place al visitor
        root.appendChild(v.getResult()); // Aggiunge l'elemento XML del Place al root
    }

    QFile file(filePath); // Apre il file per scrivere
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Mostra errore se non riesce ad aprire il file
        view->showMessage(UiCommon::MsgIcon::Critical,
                          tr("File writing error"),
                          tr("Cannot open file for writing:\n%1").arg(filePath));
        return; // Esce senza scrivere
    }
    file.write(doc.toByteArray(4)); // Scrive il XML formattato, indentandolom, nel file
    file.close(); // Chiude il file

    // Mostra messaggi di successo
    view->showStatusBarMsg(
        tr("Exported %1 places to %2")
            .arg(root.childNodes().count()) // Conta i Place esportati
            .arg(filePath),8000);
    view->showMessage(UiCommon::MsgIcon::Info,
                      tr("Export completed"),
                      tr("Exported %1 places to\n%2")
                          .arg(root.childNodes().count())
                          .arg(filePath));
    setUnsavedChanges(false); // Resetta flag modifiche non salvate dopo export
}

// Azzera i campi di ricerca nella View
void PlaceController::resetSearchFields() {
    view->clearSearchFields();
}

// Esegue la ricerca e aggiorna la lista nella View
void PlaceController::findPlaces() {
    QString keyword = view->getSearchText(); // Ottiene testo ricerca
    QString city = view->getSelectedCity(); // Ottiene città selezionata
    auto groupedResults = groupedSearchResults(keyword, city); // Esegue la ricerca
    view->updateResults(groupedResults); // Aggiorna la lista nella view

    // Calcola il totale dei risultati
    int total = 0;
    for (const auto& pair : groupedResults)
        total += static_cast<int>(pair.second.size());

    // Mostra messaggio di stato con il numero di risultati trovati
    view->showStatusBarMsg(QString("Found %1 place%2")
                               .arg(total)
                               .arg(total == 1 ? "" : "s"), 2000);
}

// Avvia processo export, chiedendo all'utente come gestirlo
void PlaceController::exportToFile()
{
    // Chiede all'utente dove salvare e in quale formato
    QString path = view->askSaveFile(
        tr("Save places"),
        tr("JSON (*.json);;XML (*.xml)")
        );

    // Se l'utente non ha selezionato un percorso esce
    if (path.isEmpty()) return;

    // Determina il formato dal suffisso del file e chiama l'esportatore corretto
    QString ext = QFileInfo(path).suffix().toLower();
    if (ext == "json")
        exportToJson(path);
    else if (ext == "xml")
        exportToXml(path);
    else
        // Mostra messaggio se il formato non è supportato
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Unsupported format"),
                          tr("Choose a .json or .xml file"));
}

// Cambia pagina alla pagina credits
void PlaceController::setWidgetCredits() {
    setWidgetSafe("credits");
}

// Cambia pagina alla pagina principale, assicurandosi che l'utente abbia salvato eventuali modifiche
void PlaceController::setWidgetMain()
{
    if (setWidgetSafe("main"))
        resetCurrentPlace();
}

// Cambia pagina alla pagina di creazione
void PlaceController::setWidgetCreate() {
    setWidgetSafe("create");
}

// Mostra la pagina delle statistiche
void PlaceController::showStatistics() {
    // Calcola le statistiche e le imposta nella View
    view->setStats(repository.computeStatistics());
    setWidgetSafe("statistics");
}

// Raggruppa i risultati della ricerca per categoria
std::map<QString, std::vector<std::shared_ptr<Place>>> PlaceController::groupedSearchResults(const QString& keyword, const QString& city) const {
    std::map<QString, std::vector<std::shared_ptr<Place>>> grouped;
    auto results = repository.search(keyword, city);

    for (const auto& place : results) {
        QString category = place->getCategory();
        grouped[category].push_back(place);
    }

    return grouped;
}

// Chiede all'utente il nome di una pagina e ci naviga (chiedendo di salvare)
void PlaceController::promptAndSetWidget() {
    bool ok;
    // Mostra un input dialog per chiedere il nome della pagina
    QString label = QInputDialog::getText(nullptr, "Vai a pagina",
                                          "Inserisci nome pagina (es. food, culture, main):",
                                          QLineEdit::Normal, "", &ok);
    // Se l'utente ha cliccato OK e inserito un nome non vuoto
    if (ok && !label.isEmpty()) {
        setWidgetSafe(label); // Tenta di cambiare pagina in modo sicuro
    }
}

// Torna alla pagina principale
void PlaceController::goBack() {
    setWidgetMain();
}



// Slot per creare un nuovo Place o salvare le modifiche
void PlaceController::createNewPlace() {
    // Ottiene il widget di creazione
    CreatePlaceWidget* create = qobject_cast<CreatePlaceWidget*>(view->getWidgetByName("create"));
    if (!create) return; // Esce se il widget non è disponibile

    try {
        // Sezione di validazione campi comuni
        if (create->name().isEmpty())
            throw std::invalid_argument("Name cannot be empty");
        if (create->city().isEmpty())
            throw std::invalid_argument("City cannot be empty");
        if (create->rating() < 0.0 || create->rating() > 5.0)
            throw std::invalid_argument("Rating must be between 0.0 and 5.0");
        if (create->cost() < 0.0)
            throw std::invalid_argument("Cost cannot be negative");

        // Sezione di validazione orari settimanali
        for (int i = 0; i < 7; ++i) {
            Weekday day = static_cast<Weekday>(i);
            auto h = create->hours(day);

            if (h.alwaysClosed && h.alwaysOpen) {
                QString dayName = weeklyOpenings::weekdayToString(day);
                throw std::invalid_argument(
                    QString("Invalid opening hours for %1: cannot be both 'Always Open' and 'Always Closed'").arg(dayName).toStdString()
                    );
            }

            if (!h.alwaysClosed && !h.alwaysOpen) {
                if (!h.open.isValid() || !h.close.isValid()) {
                    QString d = weeklyOpenings::weekdayToString(day);
                    throw std::invalid_argument(
                        QString("Invalid opening hours for %1").arg(d).toStdString()
                        );
                }
            }
        }

        // Sezione di validazione per ciascun tipo di Place
        switch (create->getTypeIndex()) {

        // Disco
        case 0: {
            QTime avg = create->averageStay_Disco();
            if (!avg.isValid())
                throw std::invalid_argument("Invalid average stay duration");
            if (create->minimumAge_Disco() < 0)
                throw std::invalid_argument("Minimum age cannot be negative");
            if (create->restrictedEntry_Disco().isEmpty())
                throw std::invalid_argument("Restricted entry must be specified");
            if (create->musicGenre().isEmpty())
                throw std::invalid_argument("Music genre cannot be empty");
            if (create->dressCode().isEmpty())
                throw std::invalid_argument("Dress code cannot be empty");
            break;
        }

        // PanoramicPoint
        case 1: {
            QTime avg = create->averageStay_Panoramic();
            if (!avg.isValid())
                throw std::invalid_argument("Invalid average stay duration");
            if (create->minimumAge_Panoramic() < 0)
                throw std::invalid_argument("Minimum age cannot be negative");
            if (create->restrictedEntry_Panoramic().isEmpty())
                throw std::invalid_argument("Restricted entry must be specified");
            break;
        }

        // Cafe
        case 2: {
            QTime wait = create->averageWaitingTime_Cafe();
            if (!wait.isValid())
                throw std::invalid_argument("Invalid average waiting time");
            if (create->specialDrink().isEmpty())
                throw std::invalid_argument("Signature drink must be specified");
            break;
        }

        // Restaurant
        case 3: {
            QTime wait = create->averageWaitingTime_Restaurant();
            if (!wait.isValid())
                throw std::invalid_argument("Invalid average waiting time");
            if (create->cuisineType().isEmpty())
                throw std::invalid_argument("Cuisine type cannot be empty");
            if (create->specialDish().isEmpty())
                throw std::invalid_argument("Special dish must be specified");
            break;
        }

        // Mall
        case 4: {
            if (create->standNumber_Mall() < 0)
                throw std::invalid_argument("Stand number cannot be negative");
            if (create->shopCount() < 0)
                throw std::invalid_argument("Shop count cannot be negative");
            break;
        }

        // LocalMarket
        case 5: {
            if (create->standNumber_Market() < 0)
                throw std::invalid_argument("Stand number cannot be negative");
            if (create->period().isEmpty())
                throw std::invalid_argument("Period must be specified");
            break;
        }

        // Museum
        case 6: {
            if (create->culturalFocus_Museum().isEmpty())
                throw std::invalid_argument("Cultural focus cannot be empty");
            break;
        }

        // Monument
        case 7: {
            if (create->culturalFocus_Monument().isEmpty())
                throw std::invalid_argument("Cultural focus cannot be empty");
            if (create->conservationStatus().isEmpty())
                throw std::invalid_argument("Conservation status must be specified");
            break;
        }
        default:
            throw std::invalid_argument("Unknown place type"); // Errore: tipo sconosciuto
        }

        // Raccolta dei dati validati
        const bool editing = create->isEditing(); // Controlla se siamo in modalità modifica
        Place* oldRaw = editing ? currentPlace : nullptr; // Puntatore grezzo al vecchio Place se in modifica

        // Raccoglie i dati comuni
        QString name        = create->name();
        QString city        = create->city();
        QString description = create->description();
        double rating       = create->rating();
        double cost         = create->cost();

        // Raccoglie gli orari di apertura
        weeklyOpenings openings;
        for (int i = 0; i < 7; ++i) {
            Weekday day = static_cast<Weekday>(i);
            auto h = create->hours(day);

            if (h.alwaysClosed) {
                openings.setClosed(day);
            } else if (h.alwaysOpen) {
                openings.setAlwaysOpen(day);
            } else {
                openings.setOpening(day, h.open, h.close);
            }
        }

        // Creazione del nuovo Place
        std::shared_ptr<Place> newPlace;
        switch (create->getTypeIndex()) {

        case 0: // Disco
            newPlace = std::make_shared<Disco>(
                name, city, description, rating, openings, cost,
                create->averageStay_Disco(),
                create->minimumAge_Disco(),
                create->restrictedEntry_Disco(),
                create->musicGenre(),
                create->prive(),
                create->dressCode()
                );
            break;

        case 1: // PanoramicPoint
            newPlace = std::make_shared<PanoramicPoint>(
                name, city, description, rating, openings, cost,
                create->averageStay_Panoramic(),
                create->minimumAge_Panoramic(),
                create->restrictedEntry_Panoramic(),
                create->altitude(),
                create->binoculars(),
                create->nightLighting()
                );
            break;

        case 2: // Cafe
            newPlace = std::make_shared<Cafe>(
                name, city, description, rating, openings, cost,
                create->takeAway_Cafe(),
                create->averageWaitingTime_Cafe(),
                create->veganMenu_Cafe(),
                create->terrace(),
                create->specialDrink()
                );
            break;

        case 3: // Restaurant
            newPlace = std::make_shared<Restaurant>(
                name, city, description, rating, openings, cost,
                create->takeAway_Restaurant(),
                create->averageWaitingTime_Restaurant(),
                create->veganMenu_Restaurant(),
                create->cuisineType(),
                create->reservationNeeded(),
                create->specialDish()
                );
            break;

        case 4: // Mall
            newPlace = std::make_shared<Mall>(
                name, city, description, rating, openings, cost,
                create->outdoor_Mall(),
                create->foodArea_Mall(),
                create->standNumber_Mall(),
                create->shopCount(),
                create->cinema(),
                create->freeParking()
                );
            break;

        case 5: // LocalMarket
            newPlace = std::make_shared<LocalMarket>(
                name, city, description, rating, openings, cost,
                create->outdoor_Market(),
                create->foodArea_Market(),
                create->standNumber_Market(),
                create->artisans(),
                create->seasonal(),
                create->period()
                );
            break;

        case 6: // Museum
            newPlace = std::make_shared<Museum>(
                name, city, description, rating, openings, cost,
                create->studentDiscount_Museum(),
                create->guidedTour_Museum(),
                create->culturalFocus_Museum(),
                create->audioGuide()
                );
            break;

        case 7: // Monument
            newPlace = std::make_shared<Monument>(
                name, city, description, rating, openings, cost,
                create->studentDiscount_Monument(),
                create->guidedTour_Monument(),
                create->culturalFocus_Monument(),
                create->unesco(),
                create->conservationStatus(),
                create->openToPublic()
                );
            break;
        }

        // Controllo duplicati
        bool duplicato = false;
        for (const auto& existing : repository.getAllPlaces()) {
            // Salta il controllo se stiamo modificando lo stesso Place
            if (editing && existing.get() == currentPlace) continue;
            // Controlla se esiste già un Place con lo stesso nome e città in modo case insensitive
            if (existing->getName().compare(newPlace->getName(), Qt::CaseInsensitive) == 0 &&
                existing->getCity().compare(newPlace->getCity(), Qt::CaseInsensitive) == 0)
            {
                duplicato = true;
                break;
            }
        }
        // Se trovato un duplicato, mostra messaggio di errore ed esce
        if (duplicato) {
            view->showMessage(UiCommon::MsgIcon::Critical,
                              tr("This place already exists"),
                              tr("A place with the same name and city already exists.\nEdit one of them and retry."));
            return;
        }

        // Salvataggio nel repository
        if (editing && oldRaw){
            repository.replacePlace(oldRaw, newPlace); // Sostituisce se in modifica
        }else{
            repository.addPlace(newPlace); // Aggiunge se in creazione
        }
        setUnsavedChanges(true); // Imposta flag modifiche non salvate

        // Aggiornamento view e reset stato
        resetCurrentPlace();
        create->setEditing(false); // Esce dalla modalità modifica
        view->populateCityComboBox(repository.getAllPlaces()); // Aggiorna combo box città
        view->updateResults(groupedSearchResults("", "All")); // Aggiorna lista risultati
        goBack(); // Torna alla pagina principale
        create->resetFields(); // Pulisce i campi
    }
    // Cattura le eccezioni di validazione e mostra un warning
    catch (const std::invalid_argument& ex) {
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Invalid input"),
                          QString::fromStdString(ex.what()));
    }
    // Cattura eventuali altre eccezioni generiche
    catch (const std::exception& ex) {
        view->showMessage(UiCommon::MsgIcon::Critical,
                          tr("Error"),
                          QString::fromStdString(ex.what()));
    }
}

// Cambia pagina in modo sicuro, chiedendo di salvare se necessario
bool PlaceController::setWidgetSafe(const QString& name)
{
    // Ottiene il widget di creazione
    CreatePlaceWidget* create = qobject_cast<CreatePlaceWidget*>(view->getWidgetByName("create"));
    // Se il widget esiste ed è in modalità modifica
    if (create && create->isEditing()) {
        // Annulla l'editing e ripristina i campi
        create->setEditing(false);
        create->resetFields();
    } else {
        // Se non è il widget di creazione in modifica, controlla se ci sono altri widget in modifica
        if (anyWidgetIsEditing()) {
            view->showMessage(UiCommon::MsgIcon::Warning,
                              tr("Editing in progress"),
                              tr("You are currently editing a place.\n"
                                 "Please save before switching."));
            return false;
        }
    }

    view->showWidgetByName(name); // Cambia la pagina nella view
    return true;
}

// Controlla se il widget di creazione è in modalità modifica
bool PlaceController::anyWidgetIsEditing() const {
    CreatePlaceWidget* create = qobject_cast<CreatePlaceWidget*>(view->getWidgetByName("create"));
    return create && create->isEditing();
}

// Slot per eliminare il place corrente
void PlaceController::deleteCurrentPlace() {
    if (anyWidgetIsEditing()) {
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Editing in progress"),
                          tr("You are currently editing a place.\n"
                             "Please save before delete."));
        return;
    }

    // Controlla se la pagina corrente è una delle pagine non di dettaglio
    QWidget* currentWidget = view->getCurrentPage();
    if (currentWidget == view->getWidgetByName("main") ||
        currentWidget == view->getWidgetByName("credits") ||
        currentWidget == view->getWidgetByName("statistics")) {
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Cannot Delete"),
                          tr("You must open a place detail before deleting it."));
        return;
    }

    // Recupera l'item selezionato dalla lista
    QListWidget* list = view->getListWidget();
    QListWidgetItem* item = list ? list->currentItem() : nullptr;

    // Controlla se un item è selezionato e ha dati place validi
    if (!item || !item->data(Qt::UserRole).isValid()) {
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Invalid Selection"),
                          tr("You must open a place detail before deleting it."));
        return;
    }

    auto* place = static_cast<Place*>(item->data(Qt::UserRole).value<void*>());
    if (!place) return;

    // Chiede conferma all'utente prima di eliminare
    bool reply = view->askConfirmation(
        tr("Confirm Deletion"),
        tr("Are you sure you want to delete this place?"));

    // Se l'utente conferma
    if (reply) {
        const auto& all = repository.getAllPlaces(); // Ottiene tutti i place
        // Trova l'iteratore al Place da eliminare
        auto it = std::find_if(all.begin(), all.end(), [place](const std::shared_ptr<Place>& p) {
            return p.get() == place;
        });

        // Se il place viene trovato viene rimosso
        if (it != all.end()) {
            repository.removePlace(std::distance(all.begin(), it));
            setUnsavedChanges(true);
            findPlaces(); // Aggiorna la lista dei risultati
            goBack();
            view->populateCityComboBox(repository.getAllPlaces()); // Aggiorna
        }
    }
}

// Chiede all'utente dove salvare il file XML ed esporta
void PlaceController::promptExportToXml() {
    QString path = view->askSaveFile(
        tr("Save as XML"),
        tr("XML files (*.xml)")
        );
    if (!path.isEmpty())
        exportToXml(path);
}

// Chiede all'utente dove salvare il file JSON ed esporta
void PlaceController::promptExportToJson() {
    QString path = view->askSaveFile(
        tr("Save as JSON"),
        tr("JSON files (*.json)")
        );
    if (!path.isEmpty())
        exportToJson(path);
}

// Slot per modificare il Place corrente
void PlaceController::editCurrentPlace()
{
    QListWidget* list = view->getListWidget();
    QListWidgetItem* item = list ? list->currentItem() : nullptr;

    // Controlla se un place è selezionato e se non siamo già in una pagina non di dettaglio o creazione
    QWidget* currentWidget = view->getCurrentPage();
    if (!item || !item->data(Qt::UserRole).isValid() ||
        currentWidget == view->getWidgetByName("main") ||
        currentWidget == view->getWidgetByName("credits") ||
        currentWidget == view->getWidgetByName("create") ||
        currentWidget == view->getWidgetByName("statistics"))
    {
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Cannot Edit"),
                          tr("You must open a place detail before editing it."));
        return;
    }

    // Recupera il puntatore al place selezionato
    auto* place = static_cast<Place*>(item->data(Qt::UserRole).value<void*>());
    if (!place) {
        return;
    }

    // Otteniamo il widget
    CreatePlaceWidget* create = qobject_cast<CreatePlaceWidget*>(view->getWidgetByName("create"));
    if (!create) return;

    // Imposta i campi comuni nel widget di creazione
    create->setName(place->getName());
    create->setCity(place->getCity());
    create->setDescription(place->getDescription());
    create->setRating(place->getRating());
    create->setCost(place->getCost());

    const weeklyOpenings& wo = place->getOpen();
    for (int i = 0; i < 7; ++i) {
        Weekday d = static_cast<Weekday>(i);
        CreatePlaceWidget::DayHours dh;
        if (wo.isClosed(d)) {
            dh.alwaysClosed = true;
        } else if (wo.isAlwaysOpen(d)) {
            dh.alwaysOpen = true;
        } else {
            dh.open  = wo.openTime(d);
            dh.close = wo.closeTime(d);
        }
        create->setHours(d, dh); // Imposta gli orari nel widget
    }

    // Determina il tipo di Place e imposta i campi specifici nel widget
    if (auto* d = dynamic_cast<Disco*>(place)) {
        create->setType("Disco");
        create->setAverageStay_Disco(d->getAvgStayDuration());
        create->setMinimumAge_Disco(d->getMinAge());
        create->setRestrictedEntry_Disco(d->getRestrictedEntry());
        create->setMusicGenre(d->getMusicGenre());
        create->setPrive(d->hasPriveAccess());
        create->setDressCode(d->getDressCode());

    } else if (auto* p = dynamic_cast<PanoramicPoint*>(place)) {
        create->setType("PanoramicPoint");
        create->setAverageStay_Panoramic(p->getAvgStayDuration());
        create->setMinimumAge_Panoramic(p->getMinAge());
        create->setRestrictedEntry_Panoramic(p->getRestrictedEntry());
        create->setAltitude(p->getAltitude());
        create->setBinoculars(p->hasBinoculars());
        create->setNightLighting(p->isNightLit());

    } else if (auto* c = dynamic_cast<Cafe*>(place)) {
        create->setType("Cafe");
        create->setTakeAway_Cafe(c->hasTakeAway());
        create->setAverageWaitingTime_Cafe(c->getAvgWaitingTime());
        create->setVeganMenu_Cafe(c->hasVeganMenu());
        create->setTerrace(c->hasTerrace());
        create->setSpecialDrink(c->getSpecialDrink());

    } else if (auto* r = dynamic_cast<Restaurant*>(place)) {
        create->setType("Restaurant");
        create->setTakeAway_Restaurant(r->hasTakeAway());
        create->setAverageWaitingTime_Restaurant(r->getAvgWaitingTime());
        create->setVeganMenu_Restaurant(r->hasVeganMenu());
        create->setCuisineType(r->getCuisineType());
        create->setReservationNeeded(r->hasReservation());
        create->setSpecialDish(r->getSpecialDish());

    } else if (auto* mall = dynamic_cast<Mall*>(place)) {
        create->setType("Mall");
        create->setOutdoor_Mall(mall->isOutdoor());
        create->setFoodArea_Mall(mall->foodAreaPresent());
        create->setStandNumber_Mall(mall->getStandNumber());
        create->setShopCount(mall->getShopCount());
        create->setCinema(mall->hasCinema());
        create->setFreeParking(mall->hasFreeParking());

    } else if (auto* localMarket = dynamic_cast<LocalMarket*>(place)) {
        create->setType("LocalMarket");
        create->setOutdoor_Market(localMarket->isOutdoor());
        create->setFoodArea_Market(localMarket->foodAreaPresent());
        create->setStandNumber_Market(localMarket->getStandNumber());
        create->setArtisans(localMarket->hasArtisans());
        create->setSeasonal(localMarket->isSeasonal());
        create->setPeriod(localMarket->getPeriod());

    } else if (auto* mus = dynamic_cast<Museum*>(place)) {
        create->setType("Museum");
        create->setStudentDiscount_Museum(mus->getStudentDiscount());
        create->setGuidedTour_Museum(mus->hasGuidedTour());
        create->setCulturalFocus_Museum(mus->getCulturalFocus());
        create->setAudioGuide(mus->hasAudioGuideAvailable());

    } else if (auto* mon = dynamic_cast<Monument*>(place)) {
        create->setType("Monument");
        create->setStudentDiscount_Monument(mon->getStudentDiscount());
        create->setGuidedTour_Monument(mon->hasGuidedTour());
        create->setCulturalFocus_Monument(mon->getCulturalFocus());
        create->setUnesco(mon->isUnesco());
        create->setConservationStatus(mon->getConservationStatus());
        create->setOpenToPublic(mon->isOpenToPublic());
    }

    create->setEditing(true); // Imposta il widget in modalità modifica
    view->showWidgetByName("create"); // Mostra il widget di creazione
}

// Attiva/disattiva modalità debug e aggiorna view
void PlaceController::toggleDebug(){
    bool current = DebugConfig::isEnabled(); // Ottiene stato attuale
    DebugConfig::setEnabled(!current); // Imposta stato opposto

    view->updateDebugActionText(!current);

    // Mostra messaggio di stato
    view->showMessage(UiCommon::MsgIcon::Info,
                      tr("Debug Mode"),
                      current ? tr("Debug mode deactivated.")
                              : tr("Debug mode activated."));
}

// Gestisce cambio tipo place nel widget creazione
void PlaceController::onCreateTypeChanged(int idx)
{
    // Ottiene il widget di creazione e mostra il dettaglio corretto
    auto *create = qobject_cast<CreatePlaceWidget*>(view->getWidgetByName("create"));
    if (create) create->showDetailPage(idx);
}

// Attiva/disattiva dark mode nella View
void PlaceController::toggleDarkMode(){
    view->toggleDarkMode(!(view->getDarkModeEnabled()));
}

// Controlla se l'applicazione può essere chiusa
bool PlaceController::canClose()
{
    if (!hasUnsavedChanges())
        return true;

    // Chiede conferma se modifiche non salvate
    return view->askConfirmation(
        tr("Unsaved Changes"),
        tr("You have unsaved changes. Do you really want to exit without saving?")
        );
}
