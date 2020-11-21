#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QUdpSocket>
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
    int brightnessAdjust = 0;
    int contrastAdjust = 0;

    void nextFrame();
    QImage Mat2QImage(Mat const& src);
    uchar truncate(uchar value, int adjust); 

    QUdpSocket *udpSocket = nullptr;
    void initSocket();
    void readPendingDatagrams();
    void processDatagram(QByteArray datagram);
};

#endif // MAINWINDOW_H
