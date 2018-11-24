#include "mainwindow.h"
#include <QApplication>
#include <QZXing.h>
#include <QDebug>
#include <QImage>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
