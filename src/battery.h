#ifndef BATTERY_H
#define BATTERY_H


class Battery
{
public:
    Battery(int v);
    int getBattery() const;
    int reduceBattery(int v);

private:
    int battery;
};

#endif // BATTERY_H
