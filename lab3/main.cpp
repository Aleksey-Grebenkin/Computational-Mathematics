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

double l(int index, vector<double> x, double x_current )
{
    double l=1;
    for (int i=0;i<x.size();i++)
    {
        if (i!=index)
        {
            l*=(x_current-x[i])/(x[index]-x[i]);
        }
    }
    return l;
}

double interpolateLagrange(vector<double> x, vector<double>y, double x_current) {
    double res = 0;
    for (int i = 0; i < x.size(); i++)
    {
        res+=y[i]*l(i,x,x_current);
    }
     return res;
}

double dy(vector<double> x, vector<double> y)
{
    if(y.size()>2)
    {
        vector<double>x_left =x;
        vector<double>y_left =y;
        x_left.erase(x_left.begin());
        y_left.erase(y_left.begin());
        vector<double>x_right =x;
        vector<double>y_right =y;
        x_right.erase(x_right.end()-1);
        y_right.erase(y_right.end()-1);
        return (dy(x_left,y_left)-dy(x_right,y_right))/(x[x.size()-1]-x[0]);
    }
    else if(y.size()==2)
    {
        return (y[1]-y[0])/(x[1]-x[0]);
    }
    return 0;
}

double interpolateNewton(vector<double> x,vector<double> y,double x_current)
{
    double res = y[0];
    double tmp;
    for (int i=1; i<y.size();i++)
    {
        vector <double> x_list = vector<double>(x.begin(),x.begin()+i+1);
        vector <double> y_list = vector<double>(y.begin(),y.begin()+i+1);
        tmp=1;
        for(int j=0;j<i;j++)
            tmp*=x_current-x[j];
        res+=dy(x_list,y_list)*tmp;
    }
    return res;
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
   /* vector<vector<double>> differences1; //таблица конечных разностей вперед
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
    */
    
    for (double x_current = x1;x_current<=x2;x_current+=dx)
    {
        x_newt.push_back(x_current);
        y_newt.push_back(interpolateNewton(x,y,x_current));
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
