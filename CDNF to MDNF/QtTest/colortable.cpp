#include "colortable.h"

QColor ColorTable::convertColor(int color) {
    Qt::GlobalColor qcolor;
    if (color ==  0) qcolor = Qt::transparent;
    if (color ==  1) return QColor(190, 16, 255);
    if (color ==  2) qcolor = Qt::green;
    if (color ==  3) return QColor(100, 0, 0);
    if (color ==  4) return QColor(255, 61, 67);
    if (color ==  5) qcolor = Qt::magenta;
    if (color ==  6) qcolor = Qt::yellow;
    if (color ==  7) qcolor = Qt::black;
    if (color ==  8) qcolor = Qt::black;
    if (color ==  9) return QColor(190, 16, 255);
    if (color == 10) qcolor = Qt::black;
    if (color == 11) qcolor = Qt::black;
    if (color == 12) return QColor(150, 51, 37);
    if (color == 13) qcolor = Qt::black;
    if (color == 14) qcolor = Qt::white;
    return qcolor;
}
std::vector<std::vector<QLabel*>> ColorTable::genTable(QWidget* parent, int x_size, int y_size){
    std::vector<std::vector<QLabel*>> table(y_size);
    auto table_w = new QWidget(parent);
    QGridLayout *btnLayout = new QGridLayout(table_w);
    for (int i = 0; i < y_size; ++i) {
        table[i].resize(x_size);
        for (int j = 0; j < x_size; ++j) {
            table[i][j] = new QLabel(parent);
            btnLayout->addWidget(table[i][j], i, j);
            btnLayout->setSpacing(0);
        }
    }
    return table;
}
void ColorTable::setTable(Table table, int vars, int num, int step){
    auto gen_table_res = table.genTable(vars, num, step);
    auto vec = gen_table_res.first;
    std::cout <<gen_table_res.second;
    table_widget->setRowCount(vec.size());
    table_widget->setColumnCount(vec[0].size());
    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = 0; j < vec[i].size(); ++j) {
            auto tmp = new QTableWidgetItem(QString(vec[i][j].first.c_str()));
            table_widget->setItem(i, j, tmp);
            table_widget->item(i, j)->setBackground(convertColor(vec[i][j].second / 16));
            table_widget->item(i, j)->setForeground(convertColor(vec[i][j].second % 16));
        }
    }
}
void ColorTable::updateAns() {
    table.calc(vars, num, 8);
    result->setText(QCoreApplication::translate("MainWindow", table.genAns().c_str(), nullptr));
}
void ColorTable::updateTable() {
    setTable(table, vars, num, state);
    table_widget->resizeRowsToContents();
    table_widget->resizeColumnsToContents();
}
void ColorTable::onSliderState(int value) {
    state = value;
    updateTable();
}
void ColorTable::onSliderVars(int value) {
    vars = value;
    updateTable();
}
void ColorTable::onTextEdit(const QString & text) {
    num = text.toInt();
    std::string binary;
    if (vars == 1) binary = std::bitset<2>(num).to_string();
    if (vars == 2) binary = std::bitset<4>(num).to_string();
    if (vars == 3) binary = std::bitset<8>(num).to_string();
    if (vars == 4) binary = std::bitset<16>(num).to_string();
    if (vars == 5) binary = std::bitset<32>(num).to_string();
    if (vars == 6) binary = std::bitset<64>(num).to_string();
    textEdit2->blockSignals(true);
    textEdit2->setText(QCoreApplication::translate("MainWindow", binary.c_str(), nullptr));
    textEdit2->blockSignals(false);
    updateTable();
    updateAns();
}
void ColorTable::onTextEditBin(const QString & text) {
    num = text.toInt(nullptr, 2);
    textEdit->blockSignals(true);
    textEdit->setText(QCoreApplication::translate("MainWindow", std::to_string(num).c_str(), nullptr));
    textEdit->blockSignals(false);
    updateTable();
    updateAns();
}
ColorTable::ColorTable() {
    QWidget table_w(this);

    table_widget = new QTableWidget(this);
    table_widget->verticalHeader();
    table_widget->setGeometry(QRect(25, 25, screen_x - 50, screen_y - 130));

    table_widget->setObjectName(QString::fromUtf8("tableWidget"));
    table_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    table_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    table_widget->horizontalHeader()->setVisible(false);
    table_widget->verticalHeader()->setVisible(false);
    updateTable();
    resize(screen_x, screen_y);

    textEdit = new QLineEdit(this);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setGeometry(QRect(200, screen_y - 720 + 630, 191, 31));

    textEdit2 = new QLineEdit(this);
    textEdit2->setObjectName(QString::fromUtf8("textEdit2"));
    textEdit2->setGeometry(QRect(200 + 400, screen_y - 720 + 630, 191, 31));

    horizontalSlider_2 = new QSlider(this);
    horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
    horizontalSlider_2->setGeometry(QRect(119, screen_y - 720 + 670, 1231, 20));
    horizontalSlider_2->setMinimum(0);
    horizontalSlider_2->setMaximum(6);
    horizontalSlider_2->setOrientation(Qt::Horizontal);

    horizontalSlider = new QSlider(this);
    horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
    horizontalSlider->setGeometry(QRect(500 + 400, screen_y - 720 + 640, 101, 20));
    horizontalSlider->setAutoFillBackground(false);
    horizontalSlider->setMinimum(1);
    horizontalSlider->setValue(vars);
    horizontalSlider->setMaximum(5);
    horizontalSlider->setOrientation(Qt::Horizontal);
    horizontalSlider->setInvertedAppearance(false);
    horizontalSlider->setInvertedControls(false);

    connect(horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(onSliderState(int)));
    connect(horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderVars(int)));
    connect(textEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onTextEdit(const QString&)));
    connect(textEdit2, SIGNAL(textChanged(const QString &)), this, SLOT(onTextEditBin(const QString&)));

    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(420 + 400, screen_y - 720 + 640, 71, 20));
    QFont font;
    font.setFamily(QString::fromUtf8("Product Sans Medium"));
    font.setPointSize(12);
    font.setStrikeOut(false);
    label->setFont(font);
    label->setMargin(-1);
    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(30, screen_y - 720 + 641, 171, 20));
    label_2->setFont(font);
    label_2->setMargin(-1);
    label_22 = new QLabel(this);
    label_22->setObjectName(QString::fromUtf8("label_22"));
    label_22->setGeometry(QRect(30 + 400, screen_y - 720 + 641, 171, 20));
    label_22->setFont(font);
    label_22->setMargin(-1);
    label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(30, screen_y - 720 + 670, 91, 20));
    label_3->setFont(font);
    label_3->setMargin(-1);
    label_4 = new QLabel(this);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(30, screen_y - 20, 2000, 20));
    label_4->setFont(font);
    label_4->setMargin(-1);

    result = new QTextEdit(this);
    result->setObjectName(QString::fromUtf8("result"));
    result->setGeometry(QRect(screen_x - 1280 + 950 - 50, screen_y - 720 + 620, 305 + 50, 81));
    result->blockSignals(true);
    result->setText(QCoreApplication::translate("ok, and?", nullptr));
    table = Table(4, 99);
    result->setFont(font);


    label->setText(QCoreApplication::translate("MainWindow", "Variables:", nullptr));
    label_2->setText(QCoreApplication::translate("MainWindow", "Function (in decimal):", nullptr));
    label_22->setText(QCoreApplication::translate("MainWindow", "  Function (in binary):", nullptr));
    label_3->setText(QCoreApplication::translate("MainWindow", "Table state:", nullptr));
    label_4->setText(QCoreApplication::translate("MainWindow",
    "            default table                     removing zero rows         remove cells from zero rows       absorption in strings           remove bad columns                    find true answer                   table for parcing"
    , nullptr));
    textEdit->setText(QCoreApplication::translate("MainWindow", std::to_string(num).c_str(), nullptr));
    result->setText(QCoreApplication::translate("MainWindow", "test", nullptr));
    updateAns();
}
