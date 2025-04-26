#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "model/Place.h"

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
    void updateResults(const std::vector<std::shared_ptr<Place>>& results);
    void setController(PlaceController* controller);
    void clearSearchFields();
    void populateCityComboBox(const std::vector<std::shared_ptr<Place>>& places);
private:
    Ui::MainWindow *ui;
    PlaceController* controller;
};
#endif // MAINWINDOW_H
