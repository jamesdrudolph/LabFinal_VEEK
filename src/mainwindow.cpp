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

    cap = new D8MCapture(0x3b000, "/dev/f2h-dma-memory");
    image = (char*)malloc(size);

    qScene = new QGraphicsScene();
    connect(qScene, &QGraphicsScene::changed, this, &MainWindow::nextFrame);
    ui->graphicsView->setScene(qScene);

    /*int dfd = open("img.bin", O_RDWR | O_CREAT, 0666);
    ftruncate(dfd, size);
    char *dest = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
    memcpy(dest, image, size);
    munmap(dest, size);
    ::close(dfd);*/

}

MainWindow::~MainWindow()
{
    delete ui;
    delete cap;
    free(image);
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
    cvtColor(src, temp, CV_BGR2RGB);
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits();
    return dest;
}
