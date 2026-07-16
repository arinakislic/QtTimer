#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);

    timeLeft = ui->spinBoxMinutes->value() * 60;
    isRunning = false;
    updateTime();

    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MainWindow::startTimer);
    connect(ui->pushButtonPause, &QPushButton::clicked, this, &MainWindow::pauseTimer);
    connect(ui->pushButtonReset, &QPushButton::clicked, this, &MainWindow::resetTimer);
    connect(ui->spinBoxMinutes, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onMinutesChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTimer()
{
    if (!isRunning) {
        isRunning = true;
        timer->start(1000);
    }
}

void MainWindow::pauseTimer()
{
    if (isRunning) {
        isRunning = false;
        timer->stop();
    }
}

void MainWindow::resetTimer()
{
    timer->stop();
    isRunning = false;
    ui->spinBoxMinutes->setValue(1);
    timeLeft = 60;      // полностью сбросить
    updateTime();
}

void MainWindow::updateTime()
{
    int minutes = timeLeft / 60;
    int seconds = timeLeft % 60;

    ui->lcdNumber->display(QString("%1:%2")
                               .arg(minutes, 2, 10, QChar('0'))
                               .arg(seconds, 2, 10, QChar('0')));

    if (timeLeft > 0 && isRunning) {
        timeLeft--;
    } else if (timeLeft == 0 && isRunning) {
        timer->stop();
        isRunning = false;
    }
}

void MainWindow::onMinutesChanged(int value)
{
    if (!isRunning) {
        timeLeft = value * 60;
        updateTime();
    }
}
