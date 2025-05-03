#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "model/Place.h"
#include <QStackedWidget>
#include <QListWidget>
#include <model/statisticsResult.h>

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
private:
    QStackedWidget* stackedWidget;
    Ui::MainWindow *ui;
    PlaceController* controller;
};
#endif // MAINWINDOW_H
