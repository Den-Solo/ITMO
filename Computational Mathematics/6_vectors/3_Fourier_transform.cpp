#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <complex>
#include <cassert>
#define M_PI 3.141592653 //у меня не включаются константы


using namespace std;


//for .csv
template <class T>
ostream& operator<<(ostream& ostr, const vector<T>& v) {
	for (const T& i : v)
		ostr << i << ";\n";
	return ostr;
}

template <>
ostream& operator<<(ostream& ostr, const vector<complex<double>>& v) {
	const double EPS = 1e-8;
	for (const complex<double>& i : v) {
		ostr << i.real();
		auto im = i.imag();
		if (abs(im) < EPS) im = +0;

		if (i.imag() > 0)
			ostr << " + i" << im;
		else
			ostr << " - i" << ((im == 0) ? 0 : -im);

		ostr << ";\n";
	}
	return ostr;
}


using cd = complex<double>;

		

		
void _fft(vector<cd>& a, bool invert) {
	int n = a.size();
	if (n == 1)
		return;
	vector<cd> a0(n / 2), a1(n / 2);
	for (int i = 0; 2 * i < n; i++) {
		a0[i] = a[2 * i];
		a1[i] = a[2 * i + 1];
	}
	_fft(a0, invert);
	_fft(a1, invert);
	double ang = 2 * M_PI / n * (invert ? 1 : -1);
	cd w(1), wn(cos(ang), sin(ang));
	for (int i = 0; 2 * i < n; i++) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if (invert) {
			a[i] /= 2;
			a[i + n / 2] /= 2;
		}
		w *= wn;
	}
}
//наивный подход O(N^2), но произвольный размр исходных данных
//и выделение памяти только одно
vector<cd> _dft(const vector<cd>& data, bool invert) {
	size_t N = data.size();
	vector<cd> a(N);
	for (size_t k = 0; k < N; ++k) {
		for (size_t n = 0; n < N; ++n) {
			double ang = 2 * M_PI * k * n / N * (invert ? 1 : -1);
			cd wn(cos(ang), sin(ang));
			a[k] += wn * data[n];
		}
		if (invert) a[k] /= N;
	}
	return a;
}



vector<cd> fft(const vector<cd>& data, bool invert) {
	int n = data.size();
	if (n == 1)
		return data;
	//не степень 2 => наивный подход O(n^2)
	//степень 2 => O(nlog(n))
	if (ceil(log2(n)) != floor(log2(n))) {
		return _dft(data,invert);
	}
	else {
		vector<cd> a = data;
		_fft(a, invert);
		return a;
	}
}

int main(){
    vector<complex<double>> a = { 0.8427, 0.8802, 0.9103, 0.9340,
									0.9523, 0.9661, 0.9763, 0.9838,
									0.9891, 0.9928, 0.9953 };
		a = fft(a, false);

		cout << a << "\n\n";

		a = fft(a, true);
		cout << a;
}