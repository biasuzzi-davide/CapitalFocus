#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller/placecontroller.h"
#include"foodwidget.h"
#include"culturewidget.h"
#include"shoppingwidget.h"
#include"entertainmentwidget.h"
#include <QFileDialog>
#include "model/statisticsResult.h"
#include "view/createplacewidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(nullptr)
{

    ui->setupUi(this);

    culturewidget* culture = new culturewidget(this);
    entertainmentwidget* entertainment = new entertainmentwidget(this);
    foodwidget* food = new foodwidget(this);
    shoppingwidget* shopping = new shoppingwidget(this);
    CreatePlaceWidget* cp = new CreatePlaceWidget(this);

    widgetMap["main"] = ui->mainPage;
    widgetMap["credits"] = ui->creditsPage;
    widgetMap["statistics"] = ui->statisticsPage;
    widgetMap["culture"] = culture;
    widgetMap["entertainment"] = entertainment;
    widgetMap["food"] = food;
    widgetMap["shopping"] = shopping;
    widgetMap["create"] = cp;

    ui->stackedWidget->addWidget(culture);
    ui->stackedWidget->addWidget(entertainment);
    ui->stackedWidget->addWidget(food);
    ui->stackedWidget->addWidget(shopping);
    ui->stackedWidget->addWidget(cp);



    ui->verticalLayout->setAlignment(ui->label, Qt::AlignHCenter);
    ui->verticalLayout->setStretch(3, 1);

    ui->verticalLayout->setContentsMargins(15, 15, 15, 15);
    ui->verticalLayout->setSpacing(10);

}

void MainWindow::showWidgetByName(const QString& name) {
    if (widgetMap.contains(name)) {
        ui->stackedWidget->setCurrentWidget(widgetMap[name]);
    } else {
        qWarning("ERRORE: Widget con nome '%s' non trovato", qPrintable(name));
    }
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
    showWidgetByName("statistics");
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
void MainWindow::showMessage(UiCommon::MsgIcon icon,
                             const QString& title,
                             const QString& text)
{
    switch (icon) {
    case UiCommon::MsgIcon::Warning:
        QMessageBox::warning   (this, title, text); break;
    case UiCommon::MsgIcon::Critical:
        QMessageBox::critical  (this, title, text); break;
    case UiCommon::MsgIcon::Info:
    default:
        QMessageBox::information(this, title, text); break;
    }
}

bool MainWindow::askConfirmation(const QString& title,
                                 const QString& question,
                                 QMessageBox::StandardButton def)
{
    auto ret = QMessageBox::question(this,
                                     title,
                                     question,
                                     QMessageBox::Yes | QMessageBox::No,
                                     def);
    return ret == QMessageBox::Yes;
}

void MainWindow::setController(PlaceController* controller) {
    this->controller = controller;

    connect(ui->pushButtonSearch, &QPushButton::clicked, controller, &PlaceController::findPlaces);
    connect(ui->pushButtonReset, &QPushButton::clicked, controller, &PlaceController::resetSearchFields);
    connect(ui->actionAuto_Import, &QAction::triggered, controller, &PlaceController::importFromFile);
    connect(ui->pushButtonBacktoMain, &QPushButton::clicked, controller, &PlaceController::setWidgetMain);
    connect(ui->listWidgetResults, &QListWidget::itemClicked,controller, &PlaceController::onPlaceSelected);
    connect(ui->actionCredits,      &QAction::triggered,    controller,       &PlaceController::setWidgetCredits);
    connect(ui->actionStatistics, &QAction::triggered, controller, &PlaceController::showStatistics);
    connect(ui->actionEdit, &QAction::triggered, controller, &PlaceController::editCurrentPlace);
    connect(ui->actionDelete, &QAction::triggered, controller, &PlaceController::deleteCurrentPlace);
    connect(ui->actionXML, &QAction::triggered, controller, &PlaceController::promptExportToXml);
    connect(ui->actionJSON, &QAction::triggered, controller, &PlaceController::promptExportToJson);
    connect(ui->actionToggleDebug, &QAction::triggered, controller, &PlaceController::toggleDebug);
    connect(ui->actionNew, &QAction::triggered, controller, &PlaceController::setWidgetCreate);
    connect(ui->pushButtonCreate, &QPushButton::clicked, controller, &PlaceController::setWidgetCreate);
    qobject_cast<foodwidget*>(widgetMap["food"])->setController(controller);
    qobject_cast<shoppingwidget*>(widgetMap["shopping"])->setController(controller);
    qobject_cast<culturewidget*>(widgetMap["culture"])->setController(controller);
    qobject_cast<entertainmentwidget*>(widgetMap["entertainment"])->setController(controller);
    qobject_cast<CreatePlaceWidget*>(widgetMap["create"])->setController(controller);

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
void MainWindow::setWidgetCredits(){showWidgetByName("credits");}
void MainWindow::setWidgetMain(){showWidgetByName("main");}

void MainWindow::updateDebugActionText(bool debugEnabled) {
    ui->actionToggleDebug->setText(debugEnabled ? "Deactivate Debug" : "Activate Debug");
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

QWidget* MainWindow::getCurrentPage() const {
    return ui->stackedWidget->currentWidget();
}

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
QWidget* MainWindow::getWidgetByName(const QString& name) const {
    return widgetMap.contains(name) ? widgetMap.value(name) : nullptr;
}
QString MainWindow::askOpenFile(const QString& caption,
                                const QString& filter,
                                const QString& startDir) const
{
    return QFileDialog::getOpenFileName(
        nullptr, caption, startDir, filter);
}

QString MainWindow::askSaveFile(const QString& caption,
                                const QString& filter,
                                const QString& startDir) const
{
    return QFileDialog::getSaveFileName(
        nullptr, caption, startDir, filter);
}
