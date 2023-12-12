 #include "battery.h"

Battery::Battery(int v)
{
    battery = v;
}

int Battery::getBattery() const {
    return battery;
}

int Battery::reduceBattery(int v) {
    return battery = battery - v;
}

void Battery::setBattery(int v) {
    battery = v;
}
