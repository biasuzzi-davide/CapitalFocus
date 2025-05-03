#include "placeController.h"
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

void PlaceController::importPlacesFromXml(const QString& filePath){
    try {
        std::vector<std::shared_ptr<Place>> newXmlPlaces = xmlImporter.importFromFile(filePath);

        repository.clear();
        for (const auto& sp : newXmlPlaces)
            repository.addPlace(sp);

        //TODO: metodi per la view da implementare correttamente
        // → implementare dopo TableModel
        //view->populateCityComboBox(repository.getAllPlaces());
        //view->updateResults(repository.getAllPlaces());

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

        //TODO: metodi per la view da implementare correttamente
        // → implementare dopo TableModel
        //view->populateCityComboBox(repository.getAllPlaces());
        //view->updateResults(repository.getAllPlaces());

    } catch (const FileOpenError& e) {
        QMessageBox::critical(view, tr("File opening error"), e.what());
    } catch (const JsonParseError& e) {
        QMessageBox::critical(view, tr("JSON parsing error"), e.what());
    } catch (const std::exception& e) {
        QMessageBox::warning(view, tr("Invalid data"), e.what());
    }
}

void PlaceController::importFromFile()
{
    QString path = QFileDialog::getOpenFileName(view, tr("Select file"),"", tr("JSON or XML file (*.json *.xml)"));

    if (path.isEmpty()) return;

    QString ext = QFileInfo(path).suffix().toLower();
    if (ext == "json")
        importPlacesFromJson(path);
    else if (ext == "xml")
        importPlacesFromXml(path);
    else
        QMessageBox::warning(view, tr("Unsupported format"),tr("Select a .json or .xml file"));
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
        QMessageBox::critical(view, tr("File writing error"),tr("Cannot open file for writing:\n%1").arg(filePath));
        return;
    }
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    QMessageBox::information(view, tr("Export completed"),tr("Exported %1 places to\n%2").arg(placesArray.size()).arg(filePath));
}

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
        QMessageBox::critical(view, tr("File writing error"),
                              tr("Cannot open file for writing:\n%1").arg(filePath));
        return;
    }
    file.write(doc.toByteArray(4)); // aggiunta spazi di indentazione
    file.close();

    QMessageBox::information(view, tr("Export completed"),tr("Exported %1 places to\n%2").arg(root.childNodes().count()).arg(filePath));
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

void PlaceController::resetSearchFields() {
    view->clearSearchFields();  // se la view ha questo metodo
}

void PlaceController::findPlaces() {
    QString keyword = view->getSearchText();
    QString city = view->getSelectedCity();

    auto results = repository.search(keyword, city);  // qui city può essere "All"
    qDebug() << "KW: " << keyword << " CTY: " << city << " N: " << results.size();

    view->updateResults(results);
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
        QMessageBox::warning(view,tr("Unsupported format"),tr("Choose a .json or .xml file"));
}

void PlaceController::setWidgetCredits() {
    view->setWidgetCredits();
}
void PlaceController::setWidgetMain() {
    view->setWidgetMain();
}
void PlaceController::showStatistics() {
    StatisticsResult stats = repository.computeStatistics();
    view->showStatistics(stats);
}

