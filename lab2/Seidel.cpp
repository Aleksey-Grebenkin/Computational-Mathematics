#include <iostream>
#include <locale.h>
#include <vector>
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
	int element = 0;
	for (auto& i : v) {
		for (auto& item : i) {
			cin >> item;
		}
	}
}

double Norm(const vector<vector<double>>& v, int n, int m)
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

vector<double> Seidel(const vector<vector<double>>& a, const vector<double>& b,int n, double eps)
{
	vector<double> x(n);
	double sum=0;
	double tmp;
	x = b;
	do {
		for (int i = 0; i < n; i++) {
			tmp = b[i];
			for (int j = 0; j < n; j++) {
				tmp += a[i][j] * x[j];
			}
			sum += (x[i] - tmp) * (x[i] - tmp);
			x[i] = tmp;
		}
	} while (sqrt(sum) >= eps * (1 - Norm(a, n, n)) / Norm(a, n, n));
	return x;
}

int main()
{
	setlocale(LC_ALL, "rus");
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
	x=Seidel(a, b, n, 0.1);
	Print1(x,n);
	
}
