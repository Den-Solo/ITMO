#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <optional>
#include "Matrix.h"
using namespace std;




template <class T>
optional<Matrix<T>> Kramer(const Matrix<T>& m, const MatrixCol<T>& b) {
	auto inv = m.Inverse();
	if (inv)
		return inv.value() * b;
	else
		return nullopt;
}

int main() {

	try {
		cout << "Kramer Method\n";
		auto m = ReadMatrixDialog<double>(cin, cout);
		auto v = ReadMatrixColDialog<double>(cin, cout);

		auto res = Kramer<double>(m, v);
		if (res)
			cout << "Result:\n" << res.value() << "\n";
		else
			cout << "Cannot solve\n";
	}
	catch (runtime_error& e) {
		cerr << e.what() << '\n';
	}
}


