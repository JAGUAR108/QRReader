#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QPushButton>
#include <QImage>
#include <QDebug>
#include <QZXing.h>
#include <QTimer>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget = new QWidget();
    setCentralWidget(widget);
    camera = new QCamera(this);
    cameraViewfinder = new QCameraViewfinder(this);
    cameraImageCapture = new QCameraImageCapture(camera, this);
    camera->setViewfinder(cameraViewfinder);
    resultLabel = new QLabel(this);

    layout = new QVBoxLayout();
    layout ->addWidget(cameraViewfinder);
    layout->addWidget(resultLabel);
    widget->setLayout(layout);


    decoder.setDecoder( QZXing::DecoderFormat_QR_CODE | QZXing::DecoderFormat_EAN_13 );
//    QString result = decoder.decodeImageFromFile("/Users/bachurin/Documents/Develop/QrReader/qrcode.png");
//    qDebug() << "123 = " + result;

    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
    QObject::connect(cameraImageCapture, &QCameraImageCapture::imageCaptured, [=] (int id, QImage img) {
        //img.save("/Users/bachurin/Desktop/123.png", "PNG");
        QString result = decoder.decodeImage(img);
        if(result > "") {
            resultLabel->setText(result);
        }
    });
    QObject::connect(cameraImageCapture, &QCameraImageCapture::readyForCaptureChanged, [=] (bool state) {
       if(state == true) {
           camera->searchAndLock();
           cameraImageCapture->capture();
           camera->unlock();
       }
    });
    camera->start();
    timer = new QTimer();
    timer->setInterval(1000);

    QObject::connect(timer, &QTimer::timeout, [=]() {
        cameraImageCapture->capture();
    });
    timer->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}
