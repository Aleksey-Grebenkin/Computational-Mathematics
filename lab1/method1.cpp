#include <iostream>
#include <cmath>

using namespace std;

const double eps = 0.1;



double InitialFunction(double x)
{
    return  2 * pow(x, 4) - 24 * pow(x, 2) - x + 8;
}

double DerivativeFirst(double x)
{
    return 8 * pow(x, 3) - 48 * x - 1;
}

double DerivativeSecond(double x)
{
    return 24 * pow(x, 2) - 48;
}

int main()
{
    double a, b,x_n1,x_n0,x0;
    int n=1;
    cin >> a >> b;
    if (InitialFunction(a) * DerivativeSecond(a) > 0)
    {
        x0 = a;
    }
    else
    {
        x0 = b;
    }
    
    x_n0=x0- InitialFunction(x0) / DerivativeFirst(x0);
    x_n1 = x_n0 - InitialFunction(x_n0) / DerivativeFirst(x_n0);

    while (abs(x_n1 - x_n0)>=eps)
    {
        n += 1;
        x_n0 = x_n1;
        x_n1 = x_n0 - InitialFunction(x_n0) / DerivativeFirst(x_n0);
    }
    cout << x_n1 << " " << " - root" << endl;
    cout << "Number of iterations " << n << endl;
    return 0;
}
