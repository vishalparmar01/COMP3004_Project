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

    QPixmap pix10(":/img/img/reset.png");
    int w10 = ui->ecg_label->width();
    int h10 = ui->ecg_label->height();
    ui->ecg_label->setPixmap(pix10.scaled(w10,h10,Qt::KeepAspectRatio));

    QPixmap pix14(":/img/img/reset.png");
    int w14 = ui->compressions_label->width();
    int h14 = ui->compressions_label->height();
    ui->compressions_label->setPixmap(pix14.scaled(w14,h14,Qt::KeepAspectRatio));




    //*******************************************************************//
    
    //dfibs pads drop box
    ui->padType->addItem("Choose pads");
    ui->padType->addItem("ADULT PADS");
    ui->padType->addItem("INFANT PADS");

    //compressions dropbox
    ui->compression_type->addItem("Choose Depth");
    ui->compression_type->addItem("2-2.25 inches");
    ui->compression_type->addItem("<2 inches");
    ui->compression_type->addItem("<0.75 inches");

    ui->scenario->addItem("Choose Scenario");
    ui->scenario->addItem("1 - NORMAL SCENARIO");
    ui->scenario->addItem("2 - PADS ATTACHED");
    ui->scenario->addItem("3 - Loose Battery");
    ui->scenario->addItem("4 - PRE TEST FAIL");

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

    led9 = new LedWidget(this);
    ui->led_9->addWidget(led9);

    //*******************************************************************************//

    timer = new QTimer(this);

    powerOffTimer = new QTimer(this);

    stateSwitchTimer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(handleTime()));    

    connect(ui->power_on, SIGNAL(clicked()), this, SLOT(deviceOn()));

    connect(stateSwitchTimer, SIGNAL(timeout()), this, SLOT(handleStateSwitch()));

    connect(ui->padType, SIGNAL(currentIndexChanged(int)), this, SLOT(selectPadType()));

    connect(powerOffTimer, SIGNAL(timeout()), this, SLOT(onPowerOffTimeout()));

    connect(ui->power_off, SIGNAL(clicked()), this, SLOT(deviceOff()));

    connect(ui->compression, SIGNAL(clicked()), this, SLOT(checkCompressions()));

    connect(ui->perform_cpr, SIGNAL (clicked()), this, SLOT (handleAnalysing()));
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


    QTimer::singleShot(0000, led1, &LedWidget::turnOn);
    QTimer::singleShot(5000, led1, &LedWidget::turnOff);
    QTimer::singleShot(5000, this, SLOT(resetDisplay()));

}

void MainWindow::callForHelp() {
    ui->display->setText("CALL FOR HELP");
    ui->display->setAlignment(Qt::AlignCenter);

    QTimer::singleShot(0000, led2, &LedWidget::turnOn);
    QTimer::singleShot(5000, led2, &LedWidget::turnOff);
    QTimer::singleShot(5000, this, SLOT(resetDisplay()));
}

void MainWindow::usePass() {
    ui->display->setText("USE PASS");
    ui->display->setAlignment(Qt::AlignCenter);

    QTimer::singleShot(0000, led3, &LedWidget::turnOn);
    QTimer::singleShot(5000, led3, &LedWidget::turnOff);
    QTimer::singleShot(5000, this, SLOT(resetDisplay()));
}

void MainWindow::checkBreathing() {
    ui->display->setText("CHECK BREATHING");
    ui->display->setAlignment(Qt::AlignCenter);

    QTimer::singleShot(0000, led4, &LedWidget::turnOn);
    QTimer::singleShot(5000, led4, &LedWidget::turnOff);
    QTimer::singleShot(5000, this, SLOT(resetDisplay()));
}

