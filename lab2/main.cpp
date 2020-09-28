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
    //Print2(a,b,n);
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
/*double Norm(const vector<vector<double>>& v, int n, int m)
{
    int i, j;
    double sum = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            sum += (v[i][j] * v[i][j]);
        }
    }
    sum = sqrt(sum);
    return sum;
}
*/

vector<double> Seidel( vector<vector<double>>& a,  vector<double>& b,int n, double eps)
{
    vector<double> x(n,0);
    vector<double> xn(n);
    double delta_max=0;
    int count=0;
    while(true)
    {
        count++;
        delta_max=0;
        for (int i=0;i<n;i++)
        {
            xn[i]=0;
            for (int j=0;j<n;j++)
            {
                if (i>j)
                    xn[i]-=(a[i][j]*x[j]);
                if (i<j)
                    xn[i]-=(a[i][j]*xn[j]);
            }
            xn[i]+=b[i];
            xn[i]/=a[i][i];
            if (delta_max<abs(x[i]-xn[i]))
                delta_max=abs(x[i]-xn[i]);
        }
        x=xn;
        if(count==1) continue;
        if (delta_max<=eps) break;
    }
    return xn;
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
    vector<double> x(n);
    
    vector<vector<double>> a_tmp = a;
    vector <double> b_tmp = b;
    x=Gaus(a_tmp,b_tmp,n);
    cout<<"Метод Гауса|Матрица решений: "<<endl;
    Print1(x,n);
    
    x=Seidel(a,b,n,0.000001);
    cout<<"Метод Зейделя|Матрица решений: "<<endl;
    Print1(x,n);
    
}
