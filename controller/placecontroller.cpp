#include "placecontroller.h"
#include "../model/visitor/placeexporttoxmlvisitor.h"
#include "../model/visitor/placeExportToJsonVisitor.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDomDocument>
#include "../model/debugconfig.h"
#include "../model/import_errors.h"
#include "../model/uicommon.h"
#include <foodwidget.h>
#include <entertainmentwidget.h>
#include <shoppingwidget.h>
#include <culturewidget.h>
#include <view/createplacewidget.h>

PlaceController::PlaceController(MainWindow* v, PlaceRepository& repo)
    : view(v), repository(repo), currentPlace(nullptr) {};

void PlaceController::addPlace(const std::shared_ptr<Place>& place) {
    repository.addPlace(place);
}

void PlaceController::removePlace(int index) {
    repository.removePlace(index);
}
Place* PlaceController::getCurrentPlace() const {
    return currentPlace;
}

void PlaceController::resetCurrentPlace() {
    currentPlace = nullptr;
}

std::vector<std::shared_ptr<Place>> PlaceController::search(const QString& keyword, const QString& city) const {
    return repository.search(keyword, city);
}

const std::vector<std::shared_ptr<Place>>& PlaceController::getAll() const {
    return repository.getAllPlaces();
}

void PlaceController::importPlacesFromXml(const QString& filePath){
    try {
        std::vector<std::shared_ptr<Place>> newXmlPlaces = xmlImporter.importFromFile(filePath);

        repository.clear();
        for (const auto& sp : newXmlPlaces)
            repository.addPlace(sp);

        view->populateCityComboBox(repository.getAllPlaces());
        auto grouped = groupedSearchResults("", "All");
        view->updateResults(grouped);


    } catch (const FileOpenError& e) {
        QMessageBox::critical(view, tr("File opening error"), e.what());
    } catch (const XmlParseError& e) {
        QMessageBox::critical(view, tr("XML parsing error"), e.what());
    } catch (const std::exception& e) {
        QMessageBox::warning(view, tr("Invalid data"), e.what());
    }
}

void PlaceController::importPlacesFromJson(const QString& filePath){
    try {
        std::vector<std::shared_ptr<Place>> newJsonPlaces = jsonImporter.importFromJson(filePath);

        repository.clear();
        for (const auto& sp : newJsonPlaces)
            repository.addPlace(sp);

        view->populateCityComboBox(repository.getAllPlaces());
        auto grouped = groupedSearchResults("", "All");
        view->updateResults(grouped);

    // Sono stati tolti
    } catch (const FileOpenError& e) {
        view->showMessage(UiCommon::MsgIcon::Critical, tr("File opening error"), e.what());
    } catch (const JsonParseError& e) {
        view->showMessage(UiCommon::MsgIcon::Critical, tr("JSON parsing error"), e.what());
    } catch (const std::exception& e) {
        view->showMessage(UiCommon::MsgIcon::Critical, tr("Invalid data"), e.what());
    }
}

