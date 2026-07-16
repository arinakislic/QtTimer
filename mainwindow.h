#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int timeLeft;       // сколько секунд осталось
    bool isRunning;     // запущен ли таймер

private slots:
    void startTimer();
    void pauseTimer();
    void resetTimer();
    void updateTime();
    void onMinutesChanged(int value);

};
#endif // MAINWINDOW_H
