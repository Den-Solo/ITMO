#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <functional>
#include <optional>

using namespace std;

struct MethodAnswer {
	double result;
	size_t num_of_iterations;
};

ostream& operator<<(ostream& os, optional<MethodAnswer> opt) {
	if (opt.has_value())
		return os << "Root: " << opt.value().result
		<< "; number of iterations: " << opt.value().num_of_iterations;
	else
		return os << "No roots in interval";
}



double f1_halfDiv(double x) {
	return 2 * x * x * x + x * x + 7;
}
double f2_halfDiv(double x) {
	return 5 * cos(3 * x) + 0.5 * x - 2;
}
double f3_halfDiv(double x) {
	return log(abs(x * x * x) + 1) + x * x * x - 2;
}


#define ZERO 1e-9
optional<MethodAnswer> HalfDivMethod(
	const function<double(double)>& f,
	double a, double b, double precision
) {
	if ((b - a < 0) || (f(a) * f(b) > 0))//неверный интервал
		return nullopt;

	double x;
	size_t i = 0;
	for (; i != 1000; ++i) {
		x = (a + b) / 2;
		double res = f(x);
		if ((abs(res) < ZERO) || (b - a < precision))
			break;
		if (f(a) * res < 0)
			b = x;
		else if (f(b) * res < 0)
			a = x;
		else
			return nullopt;
	}
	return MethodAnswer{ x, i };
}


double f1c(double x) {
	return pow(5, x) * sqrt(pow(8, x - 1)) - 189;
}

double f2c(double x) {
	return pow(x, 3) - x * x + 2 * x - 5;
}
double f3c(double x) {
	return 2 * sin(2 * x) - cos(3 * x) - 0.5;
}


optional<MethodAnswer> ChordMethod(const function<double(double)>& f,
	double a, double b, double precision) {
	if ((b - a < 0) || (f(a) * f(b) > 0))
		return nullopt;

	size_t i = 0;
	double x;
	for (; i < 1000; ++i) {
		double ya = f(a);
		double yb = f(b);
		double k = (ya - yb) / (a - b);
		//к не равна 0, т.к. функция 
		//мнотонна на промежутке

		x = -1 * (ya - k * a) / k; //точка пер-я оси ох хордой
		double yx = f(x);		   //значение функции в ^этой точке

		if (abs(yx) < ZERO || (b - a < precision))
			break;
		if (ya * yx < 0)
			b = x;
		else if (yb * yx < 0)
			a = x;
		else
			return nullopt;
	}
	return MethodAnswer{ x,i };
}



double f1n(double x) {
	return 2 * log(x) - cos(x);
}
double f2n(double x) {
	return 2 * pow(sin(2 * x), 3) - cos(x);
}
double f3n(double x) {
	return pow(x, 5) + 3 * pow(x, 4) + 8 * x * x + 2 * x - 7;
}




double Deriv1(const function<double(double)>& f, double x) {
	const double eps = 1e-9;
	return (f(x) - f(x + eps)) / (-eps);
}
double Deriv2(const function<double(double)>& f, double x) {
	const double eps = 1e-12;
	double x0 = x + eps;
	return (f(x + eps) - 2 * f(x) + f(x - eps)) / (eps * eps);
}

optional<MethodAnswer> NewtonMethod(
	const function<double(double)>& f,
	double a, double b, double precision) {
	double
		d2a = Deriv2(f, a),
		d2b = Deriv2(f, b),
		fa = f(a), fb = f(b);
	if ((b - a < 0)
		|| (fa * fb > 0)
		|| (Deriv1(f, a) * Deriv1(f, b) < 0)
		|| (d2a * d2b < 0))
		return nullopt;

	double xn, xn_prev;
	if (fa * d2a > 0)      xn = a, xn_prev = b;
	else if (fb * d2b > 0) xn = b, xn_prev = a;
	else return nullopt;

	size_t i = 0;
	for (; i < 1000; ++i) {
		double fxn = f(xn);
		if (abs(f(fxn)) < ZERO || abs(xn - xn_prev) < precision)
			break;
		double d1xn = Deriv1(f, xn);
		if (abs(d1xn) == 0)
			return nullopt;
		xn_prev = xn;
		xn -= fxn / d1xn;
	}
	return MethodAnswer{ xn, i };
}

int main() {

	cout << HalfDivMethod(f1_halfDiv, -5, 6, 0.0001) << '\n';
	cout << HalfDivMethod(f2_halfDiv, 0, 1, 0.0001) << '\n';
	cout << HalfDivMethod(f3_halfDiv, -5, 6, 0.001) << '\n';
	cout << '\n';

	cout << ChordMethod(f1c, 2, 3, 0.0001) << '\n';
	cout << ChordMethod(f2c, 1.5, 2, 0.0001) << '\n';
	cout << ChordMethod(f3c, 3.14, 6.28, 0.0001) << '\n';
	cout << '\n';

	cout << NewtonMethod(f1n, 1, 2, 0.0001) << '\n';
	cout << NewtonMethod(f2n, 0, 0.5, 0.0001) << '\n';
	cout << NewtonMethod(f3n, 0, 1, 0.0001) << '\n';
	cout << '\n';

		//cout << ChordMethod(f1n, 1, 2, 0.0001) << '\n';
		//cout << ChordMethod(f2n, 0, 0.5, 0.0001) << '\n';
		//cout << ChordMethod(f3n, 0, 1, 0.0001) << '\n';

	//
	//';
	//

	//cout << HalfDivMethod(foo, 3.14, 6.28, 0.0001) << '\n';
	//cout << ChordMethod(foo, 3.14, 6.28, 0.0001) << '\n';
	//cout << NewtonMethod(foo, 3.14, 6.28, 0.0001) << '\n';

	//cout << HalfDivMethod(boo, 0.5, 1.5, 0.0001) << '\n';
	//cout << ChordMethod(boo, 0.5, 1.5, 0.0001) << '\n';
	//cout << NewtonMethod(boo, 0.5, 1.5, 0.0001) << '\n';*/

}