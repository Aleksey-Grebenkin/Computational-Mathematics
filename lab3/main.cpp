#include <iostream>
#include <vector>
#include <cmath>

const int N = 5;
const double dx=0.25;
using namespace std;

void init(vector<double> &x,vector<double> &y)
{
    double a;
    cout<<"Введите вектор значений x"<<endl;
    for (int i=0; i<N; i++)
    {
        cin>>a;
        x.push_back(a);
    }
    cout<<"Введите вектор значений y"<<endl;
    for (int i=0; i<N; i++)
    {
        cin>>a;
        y.push_back(a);
    }
}

double interpolateLagrange(vector<double> x, vector<double>y, double x_current) {
    double result = 0;
    for (int i = 0; i < N; i++) {
        double term = y[i];
        for (int j = 0; j < N; j++) {
            if (j != i)
                term *= (x_current - x[j]) / (x[i] - x[j]);
        }
    result += term;
    }
     return result;
}

int fact(int a)
{
    if (a==1) return 1;
    return fact(a-1)*a;
}

double u_cal1 (double u, int n) {
     double temp = u;
     for (int i = 1; i < n; i++) temp *= (u - i);
     return temp;
}

double u_cal2 (double u, int n) {
     double temp = u;
     for (int i = 1; i < n; i++) temp *= (u + i);
     return temp;
}

double interpolateNewton(vector<double> x,vector<vector<double>> differences,double x_current, float left_half) {
    double sum;
    if (left_half)
    {
        sum = differences[0][0];
        double u = (x_current - x[0]) / (x[1] - x[0]);
        for (int i = 1; i < x.size(); i++)
            sum += (u_cal1(u, i) * differences[0][i]) / fact(i);
    }
    else
    {
        sum = differences[x.size()-1][0];
        double u = (x_current - x[x.size()-1]) / (x[1] - x[0]);
        for (int i = 1; i < x.size(); i++)
            sum += (u_cal2(u, i) * differences[x.size()-1][i]) / fact(i);
    }
    return sum;
}

vector <double> interpolateLeastSquare(vector<double> x, vector<double>y, int K)
{
    vector<vector<double>> sums;
    sums.assign(K+1, vector<double>(K+1));
    
    vector<double> a(K+1,0);
    vector<double> b(K+1,0);
    
    
    for(int i=0; i<K+1; i++)
    {
        for(int j=0; j<K+1; j++)
        {
            sums[i][j] = 0;
            for(int k=0; k<N; k++)
            {
                sums[i][j] += pow(x[k], i+j);
            }
        }
    }
    for(int i=0; i<K+1; i++)
    {
        for(int k=0; k<N; k++)
        {
        b[i] += pow(x[k], i) * y[k];
        }
    }
    
    double temp=0;
    for(int i=0; i<K+1; i++) //приведение к диагонланьному виду
    {
        if(sums[i][i]==0)
        {
            for(int j=0; j<K+1; j++)
            {
                if(j==i) continue;
                if(sums[j][i] !=0 && sums[i][j]!=0)
                {
                for(int k=0; k<K+1; k++){
                    temp = sums[j][k];
                    sums[j][k] = sums[i][k];
                    sums[i][k] = temp;
                }
                temp = b[j];
                b[j] = b[i];
                b[i] = temp;
                break;
                }
            }
        }
    }
    
    for(int k=0; k<K+1; k++) //расчет решения
    {
        for(int i=k+1; i<K+1; i++)
        {
        if(sums[k][k]==0)
        {
            printf("\nРешения не существует\n");
            exit(1);
        }
        double M = sums[i][k] / sums[k][k];
        for(int j=k; j<K+1; j++)
        {
            sums[i][j] -= M * sums[k][j];
        }
        b[i] -= M*b[k];
        }
    }
    
    for(int i=(K+1)-1; i>=0; i--)
    {
        float s = 0;
        for(int j = i; j<K+1; j++)
        {
        s = s + sums[i][j]*a[j];
        }
        a[i] = (b[i] - s) / sums[i][i];
    }
    return a;
}

