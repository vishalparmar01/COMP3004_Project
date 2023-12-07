#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>

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
    ui->comboBox->addItem("Choose pads");
    ui->comboBox->addItem("Adult pads");
    ui->comboBox->addItem("Infant pads");


    LedWidget *led1 = new LedWidget(this);
    ui->led_1->addWidget(led1);
    connect(ui->turnOnButton, &QPushButton::clicked, led1, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led1, &LedWidget::turnOff);

    LedWidget *led2 = new LedWidget(this);
    ui->led_2->addWidget(led2);
    connect(ui->turnOnButton, &QPushButton::clicked, led2, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led2, &LedWidget::turnOff);

    LedWidget *led3 = new LedWidget(this);
    ui->led_3->addWidget(led3);
    connect(ui->turnOnButton, &QPushButton::clicked, led3, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led3, &LedWidget::turnOff);

    LedWidget *led4 = new LedWidget(this);
    ui->led_4->addWidget(led4);
    connect(ui->turnOnButton, &QPushButton::clicked, led4, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led4, &LedWidget::turnOff);

    LedWidget *led5 = new LedWidget(this);
    ui->led_5->addWidget(led5);
    connect(ui->turnOnButton, &QPushButton::clicked, led5, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led5, &LedWidget::turnOff);

    LedWidget *led6 = new LedWidget(this);
    ui->led_6->addWidget(led6);
    connect(ui->turnOnButton, &QPushButton::clicked, led6, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led6, &LedWidget::turnOff);

    LedWidget *led7 = new LedWidget(this);
    ui->led_7->addWidget(led7);
    connect(ui->turnOnButton, &QPushButton::clicked, led7, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led7, &LedWidget::turnOff);

    LedWidget *led8 = new LedWidget(this);
    ui->led_8->addWidget(led8);
    connect(ui->turnOnButton, &QPushButton::clicked, led8, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led8, &LedWidget::turnOff);

    LedWidget *led9 = new LedWidget(this);
    ui->led_9->addWidget(led9);
    connect(ui->turnOnButton, &QPushButton::clicked, led9, &LedWidget::turnOn);
    connect(ui->turnOffButton, &QPushButton::clicked, led9, &LedWidget::turnOff);


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

