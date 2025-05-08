#ifndef CULTUREWIDGET_H
#define CULTUREWIDGET_H

#include <QWidget>

class PlaceController;  // forward declaration

namespace Ui {
class culturewidget;
}

class culturewidget : public QWidget
{
    Q_OBJECT

public:
    explicit culturewidget(QWidget *parent = nullptr);
    ~culturewidget();
    void setValues(const QString& name,
                   const QString& city,
                   const QString& description,
                   const QString& rating,
                   const QString& cost,
                   const QString& openings,
                   const QString& studentDiscount,
                   const QString& guidedTour,
                   const QString& culturalFocus,
                   const QString& specific);
    void setController(PlaceController* c);

private:
    bool editingEnabled = false;
    Ui::culturewidget *ui;
    PlaceController* controller = nullptr;
};

#endif // CULTUREWIDGET_H