void PlaceController::onPlaceSelected(QListWidgetItem* item) {
    if (!item) return;

    QVariant data = item->data(Qt::UserRole);
    if (!data.isValid()) return;

    auto* place = static_cast<Place*>(data.value<void*>());
    if (!place) return;
    currentPlace = place;         // <-- aggiorna sempre il riferimento al place attuale
    QWidget* widget = nullptr;

    if (auto s = dynamic_cast<Shopping*>(place)) {
        DEBUG_LOG("CONTROLLER: APERTURA WIDGET SHOPPING");
        shoppingwidget* shopping = qobject_cast<shoppingwidget*>(view->getWidgetByName("shopping"));
        if (shopping) {
            shopping->setValues(
                s->getName(),
                s->getCity(),
                s->getDescription(),
                QString::number(s->getRating(), 'f', 1)+" ☆ / 5 ☆",
                QString::number(s->getCost(), 'f', 1),
                (s->getOpen()).toQStringMultiline(),
                s->isOutdoor() ? "Yes" : "No",
                s->foodAreaPresent() ? "Yes" : "No",
                QString::number(s->getStandNumber())+" stands",
                s->getShoppingSummary());
            setWidgetSafe("shopping");
        }

    } else if (auto f = dynamic_cast<Food*>(place)) {
        DEBUG_LOG("CONTROLLER: APERTURA WIDGET FOOD");
        foodwidget* food = qobject_cast<foodwidget*>(view->getWidgetByName("food"));
        if (food) {
            food->setValues(
                f->getName(),
                f->getCity(),
                f->getDescription(),
                QString::number(f->getRating(), 'f', 1)+" ☆ / 5 ☆",
                QString::number(f->getCost(), 'f', 1),
                (f->getOpen()).toQStringMultiline(),
                f->hasTakeAway() ? "Yes" : "No",
                f->getAvgWaitingTime().toString("hh:mm"),
                f->hasVeganMenu() ? "Yes" : "No",
                f->getFoodSummary());
            setWidgetSafe("food");
        }

    } else if (auto e = dynamic_cast<Entertainment*>(place)) {
        DEBUG_LOG("CONTROLLER: APERTURA WIDGET ENTERTAINMENT");
        entertainmentwidget* entertainment = qobject_cast<entertainmentwidget*>(view->getWidgetByName("entertainment"));
        if (entertainment) {
            entertainment->setValues(
                e->getName(),
                e->getCity(),
                e->getDescription(),
                QString::number(e->getRating(), 'f', 1)+" ☆ / 5 ☆",
                QString::number(e->getCost(), 'f', 1),
                (e->getOpen()).toQStringMultiline(),
                e->getAvgStayDuration().toString("hh:mm"),
                QString::number(e->getMinAge(), 'f', 1),    e->getRestrictedEntry(),
                e->getEntertainmentSummary());
            setWidgetSafe("entertainment");
        }
    } else if (auto c = dynamic_cast<Culture*>(place)) {
        DEBUG_LOG("CONTROLLER: APERTURA WIDGET CULTURE");
        culturewidget* culture = qobject_cast<culturewidget*>(view->getWidgetByName("culture"));
        if (culture) {
            culture->setValues(
                c->getName(),
                c->getCity(),
                c->getDescription(),
                QString::number(c->getRating(), 'f', 1)+" ☆ / 5 ☆",
                QString::number(c->getCost(), 'f', 1),
                (c->getOpen()).toQStringMultiline(),
                QString::number(c->getStudentDiscount(), 'f', 1),
                c->hasGuidedTour() ? "Yes" : "No",
                c->getCulturalFocus(),
                c->getCultureSummary());
            setWidgetSafe("culture");

        }
    }

    if (widget)
        view->setDetailsWidget(widget);
}

void PlaceController::importFromFile()
{
    QString path = view->askOpenFile(tr("Select file"),
                                     tr("JSON or XML file (*.json *.xml)"));
    if (path.isEmpty()) return;

    QString ext = QFileInfo(path).suffix().toLower();
    if (ext == "json")
        importPlacesFromJson(path);
    else if (ext == "xml")
        importPlacesFromXml(path);
    else
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Unsupported format"),
                          tr("Select a .json or .xml file"));
}

void PlaceController::exportToJson(const QString& filePath) const {
    QJsonArray placesArray;

    for (const auto& place : repository.getAllPlaces()) {
        PlaceExportToJsonVisitor v;
        place->acceptVisitor(v);
        placesArray.append(v.getResult());
    }

    QJsonDocument doc(placesArray);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        view->showMessage(UiCommon::MsgIcon::Critical,
                                                   tr("File writing error"),
                                                    tr("Cannot open file for writing:\n%1").arg(filePath));        return;
    }
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    view->showMessage(UiCommon::MsgIcon::Info,
                                            tr("Export completed"),
                                            tr("Exported %1 places to\n%2")
                                                    .arg(placesArray.size())
                                                    .arg(filePath));}

void PlaceController::exportToXml (const QString& filePath) const {
    QDomDocument doc("placesDoc");
    QDomElement root = doc.createElement("places");
    doc.appendChild(root);

    for (const auto& place : repository.getAllPlaces()) {
        PlaceExportToXmlVisitor v(doc); // passa il QDomDocument
        place->acceptVisitor(v);
        root.appendChild(v.getResult()); // aggiunge nodi
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        view->showMessage(UiCommon::MsgIcon::Critical,
                          tr("File writing error"),
                          tr("Cannot open file for writing:\n%1").arg(filePath));
        return;
    }
    file.write(doc.toByteArray(4)); // aggiunta spazi di indentazione
    file.close();

    view->showMessage(UiCommon::MsgIcon::Info,
                      tr("Export completed"),
                      tr("Exported %1 places to\n%2")
                          .arg(root.childNodes().count())
                          .arg(filePath));}

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

void PlaceController::resetSearchFields() {
    view->clearSearchFields();  // se la view ha questo metodo
}

void PlaceController::findPlaces() {
    QString keyword = view->getSearchText();
    QString city = view->getSelectedCity();
    auto groupedResults = groupedSearchResults(keyword, city);
    view->updateResults(groupedResults);
}

