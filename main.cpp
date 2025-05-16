#include "view/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "model/placerepository.h"
#include "controller/placecontroller.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    PlaceRepository repo;
    MainWindow* window = new MainWindow();
    PlaceController controller(window, repo);
    window->setController(&controller);
    window->show();
    return a.exec();
}
