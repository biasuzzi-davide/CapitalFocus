#ifndef FOODWIDGET_H
#define FOODWIDGET_H

#include <QWidget>

namespace Ui {
class foodwidget;
}

class foodwidget : public QWidget
{
    Q_OBJECT

public:
    explicit foodwidget(QWidget *parent = nullptr);
    ~foodwidget();

private:
    Ui::foodwidget *ui;
};

#endif // FOODWIDGET_H
