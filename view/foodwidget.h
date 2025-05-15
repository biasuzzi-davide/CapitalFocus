#ifndef FOODWIDGET_H
#define FOODWIDGET_H

#include <QWidget>

class PlaceController; // Dichiarazione forward

namespace Ui {
class foodwidget;
}

// Widget per visualizzare i dettagli di un luogo di ristorazione
class foodwidget : public QWidget
{
    Q_OBJECT

public:
    // Costruttore
    explicit foodwidget(QWidget *parent = nullptr);
    // Distruttore
    ~foodwidget();

    // Imposta i valori dei campi del widget
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
    // Imposta il controller associato
    void setController(PlaceController* c);

private:
    Ui::foodwidget *ui; // Puntatore all'UI generata da Qt Designer
    PlaceController* controller = nullptr; // Puntatore al Controller
};

#endif // FOODWIDGET_H
