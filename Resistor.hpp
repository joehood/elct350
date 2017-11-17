
#include "Simulator.hpp"

class Resistor : public Device
{
public:

    // constructor:
    Resistor(int nodei, int nodej, double R);

    // Device interface:
    void Step(double t, double dt);

    // viewable functions:
    double GetVoltage();
    double GetCurrent();
    double GetPower();

//private:

    // node indices:
    int nodei;
    int nodej;

    // parameters:
    double R;
};


Resistor::Resistor(int nodei, int nodej, double R)
{
    this->nodei = nodei;
    this->nodej = nodej;
    this->R = R;
}

void Resistor::Step(double t, double dt)
{
    double g = 1.0 / R;

    AddJacobian(nodei, nodei, g);
    AddJacobian(nodei, nodej, -g);
    AddJacobian(nodej, nodei, -g);
    AddJacobian(nodej, nodej, g);
}

double Resistor::GetVoltage()
{
    return GetStateDifference(nodei, nodej);
}

double Resistor::GetCurrent()
{
    return Resistor::GetVoltage() / R;
}

double Resistor::GetPower()
{
    return Resistor::GetVoltage() * Resistor::GetCurrent();
}
