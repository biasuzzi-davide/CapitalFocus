#ifndef ENTERTAINMENTWIDGET_H
#define ENTERTAINMENTWIDGET_H

#include <QWidget>

class PlaceController;  // forward declaration

namespace Ui {
class entertainmentwidget;
}

class entertainmentwidget : public QWidget
{
    Q_OBJECT

public:
    explicit entertainmentwidget(QWidget *parent = nullptr);
    ~entertainmentwidget();
    void setValues(const QString& name,
                   const QString& city,
                   const QString& description,
                   const QString& rating,
                   const QString& cost,
                   const QString& openings,
                   const QString& avgStayDuration,
                   const QString& minimumAge,
                   const QString& restrictedEntry,
                   const QString& specific);
    void setController(PlaceController* c);
private:
    Ui::entertainmentwidget *ui;
    PlaceController* controller = nullptr;
};

#endif // ENTERTAINMENTWIDGET_H
