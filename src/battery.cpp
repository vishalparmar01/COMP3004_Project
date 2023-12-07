#include "battery.h"

Battery::Battery(int v)
{
    setBatteryPercent(v);
}

void Battery::setBatteryPercent(int v) {
    battery = v;
}

int Battery::getBattery() const {
    return this->battery;
}

int Battery::reduceBattery(int v) {
    int newBattery = this->battery - v;
    return newBattery;
}