void MainWindow::attachPads() {
    ui->display->setText("ATTACH PADS");
    ui->display->setAlignment(Qt::AlignCenter);
    qDebug() << "Please choose PADS to attach";
    QTimer::singleShot(0000, led5, &LedWidget::turnOn);
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
    ui->display->setText("DON'T TOUCH THE PATIENT");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::analyze() {
    ui->display->setText("ANALYZING");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::startCPR() {
    ui->display->setText("START CPR");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::takeBreaths() {
    ui->display->setText("2 BREATHS");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::stopCPR() {
    ui->display->setText("STOP CPR");
    ui->display->setAlignment(Qt::AlignCenter);
}


void MainWindow::vfRhythm() {
    ui->display->setText("Vertricular Fibrillation");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::vtRhythm() {
    ui->display->setText("Vertricular Tachycardia");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::asysRhythm() {
    ui->display->setText("Asystole");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::sinusRhythm() {
    ui->display->setText("Sinus");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::shockDelivery() {
    ui->display->setText("Delivering Shock in 3 - 2 - 1");
    ui->display->setAlignment(Qt::AlignCenter);
}


void MainWindow::startAnalysing() {
    ui->display->setText("Start Analysing");
    ui->display->setAlignment(Qt::AlignCenter);
}

void MainWindow::displayVFRhythm() {
    QPixmap pix14(":/img/img/vf.png");
    int w14 = ui->ecg_label->width();
    int h14 = ui->ecg_label->height();
    ui->ecg_label->setPixmap(pix14.scaled(w14,h14,Qt::KeepAspectRatio));

}

void MainWindow::displayVTRhythm( ) {
    QPixmap pix14(":/img/img/vt.png");
    int w14 = ui->ecg_label->width();
    int h14 = ui->ecg_label->height();
    ui->ecg_label->setPixmap(pix14.scaled(w14,h14,Qt::KeepAspectRatio));

}

void MainWindow::displaySinusRhythm() {
    QPixmap pix14(":/img/img/sinus.png");
    int w14 = ui->ecg_label->width();
    int h14 = ui->ecg_label->height();
    ui->ecg_label->setPixmap(pix14.scaled(w14,h14,Qt::KeepAspectRatio));

}

void MainWindow::displayAsysRhythm( ) {
    QPixmap pix14(":/img/img/asystole.png");
    int w14 = ui->ecg_label->width();
    int h14 = ui->ecg_label->height();
    ui->ecg_label->setPixmap(pix14.scaled(w14,h14,Qt::KeepAspectRatio));
}


void MainWindow::handleStateSwitch() {
    if (stateCount == 1) {
        checkResponsiveness();
        stateCount+=1;
    }
    else if (stateCount == 2) {
        callForHelp();
        stateCount+=1;
    }
    else if (stateCount == 3) {
        usePass();
        stateCount+=1;
    }
    else if (stateCount == 4) {
        checkBreathing();
        stateCount+=1;
    }
    else if (stateCount == 5) {
        attachPads();
        stateCount+=1;
    }
}

void MainWindow::deviceOn() {
    //Setting the flag to true
    //Start the timer
    timer->start(1000);
    powerOnButtonClicked = true;
    // Check if there is enough battery to provide 3 Shocks.

    QString scenario = ui->scenario->currentText();
    if (scenario == "1 - NORMAL SCENARIO" || scenario == "3 - LOOSE BATTERY") {
//        if (stateCount == 1) {
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
            QTimer::singleShot(3000, this, SLOT(stayCalm()));


//            if (!(ui->electrode_pads->isChecked()) && ui->padType->currentText() == "Choose pads") {
                stateSwitchTimer->start(6000);
//            }


        }
    else if (scenario == "2 - PADS ATTACHED") {
        pads = ui->padType->currentText();
        QTimer::singleShot(3000, led5, &LedWidget::turnOn);
        QTimer::singleShot(3000, this, SLOT(padsAttached()));
        QTimer::singleShot(8000, led5, &LedWidget::turnOff);
        qDebug() << "\n" << pads + " already attached";
        aed->setShockValues(pads);
        QTimer::singleShot(10000, led6, &LedWidget::turnOn);
        QTimer::singleShot(10000, this, SLOT(awayFromPatient()));
        QTimer::singleShot(11000, this, SLOT(startAnalysing()));
    }
//    }
    else if (scenario == "4 - PRE TEST FAIL"){
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
    if (!(ui->electrode_pads->isChecked())) {
        QTimer::singleShot(1000, led5, &LedWidget::turnOff);
        QTimer::singleShot(1000, this, SLOT(resetDisplay()));
        pads = ui->padType->currentText();
        if (aed->setShockValues(pads)) {
            qDebug() << pads + " ATTACHED and Shock Values Set";
            QTimer::singleShot(3000, this, SLOT(padsAttached()));
            QTimer::singleShot(3000, led6, &LedWidget::turnOn);
            QTimer::singleShot(8000, this, SLOT(awayFromPatient()));
            QTimer::singleShot(11000, this, SLOT(startAnalysing()));
        }
        else {
            qDebug() << "PLEASE MAKE RIGHT PAD SELECTION";
        }
    }

    else {
        stateCount = 5;
        return;
    }

}

void MainWindow::checkCompressions(){
    QTimer::singleShot(3000, led6, &LedWidget::turnOff);
    QTimer::singleShot(3000, led7, &LedWidget::turnOn);
    QString comp=ui->compression_type->currentText();

    QPixmap pix14(":/img/img/compressions.png");
    int w14 = ui->compressions_label->width();
    int h14 = ui->compressions_label->height();
    ui->compressions_label->setPixmap(pix14.scaled(w14,h14,Qt::KeepAspectRatio));

    if(comp=="2-2.25 inches"){
        ui->display->setText("GOOD COMPRESSION");
        compressionCount+=1;   
        ui->compressionCounter->display(compressionCount);
    }else if(comp=="<2 inches"){
        ui->display->setText("PUSH HARDER");
        compressionCount+=1;
        ui->compressionCounter->display(compressionCount);
    }else if(comp=="<0.75 inches"){
        ui->display->setText("CONTINUE CPR");
        ui->compressionCounter->display(compressionCount);
    }
    qDebug() << compressionCount;
    if(compressionCount >= 30){
        compressionCount=0;
        ui->compressionCounter->display(compressionCount);
        QTimer::singleShot(4000, this, SLOT(takeBreaths()));
        QTimer::singleShot(10000, this, SLOT(stopCPR()));
        QTimer::singleShot(10000, led7, &LedWidget::turnOff);

        QPixmap pix14(":/img/img/reset.png");
        int w14 = ui->compressions_label->width();
        int h14 = ui->compressions_label->height();
        ui->compressions_label->setPixmap(pix14.scaled(w14,h14,Qt::KeepAspectRatio));
        QTimer::singleShot(11000, this, SLOT(startAnalysing()));

    }
}

void MainWindow::deviceOff() {

    qDebug() << "Turning AED Off";
    resetDisplay();

    stateSwitchTimer->stop();

    //Set the flag to false
    powerOnButtonClicked = false;

    //Start the timer for 5 seconds
    powerOffTimer->start(5000);

}

void MainWindow::onPowerOffTimeout() {
    //This function will be called if the powerOffTimer runs out

    //Check if power_On Button was clicked within the 5 seconds
    if(powerOnButtonClicked){
        qDebug() << "AED is turned back on within 5 seconds";
        stateSwitchTimer->start();
    }
    else{  
        //Reset the Elapsed Time
        timeCount = 0;
        timer->stop();
        //Turn off all the LED
        QTimer::singleShot(1000, led1, &LedWidget::turnOff);
        QTimer::singleShot(1000, led2, &LedWidget::turnOff);
        QTimer::singleShot(1000, led3, &LedWidget::turnOff);
        QTimer::singleShot(1000, led4, &LedWidget::turnOff);
        QTimer::singleShot(1000, led5, &LedWidget::turnOff);
        QTimer::singleShot(1000, led6, &LedWidget::turnOff);
        QTimer::singleShot(1000, led7, &LedWidget::turnOff);
        QTimer::singleShot(1000, led8, &LedWidget::turnOff);
        QTimer::singleShot(1000, led9, &LedWidget::turnOff);
        QTimer::singleShot(1000, this, SLOT(resetDisplay()));
        QPixmap pix10(":/img/img/reset.png");
        int w10 = ui->ecg_label->width();
        int h10 = ui->ecg_label->height();
        ui->ecg_label->setPixmap(pix10.scaled(w10,h10,Qt::KeepAspectRatio));

        QPixmap pix14(":/img/img/reset.png");
        int w14 = ui->self_test_label->width();
        int h14 = ui->self_test_label->height();
        ui->self_test_label->setPixmap(pix14.scaled(w14,h14,Qt::KeepAspectRatio));

        qDebug() << "AED is turned off for more than 5 seconds";
        stateCount = 1;
        ui->elapsedTime->display(0);
    }

    //Stop the timer
    powerOffTimer->stop();
}

void MainWindow::handleAnalysing() {
    QString scenario = ui->scenario->currentText();
    QString detectedRhythm = aed->analyzeHB();
    if (currentShock == 3) {
        currentShock = 0;
    }
    QTimer::singleShot(2000, this, SLOT(analyze()));
    if (scenario == "1 - NORMAL SCENARIO" || scenario == "2 - PADS ATTACHED") {
        if (detectedRhythm == "vf" && (battery->getBattery() > aed->getShock(currentShock))) {
            qDebug() << detectedRhythm << " rhythm detected.";
            qDebug() << "Delivering " << aed->getShock(currentShock) << "J";
            QTimer::singleShot(8000, this, SLOT(vfRhythm()));
            QTimer::singleShot(8000, this, SLOT(displayVFRhythm()));
            QTimer::singleShot(10000, led6, &LedWidget::turnOff);
            QTimer::singleShot(10000, this, SLOT(shockDelivery()));
            QTimer::singleShot(13000, led9, &LedWidget::turnOn);

            // handle shock count
            currentShock+=1;

            // handle cpr stage
            QTimer::singleShot(16000, this, SLOT(startCPR()));
            QTimer::singleShot(16000, led9, &LedWidget::turnOff);

            // reset display on screen

            // move led to cpr stage
            QTimer::singleShot(16000, led7, &LedWidget::turnOn);

            // handle battery reduction
        }

        else if (detectedRhythm == "vt" && (battery->getBattery() > aed->getShock(currentShock))) {
            qDebug() << detectedRhythm << " rhythm detected.";
            qDebug() << "Delivering " << aed->getShock(currentShock) << "J";
            QTimer::singleShot(8000, this, SLOT(vtRhythm()));
            QTimer::singleShot(8000, this, SLOT(displayVTRhythm()));
            QTimer::singleShot(10000, led6, &LedWidget::turnOff);
            QTimer::singleShot(10000, this, SLOT(shockDelivery()));
            QTimer::singleShot(13000, led9, &LedWidget::turnOn);

            // handle shock count
            currentShock+=1;

            // handle cpr stage
            QTimer::singleShot(16000, this, SLOT(startCPR()));
            QTimer::singleShot(16000, led9, &LedWidget::turnOff);


            // reset display on screen

            // move led to cpr stage
            QTimer::singleShot(16000, led7, &LedWidget::turnOn);

            // handle battery reduction
        }

        else if (detectedRhythm == "Asystole" && (battery->getBattery() > aed->getShock(currentShock))) {
            qDebug() << detectedRhythm << " rhythm detected.";
            QTimer::singleShot(8000, this, SLOT(asysRhythm()));
            QTimer::singleShot(8000, this, SLOT(displayAsysRhythm()));
            QTimer::singleShot(10000, led6, &LedWidget::turnOff);

            // handle cpr stage
            QTimer::singleShot(13000, this, SLOT(startCPR()));

            // reset display on screen

            // move led to cpr stage
            QTimer::singleShot(13000, led7, &LedWidget::turnOn);

            // handle battery reduction
        }

        else if (detectedRhythm == "Sinus") {
            qDebug() << detectedRhythm << " rhythm detected.";
            QTimer::singleShot(8000, this, SLOT(sinusRhythm()));
            QTimer::singleShot(8000, this, SLOT(displaySinusRhythm()));
            QTimer::singleShot(10000, led6, &LedWidget::turnOff);

            // handle battery reduction

            // handle signing off message.
        }

        else {
            // handle power off and switch off device.
            ui->display->setText("BATTERY CRITTICALLY LOW");
            deviceOff();
            onPowerOffTimeout();
        }

    }

    else if (scenario == "3 - Loose Battery") {
        if (ui->padType->currentText() == "ADULT PADS") {
            battery->setBattery(130);
        }
        else if (ui->padType->currentText() == "INFANT PADS") {
            battery->setBattery(60);
        }
        if (currentShock == 0) {
            detectedRhythm = "vf";
        }
        else {
            detectedRhythm = "vt";
        }
        if (detectedRhythm == "vf") {
            qDebug() << detectedRhythm << " rhythm detected.";
            qDebug() << "Delivering " << aed->getShock(currentShock) << "J";
            QTimer::singleShot(8000, this, SLOT(vfRhythm()));
            QTimer::singleShot(8000, this, SLOT(displayVFRhythm()));
            QTimer::singleShot(10000, led6, &LedWidget::turnOff);
            QTimer::singleShot(10000, this, SLOT(shockDelivery()));

            if ((battery->getBattery() > aed->getShock(currentShock))) {
                QTimer::singleShot(13000, led9, &LedWidget::turnOn);

                // handle shock count
                currentShock+=1;

                // handle cpr stage
                QTimer::singleShot(16000, this, SLOT(startCPR()));
                QTimer::singleShot(16000, led9, &LedWidget::turnOff);
                QTimer::singleShot(3000, led7, &LedWidget::turnOn);

                // handle battery reduction
                battery->reduceBattery(15);
            }
        }

        else if (detectedRhythm == "vt") {
            qDebug() << detectedRhythm << " rhythm detected.";
            qDebug() << "Delivering " << aed->getShock(currentShock) << "J";
            QTimer::singleShot(8000, this, SLOT(vtRhythm()));
            QTimer::singleShot(8000, this, SLOT(displayVTRhythm()));
            QTimer::singleShot(10000, led6, &LedWidget::turnOff);
            QTimer::singleShot(10000, this, SLOT(shockDelivery()));

            if ((battery->getBattery() > aed->getShock(currentShock))) {
                QTimer::singleShot(13000, led9, &LedWidget::turnOn);

                // handle shock count
                currentShock+=1;

                // handle cpr stage
                QTimer::singleShot(16000, this, SLOT(startCPR()));
                QTimer::singleShot(16000, led9, &LedWidget::turnOff);
                QTimer::singleShot(3000, led7, &LedWidget::turnOn);

                // handle battery reduction

            }

            else {
                deviceOff();
                QTimer::singleShot(14000, this, SLOT(outOfBattery()));
                onPowerOffTimeout();
            }

        }
    }

    else {
        return;
    }
}
