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

double EquivalentEquation(double x)
{
    return x-(1/DerivativeFirst(x))*InitialFunction(x);
}

 
int main(){
    int n=0;
    double  a,b,x0, x1 = 0;
    cin>>a>>b;
    x0=(a+b)/2;
    for(;;)
    {
        x1 = EquivalentEquation(x0);
        n++;
        if (fabs(x1 - x0) < eps) break;
        x0 = x1;
        //cout << x1 << " - root" << endl;
    }
    cout << x1 << " - root" << endl;
    cout << "Number of iterations " << n << endl;
    return 0;
 
}
