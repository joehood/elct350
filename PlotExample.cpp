#include "Matrix.hpp"
#include "Plotter.hpp"

int main()
{
    Matrix A(2, 2);
    ColumnVector B(2);
    ColumnVector X(2);
    
    Plotter plotter("State Space Test");
    
    A(1, 2) = 1.0;
    A(2, 1) = -2.0;
    A(2, 2) = -1.0;
    B(2) = 5.0;
    
    double h = 0.05;
    double t = 0.0;
    double tmax = 5.0;
    double u = 10.0;
    
    while (t <= tmax)
    {
        X += (A * X + B * u) * h;
        plotter.AddRow(t, X(1), X(2));
        t += h;
    }
    
    plotter.SetLabels("x1", "x2");
    plotter.Plot();
}
