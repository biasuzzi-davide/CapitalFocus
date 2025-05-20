QT       += core gui
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/placecontroller.cpp \
    view/culturewidget.cpp \
    view/entertainmentwidget.cpp \
    view/foodwidget.cpp \
    main.cpp \
    #main_old.cpp \
    model/Cafe.cpp \
    model/Culture.cpp \
    model/Disco.cpp \
    model/Entertainment.cpp \
    model/Food.cpp \
    model/LocalMarket.cpp \
    model//Mall.cpp \
    model//Restaurant.cpp \
    model//Shopping.cpp \
    view/mainwindow.cpp \
    model/Monument.cpp \
    model/Museum.cpp \
    model/PanoramicPoint.cpp \
    model/Place.cpp \
    model/debugconfig.cpp \
    model/openingFrames.cpp \
    model/placerepository.cpp \
    model/visitor/PlaceImportFromJson.cpp \
    model/visitor/placeExportToJsonVisitor.cpp \
    model/visitor/placeimportfromxml.cpp \
    model/visitor/statisticsvisitor.cpp \
    model/weeklyOpenings.cpp \
    model/visitor/placeexporttoxmlvisitor.cpp \
    view/shoppingwidget.cpp \
    view/createplacewidget.cpp

HEADERS += \
    controller/placecontroller.h \
    view/culturewidget.h \
    view/entertainmentwidget.h \
    view/foodwidget.h \
    model/Cafe.h \
    model/Culture.h \
    model/Disco.h \
    model/Entertainment.h \
    model/Food.h \
    model/LocalMarket.h \
    model/Mall.h \
    model/Monument.h \
    model/Museum.h \
    model/PanoramicPoint.h \
    model/Place.h \
    model/Restaurant.h \
    model/Shopping.h \
    model/debugconfig.h \
    model/import_errors.h \
    model/openingFrames.h \
    model/placerepository.h \
    model/statisticsResult.h \
    model/uicommon.h \
    model/visitor/PlaceImportFromJson.h \
    model/visitor/placeExportToJsonVisitor.h \
    model/visitor/placeimportfromxml.h \
    model/visitor/statisticsvisitor.h \
    model/visitor/placevisitorinterface.h \
    model/weekday.h \
    model/weeklyOpenings.h \
    view/mainwindow.h \
    model/visitor/placeexporttoxmlvisitor.h \
    view/shoppingwidget.h \
    view/createplacewidget.h

FORMS += \
    view/culturewidget.ui \
    view/entertainmentwidget.ui \
    view/foodwidget.ui \
    view/mainwindow.ui \
    view/shoppingwidget.ui \
    view/createplacewidget.ui

CONFIG += sdk_no_version_check
CONFIG += lrelease
CONFIG += embed_translations
QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
