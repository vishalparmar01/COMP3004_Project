// LedWidget.cpp
#include "LedWidget.h"
#include <QPainter>

LedWidget::LedWidget(QWidget* parent) : QWidget(parent), m_isOn(false) {}

void LedWidget::turnOn() {
    m_isOn = true;
    update(); // Trigger repaint
}

void LedWidget::turnOff() {
    m_isOn = false;
    update(); // Trigger repaint
}

void LedWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw circular LED shape
    QColor ledColor = m_isOn ? Qt::red : Qt::gray;
    painter.setBrush(ledColor);
    painter.drawEllipse(rect());
}