void PlaceController::exportToFile()
{
    QString path = QFileDialog::getSaveFileName(
        view,
        tr("Save places"),
        "",
        tr("JSON (*.json);;XML (*.xml)"));

    if (path.isEmpty()) return;

    QString ext = QFileInfo(path).suffix().toLower();
    if (ext == "json")
        exportToJson(path);
    else if (ext == "xml")
        exportToXml(path);
    else
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Unsupported format"),
                          tr("Choose a .json or .xml file"));}

void PlaceController::setWidgetCredits() {
    setWidgetSafe("credits");
}
void PlaceController::setWidgetMain()
{
    if (setWidgetSafe("main"))          // pagina cambiata con successo?
        resetCurrentPlace();            // allora posso azzerare
}
void PlaceController::setWidgetCreate() {
    setWidgetSafe("create");
}
void PlaceController::showStatistics() {
    StatisticsResult stats = repository.computeStatistics();
    setWidgetSafe("statistics");
}

std::map<QString, std::vector<std::shared_ptr<Place>>> PlaceController::groupedSearchResults(const QString& keyword, const QString& city) const {
    std::map<QString, std::vector<std::shared_ptr<Place>>> grouped;
    auto results = repository.search(keyword, city);

    for (const auto& place : results) {
        QString category = place->getCategory();
        grouped[category].push_back(place);
    }

    return grouped;
}
#include <QInputDialog>
#include "mainwindow.h"

void PlaceController::promptAndSetWidget() { // ATTENZIONE, FUNZIONE DI DEBUG DI UTILITA, non rispetta pattern MVC e gestisce label autonomamente
    bool ok;
    QString label = QInputDialog::getText(nullptr, "Vai a pagina",
                                          "Inserisci nome pagina (es. food, culture, main):",
                                          QLineEdit::Normal, "", &ok);
    if (ok && !label.isEmpty()) {
        setWidgetSafe(label);
    }
}
void PlaceController::goBack() {
    setWidgetMain();
}

