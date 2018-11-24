#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSizePolicy>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widget = new QWidget();
    setCentralWidget(widget);

    m_viewFinder = new myViewFinder(this);
    m_viewFinder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    copyPushButton = new QPushButton();
    copyPushButton->setEnabled(0);
    copyPushButton->setText("Копировать");

    resultLabel = new QLabel(this);

    layout = new QVBoxLayout();
    layout ->addWidget(m_viewFinder);
    layout->addWidget(resultLabel);
    layout->addWidget(copyPushButton);

    widget->setLayout(layout);

    connect(m_viewFinder, SIGNAL(detectedQRCode(QString&)), SLOT(refreshResultLabel(QString&)));
    connect(copyPushButton, SIGNAL(clicked()), SLOT(copyResultToClipboard()));
}

void MainWindow::refreshResultLabel(QString &result)
{
    copyPushButton->setEnabled(1);
    resultLabel->setText(result);
}

void MainWindow::copyResultToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    if(clipboard) {
        clipboard->setText(resultLabel->text());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
