#include <QApplication>
#include <QPushButton>
#include <qgridlayout.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qobject.h>
#include <QtGui>
#include <QDebug>
#include <QSlider>
#include "ui_mainwindow.h"
#include "colortable.h"

int main(int argc, char **argv) {
    QApplication app (argc, argv);

    auto table = ColorTable();
    table.show();
    return app.exec();
}