void PlaceController::createNewPlace() {
    CreatePlaceWidget* create = qobject_cast<CreatePlaceWidget*>(view->getWidgetByName("create"));
    if (!create) return;

    try {
        // 1) Validazione campi comuni
        if (create->name().isEmpty())
            throw std::invalid_argument("Name cannot be empty");
        if (create->city().isEmpty())
            throw std::invalid_argument("City cannot be empty");
        if (create->rating() < 0.0 || create->rating() > 5.0)
            throw std::invalid_argument("Rating must be between 0.0 and 5.0");
        if (create->cost() < 0.0)
            throw std::invalid_argument("Cost cannot be negative");

        // 1.b) Validazione orari settimanali
        for (int i = 0; i < 7; ++i) {
            Weekday day = static_cast<Weekday>(i);
            auto h = create->hours(day);
            if (!h.alwaysClosed && !h.alwaysOpen) {
                if (!h.open.isValid() || !h.close.isValid() || h.open >= h.close) {
                    QString d = weeklyOpenings::weekdayToString(day);
                    throw std::invalid_argument(
                        QString("Invalid opening hours for %1").arg(d).toStdString()
                        );
                }
            }
        }

        // 2) Validazione specifica per ciascun tipo
        switch (create->getTypeIndex()) {
        case 0: { // Disco
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
        case 1: { // PanoramicPoints
            QTime avg = create->averageStay_Panoramic();
            if (!avg.isValid())
                throw std::invalid_argument("Invalid average stay duration");
            if (create->minimumAge_Panoramic() < 0)
                throw std::invalid_argument("Minimum age cannot be negative");
            if (create->restrictedEntry_Panoramic().isEmpty())
                throw std::invalid_argument("Restricted entry must be specified");
            break;
        }
        case 2: { // Cafe
            QTime wait = create->averageWaitingTime_Cafe();
            if (!wait.isValid())
                throw std::invalid_argument("Invalid average waiting time");
            if (create->specialDrink().isEmpty())
                throw std::invalid_argument("Signature drink must be specified");
            break;
        }
        case 3: { // Restaurant
            QTime wait = create->averageWaitingTime_Restaurant();
            if (!wait.isValid())
                throw std::invalid_argument("Invalid average waiting time");
            if (create->cuisineType().isEmpty())
                throw std::invalid_argument("Cuisine type cannot be empty");
            if (create->specialDish().isEmpty())
                throw std::invalid_argument("Special dish must be specified");
            break;
        }
        case 4: { // Mall
            if (create->standNumber_Mall() < 0)
                throw std::invalid_argument("Stand number cannot be negative");
            if (create->shopCount() < 0)
                throw std::invalid_argument("Shop count cannot be negative");
            break;
        }
        case 5: { // LocalMarket
            if (create->standNumber_Market() < 0)
                throw std::invalid_argument("Stand number cannot be negative");
            if (create->period().isEmpty())
                throw std::invalid_argument("Period must be specified");
            break;
        }
        case 6: { // Museum
            if (create->culturalFocus_Museum().isEmpty())
                throw std::invalid_argument("Cultural focus cannot be empty");
            break;
        }
        case 7: { // Monument
            if (create->culturalFocus_Monument().isEmpty())
                throw std::invalid_argument("Cultural focus cannot be empty");
            if (create->conservationStatus().isEmpty())
                throw std::invalid_argument("Conservation status must be specified");
            break;
        }
        default:
            throw std::invalid_argument("Unknown place type");
        }

        // 3) Raccolta dati (già validati)
        const bool editing = create->isEditing();
        Place* oldRaw = editing ? currentPlace : nullptr;

        QString name        = create->name();
        QString city        = create->city();
        QString description = create->description();
        double rating       = create->rating();
        double cost         = create->cost();

        weeklyOpenings openings;
        for (int i = 0; i < 7; ++i) {
            Weekday d = static_cast<Weekday>(i);
            auto h = create->hours(d);
            if (h.alwaysClosed) openings.setClosed(d);
            else                openings.setOpening(d, h.open, h.close);
        }

        // 4) Creazione del Place
        std::shared_ptr<Place> newPlace;
        switch (create->getTypeIndex()) {
        case 0:
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
        case 1:
            newPlace = std::make_shared<PanoramicPoints>(
                name, city, description, rating, openings, cost,
                create->averageStay_Panoramic(),
                create->minimumAge_Panoramic(),
                create->restrictedEntry_Panoramic(),
                create->altitude(),
                create->binoculars(),
                create->nightLighting()
                );
            break;
        case 2:
            newPlace = std::make_shared<Cafe>(
                name, city, description, rating, openings, cost,
                create->takeAway_Cafe(),
                create->averageWaitingTime_Cafe(),
                create->veganMenu_Cafe(),
                create->terrace(),
                create->specialDrink()
                );
            break;
        case 3:
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
        case 4:
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
        case 5:
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
        case 6:
            newPlace = std::make_shared<Museum>(
                name, city, description, rating, openings, cost,
                create->studentDiscount_Museum(),
                create->guidedTour_Museum(),
                create->culturalFocus_Museum(),
                create->audioGuide()
                );
            break;
        case 7:
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

        // 5) Controllo duplicati
        bool duplicato = false;
        for (const auto& existing : repository.getAllPlaces()) {
            if (editing && existing.get() == currentPlace) continue;
            if (existing->getName().compare(newPlace->getName(), Qt::CaseInsensitive) == 0 &&
                existing->getCity().compare(newPlace->getCity(), Qt::CaseInsensitive) == 0)
            {
                duplicato = true;
                break;
            }
        }
        if (duplicato) {
            view->showMessage(UiCommon::MsgIcon::Critical,
                              tr("Luogo già presente"),
                              tr("Esiste già un luogo con lo stesso nome e città.\nModifica uno dei due e riprova."));
            return;
        }

        // 6) Salvataggio
        if (editing && oldRaw)
            repository.replacePlace(oldRaw, newPlace);
        else
            repository.addPlace(newPlace);

        resetCurrentPlace();
        create->setEditing(false);
        view->populateCityComboBox(repository.getAllPlaces());
        view->updateResults(groupedSearchResults("", "All"));
        goBack();
        create->resetFields();
    }
    // Cattura le invalid_argument con messaggio in Warning
    catch (const std::invalid_argument& ex) {
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Invalid input"),
                          QString::fromStdString(ex.what()));
    }
    // Cattura eventuali altre eccezioni con Critical
    catch (const std::exception& ex) {
        view->showMessage(UiCommon::MsgIcon::Critical,
                          tr("Error"),
                          QString::fromStdString(ex.what()));
    }
}


bool PlaceController::setWidgetSafe(const QString& name)
{
    if (anyWidgetIsEditing()) {
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Editing in progress"),
                          tr("You are currently editing a place.\n"
                             "Please save before switching."));
        return false;                   // cambio pagina bloccato
    }

    view->showWidgetByName(name);
    return true;                        // cambio pagina riuscito
}

bool PlaceController::anyWidgetIsEditing() const {
    CreatePlaceWidget* create = qobject_cast<CreatePlaceWidget*>(view->getWidgetByName("create"));
    return create->isEditing();
}

