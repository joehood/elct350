# ELCT 350 Code Library (UofSC EE Dept)

## Example Usage of Matrix and Plotter

```cpp
#include "Matrix.hpp"
#include "Plotter.hpp"

using namespace std;

int main()
{
    // Circuit Parameters:
    double Is = 10.0;
    double R1 = 1.0;
    double R2 = 10.0;
    double L1 = 1.0e-3;
    double C1 = 10.0e-6;
    
    // State Space Model:
    Matrix A(2, 2);
    ColumnVector B(2);
    ColumnVector X(2);
    
    A(1, 1) = -1.0 / (R1*C1);
    A(1, 2) = -1.0 / C1;
    A(2, 1) = 1.0 / L1;
    A(2, 2) = -R2  /L1;
    
    B(1) = 1.0 / C1;
    B(2) = 0.0;
    
    X(1) = 0.0; // initial vC
    X(2) = 0.0; // initial iL
    
    A.Print();
    B.Print();
    
    double t = 0.0;
    double tmax = 1.0e-3;
    double h = 10.0e-6;
    
    Plotter plt("RLC Circuit State Space");
    plt.SetLabels("iL");
    
    while(t <= tmax + h)
    {
        plt.AddRow(t, X(2));
        
        X += h * A * X + h * B * Is;
        
        t += h;
    }
    
    plt.Plot();

}
```

