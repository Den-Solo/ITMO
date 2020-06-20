#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <functional>
#include <optional>
#include <fstream>

using namespace std;

struct MethodAnswerBern {
	double result;
	size_t num_of_iterations;
};

ostream& operator<<(ostream& os, optional<MethodAnswerBern> opt) {
	if (opt.has_value())
		return os << "Root: "
		<< opt.value().result
		<< "; number of iterations: "
		<< opt.value().num_of_iterations;
	else
		return os << "Probably largest root is a complex number";
}


optional<MethodAnswerBern> Bernully(
	const vector<double>& coefs, double eps
	) {
	vector<double> yi;
	yi.reserve(coefs.size() * 2);
	yi.resize(coefs.size() - 1, 0);
	yi.back() = 1;

	double x1 = numeric_limits<double>::max() - 1;

	size_t j = 0;
	for (; j < 1000; ++j) {
		double  yn = 0;
		for (
			size_t n = coefs.size() - 1, i = yi.size() - n;
			n != 0;
			--n, ++i
			) {
			yn += coefs[n] * yi[i];
		}
		yn *= (-1) / coefs.front();
		if (abs(yn / yi.back() - x1) < eps && j > 10)
			break;
		x1 = yn / yi.back();
		yi.emplace_back(yn);
	}
	if (j != 1000)
		return MethodAnswerBern{ x1, j };
	else
		return nullopt;
}

optional<MethodAnswerBern> Bernully(
	const vector<double>& coefs, double x, double eps
	) {
	vector<double> yi;
	yi.reserve(coefs.size() * 2);
	yi.resize(coefs.size() - 1);
	yi[0] = 1;
	double x_prev = 1;
	for (size_t i = 1; i < yi.size(); ++i) {
		x_prev = yi[i] = x * x_prev;
	}
	double x1 = numeric_limits<double>::max() - 1;
	size_t j = 0;
	for (; j < 1000; ++j) {
		double  yn = 0;
		for (
			size_t n = coefs.size() - 1, i = yi.size() - n;
			n != 0;
			--n, ++i
			) {
			yn += coefs[n] * yi[i];
		}
		yn *= (-1) / coefs.front();
		if (abs(yn / yi.back() - x1) < eps && j > 10)
			break;
		x1 = yn / yi.back();
		yi.emplace_back(yn);
	}
	if (j != 1000)
		return MethodAnswerBern{ x1, j };
	else
		return nullopt;
}



int main() {

	//5x^4 - 2x^3 + 3x^2 +x - 4 = 0
	vector<double> eq1 = { 5, -2, 3, 1, -4 };
	cout << Bernully(eq1, 0.0001) << '\n';
	cout << Bernully(eq1, 0.18, 0.0001) << '\n';

	//x^5 + 5x^4 - 5 = 0 
	vector<double> eq2 = { 1,5,0,0,0,-5 };
	cout << Bernully(eq2, 0.0001) << '\n';
	cout << Bernully(eq2, 5, 0.0001) << '\n';
}