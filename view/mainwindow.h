#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "model/Place.h"
#include <QStackedWidget>
#include <QListWidget>
#include <model/statisticsResult.h>
#include <QMessageBox>
#include "model/uicommon.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// controller forward declaration
class PlaceController;

// classe MainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // abilita disabilita dark mode
    void toggleDarkMode(bool enabled);
    // costruttore
    explicit MainWindow(QWidget *parent = nullptr);
    // distruttore
    ~MainWindow();
    // prendi testo ricerca
    QString getSearchText() const;
    // prendi citta selezionata
    QString getSelectedCity() const;
    // setta il controller
    void setController(PlaceController* controller);
    // pulisci campi ricerca
    void clearSearchFields();
    // riempi combo box citta
    void populateCityComboBox(const std::vector<std::shared_ptr<Place>>& places);
    // vai su widget crediti
    void setWidgetCredits();
    // vai su widget principale
    void setWidgetMain();
    // setta statistiche
    void setStats(const StatisticsResult& stats);
    // aggiorna risultati
    void updateResults(const std::map<QString, std::vector<std::shared_ptr<Place>>>& groupedResults);
    // prendi list widget
    QListWidget* getListWidget() const;
    // setta widget dettagli
    void setDetailsWidget(QWidget* widget);
    // mostra widget per nome
    void showWidgetByName(const QString& name);
    // prendi widget per nome
    QWidget* getWidgetByName(const QString& name) const;
    // prendi pagina corrente
    QWidget* getCurrentPage() const;
    // aggiorna testo azione debug
    void updateDebugActionText(bool debugEnabled);
    // mostra messaggio
    void showMessage(UiCommon::MsgIcon icon,
                     const QString& title,
                     const QString& text);
    // chiedi conferma
    bool askConfirmation(const QString& title,
                         const QString& question);
    // chiedi apri file
    QString askOpenFile  (const QString& caption,
                        const QString& filter,
                        const QString& startDir = QString()) const;
    // chiedi salva file
    QString askSaveFile  (const QString& caption,
                        const QString& filter,
                        const QString& startDir = QString()) const;
    // e dark mode attiva
    bool getDarkModeEnabled();
    // mostra messaggio status bar
    void showStatusBarMsg(const QString& message, int timeoutMs = 3000);
private:
    // stato dark mode
    bool isDarkModeEnabled = false;
    // mappa widget
    QMap<QString, QWidget*> widgetMap;
    // widget impilato
    QStackedWidget* stackedWidget;
    // ui design
    Ui::MainWindow *ui;
    // puntatore controller
    PlaceController* controller;
protected:
    // evento chiusura
    void closeEvent(QCloseEvent* event) override;
};
#endif // MAINWINDOW_H
