#ifndef AED_H
#define AED_H

#include <QString>
#include <vector>

class AED
{
public:
    AED();
    bool setShockValues(QString pt);
    std::vector<int> getShockList();

private:
    std::vector<int> shocks;
};

#endif // AED_H
