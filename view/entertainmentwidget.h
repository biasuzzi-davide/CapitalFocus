#ifndef ENTERTAINMENTWIDGET_H
#define ENTERTAINMENTWIDGET_H

#include <QWidget>

class PlaceController;  // forward declaration

class PlaceController; // Dichiarazione forward

namespace Ui {
class entertainmentwidget;
}

// Widget per visualizzare i dettagli di un luogo di intrattenimento
class entertainmentwidget : public QWidget
{
    Q_OBJECT

public:
    // Costruttore
    explicit entertainmentwidget(QWidget *parent = nullptr);
    // Distruttore
    ~entertainmentwidget();

    // Imposta i valori dei campi del widget
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
    // Imposta il controller associato
    void setController(PlaceController* c);

private:
    Ui::entertainmentwidget *ui; // Puntatore all'UI generata da Qt Designer
    PlaceController* controller = nullptr; // Puntatore al Controller
};

#endif // ENTERTAINMENTWIDGET_H