void PlaceController::deleteCurrentPlace() {
    if (anyWidgetIsEditing()) {
        view->showMessage(UiCommon::MsgIcon::Warning,
                          tr("Editing in progress"),
                          tr("You are currently editing a place.\n"
                             "Please save before delete."));
    }else{
        QWidget* currentWidget = view->getCurrentPage();  // DA IMPLEMENTARE NELLA VIEW
        if (currentWidget == view->getWidgetByName("main") ||
            currentWidget == view->getWidgetByName("credits") ||
            currentWidget == view->getWidgetByName("statistics")) {
            view->showMessage(UiCommon::MsgIcon::Warning,
                              tr("Cannot Delete"),
                              tr("You must open a place detail before deleting it."));
            return;
        }

        // Recupera l'item selezionato
        QListWidget* list = view->getListWidget();
        QListWidgetItem* item = list->currentItem();

        if (!item || !item->data(Qt::UserRole).isValid()) {
            view->showMessage(UiCommon::MsgIcon::Warning,
                              tr("Invalid Selection"),
                              tr("You must open a place detail before deleting it."));
            return;
        }

        auto* place = static_cast<Place*>(item->data(Qt::UserRole).value<void*>());
        if (!place) return;

        // Conferma eliminazione
        QMessageBox::StandardButton reply = QMessageBox::question(
            view,
            "Confirm Deletion",
            "Are you sure you want to delete this place?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            const auto& all = repository.getAllPlaces();
            auto it = std::find_if(all.begin(), all.end(), [place](const std::shared_ptr<Place>& p) {
                return p.get() == place;
            });

            if (it != all.end()) {
                repository.removePlace(std::distance(all.begin(), it));
                findPlaces();
                goBack();
                view->populateCityComboBox(repository.getAllPlaces());
            }
        }
    }
}
void PlaceController::promptExportToXml() {
    QString path = QFileDialog::getSaveFileName(view, QObject::tr("Save as XML"), "", QObject::tr("XML files (*.xml)"));
    if (!path.isEmpty()) exportToXml(path);
}

void PlaceController::promptExportToJson() {
    QString path = QFileDialog::getSaveFileName(view, QObject::tr("Save as JSON"), "", QObject::tr("JSON files (*.json)"));
    if (!path.isEmpty()) exportToJson(path);
}

void PlaceController::editCurrentPlace()
{
    // 1. Controlli preliminari  ----------------------------
    QListWidget* list = view->getListWidget();
    QListWidgetItem* item = list ? list->currentItem() : nullptr;

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

    auto* place = static_cast<Place*>(item->data(Qt::UserRole).value<void*>());
    if (!place) {
        return;
    }

    // 2. Otteniamo il widget "create" ----------------------
    CreatePlaceWidget* create = qobject_cast<CreatePlaceWidget*>(view->getWidgetByName("create"));
    if (!create) return;

    // 3. Helper per QTime da minuti ------------------------
    auto minutesToQTime = [](double minutes) -> QTime {
        int m = static_cast<int>(minutes + 0.5);          // arrotonda
        return QTime(0,0).addSecs(m * 60);
    };

    // 4. Campi comuni -------------------------------------
    create->setName(place->getName());
    create->setCity(place->getCity());
    create->setDescription(place->getDescription());
    create->setRating(place->getRating());
    create->setCost(place->getCost());

    // orari settimanali
    const weeklyOpenings& wo = place->getOpen();          // adatta se il getter è diverso
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
        create->setHours(d, dh);
    }

    // 5. Campi specifici per categoria --------------------
    if (auto* d = dynamic_cast<Disco*>(place)) {
        create->setType("Disco");
        create->setAverageStay_Disco(d->getAvgStayDuration());
        create->setMinimumAge_Disco(d->getMinAge());
        create->setRestrictedEntry_Disco(d->getRestrictedEntry());
        create->setMusicGenre(d->getMusicGenre());
        create->setPrive(d->hasPriveAccess());
        create->setDressCode(d->getDressCode());

    } else if (auto* p = dynamic_cast<PanoramicPoints*>(place)) {
        create->setType("PanoramicPoints");
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

    create->setEditing(true);
    view->showWidgetByName("create");
}

void PlaceController::toggleDebug(){
    bool current = DebugConfig::isEnabled();
    DebugConfig::setEnabled(!current);

    view->updateDebugActionText(!current);  // Chiama il metodo pubblico

    view->showMessage(UiCommon::MsgIcon::Info,
                      tr("Debug Mode"),
                      current ? tr("Debug mode deactivated.")
                              : tr("Debug mode activated."));}

void PlaceController::onCreateTypeChanged(int idx)
{
    auto *create = qobject_cast<CreatePlaceWidget*>(view->getWidgetByName("create"));
    if (create) create->showDetailPage(idx);
}
