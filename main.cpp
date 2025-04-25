#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "model/placerepository.h"
#include "controller/placecontroller.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    PlaceRepository repo;
    PlaceController controller(repo);
    MainWindow w(controller);
    w.show();

    return a.exec();
}
