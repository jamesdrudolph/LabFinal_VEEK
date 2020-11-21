#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>

#include "D8MCapture.h"

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
    QGraphicsScene *qScene;
    D8MCapture *cap;
    char *image = NULL;
    const int size = 800 * 480 * 4;

    void nextFrame();
    QImage Mat2QImage(Mat const& src);
};

#endif // MAINWINDOW_H
