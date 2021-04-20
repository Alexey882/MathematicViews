#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
double function(vector < double > x) {
	return pow(x[0] - 5, 2) + pow(x[1] - 1, 2) + pow(x[2] + 2, 2);
}
double dfdx1(vector < double > x0) {
	double deltax1 = pow(10, -5);
	vector<double> x = { x0[0] + deltax1 , x0[1] ,x0[2] };
	double df = (function(x) - function(x0)) / deltax1;
	return df;
}
double dfdx2(vector < double > x0) {
	double deltax2 = pow(10, -5);
	vector<double> x = { x0[0] , x0[1] + deltax2 ,x0[2] };
	double df = (function(x) - function(x0)) / deltax2;
	return df;
}
double dfdx3(vector < double > x0) {
	double deltax3 = pow(10, -5);
	vector<double> x = { x0[0] , x0[1] ,x0[2] + deltax3 };
	double df = (function(x) - function(x0)) / deltax3;
	return df;
}
vector<double> gradient(vector<double>x) {
	vector<double> grad = { dfdx1(x) , dfdx2(x), dfdx3(x) };
	return grad;
}
double functionOneVariable(vector<double> x, double tk) {
	vector < double > grad = gradient(x);
	vector<double> newVector = { x[0] - tk * grad[0], x[1] - tk * grad[1] , x[2] - tk * grad[2] };
	return function(newVector);
}
double GoldenSearch(vector<double> x,double eps) {
	   double tmin = 0.01, tmax = 10;
		double y0, z0;
		while (fabs(tmin - tmax) > eps) {
			y0 = tmax - (tmax - tmin) / ((1 + sqrt(5)) / 2);
			z0 = tmin + (tmax - tmin) / ((1 + sqrt(5)) / 2);
			if (functionOneVariable(x,y0) > functionOneVariable(x, z0))
				tmin = y0;
			else
				tmax = z0;
		}
		return (tmax + tmin) / 2;
	}
double EvklidNorm(vector<double> x) {
	double sum = 0;
	for (int i = 0; i < x.size(); i++) {
		sum += pow(x[i], 2);
}
	return sqrt(sum);
}
void step3(double eps1, vector < vector < double >>x ,int k) {
	double norm = EvklidNorm(gradient(x[k]));
	if (norm < eps1) {
		cout << "Solution = \n";
		for (int i = 0; i < 3; i++) {
			cout << x[k][i]<<'\t';
		}
		cout << '\n';
		exit(0);
	}
}
double step4(vector<double>x , double eps) {
	double tk = GoldenSearch(x, eps);
	return tk;
}
void step5(vector < vector < double >> &x,int k , double eps) {
	double tk = step4(x[k], eps);
	vector<double> grad = gradient(x[k]);
	vector<double> xk = {x[k][0] - tk*grad[0], x[k][1] - tk*grad[1] , x[k][2] - tk*grad[2]};
	x.push_back(xk);
}
void Search() {
	int n = 3;
	int kmax;
	cout << "input a kmax = \n";
	cin >> kmax;
	int k = 0;
	double eps1, eps2;
	cout << "input a eps1 = \n";
	cin >> eps1;
	cout << "input a eps2 = \n";
	cin >> eps2;
	vector<double>x0 = {0,0,0};
	cout << "input a start values = \n";
	cout << "x1 = \n";
	cin >> x0[0];
	cout << "x2 = \n";
	cin >> x0[1];
	cout << "x3 = \n";
	cin >> x0[2];
	vector<vector<double>>x;
	x.push_back(x0)
	while (true) {
		step3(eps1, x, k);
		step5(x, k, eps1);
		vector<double>diff = { x[k + 1][0] - x[k][0] , x[k + 1][1] - x[k][1] , x[k + 1][2] - x[k][2] };
		double norm = EvklidNorm(diff);
		if (norm < eps2) {
			cout << "solutions = \n";
			for (int i = 0; i < 3; i++) {
				cout << x[k + 1][i]<<'\t';
			}
			cout << '\n';
			exit(0);
		}
		else {
			k++;
			if (k == kmax) {
				cout << "solutions = \n";
				for (int i = 0; i < 3; i++) {
					cout << x[k][i]<<'\t';
				}
				cout << '\n';
				exit(0);
			}
		}
	}
}
int main() {
	Search();
}
