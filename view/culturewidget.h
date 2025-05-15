#ifndef CULTUREWIDGET_H
#define CULTUREWIDGET_H

#include <QWidget>

class PlaceController;  // forward declaration

namespace Ui {
class culturewidget;
}

// Widget per visualizzare i dettagli di un luogo di cultura
class culturewidget : public QWidget
{
    Q_OBJECT

public:
    // Costruttore
    explicit culturewidget(QWidget *parent = nullptr);
    // Distruttore
    ~culturewidget();

    // Imposta i valori dei campi del widget
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
    // Imposta il controller associato
    void setController(PlaceController* c);

private:
    Ui::culturewidget *ui; // Puntatore all'UI generata da Qt Designer
    PlaceController* controller = nullptr; // Puntatore al Controller
};

#endif // CULTUREWIDGET_H
