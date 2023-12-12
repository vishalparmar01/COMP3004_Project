#ifndef AED_H
#define AED_H

#include <QString>
#include <vector>
#include <map>

class AED
{
public:
    AED();
    bool setShockValues(QString pt);
    int getShock(int index);
    QString analyzeHB();

private:
    std::vector<int> shocks;
    std::vector<int> sinusRhythms;
    std::vector<int> asystoleRhythms;
    std::vector<int> vfRhythms;
    std::vector<int> vtRhythms;
    std::map<QString, std::vector<int>> states;
};

#endif // AED_H
