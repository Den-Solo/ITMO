#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <optional>
#include "Matrix.h"
using namespace std;



template <class T>
void Permute(Matrix<T>& m, MatrixCol<T>& b) {
	for (size_t i = 0; i < m.LineCnt(); ++i) {
		if (size_t k = m.MaxInColIdx(i, i); k != i) {
			swap(m[i], m[k]);
			swap(b.at(i, 0), b.at(k, 0));
		}
	}
}

template <class T>
optional<MatrixCol<T>> IterMethod(Matrix<T>& A, MatrixCol<T>& b) {
	if (A.ColCnt() != A.LineCnt() || A.LineCnt() != b.LineCnt())
		throw runtime_error("Chaletski: wrong A matrix");

	const T EPS = 1e-3;
	Permute(A, b);
	//devide by diagonal elements
	for (size_t i = 0; i < A.LineCnt(); ++i) {
		T tmp = A.at(i, i);
		for (size_t j = 0; j < A.ColCnt(); ++j)
			A.at(i, j) /= tmp;
		b.at(i, 0) /= tmp;
	}

	vector<T> x(b.LineCnt());
	for (size_t i = 0; i < A.ColCnt(); ++i)
		x[i] = b.at(i, 0);
	vector<T> x_prev(x);

	for (size_t iter = 0;; ++iter) {
		for (size_t line = 0; line < A.LineCnt(); ++line) {
			T res = 0;
			for (size_t col = 0; col < A.ColCnt(); ++col) {
				if (col != line)
					res -= A.at(line, col) * x[col];
			}
			res += b.at(line, 0);
			x[line] = res;
		}
		bool done = true;
		for (size_t i = 0; i < A.LineCnt(); ++i)
			done &= (abs(x_prev[i] - x[i]) < abs(EPS));
		if (done)
			break;
		else
			x_prev = x;
	}
	MatrixCol<T> res(0);
	res[0] = move(x);
	return res;
}


int main() {

	try {
		//freopen("inp.txt", "r", stdin);

		size_t m, n;
		cout << "Input number of lines\n";
		cin >> m;
		cout << "Input number of cols\n";
		cin >> n;
		Matrix<double> A(m,n);
		MatrixCol<double> b(m);
		cout << "Input matrix\n";
		for (size_t line = 0; line < m; ++line)
			for (size_t col = 0; col < n; ++col)
				cin >> A.at(line, col);
		cout << "Input vector b\n";
		for (size_t line = 0; line < m; ++line)
			cin >> b.at(line, 0);

		auto res = IterMethod(A, b);

		if (res)
			cout << "Result:\n" << res.value() << "\n";
		else
			cout << "Cannot solve\n";
	}
	catch (runtime_error& e) {
		cerr << e.what() << '\n';
	}
}





