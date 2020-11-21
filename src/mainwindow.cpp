#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cap = new D8MCapture(0x3b000, "/dev/f2h-dma-memory");
    

    qScene = new QGraphicsScene();
    connect(qScene, &QGraphicsScene::changed, this, &MainWindow::nextFrame);

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
    free(image);
}

void MainWindow::nextFrame() {
    qDebug() << "next frame";

    image = (char*)calloc(1, size);
    cap->read(image);

    QImage qImage(800, 480, QImage::Format_RGB32);
    QRgb pixel;
    
    int index = 0;
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 800; x++) {
            pixel = qRgb(image[index + 2], image[index + 1], image[index]);
            qImage.setPixel(x, y, pixel);
        
            index += 4;
        }
    }

    free(image);
    
    QPixmap qPixmap = QPixmap::fromImage(qImage);

    qScene->clear();
    qScene->addPixmap(qPixmap);
    ui->graphicsView->setScene(qScene);
}
