#define _USE_MATH_DEFINES
#include "Matrix.h"
#include "Vectors.h"
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;
using cd = complex<double>;



vector<cd> operator*(const Matrix<cd>& m, const vector<cd>& v) {
	if (m.ColCnt() != v.size())
		throw runtime_error("Incorrect matrixes Matrix<cd> and vector<cd> for multiplication");
	vector<cd> res(v.size());
	for (size_t line_l = 0; line_l < m.LineCnt(); ++line_l) {
		for (size_t col_r = 0; col_r < 1; ++col_r) {
			cd sum{ 0 };
			for (size_t col_l = 0, line_r = 0; col_l < m.ColCnt(); ++col_l, ++line_r) {
				sum += m[line_l][col_l] * v[line_r];
			}
			res[line_l] = sum;
		}
	}
	return res;
}

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

Matrix<cd> MakeUnitaryFtMatrix(size_t N) {
	Matrix<cd> res(N, N);
	cd z = exp(cd(0, -2 * M_PI / N));

	//diagonal
	res[0][0] = 1;
	res[1][1] = z;
	for (size_t i = 2; i < N; ++i) {
		res[i][i] = res[i - 1][i - 1];
		for (size_t j = 0; j < 2 * i - 1; ++j)
			res[i][i] *= z;
	}

	//элементы выше главной диагонали
	fill(res[0].begin(), res[0].end(), cd{ 1 });
	for (size_t line = 1; line < N; ++line) {
		for (size_t col = line + 1; col < N; ++col) {
			res[line][col] = res[line][col - 1];
			for (size_t i = 0; i < line; ++i)
				res[line][col] *= z;
		}
	}

	//транспонируем элементы над верхней диагональю в нижнюю
	for (size_t col = 0; col < N; ++col) {
		for (size_t line = col + 1; line < N; ++line)
			res[line][col] = res[col][line];
	}
	return res;
}


bool CheckUnitary(const Matrix<cd>& m) {
	auto m_copy1{ m };
	m_copy1 *= cd(1 / sqrt(m.LineCnt()));
	auto inv = m_copy1.Inverse();

	if (!inv)
		return false;

	//эрмитово сопряжение //хз что это, но работает
	auto m_copy2{ m_copy1 };
	m_copy2.Transpon();
	m_copy2.Conj();
	return inv.value() == m_copy2;
}

vector<cd> ft(const vector<cd>& x, const Matrix<cd>& Z, bool inverse = false) {
	if (!inverse)
		return Z * x;
	auto z_copy{ Z };
	z_copy.Conj();
	auto res = z_copy * x;
	for (auto& i : res)
		i /= res.size();
	return res;
}

int main() {
	/*{
		size_t N;
		cout << "Input N:\n";
		cin >> N;

		auto Z = MakeUnitaryFtMatrix(N);
		cout << "\n1/" << N << " * \n\n" << Z << "\n";

		cout << "Check unitarity\n" << boolalpha << CheckUnitary(Z);
	}*/
	
	
	{
		size_t N;
		cout << "Input size of vector\n";
		cin >> N;
		cout << "Input vector x\n";
		vector<cd> x(N);
		for (auto& c : x) {
			double a;
			cin >> a;
			c = cd(a);
		}
		auto Z = MakeUnitaryFtMatrix(N);
		auto X = ft(x, Z, false);
		cout << "Fourier Transformed\n\n" << X;
		cout << "\n\n";
		cout << ft(X, Z, true);

	}
	/*{
		vector<complex<double>> x = { 0.8427, 0.8802, 0.9103, 0.9340,
									   0.9523, 0.9661, 0.9763, 0.9838 };

		auto Z = MakeUnitaryFtMatrix(x.size());
		cout << "Is unitary: " << boolalpha << CheckUnitary(Z) << '\n';


		//туда
		auto X = ft(x, Z, false);
		cout << "Matrix ft:\n" << X;

		cout << "\n\n";

		auto X_ = _dft(x, false);
		cout << "Ordinary ft:\n" << X_;

		cout << "\n\n";
		//обратно

		auto xinv = ft(X, Z, true);
		cout << "Matrix ift:\n" << xinv;

		cout << "\n\n";

		auto x_inv = _dft(X_, true);
		cout << "Ordinary ift:\n" << x_inv;
	}*/
}