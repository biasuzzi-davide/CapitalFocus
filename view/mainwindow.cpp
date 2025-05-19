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
#include <QShortcut>
#include <QStatusBar>
#include <QSizePolicy>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(nullptr)
{
    QApplication::setStyle("Fusion");
    QApplication::setFont(QFont("Arial", 11));
    showStatusBarMsg("Welcome to CapitalFocus! v:1.0");
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



    if(ui->listWidgetResults){
        ui->listWidgetResults->setMaximumHeight(400);
        QSizePolicy sp = ui->listWidgetResults->sizePolicy();
        sp.setVerticalPolicy(QSizePolicy::MinimumExpanding);
        ui->listWidgetResults->setSizePolicy(sp);
    }
    ui->verticalLayout->setAlignment(ui->label, Qt::AlignHCenter);
    ui->verticalLayout->setStretch(3, 0);
    ui->verticalLayout->setContentsMargins(15, 15, 15, 15);
    ui->verticalLayout->setSpacing(10);
    toggleDarkMode(false);

    setMinimumHeight(850);
}

void MainWindow::showStatusBarMsg(const QString& message, int timeoutMs) {
    statusBar()->showMessage(message, timeoutMs);
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


void MainWindow::setStats(const StatisticsResult& stats) {
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
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(title);
    msgBox.setText(text);

    msgBox.setStyleSheet(R"(
        QMessageBox QPushButton#qt_msgbox_buttonbox QPushButton {
            background-color: #fe2b43;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 5px 15px;
        }
        QMessageBox QPushButton#qt_msgbox_buttonbox QPushButton:hover {
            background-color: #D32F2F;
        }
    )");

    switch (icon) {
    case UiCommon::MsgIcon::Warning:
    {
        QPixmap warningIcon(":/images/images/alert_icon.png");
        if (!warningIcon.isNull()) {
            msgBox.setIconPixmap(warningIcon);
        } else {
            msgBox.setIcon(QMessageBox::Warning);
        }
    }
    break;
    case UiCommon::MsgIcon::Critical:
    {
        QPixmap criticalIcon(":/images/images/alert_icon.png");
        if (!criticalIcon.isNull()) {
            msgBox.setIconPixmap(criticalIcon);
        } else {
            msgBox.setIcon(QMessageBox::Critical);
        }
    }
    break;
    case UiCommon::MsgIcon::Info:
    default:
    {
        QPixmap infoIcon(":/images/images/alert_icon.png");
        if (!infoIcon.isNull()) {
            msgBox.setIconPixmap(infoIcon);
        } else {
            msgBox.setIcon(QMessageBox::Information);
        }
    }
    break;
    }

    msgBox.exec();
}

bool MainWindow::askConfirmation(const QString& title,
                                 const QString& question)
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(title);
    msgBox.setText(question);

    {
        QPixmap confirmationIcon(":/images/images/alert_icon.png");
        if (!confirmationIcon.isNull()) {
            msgBox.setIconPixmap(confirmationIcon);
        } else {
            msgBox.setIcon(QMessageBox::Question);
        }
    }

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    msgBox.setStyleSheet(R"(
        QMessageBox QPushButton#qt_msgbox_buttonbox QPushButton {
            background-color: #fe2b43;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 5px 15px;
        }
        QMessageBox QPushButton#qt_msgbox_buttonbox QPushButton:hover {
            background-color: #D32F2F;
        }
    )");

    return msgBox.exec() == QMessageBox::Yes;
}

