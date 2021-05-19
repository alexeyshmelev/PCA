#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QPainter>
#include <QPalette>

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QComboBox *pca_x;
    QComboBox *pca_y;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Draw(int);

private:
    Ui::MainWindow *ui;
};



class Canvas : public QWidget
{
    Q_OBJECT

public:
    int type = 0;
    Canvas(QWidget *parent = nullptr);
    QStringList countRows();

public slots:
    void Draw_type(int);
    void Draw_x(int);
    void Draw_y(int);

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // MAINWINDOW_H
