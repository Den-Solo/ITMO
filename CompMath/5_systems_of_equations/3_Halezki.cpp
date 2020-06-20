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
optional<MatrixCol<T>> Chaletski(Matrix<T>& A, MatrixCol<T>& b) {
	if (A.ColCnt() != A.LineCnt() || A.LineCnt() != b.LineCnt())
		throw runtime_error("Chaletski: wrong A matrix");

	Permute(A, b);
	Matrix<T> B(A.ColCnt(), A.ColCnt());
	Matrix<T> C(A.ColCnt(), A.ColCnt());


	for (size_t i = 0; i < A.ColCnt(); ++i) {
		B.at(i, 0) = A.at(i, 0);
		C.at(0, i) = A.at(0, i) / A.at(0, 0);
		C.at(i, i) = T{ 1 };
	}
	for (size_t m = 1; m < A.ColCnt(); ++m) {
		for (size_t i = 1; i < A.LineCnt(); ++i) {
			T sum{ 0 };
			for (size_t k = 0; k < m; ++k)
				sum += B.at(i, k) * C.at(k, m);
			B.at(i, m) = A.at(i, m) - sum;
		}
		for (size_t j = m + 1; j < A.LineCnt(); ++j) {
			T sum{ 0 };
			for (size_t k = 0; k < m; ++k)
				sum += B.at(m, k) * C.at(k, j);
			C.at(m, j) = 1 / (B.at(m, m)) * (A.at(m, j) - sum);
		}
	}

	//calc y
	MatrixCol<T> y(A.ColCnt());
	y.at(0, 0) = b.at(0, 0) / B.at(0, 0);
	for (size_t i = 1; i < A.ColCnt(); ++i) {
		T sum{ 0 };
		for (size_t k = 0; k < i; ++k)
			sum += B.at(i, k) * y.at(k, 0);
		y.at(i, 0) = 1 / B.at(i, i) * (b.at(i, 0) - sum);
	}
	//calc x
	MatrixCol<T> x(A.ColCnt());
	x.at(A.ColCnt() - 1, 0) = y.at(A.ColCnt() - 1, 0);
	for (size_t i = A.ColCnt() - 2;; --i) {
		T sum{ 0 };
		for (size_t k = i + 1; k < A.ColCnt(); ++k)
			sum += C.at(i, k) * x.at(k,0);
		x.at(i, 0) = y.at(i, 0) - sum;
		if (i == 0)
			break;
	}
	return x;
}


int main() {

	try {
		//freopen("inp.txt", "r", stdin);
		cout << "Chaletski Method\n";

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

		auto res = Chaletski(A, b);

		if (res)
			cout << "Result:\n" << res.value() << "\n";
		else
			cout << "Cannot solve\n";
	}
	catch (runtime_error& e) {
		cerr << e.what() << '\n';
	}
}





