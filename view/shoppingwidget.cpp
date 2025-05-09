#include "shoppingwidget.h"
#include "ui_shoppingwidget.h"
#include <QGraphicsDropShadowEffect>
#include "controller/placecontroller.h"

shoppingwidget::shoppingwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::shoppingwidget)
{
    ui->setupUi(this);

    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(12);
    shadow->setColor(QColor(0, 0, 0, 25));
    shadow->setOffset(0, 4);
    ui->cardFrame->setGraphicsEffect(shadow);
}


#include "shoppingwidget.h"

void shoppingwidget::setValues(const QString& name,
                               const QString& city,
                               const QString& description,
                               const QString& rating,
                               const QString& cost,
                               const QString& openings,
                               const QString& outdoor,
                               const QString& foodArea,
                               const QString& standNumber,
                               const QString& specific)
{
    ui->valueName->setText(name);
    ui->valueCity->setText(city);
    ui->valueDesc->setPlainText(description);
    ui->valueRating->setText(rating);
    ui->valueCost->setText(cost);
    ui->valueOpenings->setText(openings);
    ui->valueOutdoor->setText(outdoor);
    ui->valueFoodArea->setText(foodArea);
    ui->valueStandNumber->setText(standNumber);
    ui->valueSpecific->setText(specific);
}

shoppingwidget::~shoppingwidget()
{
    delete ui;
}
void shoppingwidget::setController(PlaceController* c) {
    controller = c;
    connect(ui->pushBack, &QPushButton::clicked, controller, &PlaceController::goBack);
    connect(ui->pushEdit, &QPushButton::clicked, controller, &PlaceController::editCurrentPlace);
    connect(ui->pushDelete, &QPushButton::clicked, controller, &PlaceController::deleteCurrentPlace);
}
