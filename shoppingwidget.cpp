#include "shoppingwidget.h"
#include "ui_shoppingwidget.h"
#include <QGraphicsDropShadowEffect>

shoppingwidget::shoppingwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::shoppingwidget)
{
    ui->setupUi(this);
    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(12);
    shadow->setColor(QColor(0,0,0,25));
    shadow->setOffset(0,4);
    ui->cardFrame->setGraphicsEffect(shadow);
}

shoppingwidget::~shoppingwidget()
{
    delete ui;
}
