#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCamera>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QCamera camera;
    bool checkCameraAvailability();
};
#endif // MAINWINDOW_H