int main()
{
    vector <double> x;
    vector <double> y;
    vector <double> x_lagr;
    vector <double> y_lagr;
    
    vector <double> x_newt;
    vector <double> y_newt;
    
    vector <double> x_squ1;
    vector <double> y_squ1;
    vector <double> x_squ2;
    vector <double> y_squ2;
    vector <double> x_squ3;
    vector <double> y_squ3;
    
    init (x,y);
    double x1= *min_element(begin(x),end(x));
    double x2= *max_element(begin(x),end(x));
    
    //ЛАГРАНЖ
    for (double x_current = x1;x_current<=x2;x_current+=dx)
    {
        x_lagr.push_back(x_current);
        y_lagr.push_back(interpolateLagrange(x,y,x_current));
    }
    
    cout<<endl;
    //НЬЮТОН
    vector<vector<double>> differences1; //таблица конечных разностей вперед
    vector<vector<double>> differences2; //таблица конечных разностей назад
    differences1.assign(N, vector<double>(N));
    differences2.assign(N, vector<double>(N));
    for (int i = 0; i < x.size(); i++)
    {
        differences1[i][0]=y[i];
        differences2[i][0]=y[i];
    }
    for (int i = 1; i < x.size(); i++)
    {
        for (int j = 0; j < x.size() - i; j++)
        {
            differences1[j][i]=differences1[j + 1][i - 1] - differences1[j][i - 1];
        }
        for (int j = x.size()-1; j >= i; j--)
        {
            differences2[j][i]=differences2[j][i - 1] - differences2[j-1][i - 1];
        }
    }
    for (double x_current = x1;x_current<(x1+x2)/2;x_current+=dx)
    {
        x_newt.push_back(x_current);
        y_newt.push_back(interpolateNewton(x,differences1,x_current,true));
    }

    for (double x_current = (x1+x2)/2;x_current<=x2;x_current+=dx)
       {
           x_newt.push_back(x_current);
           y_newt.push_back(interpolateNewton(x,differences2,x_current,false));
       }
    
    vector<double> a;
    
    //Наименьших квадратов 1 степени
    int K=1;
    a=interpolateLeastSquare(x,y,K);
    for (double x_current = x1;x_current<=x2;x_current+=dx)
    {
        double sum=0;
        for(int i=0;i<K+1;i++)
        {
            sum+=a[i]*pow(x_current,i);
        }
        x_squ1.push_back(x_current);
        y_squ1.push_back(sum);
    }
    
    
    //Наименьших квадратов 2 степени
    K=2;
    a=interpolateLeastSquare(x,y,K);
    for (double x_current = x1;x_current<=x2;x_current+=dx)
    {
        double sum=0;
        for(int i=0;i<K+1;i++)
        {
            sum+=a[i]*pow(x_current,i);
        }
        x_squ2.push_back(x_current);
        y_squ2.push_back(sum);
    }
    
    //Наименьших квадратов 3 степени
    K=3;
    a=interpolateLeastSquare(x,y,K);
    for (double x_current = x1;x_current<=x2;x_current+=dx)
    {
        double sum=0;
        for(int i=0;i<K+1;i++)
        {
            sum+=a[i]*pow(x_current,i);
        }
        x_squ3.push_back(x_current);
        y_squ3.push_back(sum);
    }
    
    for(int i=0;i<y_lagr.size();i++)
    {
        cout<<x_lagr[i]<< ";"<<y_lagr[i] <<";"<<endl;
    }
     cout<<endl;
    
    for(int i=0;i<y_newt.size();i++)
    {
        cout<<x_newt[i]<< ";"<<y_newt[i]<<";"<<endl;
    }
     cout<<endl;
    
    for(int i=0;i<y_squ1.size();i++)
       {
           cout<<x_squ1[i]<<";"<<y_squ1[i]<<";"<<endl;
       }
    cout<<endl;
    
    for(int i=0;i<y_squ2.size();i++)
       {
           cout<<x_squ2[i]<<";"<<y_squ2[i]<<";"<<endl;
       }
    cout<<endl;
    
    for(int i=0;i<y_squ3.size();i++)
          {
              cout<<x_squ3[i]<<";"<<y_squ3[i]<<";"<<endl;
          }
       cout<<endl;
    
}
