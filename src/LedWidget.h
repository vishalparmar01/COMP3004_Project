// LedWidget.h
#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include <QWidget>

class LedWidget : public QWidget {
    Q_OBJECT
public:
    explicit LedWidget(QWidget* parent = nullptr);

    void turnOn();  // Turn the LED on
    void turnOff(); // Turn the LED off

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    bool m_isOn;
};

#endif // LEDWIDGET_H
