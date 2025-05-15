#ifndef SHOPPINGWIDGET_H
#define SHOPPINGWIDGET_H

#include <QWidget>

class PlaceController; // Dichiarazione forward

namespace Ui {
class shoppingwidget;
}

// Widget per visualizzare i dettagli di un luogo di shopping
class shoppingwidget : public QWidget
{
    Q_OBJECT

public:
    // Costruttore
    explicit shoppingwidget(QWidget *parent = nullptr);
    // Distruttore
    ~shoppingwidget();

    // Imposta i valori dei campi del widget
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
    // Imposta il controller associato
    void setController(PlaceController* c);

private:
    Ui::shoppingwidget *ui; // Puntatore all'UI generata da Qt Designer
    PlaceController* controller = nullptr; // Puntatore al Controller
};

#endif // SHOPPINGWIDGET_H
