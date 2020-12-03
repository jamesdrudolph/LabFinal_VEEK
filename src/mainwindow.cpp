#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    initSocket();

    cap = new D8MCapture(0x3b000, "/dev/f2h-dma-memory");

    qScene = new QGraphicsScene();
    connect(qScene, &QGraphicsScene::changed, this, &MainWindow::nextFrame);
    ui->graphicsView->setScene(qScene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cap;
}

void MainWindow::nextFrame() {
    Mat src;
    bool success = cap->read(src);
    //printf("read success: %s\n", success ? "true" : "false");
    /*QImage qImage(800, 480, QImage::Format_RGB32);
    QRgb pixel;
    
    int index = 0;
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 800; x++) {
            pixel = qRgb(image[index + 2], image[index + 1], image[index]);
            qImage.setPixel(x, y, pixel);
        
            index += 4;
        }
    }*/
    
    QPixmap qPixmap = QPixmap::fromImage(Mat2QImage(src));

    qScene->clear();
    qScene->addPixmap(qPixmap);
}

QImage MainWindow::Mat2QImage(Mat const& src) {
    Mat temp;
    Mat newImage;
    cvtColor(src, temp, CV_BGR2RGB);
    /*
    if (brightnessAdjust != 0) {
        for (int i = 0; i < 800 * 480 * 3; i++) {
            temp.data[i] = truncate(temp.data[i], brightnessAdjust);
        }
    }
    */
    temp.convertTo(newImage, -1, contrastAdjust, brightnessAdjust);
    QImage dest((const uchar *) newImage.data, newImage.cols, newImage.rows, newImage.step, QImage::Format_RGB888);
    dest.bits();
    return dest;
}

uchar MainWindow::truncate(uchar value, int adjust) {
    int adjusted = (int)value + adjust;
    
    if (adjusted > 255) return 255;
    else if (adjusted < 0) return 0;
    return (uchar)adjusted;
}

//refactor everything below this to a server class later for reuse in b/c
void MainWindow::initSocket() {
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 420);

    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readPendingDatagrams);
}

void MainWindow::readPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        processDatagram(datagram);
    }
}

void MainWindow::processDatagram(QByteArray datagram) {
    if (datagram.data() == QStringLiteral("TOGGLE_OVERLAY")) {
        qDebug() << "received TOGGLE_OVERLAY";
        //toggleOverlay();
    } else if (datagram.startsWith("BRIGHTNESS")) {
        qDebug() << "received BRIGHTNESS";
        brightnessAdjust = std::stoi(datagram.split(':')[1].data());
    } else if (datagram.startsWith("CONTRAST")) {
        qDebug() << "received CONTRAST";
        contrastAdjust = std::stoi(datagram.split(':')[1].data());
    } else {
        qDebug() << datagram;
    }
}
