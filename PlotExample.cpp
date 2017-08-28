#include "Matrix.hpp"
#include "Plotter.hpp"

int main()
{
    ComplexMatrix A(2, 2);
    ComplexColumnVector B(2);
    ComplexColumnVector X(2);
    
    Plotter plotter("State Space Test");
    
    A(1, 2) = Complex(1.0, 0.5);
    A(2, 1) = Complex(-2.0, 1.0);
    A(2, 2) = Complex(-1.0, 0.5);
    B(2) = Complex(5.0);
    
    double dt = 0.05;
    double u = 10.0;
    
    for (double t = 0.0; t < 5.0; t += 0.05)
    {
        X += (A * X + B * u) * dt;
        plotter.AddRow(t, X(1).real(), X(2).real());
    }
    
    plotter.SetLabels("x1", "x2");
    plotter.Plot();
}