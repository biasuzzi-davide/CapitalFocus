#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "model/placerepository.h"
#include "controller/placecontroller.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    PlaceRepository repo;
    QApplication::setStyle("Fusion");

    // 1. Crea prima la finestra
    MainWindow* window = new MainWindow();



    QString style = R"(
QWidget {
    background-color: #f7f7f7;
    font-family: 'Segoe UI';
    font-size: 11pt;
    color: #333333;
}

QPushButton {
    background-color: #8B0000;
    color: white;
    border: none;
    border-radius: 6px;
    padding: 8px 16px;
}

QPushButton:hover {
    background-color: #a30000;
}

QLineEdit, QComboBox {
    background-color: white;
    border: 1px solid #cccccc;
    padding: 6px;
    border-radius: 4px;
}

QListWidget {
    background-color: white;
    border: 1px solid #cccccc;
}

QListWidget::item:selected {
    background-color: #8B0000;
    color: white;
}

QMenuBar {
    background-color: #f7f7f7;
}

QMenuBar::item:selected {
    background-color: #dddddd;
}

QStatusBar {
    background-color: #f7f7f7;
    border-top: 1px solid #cccccc;
}
)";
    qApp->setStyleSheet(style);

    QFont base("Arial", 11);
    a.setFont(base);

    // 2. Crea il controller passando la view e il model
    PlaceController controller(window, repo);

    // 3. Se vuoi, puoi registrare il controller dentro la view (opzionale)
    window->setController(&controller);

    window->show();
    return a.exec();
}
