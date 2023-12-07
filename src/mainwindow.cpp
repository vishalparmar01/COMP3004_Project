#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <QTimer>

#include "LedWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //images for each step in AED
    QPixmap pix(":/img/img/label_1.png");
    int w = ui->label_1->width();
    int h = ui->label_1->height();
    ui->label_1->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pix2(":/img/img/label_2.png");
    int w2 = ui->label_2->width();
    int h2 = ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(w2,h2,Qt::KeepAspectRatio));

    QPixmap pix3(":/img/img/label_3.png");
    int w3 = ui->label_3->width();
    int h3 = ui->label_3->height();
    ui->label_3->setPixmap(pix3.scaled(w3,h3,Qt::KeepAspectRatio));

    QPixmap pix4(":/img/img/label_4.jpg");
    int w4 = ui->label_4->width();
    int h4 = ui->label_4->height();
    ui->label_4->setPixmap(pix4.scaled(w4,h4,Qt::KeepAspectRatio));

    QPixmap pix5(":/img/img/label_5.png");
    int w5 = ui->label_5->width();
    int h5 = ui->label_5->height();
    ui->label_5->setPixmap(pix5.scaled(w5,h5,Qt::KeepAspectRatio));

    QPixmap pix6(":/img/img/label_6.png");
    int w6 = ui->label_6->width();
    int h6 = ui->label_6->height();
    ui->label_6->setPixmap(pix6.scaled(w6,h6,Qt::KeepAspectRatio));

    QPixmap pix7(":/img/img/label_7.png");
    int w7 = ui->label_7->width();
    int h7 = ui->label_7->height();
    ui->label_7->setPixmap(pix7.scaled(w7,h7,Qt::KeepAspectRatio));

    QPixmap pix8(":/img/img/label_8.png");
    int w8 = ui->label_8->width();
    int h8 = ui->label_8->height();
    ui->label_8->setPixmap(pix8.scaled(w8,h8,Qt::KeepAspectRatio));

    QPixmap pix9(":/img/img/heart.png");
    int w9 = ui->heart_label->width();
    int h9 = ui->heart_label->height();
    ui->heart_label->setPixmap(pix9.scaled(w9,h9,Qt::KeepAspectRatio));
    
    //comboBox text
    ui->padType->addItem("Choose pads");
    ui->padType->addItem("Adult pads");
    ui->padType->addItem("Infant pads");

    led1 = new LedWidget(this);
    ui->led_1->addWidget(led1);
    connect(ui->turnOnButton, &QPushButton::clicked, led1, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led1, &LedWidget::turnOff);

    led2 = new LedWidget(this);
    ui->led_2->addWidget(led2);
    connect(ui->turnOnButton, &QPushButton::clicked, led2, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led2, &LedWidget::turnOff);

    led3 = new LedWidget(this);
    ui->led_3->addWidget(led3);
    connect(ui->turnOnButton, &QPushButton::clicked, led3, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led3, &LedWidget::turnOff);

    led4 = new LedWidget(this);
    ui->led_4->addWidget(led4);
    connect(ui->turnOnButton, &QPushButton::clicked, led4, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led4, &LedWidget::turnOff);

    led5 = new LedWidget(this);
    ui->led_5->addWidget(led5);
    connect(ui->turnOnButton, &QPushButton::clicked, led5, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led5, &LedWidget::turnOff);

    led6 = new LedWidget(this);
    ui->led_6->addWidget(led6);
    connect(ui->turnOnButton, &QPushButton::clicked, led6, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led6, &LedWidget::turnOff);

    led7 = new LedWidget(this);
    ui->led_7->addWidget(led7);
    connect(ui->turnOnButton, &QPushButton::clicked, led7, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led7, &LedWidget::turnOff);

    led8 = new LedWidget(this);
    ui->led_8->addWidget(led8);
    connect(ui->turnOnButton, &QPushButton::clicked, led8, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led8, &LedWidget::turnOff);

    led9 = new LedWidget(this);
    ui->led_9->addWidget(led9);
    connect(ui->turnOnButton, &QPushButton::clicked, led9, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led9, &LedWidget::turnOff);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTime()));

    connect(ui->power_on, SIGNAL(clicked()), this, SLOT(deviceOn()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_electrode_pads_stateChanged(int arg1)
{
    if(arg1){
        QMessageBox::information(this, "title", "The electrode pads are placed");
    }else{
        QMessageBox::information(this, "title", "The electrode pads are not placed");
    }
}

void MainWindow::handleTime() {
    timeCount+=1;
    ui->elapsedTime->display(timeCount);
}

void MainWindow::stayCalm() {ui->display->setText("STAY CALM"); }

void MainWindow::checkResponsiveness() { ui->display->setText("CHECK RESPONSIVENESS"); }

void MainWindow::callForHelp() { ui->display->setText("CALL FOR HELP"); }

void MainWindow::usePass() { ui->display->setText("USE PASS"); }

void MainWindow::checkBreathing() { ui->display->setText("CHECK BREATHING"); }

void MainWindow::attachPads() { ui->display->setText("ATTACH PADS"); }

void MainWindow::padsAttached() {  ui->display->setText("PADS ALREADY ATTACHED"); }

void MainWindow::outOfBattery() {  ui->display->setText("UNIT FAILED: CHANGE BATTERIES"); }

void MainWindow::resetDisplay() { ui->display->setText(""); }

void MainWindow::deviceOn() {
    timer->start(2000);
    // Check if there is enough battery to provide 3 Shocks.
    qDebug() << battery->getBattery();
    if (battery->getBattery() >= 47) {
        qDebug() << "Performing Self-Tests: ";

        qDebug() << "BATTERY TEST: PASSED";
        qDebug() << "DEFIBRILLATION ELECTRODED CONNECTION TEST: PASSED";
        qDebug() << "ECG CIRCUITRY TEST: PASSED";
        qDebug() << "CHARGE & DISCHARGE CIRCUITRY TEST: PASSED";
        qDebug() << "MICROPROCESSOR HARDWARE/SOFTWARE TEST : PASSED";
        qDebug() << "CPR CIRCUITRY TEST: PASSED";

        // TURN TICK SIGNAL TO GREEN -> AFTER TICK IS ADDED

        ui->display->setText("UNIT OK");

        if (!(ui->electrode_pads->isChecked())) {
            QTimer::singleShot(3000, this, SLOT(stayCalm()));

            // CHECK RESPONSIVENESS
            QTimer::singleShot(10000, led1, &LedWidget::turnOn);
            QTimer::singleShot(10000, this, SLOT(checkResponsiveness()));
            QTimer::singleShot(15000, led1, &LedWidget::turnOff);
            QTimer::singleShot(15000, this, SLOT(resetDisplay()));

            // CALL FOR HELP
            QTimer::singleShot(25000, led2, &LedWidget::turnOn);
            QTimer::singleShot(25000, this, SLOT(callForHelp()));
            QTimer::singleShot(30000, led2, &LedWidget::turnOff);
            QTimer::singleShot(30000, this, SLOT(resetDisplay()));

            // USE PASS
            QTimer::singleShot(40000, led3, &LedWidget::turnOn);
            QTimer::singleShot(40000, this, SLOT(usePass()));
            QTimer::singleShot(45000, led3, &LedWidget::turnOff);
            QTimer::singleShot(45000, this, SLOT(resetDisplay()));

            // CHECK BREATHING
            QTimer::singleShot(55000, led4, &LedWidget::turnOn);
            QTimer::singleShot(55000, this, SLOT(checkBreathing()));
            QTimer::singleShot(60000, led4, &LedWidget::turnOff);
            QTimer::singleShot(60000, this, SLOT(resetDisplay()));

            // ATTACH PADS
            QTimer::singleShot(70000, led5, &LedWidget::turnOn);
            QTimer::singleShot(70000, this, SLOT(attachPads()));
            QTimer::singleShot(75000, led5, &LedWidget::turnOff);
            QTimer::singleShot(75000, this, SLOT(resetDisplay()));
        }
        else {
            QTimer::singleShot(3000, led5, &LedWidget::turnOn);
            QTimer::singleShot(3000, this, SLOT(padsAttached()));
            QTimer::singleShot(8000, led5, &LedWidget::turnOff);
            qDebug() << "\nPads already attached move to next step";
        }
    }
    else {
        QTimer::singleShot(3000, this, SLOT(outOfBattery()));
    }
}


