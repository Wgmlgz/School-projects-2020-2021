#ifndef COLORTABLE_H
#define COLORTABLE_H

#include <QPushButton>
#include "C:\C\School\CDNF to MDNF\converter.h"
#include <QApplication>
#include <QPushButton>
#include <qgridlayout.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qobject.h>
#include <QtGui>
#include <QDebug>
#include <QSlider>
#include <QTextEdit>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableWidget>
#include <bitset>
#include <QHeaderView>
class ColorTable: public QWidget
{
    Q_OBJECT
private slots:
    void onSliderState(int);
    void onSliderVars(int);
    void onTextEdit(const QString&);
    void onTextEditBin(const QString&);
public:
    int vars = 4, num = 666, state = 0;

    const int screen_x = 1800, screen_y = 900;
    QWidget *centralwidget;
    QLineEdit *textEdit;
    QLineEdit *textEdit2;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_22;
    QLabel *label_3;
    QLabel *label_4;
    QTextEdit *result;
    QTableWidget* table_widget;

    Table table = Table(3, 666);
    std::vector<std::vector<QLabel*>> text_table;
    ColorTable();
    ~ColorTable(){ };
    QColor convertColor(int color);
    void updateTable();
    void updateAns();
    std::vector<std::vector<QLabel*>> genTable(QWidget* parent, int x_size, int y_size);
    void setTable(Table table, int vars, int num, int step);
};

#endif // COLORTABLE_H
