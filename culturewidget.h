#ifndef CULTUREWIDGET_H
#define CULTUREWIDGET_H

#include <QWidget>

namespace Ui {
class culturewidget;
}

class culturewidget : public QWidget
{
    Q_OBJECT

public:
    explicit culturewidget(QWidget *parent = nullptr);
    ~culturewidget();

private:
    Ui::culturewidget *ui;
};

#endif // CULTUREWIDGET_H
