
#include "Simulator.hpp"

class VoltageSource : public Device
{
    public:

    // Constructors:

    // DC source constructor:
    VoltageSource(int nodei, int nodej, double Vdc);

    // SINE source constructor:
    VoltageSource(int nodei, int nodej, double Vdc, double Va, double f, double phi);

    // Device interface:
    void Init();
    void DC();
    void Step(double t, double dt);

    void SetVdc(double vdc);

    // Viewable accessors:
    double GetVoltage();
    double GetCurrent();
    double GetPower();

private:

    // Node indices:
    int nodei;
    int nodej;

    // internal:
    int nodep;

    // Parameters:
    sourceType type;
    double Vdc;
    double Va;
    double f;
    double phi;
    double R;
    double L;
};

VoltageSource::VoltageSource(int nodei, int nodej, double Vdc)
{
    this->nodei = nodei;
    this->nodej = nodej;
    this->Vdc = Vdc;

    this->type = DCSOURCE;
}

VoltageSource::VoltageSource(int nodei, int nodej, double Vdc, double Va, double f, double phi)
{
    this->nodei = nodei;
    this->nodej = nodej;
    this->Vdc = Vdc;
    this->Va = Va;
    this->f = f;
    this->phi = phi;

    this->type = SINESOURCE;
}

void VoltageSource::Init()
{
    this->nodep = GetNextNode();
}

void VoltageSource::Step(double t, double dt)
{
    AddJacobian(nodei, nodep, -1.0);
    AddJacobian(nodej, nodep, 1.0);
    AddJacobian(nodep, nodei, -1.0);
    AddJacobian(nodep, nodej, 1.0);

    double v = 0.0;

    switch (type)
    {

    case DCSOURCE:
        v = Vdc;
        break;

    case SINESOURCE:
        v = Vdc + Va * sin(2.0 * M_PI * f * t + phi);
        break;

    case SQUARESOURCE:
        //todo
        break;

    case TRISOURCE:
        //todo
        break;
    }

    AddBEquivalent(nodep, v);
}

void VoltageSource::DC()
{
    AddJacobian(nodei, nodep, -1.0);
    AddJacobian(nodej, nodep, 1.0);
    AddJacobian(nodep, nodei, -1.0);
    AddJacobian(nodep, nodej, 1.0);

    AddBEquivalent(nodep, Vdc);
}

void VoltageSource::SetVdc(double Vdc)
{
    this->Vdc = Vdc;
}

double VoltageSource::GetVoltage()
{
    return GetStateDifference(nodei, nodej);
}

double VoltageSource::GetCurrent()
{
    return -GetState(nodep);
}

double VoltageSource::GetPower()
{
    return GetVoltage() * GetCurrent();
}
