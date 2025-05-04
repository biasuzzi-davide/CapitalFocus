#ifndef ENTERTAINMENTWIDGET_H
#define ENTERTAINMENTWIDGET_H

#include <QWidget>

namespace Ui {
class entertainmentwidget;
}

class entertainmentwidget : public QWidget
{
    Q_OBJECT

public:
    explicit entertainmentwidget(QWidget *parent = nullptr);
    ~entertainmentwidget();

private:
    Ui::entertainmentwidget *ui;
};

#endif // ENTERTAINMENTWIDGET_H
