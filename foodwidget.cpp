#include "foodwidget.h"
#include "ui_foodwidget.h"
#include <QGraphicsDropShadowEffect>

foodwidget::foodwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::foodwidget)
{
    ui->setupUi(this);
    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(12);
    shadow->setColor(QColor(0,0,0,25));
    shadow->setOffset(0,4);
    ui->cardFrame->setGraphicsEffect(shadow);

}

foodwidget::~foodwidget()
{
    delete ui;
}
