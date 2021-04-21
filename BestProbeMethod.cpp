#include <iostream>
#include <vector>
#include <cmath>
#include<cstdlib>
#include<ctime>
using namespace std;
float function(vector<double> x)
{
	return (pow(x[0] - 5, 2) + pow(x[1] - 1, 2) + pow(x[2] + 2, 2));
}
double Norm(vector<double> vectors) {
	double norm = 0;
	for (int i = 0; i < vectors.size(); i++) {
		norm += vectors[i] * vectors[i];
	}
	return sqrt(norm);
}

vector<vector<double>> step2() {
	srand(time(0));
	vector<vector<double>> Eps;
	vector<double> vectors;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			vectors.push_back((double)rand() / RAND_MAX * 2 - 1);
		}
		Eps.push_back(vectors);
		vectors.clear();
	}
	return Eps;
}
vector<vector<double>> step3(vector < vector < double >> x,  int k, vector < double > t )
{
	vector < vector < double >> Eps = step2();
	vector < vector < double >> PointY;
	for (int i = 0; i < 8; i++) {
		vector<double> vec;
		for (int j = 0; j < 3; j++) {
			vec.push_back(x[k][j] + t[k] * Eps[i][j] / Norm(Eps[i]));
		}
		PointY.push_back(vec);
	}
	return PointY;
}
vector<double> step4(vector < vector < double >> x, int k, vector < double > t) {
	vector < vector < double >> y = step3(x,k,t);
	vector<double> valuesFunc;
	for (int i = 0; i < 8; i++) {
		valuesFunc.push_back(function(y[i]));
	}
	double min = valuesFunc[0];
	for (int i = 1; i < 8; i++) {
		if (valuesFunc[i] < min) {
			min = valuesFunc[i];
		}
	}
	vector<double> Y_;
	for (int i = 0; i < 8; i++) {
		if (function(y[i]) == min) {
			Y_ = y[i];
		}
	}
	return Y_;
}
	void optimization()
	{
		int n = 3;
		vector < double> x0 = { 0,0,0 };
		vector < vector<double> > y, x;
		cout<< "Input a start values = \n";
		cin >>x0[0] >> x0[1]>> x0[2];
		x.push_back(x0);
		int countPoint = 8;
		vector < double > t = { 1.0 };
		int k_max = 10000;
		int k = 0;
		double tmin = 0.2;
		double koefB = 0.5;
		while (k <= k_max) {
			vector < double> Y_ = step4(x, k, t);
			if (function(Y_) < function(x[k])) {
				x.push_back(Y_);
				t.push_back(t[k]);
				k++;
				if (k == k_max) {
					cout << "result = " << endl;
					for (int i = 0; i < 3; i++) {
						cout << x[k][i] << " ";
					}
					exit(0);
				}
				else {
					continue;
				}
			}
			else {
				if (t[k] > tmin) {
					t[k] *= koefB;
					continue;
				}
				else {
					cout << "result = " << endl;
					for (int i = 0; i < 3; i++) {
						cout << x[k][i] << " ";
					}
					exit(0);
				}
			}
		}
	}
int main()
{
	optimization();
}
