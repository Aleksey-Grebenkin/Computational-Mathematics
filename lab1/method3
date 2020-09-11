#include <iostream>
#include <cmath>

using namespace std;

const double eps = 0.1;
double Function(double x) {
    return 2 * pow(x, 4) - 24 * pow(x, 2) - x + 8;
}

int main() {
    double a, b,x;
    cin >> a >> b;
    int n = 0;

    do {
        ++n;
        x = (b + a) /2;
        if (Function(x) == 0) {
            cout << x << " - root" << endl;
            return 0;
        }
        if (Function(a) * Function(x) < 0) {
            b = x;
        }
        else {
            a = x;
        }
        //cout << a<<" " <<b << endl;
    }
    while (b - a >= 2 * eps);
    
    cout << x << " - root" << endl;
    cout << "Number of iterations: " << n <<endl;
    return 0;
}
