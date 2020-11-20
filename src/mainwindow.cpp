#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCameraInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << checkCameraAvailability();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkCameraAvailability()
{
    return QCameraInfo::availableCameras().count() > 0;
}
