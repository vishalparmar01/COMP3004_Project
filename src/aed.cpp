#include "aed.h"

AED::AED()
{

}

bool AED::setShockValues(QString pt) {
    if (pt == "ADULT PADS") {
        shocks.push_back(120);
        shocks.push_back(150);
        shocks.push_back(200);
        return true;
    }
    else {
        shocks.push_back(50);
        shocks.push_back(70);
        shocks.push_back(85);
        return true;
    }
    return false;
}

std::vector<int> AED::getShockList() {
    return shocks;
}
