#include "foodwidget.h"
#include "ui_foodwidget.h"
#include <QGraphicsDropShadowEffect>
#include "controller/placecontroller.h"

// Costruttore
foodwidget::foodwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::foodwidget)
{
    ui->setupUi(this); // Inizializza l'UI

    // Applica un'ombra al frame principale
    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(12);
    shadow->setColor(QColor(0, 0, 0, 25));
    shadow->setOffset(0, 4);
    ui->cardFrame->setGraphicsEffect(shadow);
}

// Distruttore
foodwidget::~foodwidget()
{
    delete ui; // Dealloca l'UI
}

// Imposta i valori dei campi del widget con i dettagli del luogo
void foodwidget::setValues(const QString& name,
                           const QString& city,
                           const QString& description,
                           const QString& rating,
                           const QString& cost,
                           const QString& openings,
                           const QString& takeAway,
                           const QString& avgWaiting,
                           const QString& veganMenu,
                           const QString& specific)
{
    ui->valueName->setText(name);
    ui->valueCity->setText(city);
    ui->valueDesc->setPlainText(description);
    ui->valueRating->setText(rating);
    ui->valueCost->setText(cost);
    ui->valueOpenings->setText(openings);
    ui->valueTakeAway->setText(takeAway);
    ui->valueAvgWaiting->setText(avgWaiting);
    ui->valueVeganMenu->setText(veganMenu);
    ui->valueSpecific->setText(specific);
}

// Imposta il controller e connette i segnali dei pulsanti
void foodwidget::setController(PlaceController* c) {
    controller = c; // Salva il puntatore al controller
    // Connette i segnali clicked dei pulsanti agli slot del controller
    connect(ui->pushBack, &QPushButton::clicked, controller, &PlaceController::goBack);
    connect(ui->pushEdit, &QPushButton::clicked, controller, &PlaceController::editCurrentPlace);
    connect(ui->pushDelete, &QPushButton::clicked, controller, &PlaceController::deleteCurrentPlace);
}
