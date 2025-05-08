#ifndef FOODWIDGET_H
#define FOODWIDGET_H

#include <QWidget>

class PlaceController;  // forward declaration

namespace Ui {
class foodwidget;
}

class foodwidget : public QWidget
{
    Q_OBJECT

public:
    explicit foodwidget(QWidget *parent = nullptr);
    ~foodwidget();
    void setValues(const QString& name,
                   const QString& city,
                   const QString& description,
                   const QString& rating,
                   const QString& cost,
                   const QString& openings,
                   const QString& takeAway,
                   const QString& avgWaiting,
                   const QString& veganMenu,
                   const QString& specific);
    void setController(PlaceController* c);
private:
    Ui::foodwidget *ui;
    PlaceController* controller = nullptr;
};

#endif // FOODWIDGET_H
