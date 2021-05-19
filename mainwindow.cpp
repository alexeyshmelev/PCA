#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <exception>
#include <string>
#include "classes"
using namespace std;
namespace Global {int x = 0; int y = 0;}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setCentralWidget(ui->centralwidget);

    QGridLayout *grid = new QGridLayout();
    grid->setRowStretch(0, 2);
    grid->setRowStretch(1, 1);
    grid->setRowStretch(2, 10);

    Canvas *canvas = new Canvas;
    canvas->setFixedWidth(300);
    canvas->setFixedHeight(300);
    grid->addWidget(canvas, 2, 0, 1, 3, Qt::AlignCenter);

    QComboBox *pca_type = new QComboBox();
    pca_type->setFixedWidth(100);
    QStringList types = {"Scores", "Loadings"};
    pca_type->addItems(types);
    grid->addWidget(pca_type, 1, 0, Qt::AlignCenter);

    pca_x = new QComboBox();
    pca_x->setFixedWidth(100);
    QStringList num_rows_x = canvas->countRows();
    pca_x->addItems(num_rows_x);
    grid->addWidget(pca_x, 1, 1, Qt::AlignCenter);

    pca_y = new QComboBox();
    pca_y->setFixedWidth(100);
    QStringList num_rows_y = canvas->countRows();
    pca_y->addItems(num_rows_y);
    grid->addWidget(pca_y, 1, 2, Qt::AlignCenter);

    QLabel *type = new QLabel("Type");
    QLabel *x = new QLabel("X");
    QLabel *y = new QLabel("Y");
    grid->addWidget(type, 0, 0, Qt::AlignBottom | Qt::AlignHCenter);
    grid->addWidget(x, 0, 1, Qt::AlignBottom | Qt::AlignHCenter);
    grid->addWidget(y, 0, 2, Qt::AlignBottom | Qt::AlignHCenter);

    ui->centralwidget->setLayout(grid);

    connect(pca_type, SIGNAL(currentIndexChanged(int)), canvas, SLOT(Draw_type(int)));
    connect(pca_type, SIGNAL(currentIndexChanged(int)), this, SLOT(Draw(int)));
    connect(pca_x, SIGNAL(currentIndexChanged(int)), canvas, SLOT(Draw_x(int)));
    connect(pca_y, SIGNAL(currentIndexChanged(int)), canvas, SLOT(Draw_y(int)));
}

QStringList Canvas::countRows(){
    PCA<double> test;
    PCA<double> data;
    ifstream file;
    file.open("data.txt");
    file >> test;
    file.close();
    test.nipals();
    if (type == 0) data = test.pca_score();
    else data = test.pca_weight();
    QStringList rows;
    for (int i = 0; i < data.columns; i++) rows += QString::number(i+1);
    return rows;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Window, Qt::white);
    (this)->setAutoFillBackground(true);
    (this)->setPalette(Pal);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.drawLine(10, 150, 290, 150);
    painter.drawLine(150, 290, 150, 10);

    QString pcax = "PCA " + QString::number(Global::x + 1);
    QString pcay = "PCA " + QString::number(Global::y + 1);
    painter.drawText(260, 170, pcax);
    painter.drawText(110, 20, pcay);

    painter.setBrush(Qt::black);
    PCA<double> test;
    PCA<double> data;
    ifstream file;
    file.open("data.txt");
    file >> test;
    file.close();
    test.nipals();
    if (type == 0) data = test.pca_score();
    else data = test.pca_weight();
    for (int i = 0; i < data.rows; i++) painter.drawEllipse(QRect(150 + data.matrix.at(i).at(Global::x) * 30, 150 - data.matrix.at(i).at(Global::y) * 30, 6, 6));

}

void Canvas::Draw_type(int idx){
    type = idx;
    repaint();
}

void Canvas::Draw_x(int idx){
    Global::x = idx;
    repaint();
}

void Canvas::Draw_y(int idx){
    Global::y = idx;
    repaint();
}

void MainWindow::Draw(int idx){
    pca_x->blockSignals(true);
    pca_y->blockSignals(true);
    int type = idx;
    PCA<double> test;
    PCA<double> data;
    ifstream file;
    file.open("data.txt");
    file >> test;
    file.close();
    test.nipals();
    if (type == 0) data = test.pca_score();
    else data = test.pca_weight();
    QStringList rows;
    for (int i = 0; i < data.columns; i++) rows += QString::number(i+1);
    pca_x->clear();
    pca_x->addItems(rows);
    pca_x->setCurrentIndex(Global::x);
    pca_y->clear();
    pca_y->addItems(rows);
    pca_y->setCurrentIndex(Global::y);
    repaint();
    pca_x->blockSignals(false);
    pca_y->blockSignals(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{}
