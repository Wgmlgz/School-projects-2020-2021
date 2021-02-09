TEMPLATE = app TARGET = test_app
QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    colortable.cpp \
    main.cpp

HEADERS += \
    colortable.h

FORMS += \
    mainwindow.ui
