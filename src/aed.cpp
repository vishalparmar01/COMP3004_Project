#include "aed.h"
#include <random>
#include <QDebug>

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
    else if (pt == "INFANT PADS"){
        shocks.push_back(50);
        shocks.push_back(70);
        shocks.push_back(85);
        return true;
    }
    return false;
}

int AED::getShock(int index) {
    return shocks.at(index);
}

QString AED::analyzeHB() {
    // Sinus Rhythms
    sinusRhythms.push_back(84);
    sinusRhythms.push_back(93);
    sinusRhythms.push_back(76);
    sinusRhythms.push_back(62);
    sinusRhythms.push_back(98);
    sinusRhythms.push_back(105);
    sinusRhythms.push_back(85);
    sinusRhythms.push_back(79);
    sinusRhythms.push_back(110);
    sinusRhythms.push_back(88);

    // Asystole Rhythms
    asystoleRhythms.push_back(1);
    asystoleRhythms.push_back(1);
    asystoleRhythms.push_back(1);
    asystoleRhythms.push_back(1);
    asystoleRhythms.push_back(1);
    asystoleRhythms.push_back(0);
    asystoleRhythms.push_back(0);
    asystoleRhythms.push_back(0);
    asystoleRhythms.push_back(0);
    asystoleRhythms.push_back(0);

    // vf Rhythms
    vfRhythms.push_back(120);
    vfRhythms.push_back(180);
    vfRhythms.push_back(250);
    vfRhythms.push_back(280);
    vfRhythms.push_back(320);
    vfRhythms.push_back(400);
    vfRhythms.push_back(420);
    vfRhythms.push_back(480);
    vfRhythms.push_back(520);
    vfRhythms.push_back(550);

    // vt Rhythms
    vtRhythms.push_back(80);
    vtRhythms.push_back(90);
    vtRhythms.push_back(110);
    vtRhythms.push_back(120);
    vtRhythms.push_back(130);
    vtRhythms.push_back(140);
    vtRhythms.push_back(150);
    vtRhythms.push_back(160);
    vtRhythms.push_back(170);
    vtRhythms.push_back(180);

    states["Sinus"] = sinusRhythms;
    states["Asystole"] = asystoleRhythms;
    states["vf"] = vfRhythms;
    states["vt"] = vtRhythms;


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, states.size() - 1);
    int randomIndex = dis(gen);
    // Use an iterator to get the randomly selected state and its associated vector
    auto it = std::next(states.begin(), randomIndex);
    QString randomState = it->first;

    return randomState;
}
