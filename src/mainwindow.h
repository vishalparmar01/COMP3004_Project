#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <LedWidget.h>
#include <QTimer>
#include <battery.h>
#include <aed.h>

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
    void stayCalm();
    void checkResponsiveness();
    void callForHelp();
    void usePass();
    void checkBreathing();
    void attachPads();
    void padsAttached();
    void outOfBattery();
    void resetDisplay();
    void handleStateSwitch();
    void deviceOn();
    void deviceOff();
    void onPowerOffTimeout();
    void selectPadType();
    void awayFromPatient();
    void checkCompressions();
    void takeBreaths();
    void startCPR();
    void stopCPR();
    void analyze();
    void handleAnalysing();
    void vfRhythm();
    void shockDelivery();
    void displayVFRhythm();
    void vtRhythm();
    void displayVTRhythm();
    void asysRhythm();
    void displayAsysRhythm();
    void sinusRhythm();
    void displaySinusRhythm();
    void startAnalysing();
    void changeBattery();

private:
    Ui::MainWindow *ui;
    Battery *battery = new Battery(1050);
    int timeCount = 0;
    int stateCount = 1;
    LedWidget *led1;
    LedWidget *led2;
    LedWidget *led3;
    LedWidget *led4;
    LedWidget *led5;
    LedWidget *led6;
    LedWidget *led7;
    LedWidget *led8;
    LedWidget *led9;
    QTimer* timer;
    QTimer* powerOffTimer;
    QTimer* stateSwitchTimer;
    QString pads;
    AED *aed = new AED();
    bool powerOnButtonClicked;
    int compressionCount=0;
    int currentShock = 0;
};
#endif // MAINWINDOW_H
