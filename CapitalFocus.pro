QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    model/Cafe.cpp \
    model/Culture.cpp \
    model/Disco.cpp \
    model/Entertainment.cpp \
    model/Food.cpp \
    model/LocalMarket.cpp \
    model//Mall.cpp \
    model//Restaurant.cpp \
    model//Shopping.cpp \
    main.cpp \
    mainwindow.cpp \
    model/Monument.cpp \
    model/Museum.cpp \
    model/PanoramicPoints.cpp \
    model/Place.cpp \
    model/weeklyOpenings.cpp

HEADERS += \
    model/Cafe.h \
    model/Culture.h \
    model/Disco.h \
    model/Entertainment.h \
    model/Food.h \
    model/LocalMarket.h \
    model/Mall.h \
    model/Monument.h \
    model/Museum.h \
    model/PanoramicPoints.h \
    model/Place.h \
    model/Restaurant.h \
    model/Shopping.h \
    model/openingFrames.h \
    model/placevisitorinterface.h \
    model/weekday.h \
    model/weeklyOpenings.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    CapitalFocus_en_IT.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
