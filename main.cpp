#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "model/placerepository.h"
#include "controller/placecontroller.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    PlaceRepository repo;

    // 1. Crea prima la finestra
    MainWindow* window = new MainWindow();

    // 2. Crea il controller passando la view e il model
    PlaceController controller(window, repo);

    // 3. Se vuoi, puoi registrare il controller dentro la view (opzionale)
    window->setController(&controller);  // solo se hai un setController()

    window->show();
    return a.exec();
}
