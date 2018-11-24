#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QZXing.h>
#include <myviewfinder.h>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class MainWindow;
}

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
    QVBoxLayout *layout;
    QPushButton *copyPushButton;
    QLabel *resultLabel;
    myViewFinder *m_viewFinder;

public slots:
    void refreshResultLabel(QString &result);
    void copyResultToClipboard();
};

#endif // MAINWINDOW_H
