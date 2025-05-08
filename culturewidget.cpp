#include "culturewidget.h"
#include "ui_culturewidget.h"
#include <QGraphicsDropShadowEffect>
#include "controller/placecontroller.h"

culturewidget::culturewidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::culturewidget)
{
    ui->setupUi(this);
    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(12);
    shadow->setColor(QColor(0, 0, 0, 25));
    shadow->setOffset(0, 4);
    ui->cardFrame->setGraphicsEffect(shadow);
}

void culturewidget::setController(PlaceController* c) {
    controller = c;

    connect(ui->pushBack, &QPushButton::clicked, controller, &PlaceController::goBack);
    connect(ui->pushEdit, &QPushButton::clicked, controller, &PlaceController::editCurrentPlace);
    connect(ui->pushDelete, &QPushButton::clicked, controller, &PlaceController::deleteCurrentPlace);
}
culturewidget::~culturewidget(){delete ui;}

void culturewidget::setValues(const QString& name,
                              const QString& city,
                              const QString& description,
                              const QString& rating,
                              const QString& cost,
                              const QString& openings,
                              const QString& studentDiscount,
                              const QString& guidedTour,
                              const QString& culturalFocus,
                              const QString& specific)
{
    ui->valueName->setText(name);
    ui->valueCity->setText(city);
    ui->valueDesc->setPlainText(description);
    ui->valueRating->setText(rating);
    ui->valueCost->setText(cost);
    ui->valueOpenings->setText(openings);
    ui->valueStudentDiscount->setText(studentDiscount);
    ui->valueGuidedTour->setText(guidedTour);
    ui->valueCulturalFocus->setText(culturalFocus);
    ui->valueSpecific->setText(specific);
}
