#include "view/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "model/placerepository.h"
#include "controller/placecontroller.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    PlaceRepository repo;
    QApplication::setStyle("Fusion");

    MainWindow* window = new MainWindow();

    QFont base("Arial", 11);
    a.setFont(base);

    PlaceController controller(window, repo);

    window->setController(&controller);

    window->show();
    return a.exec();
}
