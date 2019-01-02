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
    //Задаём имя окна
    setWindowTitle("QR Reader");
    //Создаём главный виджет, на котором будут располагаться элементы
    widget = new QWidget();
    setCentralWidget(widget);
    //Создаём наш видоискатель
    m_viewFinder = new myViewFinder(this);
    m_viewFinder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //Создаём кнопку для копирования результата в буфер обмена
    copyPushButton = new QPushButton();
    copyPushButton->setEnabled(0);
    copyPushButton->setText("Копировать");
    //Создаём поле для результата
    resultLabel = new QLabel(this);
    //Инициализируем вертикальный слой и добавляем в него все элементы
    layout = new QVBoxLayout();
    layout ->addWidget(m_viewFinder);
    layout->addWidget(resultLabel);
    layout->addWidget(copyPushButton);
    //Устанавливаем слой
    widget->setLayout(layout);
    //Объединяем сигнал обнаружения QR кода и слот обновления результата
    connect(m_viewFinder, SIGNAL(detectedQRCode(QString&)), SLOT(refreshResultLabel(QString&)));
    // Устанавливаем обработчик кнопки "Копировать"
    connect(copyPushButton, SIGNAL(clicked()), SLOT(copyResultToClipboard()));
}

void MainWindow::refreshResultLabel(QString &result)
{
    //Активируем кнопку копировать и меняем текст
    copyPushButton->setEnabled(1);
    resultLabel->setText(result);
}

void MainWindow::copyResultToClipboard()
{
    //Помещаем текст в буфер обмена
    QClipboard *clipboard = QApplication::clipboard();
    if(clipboard) {
        clipboard->setText(resultLabel->text());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
