#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Создаём приложение и окно и запускаем
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
