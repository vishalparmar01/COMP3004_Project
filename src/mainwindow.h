#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <LedWidget.h>
#include <battery.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_electrode_pads_stateChanged(int arg1);
    void handleTime();
    void deviceOn();
    void stayCalm();
    void checkResponsiveness();
    void callForHelp();
    void usePass();
    void checkBreathing();
    void attachPads();
    void resetDisplay();
    void padsAttached();
    void outOfBattery();

private:
    Ui::MainWindow *ui;
    LedWidget *led = new LedWidget();
    Battery *battery = new Battery(100);
    QTimer *timer;
    int timeCount = 0;
    LedWidget *led1;
    LedWidget *led2;
    LedWidget *led3;
    LedWidget *led4;
    LedWidget *led5;
    LedWidget *led6;
    LedWidget *led7;
    LedWidget *led8;
    LedWidget *led9;
};
#endif // MAINWINDOW_H