void MainWindow::setController(PlaceController* controller) {
    this->controller = controller;

    connect(ui->pushButtonSearch, &QPushButton::clicked, controller, &PlaceController::findPlaces);
    connect(ui->lineEditSearch, &QLineEdit::returnPressed, controller, &PlaceController::findPlaces);
    connect(ui->pushButtonReset, &QPushButton::clicked, controller, &PlaceController::resetSearchFields);
    connect(ui->actionAuto_Import, &QAction::triggered, controller, &PlaceController::importFromFile);
    connect(ui->pushButtonBacktoMain, &QPushButton::clicked, controller, &PlaceController::setWidgetMain);
    connect(ui->pushButtonBacktoMain_2, &QPushButton::clicked, controller, &PlaceController::setWidgetMain);
    connect(ui->listWidgetResults, &QListWidget::itemClicked,controller, &PlaceController::onPlaceSelected);
    connect(ui->actionCredits,      &QAction::triggered,    controller,       &PlaceController::setWidgetCredits);
    connect(ui->actionStatistics, &QAction::triggered, controller, &PlaceController::showStatistics);
    connect(ui->actionEdit, &QAction::triggered, controller, &PlaceController::editCurrentPlace);
    connect(ui->actionDark_Mode, &QAction::triggered, controller, &PlaceController::toggleDarkMode);
    connect(ui->actionDelete, &QAction::triggered, controller, &PlaceController::deleteCurrentPlace);
    connect(ui->actionXML, &QAction::triggered, controller, &PlaceController::promptExportToXml);
    connect(ui->actionJSON, &QAction::triggered, controller, &PlaceController::promptExportToJson);
    connect(ui->actionToggleDebug, &QAction::triggered, controller, &PlaceController::toggleDebug);
    connect(ui->actionNew, &QAction::triggered, controller, &PlaceController::setWidgetCreate);
    connect(ui->pushButtonCreate, &QPushButton::clicked, controller, &PlaceController::setWidgetCreate);
    connect(ui->lineEditSearch, &QLineEdit::textChanged, controller, &PlaceController::findPlaces); // per ricerca automatica senza pulsante cerca
    connect(ui->comboBoxCity, &QComboBox::currentTextChanged, controller, &PlaceController::findPlaces); // per ricerca automatica senza pulsante cerca

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

bool MainWindow::getDarkModeEnabled(){
    return isDarkModeEnabled;
}

void MainWindow::toggleDarkMode(bool enabled) {
    isDarkModeEnabled = enabled;
    if (enabled) {
        ui->actionDark_Mode->setText(tr("Dark Mode OFF"));
        qApp->setStyleSheet(R"(
            QWidget {
                background-color: #3a3a3a;
                font-family: 'Segoe UI', Arial, sans-serif;
                font-size: 11pt;
                color: #e0e0e0;
            }

            QLabel { color: #e0e0e0; }
            QFrame#cardFrame { background-color: #4f4f4f; border: 1px solid #666666; border-radius: 6px; padding: 15px; }
            QTextEdit { background-color: #4f4f4f; color: #e0e0e0; border: 1px solid #666666; border-radius: 4px; padding: 5px; }
            QTextEdit[readOnly="true"] { background-color: #3a3a3a; }

            QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox, QTimeEdit {
                background-color: #4f4f4f;
                color: #e0e0e0;
                border: 1px solid #666666;
                border-radius: 4px;
                padding: 6px;
            }

            QListWidget, QTableWidget {
                background-color: #4f4f4f;
                color: #e0e0e0;
                border: 1px solid #666666;
            }

            QListWidget::item:!selectable {
                color: #fe2b43;
                font-weight: bold;
                border-bottom: 1px solid #666666;
                padding: 6px;
            }
            QListWidget::item:selectable:!selected { color: #cccccc; }
            QListWidget::item:selected, QTableWidget::item:selected {
                background-color: #fe2b43;
                color: white;
            }

            QMenuBar { background-color: #3a3a3a; color: #e0e0e0; border-bottom: 1px solid #666666; }
            QMenu { background-color: #4f4f4f; color: #e0e0e0; border: 1px solid #666666; border-radius: 6px; }
            QMenu::item:selected { background-color: #fe2b43; color: white; }

            QStatusBar { background-color: #3a3a3a; border-top: 1px solid #666666; color: #e0e0e0; }

            QPushButton {
                background-color: #666666;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 8px 16px;
                font-weight: normal;
                min-width: 70px;
            }

            QPushButton:hover { background-color: #777777; }
            QPushButton:pressed { background-color: #888888; }

            QPushButton#pushButtonSearch, QPushButton#pushButtonCreate,
            QPushButton#pushEdit, QPushButton#pushDelete,
            #culturewidget QPushButton:!hasFlatAppearance,
            #entertainmentwidget QPushButton:!hasFlatAppearance,
            #foodwidget QPushButton:!hasFlatAppearance,
            #shoppingwidget QPushButton:!hasFlatAppearance {
                background-color: #fe2b43;
                color: white;
                font-weight: bold;
            }

            QPushButton#pushButtonSearch:hover, QPushButton#pushButtonCreate:hover,
            QPushButton#pushEdit:hover, QPushButton#pushDelete:hover {
                background-color: #D32F2F;
            }

            QPushButton#pushButtonSearch:pressed, QPushButton#pushButtonCreate:pressed,
            QPushButton#pushEdit:pressed, QPushButton#pushDelete:pressed {
                background-color: #B71C1C;
            }

            QPushButton#pushButtonReset, QPushButton#pushButtonBacktoMain, QPushButton#pushButtonBacktoMain_2,
            #culturewidget QPushButton#pushBack, #entertainmentwidget QPushButton#pushBack,
            #foodwidget QPushButton#pushBack, #shoppingwidget QPushButton#pushBack {
                background-color: #666666;
                color: white;
            }

            QPushButton#pushButtonReset:hover, QPushButton#pushButtonBacktoMain:hover, QPushButton#pushButtonBacktoMain_2:hover,
            #culturewidget QPushButton#pushBack:hover, #entertainmentwidget QPushButton#pushBack:hover,
            #foodwidget QPushButton#pushBack:hover, #shoppingwidget QPushButton#pushBack:hover {
                background-color: #777777;
            }

            QPushButton#pushButtonReset:pressed, QPushButton#pushButtonBacktoMain:pressed, QPushButton#pushButtonBacktoMain_2:pressed,
            #culturewidget QPushButton#pushBack:pressed, #entertainmentwidget QPushButton#pushBack:pressed,
            #foodwidget QPushButton#pushBack:pressed, #shoppingwidget QPushButton#pushBack:pressed {
                background-color: #888888;
            }
        )");
    } else {
        ui->actionDark_Mode->setText(tr("Dark Mode ON"));
        qApp->setStyleSheet(R"(
            QWidget {
                background-color: #f0f0f0;
                font-family: 'Segoe UI', Arial, sans-serif;
                font-size: 11pt;
                color: #333333;
            }

            QLabel { color: #333333; }
            QFrame#cardFrame { background-color: #ffffff; border: 1px solid #e0e0e0; border-radius: 6px; padding: 15px; }
            QTextEdit { background-color: #ffffff; color: #333333; border: 1px solid #cccccc; border-radius: 4px; padding: 5px; }
            QTextEdit[readOnly="true"] { background-color: #f8f8f8; }

            QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox, QTimeEdit {
                background-color: white;
                color: #333333;
                border: 1px solid #cccccc;
                border-radius: 4px;
                padding: 6px;
            }

            QListWidget, QTableWidget {
                background-color: white;
                color: #333333;
                border: 1px solid #cccccc;
            }

            QListWidget::item:!selectable {
                color: #fe2b43;
                font-weight: bold;
                border-bottom: 1px solid #cccccc;
                padding: 6px;
            }
            QListWidget::item:selectable:!selected { color: #333333; }
            QListWidget::item:selected, QTableWidget::item:selected {
                background-color: #fe2b43;
                color: white;
            }

            QMenuBar { background-color: #f0f0f0; color: #333333; border-bottom: 1px solid #cccccc; }
            QMenu { background-color: #ffffff; color: #333333; border: 1px solid #cccccc; border-radius: 6px; }
            QMenu::item:selected { background-color: #fe2b43; color: white; }

            QStatusBar { background-color: #f0f0f0; border-top: 1px solid #cccccc; color: #333333; }

            QPushButton {
                background-color: #ffffff;
                color: #333333;
                border: 1px solid #cccccc;
                border-radius: 6px;
                padding: 8px 16px;
                font-weight: normal;
                min-width: 70px;
            }

            QPushButton:hover { background-color: #f0f0f0; }
            QPushButton:pressed { background-color: #dddddd; }

            QPushButton#pushButtonSearch, QPushButton#pushButtonCreate,
            QPushButton#pushEdit, QPushButton#pushDelete,
            #culturewidget QPushButton:!hasFlatAppearance,
            #entertainmentwidget QPushButton:!hasFlatAppearance,
            #foodwidget QPushButton:!hasFlatAppearance,
            #shoppingwidget QPushButton:!hasFlatAppearance {
                background-color: #fe2b43;
                color: white;
                font-weight: bold;
                border: none;
            }

            QPushButton#pushButtonSearch:hover, QPushButton#pushButtonCreate:hover,
            QPushButton#pushEdit:hover, QPushButton#pushDelete:hover {
                background-color: #D32F2F;
            }

            QPushButton#pushButtonSearch:pressed, QPushButton#pushButtonCreate:pressed,
            QPushButton#pushEdit:pressed, QPushButton#pushDelete:pressed {
                background-color: #B71C1C;
            }

            QPushButton#pushButtonReset, QPushButton#pushButtonBacktoMain, QPushButton#pushButtonBacktoMain_2,
            #culturewidget QPushButton#pushBack, #entertainmentwidget QPushButton#pushBack,
            #foodwidget QPushButton#pushBack, #shoppingwidget QPushButton#pushBack {
                background-color: #ffffff;
                color: #333333;
                border: 1px solid #cccccc;
            }

            QPushButton#pushButtonReset:hover, QPushButton#pushButtonBacktoMain:hover, QPushButton#pushButtonBacktoMain_2:hover,
            #culturewidget QPushButton#pushBack:hover, #entertainmentwidget QPushButton#pushBack:hover,
            #foodwidget QPushButton#pushBack:hover, #shoppingwidget QPushButton#pushBack:hover {
                background-color: #f0f0f0;
            }

            QPushButton#pushButtonReset:pressed, QPushButton#pushButtonBacktoMain:pressed, QPushButton#pushButtonBacktoMain_2:pressed,
            #culturewidget QPushButton#pushBack:pressed, #entertainmentwidget QPushButton#pushBack:pressed,
            #foodwidget QPushButton#pushBack:pressed, #shoppingwidget QPushButton#pushBack:pressed {
                background-color: #dddddd;
            }
        )");
    }
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
    ui->comboBoxCity->clear();// Pulisce tutto
    ui->comboBoxCity->addItem("All");// Prima voce = "All"

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
#include <QCloseEvent>
void MainWindow::closeEvent(QCloseEvent* event)
{
    if (controller && !controller->canClose()) {
        event->ignore();
    } else {
        event->accept();
    }
}
