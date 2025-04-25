#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::findPlaces() {
    QString query = ui->lineEditSearch->text().trimmed();
    QString selectedCity = ui->comboBoxCity->currentText();

    ui->listWidgetResults->clear();

    };

    // Filtro per città e testo
    for (const QString& luogo : luoghi) {
        if ((selectedCity.isEmpty() || luogo.contains(selectedCity, Qt::CaseInsensitive)) &&
            (query.isEmpty() || luogo.contains(query, Qt::CaseInsensitive))) {
            ui->listWidgetResults->addItem(luogo);
        }
    }

    if (ui->listWidgetResults->count() == 0) {
        ui->listWidgetResults->addItem("Nessun risultato trovato.");
    }
}

