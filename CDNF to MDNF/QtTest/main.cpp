#include <QApplication>
#include <QPushButton>
#include <qgridlayout.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qobject.h>
#include <QtGui>
#include "ui_mainwindow.h"
#include "C:\C\School\CDNF to MDNF\converter.h"
Qt::GlobalColor convertColor(int color) {
    Qt::GlobalColor qcolor;
    if (color ==  0) qcolor = Qt::transparent;
    if (color ==  1) qcolor = Qt::blue;
    if (color ==  2) qcolor = Qt::green;
    if (color ==  3) qcolor = Qt::red;
    if (color ==  4) qcolor = Qt::darkRed;
    if (color ==  5) qcolor = Qt::magenta;
    if (color ==  6) qcolor = Qt::yellow;
    if (color ==  7) qcolor = Qt::black;
    if (color ==  8) qcolor = Qt::gray;
    if (color ==  9) qcolor = Qt::blue;
    if (color == 10) qcolor = Qt::black;
    if (color == 11) qcolor = Qt::black;
    if (color == 12) qcolor = Qt::black;
    if (color == 13) qcolor = Qt::black;
    if (color == 14) qcolor = Qt::darkRed;
    return qcolor;
}
void createTable(QWidget* parent, Table table){
    auto vec = table.genTable(1);
    auto table_w = new QWidget(parent);
    QGridLayout *btnLayout = new QGridLayout(table_w);
    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = 0; j < vec[i].size(); ++j) {
            auto tmp = new QLabel(parent);
            tmp->setText(QString(vec[i][j].first.c_str()));


            QFont font = tmp->font();
            //font.setPointSize(13);
            //font.setBold(true);
            tmp->setFont(font);

            tmp->setAlignment(Qt::AlignHCenter);
            tmp->setFixedSize(7, 15);
            //tmp_button->setText(QString(vec[i][j].c_str()));
            ////tmp_button->setFixedSize(btnSize);
            //
            //
            QPalette palette = tmp->palette();

            palette.setColor(tmp->backgroundRole(), convertColor(vec[i][j].second / 16));
            palette.setColor(tmp->foregroundRole(), convertColor(vec[i][j].second % 16));
            tmp->setAutoFillBackground(true);
            tmp->setPalette(palette);

            btnLayout->addWidget(tmp, i, j);
            btnLayout->setSpacing(0);


        }
    }
    // return table_w;
}
static void onLeft()
 {
     qDebug() << "Left";
 }
static void onRight()
 {
     qDebug() << "right";
 }
int main(int argc, char **argv) {
    QApplication app (argc, argv);
    QMainWindow t;
    Ui::MainWindow ui;
    // ui.setupUi()
    ui.setupUi(&t);
    QWidget main_widget(&t);


    Table table(4, 4555556);

    //  std::cout << "da";
    //{{"a", "a"}}
    createTable(&main_widget, table);
    main_widget.resize(1280, 500);
    t.resize(1280, 720);


    //main_widget.show();
    //  ui.show();
    t.show();
    return app.exec();
}
