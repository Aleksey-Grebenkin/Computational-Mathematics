#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void Print1(const vector<double>& a, int n) {
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << endl;
    }
}

void Print2(const vector<vector<double>>& a, const vector<double>& b, int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << b[i] << endl;
    }

}
    
void InputVector1(vector<double>& v)
{
    for (auto& i : v){
            cin >> i;
    }
}

void InputVector2(vector<vector<double>>& v)
{
    for (auto& i : v) {
        for (auto& item : i) {
            cin >> item;
        }
    }
}

int MaxCol(const vector<vector<double>> &matrix, int col, int n) {
    double max = abs(matrix[col][col]);
    int maxPos = col;
    for (int i = col+1; i < n; ++i)
    {
        double element = abs(matrix[i][col]);
        if (element > max)
        {
          max = element;
          maxPos = i;
        }
    }
    return maxPos;
}

void Triangulation(vector<vector<double>> &a,vector<double> &b, int n) {
    for (int i = 0; i < n-1; ++i) {
        unsigned int imax = MaxCol(a, i, n);
        if (i != imax) {
            swap(a[i], a[imax]);
            swap(b[i], b[imax]);
        }
        for (int j = i + 1; j < n; ++j) {
            double mul = -a[j][i]/a[i][i];
            for (int k = i; k < n; ++k) {
                a[j][k] += a[i][k]*mul;
            }
            b[j]+=b[i]*mul;
        }
    }
}

vector<double> Gaus(vector<vector<double>>& a, vector<double>& b,int n)
{
    vector<double> x(n);
    Triangulation(a,b,n);
    Print2(a,b,n);
    x[n-1]=b[n-1]/a[n-1][n-1];
    for (int i=n-2;i>=0;i--)
    {
        double sum=0;
        for (int j=i+1;j<n;j++)
        {
            sum+=a[i][j]*x[j];
        }
        x[i]=(1/a[i][i])*(b[i]-sum);
    }
    return x;
}

int main()
{
    int n=0;
    cout << "Введите размер матрицы" << endl;
    cin >> n;
    vector<vector<double>> a;
    a.assign(n,vector<double>(n));
    vector <double> b(n);
    cout << "Введите матрицу коэф-тов" << endl;
    InputVector2(a);
    cout << "Введите матрицу значений" << endl;
    InputVector1(b);
    
    Print2(a,b,n);
    
    vector<vector<double>> a_tmp = a;
    vector <double> b_tmp = b;
    vector<double> x(n);
    x=Gaus(a_tmp,b_tmp,n);
    cout<<"Метод Гауса|Матрица решений: "<<endl;
    Print1(x,n);
    
}
