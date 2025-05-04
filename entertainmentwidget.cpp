#include "entertainmentwidget.h"
#include "ui_entertainmentwidget.h"
#include <QGraphicsDropShadowEffect>

entertainmentwidget::entertainmentwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::entertainmentwidget)
{
    ui->setupUi(this);
    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(12);
    shadow->setColor(QColor(0,0,0,25));
    shadow->setOffset(0,4);
    ui->cardFrame->setGraphicsEffect(shadow);
}

entertainmentwidget::~entertainmentwidget()
{
    delete ui;
}
