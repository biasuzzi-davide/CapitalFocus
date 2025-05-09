#ifndef SHOPPINGWIDGET_H
#define SHOPPINGWIDGET_H

#include <QWidget>

class PlaceController;  // forward declaration

namespace Ui {
class shoppingwidget;
}

class shoppingwidget : public QWidget
{
    Q_OBJECT

public:
    explicit shoppingwidget(QWidget *parent = nullptr);
    ~shoppingwidget();
    void setValues(const QString& name,
                   const QString& city,
                   const QString& description,
                   const QString& rating,
                   const QString& cost,
                   const QString& openings,
                   const QString& outdoor,
                   const QString& foodArea,
                   const QString& standNumber,
                   const QString& specific);
    void setController(PlaceController* c);
private:
    Ui::shoppingwidget *ui;
    PlaceController* controller = nullptr;
};

#endif // SHOPPINGWIDGET_H
