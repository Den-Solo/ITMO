#include <iostream>
#include <string>
#include <cmath>
#include <optional>
#include <complex>

using namespace std;
using cdouble = std::complex<double>;

struct MethodAnswerComplex {
	cdouble result;
	size_t num_of_iterations;
};


ostream& operator<<(ostream& os, optional<MethodAnswerComplex> opt) {
	if (opt.has_value())
		return os << "Root: "
		<< opt.value().result
		<< "; number of iterations: "
		<< opt.value().num_of_iterations;
	else
		return os << "No roots in interval";
}
template <class T>
complex<T> operator+(const complex<T>& z1, int x) {
	return { z1.real() + static_cast<double>(x), z1.imag() };
}
template <class T>
complex<T> operator+(int x, const complex<T>& z1) {
	return { z1.real() + static_cast<double>(x), z1.imag() };
}
template <class T>
complex<T> operator*(int x, const complex<T>& z1) {
	return { z1.real() * static_cast<double>(x), 
		z1.imag() * static_cast<double>(x) };
}
template <class T>
complex<T> operator*(const complex<T>& z1, int x) {
	return { z1.real() * static_cast<double>(x), 
		z1.imag() * static_cast<double>(x) };
}

//4 * z^4 + 2z^2 +1.3
cdouble f1(cdouble z) {
	return 4 * pow(z, 4) + 2 * z * z + 1.3;
}
cdouble f1d1(cdouble z) {
	return 16 * pow(z, 3) + 4 * z;
}

//z^2 + 2.71
cdouble f2(cdouble z) {
	return pow(z, 2) + 2.71;
}
cdouble f2d1(cdouble z) {
	return 2 * z;
}

//2 * exp(z) + sqrt(2)
cdouble f3(cdouble z) {
	return 2 * exp(z) + sqrt(2);
}
cdouble f3d1(cdouble z) {
	return 2 * exp(z);
}



#define ZERO 1e-12
template <class F>
optional<MethodAnswerComplex> NewtonMethodC(
	F&& f, F&& fd1, cdouble z0, double precision
) {
	cdouble d1z = fd1(z0);
	cdouble zn = z0, zn_prev = z0;

	size_t i = 0;
	for (; i < 1000; ++i) {
		cdouble fzn = f(zn);
		cdouble d1zn = fd1(zn);
		if (abs(d1zn) == 0)
			return nullopt;
		zn_prev = zn;
		zn -= fzn / d1zn;
		if (abs(f(fzn)) < ZERO || abs(zn - zn_prev) < precision)
			break;
	}
	return MethodAnswerComplex{ zn, i };
}



int main() {

	cout << NewtonMethodC(f1, f1d1, cdouble(1, 1), 0.0001) << '\n';
	cout << NewtonMethodC(f2, f2d1, cdouble(0, 1), 0.0001) << '\n';
	cout << NewtonMethodC(f3, f3d1, cdouble(1, 1), 0.0001) << '\n';

}