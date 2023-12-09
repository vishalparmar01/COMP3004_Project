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

    //****************************images for each step in AED***************************
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

    //*****************ECG Graphs below*******************//

    QPixmap pix10(":/img/img/sinus.png");
    int w10 = ui->ecg_label->width();
    int h10 = ui->ecg_label->height();
    ui->ecg_label->setPixmap(pix10.scaled(w10,h10,Qt::KeepAspectRatio));

    /*
    QPixmap pix11(":/img/img/asystole.png");
    int w11 = ui->ecg_label->width();
    int h11 = ui->ecg_label->height();
    ui->ecg_label->setPixmap(pix11.scaled(w11,h11,Qt::KeepAspectRatio));

    QPixmap pix12(":/img/img/vf.png");
    int w12 = ui->ecg_label->width();
    int h12 = ui->ecg_label->height();
    ui->ecg_label->setPixmap(pix12.scaled(w12,h12,Qt::KeepAspectRatio));

    QPixmap pix13(":/img/img/vt.png");
    int w13 = ui->ecg_label->width();
    int h13 = ui->ecg_label->height();
    ui->ecg_label->setPixmap(pix13.scaled(w13,h13,Qt::KeepAspectRatio));
*/

    //*********************************SELF TEST IMAGES************************//


    /*
    QPixmap pix15(":/img/img/self_green.jpeg");
    int w15 = ui->self_test_label->width();
    int h15 = ui->self_test_label->height();
    ui->self_test_label->setPixmap(pix15.scaled(w15,h15,Qt::KeepAspectRatio));
    */

    //*******************************************************************//
    
    //dfibs pads drop box
    ui->padType->addItem("Choose pads");
    ui->padType->addItem("ADULT PADS");
    ui->padType->addItem("INFANT PADS");

    //compressions dropbox
    ui->compression_type->addItem("2-2.25 inches");
    ui->compression_type->addItem("<2 inches");
    ui->compression_type->addItem("<0.75 inches");

    //********************LED LIGHTS WIDGET*************************//
    led1 = new LedWidget(this);
    ui->led_1->addWidget(led1);

    led2 = new LedWidget(this);
    ui->led_2->addWidget(led2);

    led3 = new LedWidget(this);
    ui->led_3->addWidget(led3);

    led4 = new LedWidget(this);
    ui->led_4->addWidget(led4);

    led5 = new LedWidget(this);
    ui->led_5->addWidget(led5);

    led6 = new LedWidget(this);
    ui->led_6->addWidget(led6);

    led7 = new LedWidget(this);
    ui->led_7->addWidget(led7);

    led8 = new LedWidget(this);
    ui->led_8->addWidget(led8);

    led9 = new LedWidget(this);
    ui->led_9->addWidget(led9);

    //*******************************************************************************//

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTime()));

    connect(ui->power_on, SIGNAL(clicked()), this, SLOT(deviceOn()));

    connect(ui->padType, SIGNAL(currentIndexChanged(int)), this, SLOT(selectPadType()));
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

