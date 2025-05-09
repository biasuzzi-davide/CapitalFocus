#include "entertainmentwidget.h"
#include "ui_entertainmentwidget.h"
#include <QGraphicsDropShadowEffect>
#include "controller/placecontroller.h"

entertainmentwidget::entertainmentwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::entertainmentwidget)
{
    ui->setupUi(this);

    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(12);
    shadow->setColor(QColor(0, 0, 0, 25));
    shadow->setOffset(0, 4);
    ui->cardFrame->setGraphicsEffect(shadow);
}


void entertainmentwidget::setValues(const QString& name,
                                    const QString& city,
                                    const QString& description,
                                    const QString& rating,
                                    const QString& cost,
                                    const QString& openings,
                                    const QString& avgStayDuration,
                                    const QString& minimumAge,
                                    const QString& restrictedEntry,
                                    const QString& specific)
{
    ui->valueName->setText(name);
    ui->valueCity->setText(city);
    ui->valueDesc->setPlainText(description);
    ui->valueRating->setText(rating);
    ui->valueCost->setText(cost);
    ui->valueOpenings->setText(openings);
    ui->valueAvgStayDuration->setText(avgStayDuration);
    ui->valueMinimumAge->setText(minimumAge);
    ui->valueRestrictedEntry->setText(restrictedEntry);
    ui->valueSpecific->setText(specific);
}

entertainmentwidget::~entertainmentwidget()
{
    delete ui;
}


void entertainmentwidget::setController(PlaceController* c) {
    controller = c;
    connect(ui->pushBack, &QPushButton::clicked, controller, &PlaceController::goBack);
    connect(ui->pushEdit, &QPushButton::clicked, controller, &PlaceController::editCurrentPlace);
    connect(ui->pushDelete, &QPushButton::clicked, controller, &PlaceController::deleteCurrentPlace);
}
