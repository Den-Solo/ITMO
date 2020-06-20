#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <optional>
#include "Matrix.h"
using namespace std;




template <class T>
optional<MatrixCol<T>> Gauss(const Matrix<T>& m) {
	Matrix<T> A = m.GetTriangle();
	MatrixCol<T> mc(m.LineCnt());
	size_t line = m.LineCnt() - 1;
	while (1) {
		T res = 0;
		for (size_t col = m.ColCnt() - 2; col > line; --col)
			res += mc.at(col, 0) * A.at(line, col);
		mc.at(line, 0) = (A.at(line, A.ColCnt() - 1) - res) / A.at(line, line);
		if (line == 0) break;
		--line;
	}
	return mc;
}


int main() {

	try {
		//freopen("inp.txt", "r", stdin);
		cout << "Gauss Method\n";

		size_t m, n;
		cout << "Input number of lines\n";
		cin >> m;
		cout << "Input number of cols\n";
		cin >> n;
		Matrix<complex<double>> A(m,n + 1);
		cout << "Input matrix\n";
		for (size_t line = 0; line < m; ++line)
			for (size_t col = 0; col < n; ++col)
				cin >> A.at(line, col);
		cout << "Input vector b\n";
		for (size_t line = 0; line < m; ++line)
			cin >> A.at(line, n);

		auto res = Gauss(A);

		if (res)
			cout << "Result:\n" << res.value() << "\n";
		else
			cout << "Cannot solve\n";
	}
	catch (runtime_error& e) {
		cerr << e.what() << '\n';
	}
}


