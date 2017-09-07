# ELCT 350 Code Library (UofSC EE Dept)

```cpp
#include "Matrix.hpp"
#include "Plotter.hpp"

int main()
{
    Matrix A(2, 2);
    ColumnVector B(2);
    ColumnVector X(2);
    
    // 1. Constuct the plotter. Give it a title and (optional) width and height:
    Plotter plotter("State Space Test", 600, 400);
    
    // 2. Set the curve labels. Pass in as many labels as the curves (up to 10):
    plotter.SetLabels("Voltage (V)", "Current (A)");
    
    A(1, 1) = 0.0;
    A(1, 2) = 1.0;
    A(2, 1) = -2.0;
    A(2, 2) = -1.0;
    
    B(1) = 0.0;
    B(2) = 5.0;
    
    double t = 0.0;
    double tmax = 10.0;
    double dt = 0.05;
    double u = 10.0;
    
    while (t <= tmax)
    {
        X += (A * X + B * u) * dt;
        
        // 3. In your simulation loop, add the data rows. Pass in the current
        // time followed by the data points for each curve (up to 10 curves)
        plotter.AddRow(t, X(1), X(2));
        
        t += dt;
    }
    
    // 4. Call Plot to finalize the plot and create the plot.html file
    plotter.Plot();
}
```
