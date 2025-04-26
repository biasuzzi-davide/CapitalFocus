#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller/placecontroller.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(nullptr)
{
    ui->setupUi(this);
}

void MainWindow::setController(PlaceController* controller) {
    this->controller = controller;

    // Collegamento segnali → slot del controller
    connect(ui->pushButtonSearch, &QPushButton::clicked, controller, &PlaceController::findPlaces);
    connect(ui->pushButtonReset, &QPushButton::clicked, controller, &PlaceController::resetSearchFields);
    connect(ui->actionAuto_Import, &QAction::triggered, controller, &PlaceController::importFromXml);

    // ...puoi aggiungere altri connect qui
}


MainWindow::~MainWindow()
{
    delete ui;
}
QString MainWindow::getSearchText() const {
    return ui->lineEditSearch->text();
}

QString MainWindow::getSelectedCity() const {
    return ui->comboBoxCity->currentText();
}

void MainWindow::updateResults(const std::vector<std::shared_ptr<Place>>& results) {
    ui->listWidgetResults->clear();
    for (const auto& place : results) {
        QListWidgetItem* item = new QListWidgetItem(place->getName());
        ui->listWidgetResults->addItem(item);
    }
}
void MainWindow::clearSearchFields() {
    ui->lineEditSearch->clear();
    ui->comboBoxCity->setCurrentIndex(0);
}
#include <QSet>

void MainWindow::populateCityComboBox(const std::vector<std::shared_ptr<Place>>& places) {
    ui->comboBoxCity->clear();              // Pulisce tutto
    ui->comboBoxCity->addItem("All");     // Prima voce = "Tutte"

    QSet<QString> addedCities;
    for (const auto& place : places) {
        QString city = place->getCity();
        if (!addedCities.contains(city)) {
            ui->comboBoxCity->addItem(city);
            addedCities.insert(city);
        }
    }
}
