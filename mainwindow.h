#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    explicit MainWindow(PlaceController& controller, QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    PlaceController& controller;

private slots:
    void findPlaces();
    void importFromXml();
};
#endif // MAINWINDOW_H
