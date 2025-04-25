#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller/placecontroller.h"
#include <QFileDialog>

MainWindow::MainWindow(PlaceController& ctrl, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(ctrl) {
    ui->setupUi(this);
    connect(ui->actionAuto_Import, &QAction::triggered, this, &MainWindow::importFromXml);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::importFromXml() {
    QString filePath = QFileDialog::getOpenFileName(this, "Seleziona file XML", "", "File XML (*.xml)");
    if (!filePath.isEmpty()) {
        controller.importPlacesFromXml(filePath);  // chiama il tuo controller
        findPlaces();  // aggiorna la view
    }
}

void MainWindow::findPlaces() {
    QString keyword = ui->lineEditSearch->text();

    //QString city = ui->comboBoxCity->currentText();
    QString city = "Città";

    auto results = controller.search(keyword, city);  // SOLO IL CONTROLLER
    qDebug() <<"KW " << keyword << " CT" << city << " N:" << results.size();


    ui->listWidgetResults->clear();
    for (const auto& place : results) {
        QListWidgetItem* item = new QListWidgetItem(place->getName());
        item->setData(Qt::UserRole, QVariant::fromValue(place.get())); // bonus: accesso diretto
        ui->listWidgetResults->addItem(item);
    }
}

