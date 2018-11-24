#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QZXing.h>

namespace Ui {
class MainWindow;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QPushButton;
class QTimer;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QZXing decoder;

private:
    Ui::MainWindow *ui;
    QWidget *widget;
    QCamera *camera;
    QCameraViewfinder *cameraViewfinder;
    QCameraImageCapture *cameraImageCapture;
    QVBoxLayout *layout;
    QTimer *timer;
    QLabel *resultLabel;
};

#endif // MAINWINDOW_H