void MainWindow::stayCalm() {
    ui->display->setText("STAY CALM");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::checkResponsiveness() {
    ui->display->setText("CHECK RESPONSIVENESS");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::callForHelp() {
    ui->display->setText("CALL FOR HELP");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::usePass() {
    ui->display->setText("USE PASS");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::checkBreathing() {
    ui->display->setText("CHECK BREATHING");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::attachPads() {
    ui->display->setText("ATTACH PADS");
    ui->display->setAlignment(Qt::AlignCenter);
    qDebug() << "Please choose PADS to attach";
}

void MainWindow::padsAttached() {
    ui->display->setText(pads + " ATTACHED");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::outOfBattery() {
    ui->display->setText("UNIT FAILED: CHANGE BATTERIES");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::resetDisplay() {
    ui->display->setText("");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::awayFromPatient() {
    ui->display->setText("DON'T TOUCH THE PATIENT - ANALYZING");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::deviceOn() {
    timer->start(1000);
    // Check if there is enough battery to provide 3 Shocks.
    if (battery->getBattery() >= 940) {
        qDebug() << "Performing Self-Tests: ";

        qDebug() << "BATTERY TEST: PASSED";
        qDebug() << "DEFIBRILLATION ELECTRODED CONNECTION TEST: PASSED";
        qDebug() << "ECG CIRCUITRY TEST: PASSED";
        qDebug() << "CHARGE & DISCHARGE CIRCUITRY TEST: PASSED";
        qDebug() << "MICROPROCESSOR HARDWARE/SOFTWARE TEST : PASSED";
        qDebug() << "CPR CIRCUITRY TEST: PASSED";

        // TURN TICK SIGNAL TO GREEN -> AFTER TICK IS ADDED

        ui->display->setText("UNIT OK");
        ui->display->setAlignment(Qt::AlignCenter);

        QPixmap pix14(":/img/img/self_green.png");
        int w14 = ui->self_test_label->width();
        int h14 = ui->self_test_label->height();
        ui->self_test_label->setPixmap(pix14.scaled(w14,h14,Qt::KeepAspectRatio));


        if (!(ui->electrode_pads->isChecked())) {
            QTimer::singleShot(3000, this, SLOT(stayCalm()));

            // CHECK RESPONSIVENESS
            QTimer::singleShot(6000, led1, &LedWidget::turnOn);
            QTimer::singleShot(6000, this, SLOT(checkResponsiveness()));
            QTimer::singleShot(11000, led1, &LedWidget::turnOff);
            QTimer::singleShot(11000, this, SLOT(resetDisplay()));

            // CALL FOR HELP
            QTimer::singleShot(12000, led2, &LedWidget::turnOn);
            QTimer::singleShot(12000, this, SLOT(callForHelp()));
            QTimer::singleShot(17000, led2, &LedWidget::turnOff);
            QTimer::singleShot(17000, this, SLOT(resetDisplay()));

            // USE PASS
            QTimer::singleShot(18000, led3, &LedWidget::turnOn);
            QTimer::singleShot(18000, this, SLOT(usePass()));
            QTimer::singleShot(23000, led3, &LedWidget::turnOff);
            QTimer::singleShot(23000, this, SLOT(resetDisplay()));

            // CHECK BREATHING
            QTimer::singleShot(24000, led4, &LedWidget::turnOn);
            QTimer::singleShot(24000, this, SLOT(checkBreathing()));
            QTimer::singleShot(29000, led4, &LedWidget::turnOff);
            QTimer::singleShot(29000, this, SLOT(resetDisplay()));

            // ATTACH PADS
            QTimer::singleShot(30000, led5, &LedWidget::turnOn);
            QTimer::singleShot(30000, this, SLOT(attachPads()));

        }
        else {
            pads = ui->padType->currentText();
            QTimer::singleShot(3000, led5, &LedWidget::turnOn);
            QTimer::singleShot(3000, this, SLOT(padsAttached()));
            QTimer::singleShot(8000, led5, &LedWidget::turnOff);
            qDebug() << "\n" << pads + " already attached -> Move to next step";
            aed->setShockValues(pads);
        }
    }
    else {
        QPixmap pix14(":/img/img/self_red.jpg");
        int w14 = ui->self_test_label->width();
        int h14 = ui->self_test_label->height();
        ui->self_test_label->setPixmap(pix14.scaled(w14,h14,Qt::KeepAspectRatio));
        qDebug() << "SELF TEST FAILED";
        QTimer::singleShot(3000, this, SLOT(outOfBattery()));
        timer->stop();
    }
}

void MainWindow::selectPadType() {
    QTimer::singleShot(3000, led5, &LedWidget::turnOff);
    QTimer::singleShot(3000, this, SLOT(resetDisplay()));
    pads = ui->padType->currentText();
    if (aed->setShockValues(pads)) {
        qDebug() << pads + " ATTACHED and Shock Values Set";
        QTimer::singleShot(4000, this, SLOT(padsAttached()));
        QTimer::singleShot(8000, led6, &LedWidget::turnOn);
        QTimer::singleShot(8000, this, SLOT(awayFromPatient()));
    }
    else {
        qDebug() << "PLEASE MAKE RIGHT PAD SELECTION";
    }
}




