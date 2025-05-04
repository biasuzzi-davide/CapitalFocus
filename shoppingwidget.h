#ifndef SHOPPINGWIDGET_H
#define SHOPPINGWIDGET_H

#include <QWidget>

namespace Ui {
class shoppingwidget;
}

class shoppingwidget : public QWidget
{
    Q_OBJECT

public:
    explicit shoppingwidget(QWidget *parent = nullptr);
    ~shoppingwidget();

private:
    Ui::shoppingwidget *ui;
};

#endif // SHOPPINGWIDGET_H
