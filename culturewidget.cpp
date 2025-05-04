#include "culturewidget.h"
#include "ui_culturewidget.h"
#include <QGraphicsDropShadowEffect>

culturewidget::culturewidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::culturewidget)
{
    ui->setupUi(this);
    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(12);
    shadow->setColor(QColor(0,0,0,25));
    shadow->setOffset(0,4);
    ui->cardFrame->setGraphicsEffect(shadow);
}

culturewidget::~culturewidget()
{
    delete ui;
}
