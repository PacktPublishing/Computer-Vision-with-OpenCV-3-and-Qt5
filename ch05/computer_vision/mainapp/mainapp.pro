
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Computer_Vision
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../cvplugininterface

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qenhancedgraphicsview.cpp

HEADERS += \
        mainwindow.h \
    qenhancedgraphicsview.h

FORMS += \
        mainwindow.ui

win32: {
    include("c:/dev/opencv/opencv.pri")
}

unix: !macx{
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

unix: macx{
INCLUDEPATH += /usr/local/include
LIBS += -L"/usr/local/lib" \
    -lopencv_world
}

# Add more language entries here, following the same naming rule
TRANSLATIONS = language_tr.ts
