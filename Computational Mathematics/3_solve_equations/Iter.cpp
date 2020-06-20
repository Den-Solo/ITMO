#include <iostream>
#include <cmath>
#include <functional>
#include <optionl>

using namespace std;

struct MethodAnswer {
	double result;
	size_t num_of_iterations;
};

ostream& operator<<(ostream& os, optional<MethodAnswer> opt) {
	if (opt.has_value())
		return os << "Root: "
		<< opt.value().result
		<< "; number of iterations: "
		<< opt.value().num_of_iterations;
	else
		return os << "No roots in interval";
}

double Deriv1(const function<double(double)>& f, double x) {
	const double eps = 1e-9;
	return (f(x) - f(x + eps)) / (-eps);
}

//cos(x) = 0.1
double phi1(double x) {
	return acos(0.1);
}

//x^5 - x^4 - x^2 - x - 5 = 0
double phi2(double x) {
	return pow(pow(x, 4) + pow(x, 2) + x + 5, 0.2);
}

//lnx + x = 2.25
double phi3(double x) {
	return 2.25 - log(x);
}

template <class F>
optional<MethodAnswer> IterMethod(F&& phi, double x0, double eps) {
	if (double q = abs(Deriv1(phi, x0)); q < 1) {

		double condition = q != 0 ? (1 - q) * eps / q : eps;
		double xn = phi(x0);
		size_t counter = 1;
		for (; counter < 1e6; ++counter) {
			if ((abs(xn - x0) <= condition)) {
				break;
			}
			else {
				x0 = xn;
				xn = phi(x0);
			}
		}

		return MethodAnswer{ xn, counter };
	}
	else
		return nullopt;
}





int main() {
	cout << IterMethod(phi1, 0.5, 0.0001) << '\n';
	cout << IterMethod(phi2, 0.5, 0.0001) << '\n';
	cout << IterMethod(phi3, 1.5, 0.0001) << '\n';
}