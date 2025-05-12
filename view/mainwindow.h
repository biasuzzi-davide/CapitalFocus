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

class PlaceController; // fw declaration

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void toggleDarkMode(bool enabled);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getSearchText() const;
    QString getSelectedCity() const;
    void setController(PlaceController* controller);
    void clearSearchFields();
    void populateCityComboBox(const std::vector<std::shared_ptr<Place>>& places);
    void setWidgetCredits();
    void setWidgetMain();
    void showStatistics(const StatisticsResult& stats);
    void updateResults(const std::map<QString, std::vector<std::shared_ptr<Place>>>& groupedResults);
    QListWidget* getListWidget() const;
    void setDetailsWidget(QWidget* widget);
    void showWidgetByName(const QString& name);
    QWidget* getWidgetByName(const QString& name) const;
    QWidget* getCurrentPage() const;
    void updateDebugActionText(bool debugEnabled);
    void showMessage(UiCommon::MsgIcon icon,
                     const QString& title,
                     const QString& text);
    bool askConfirmation(const QString& title,
                         const QString& question,
                         QMessageBox::StandardButton defaultBtn = QMessageBox::Yes);
    QString askOpenFile  (const QString& caption,
                        const QString& filter,
                        const QString& startDir = QString()) const;
    QString askSaveFile  (const QString& caption,
                        const QString& filter,
                        const QString& startDir = QString()) const;
    bool getDarkModeEnabled();
private:
    bool isDarkModeEnabled = false;
    QMap<QString, QWidget*> widgetMap;
    QStackedWidget* stackedWidget;
    Ui::MainWindow *ui;
    PlaceController* controller;
};
#endif // MAINWINDOW_H
