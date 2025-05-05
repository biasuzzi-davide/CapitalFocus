#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller/placecontroller.h"
#include"foodwidget.h"
#include <QFileDialog>
#include "model/statisticsResult.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(nullptr)
{

    ui->setupUi(this);

    auto *fw = new foodwidget(this);
    ui->stackedWidget->addWidget(fw);
    ui->stackedWidget->setCurrentWidget(fw);

    ui->verticalLayout->setAlignment(ui->label, Qt::AlignHCenter);
    ui->verticalLayout->setStretch(3, 1);

    ui->verticalLayout->setContentsMargins(15, 15, 15, 15);
    ui->verticalLayout->setSpacing(10);

}

void MainWindow::updateResults(const std::map<QString, std::vector<std::shared_ptr<Place>>>& groupedResults) {
    ui->listWidgetResults->clear();

    for (const auto& pair : groupedResults) {
        QString section = pair.first;  // es. "Shopping", "Food"
        const auto& places = pair.second;

        // Intestazione (non selezionabile)
        QListWidgetItem* header = new QListWidgetItem(section);
        QFont font = header->font();
        font.setBold(true);
        font.setPointSize(font.pointSize() + 2);
        header->setFont(font);
        header->setForeground(QBrush(QColor("#8B0000")));
        header->setBackground(QBrush(QColor("#F5F5F5")));
        header->setFlags(Qt::NoItemFlags);  // non cliccabile
        ui->listWidgetResults->addItem("");  // linea vuota
        ui->listWidgetResults->addItem(header);

        // Aggiunge i risultati
        for (const auto& place : places) {
            QListWidgetItem* item = new QListWidgetItem(place->getName());
            item->setData(Qt::UserRole, QVariant::fromValue<void*>(place.get()));
            ui->listWidgetResults->addItem(item);
        }
    }
}


void MainWindow::showStatistics(const StatisticsResult& stats) {
    ui->stackedWidget->setCurrentWidget(ui->statisticsPage);

    // Popola la tabella
    QTableWidget* table = ui->tableStatistics;
    table->setRowCount(3);
    table->setHorizontalHeaderLabels({ "Statistic", "Value" });
    table->verticalHeader()->setVisible(false);

    table->setItem(0, 0, new QTableWidgetItem("Total Places"));
    table->setItem(0, 1, new QTableWidgetItem(QString::number(stats.totalPlaces)));

    table->setItem(1, 0, new QTableWidgetItem("Average Rating"));
    table->setItem(1, 1, new QTableWidgetItem(QString::number(stats.averageRating, 'f', 2)));

    table->setItem(2, 0, new QTableWidgetItem("Average Cost"));
    table->setItem(2, 1, new QTableWidgetItem(QString::number(stats.averageCost, 'f', 2)));

    table->resizeColumnsToContents();

    // Popola la lista della città
    QListWidget* list = ui->listCities;
    list->clear();
    for (auto const& kv : stats.countByCity) {
        list->addItem(QString("%1: %2").arg(kv.first).arg(kv.second));
    }
}


void MainWindow::setController(PlaceController* controller) {
    this->controller = controller;

    connect(ui->pushButtonSearch, &QPushButton::clicked, controller, &PlaceController::findPlaces);
    connect(ui->pushButtonReset, &QPushButton::clicked, controller, &PlaceController::resetSearchFields);
    connect(ui->actionAuto_Import, &QAction::triggered, controller, &PlaceController::importFromFile);
    connect(ui->pushButtonBacktoMain, &QPushButton::clicked, controller, &PlaceController::setWidgetMain);
    //connect(ui->actionAuto_Import, &QAction::triggered, controller, &PlaceController::importFromXml);
    connect(ui->listWidgetResults, &QListWidget::itemClicked,controller, &PlaceController::onPlaceSelected);
    connect(ui->actionCredits,      &QAction::triggered,    controller,       &PlaceController::setWidgetCredits);
    connect(ui->actionStatistics, &QAction::triggered, controller, &PlaceController::showStatistics);

}

QListWidget* MainWindow::getListWidget() const {
    return ui->listWidgetResults;
}

void MainWindow::setDetailsWidget(QWidget* widget) {
    // Rimuove i precedenti widget
    QLayoutItem* child;
    while ((child = ui->detailsLayout->takeAt(0)) != nullptr) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    if (widget)
        ui->detailsLayout->addWidget(widget);
}
void MainWindow::setWidgetCredits(){
    ui->stackedWidget->setCurrentWidget(ui->creditsPage);
}
void MainWindow::setWidgetMain(){
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
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

void MainWindow::clearSearchFields() {
    ui->lineEditSearch->clear();
    ui->comboBoxCity->setCurrentIndex(0);
}
#include <QSet> //

void MainWindow::populateCityComboBox(const std::vector<std::shared_ptr<Place>>& places) {
    ui->comboBoxCity->clear();              // Pulisce tutto
    ui->comboBoxCity->addItem("All");     // Prima voce = "All"

    QSet<QString> addedCities;
    for (const auto& place : places) {
        QString city = place->getCity();
        if (!addedCities.contains(city)) {
            ui->comboBoxCity->addItem(city);
            addedCities.insert(city);
        }
    }
}
