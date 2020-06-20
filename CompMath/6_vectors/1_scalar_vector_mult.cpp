#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <optional>
#include "Matrix.h"
using namespace std;
using namespace CompMaths;


//две заданные строки матрицы
template <class T>
T ScalarMultLines(const Matrix<T>& A, size_t line_1, size_t line_2) {
	T res{ 0 };
	for (size_t col = 0; col < A.ColCnt(); ++col) {
		res += A.at(line_1, col) * A.at(line_2, col);
	}
	return res;
}


//два заданных столбц матрицы
template <class T>
T ScalarMultCols(const Matrix<T>& A, size_t col_1, size_t col_2) {
	T res{ 0 };
	for (size_t line = 0; line < A.LineCnt(); ++line) {
		res += A.at(line, col_1) * A.at(line, col_2);
	}
	return res;
}


//все строки матрицы
template <class T>
T ScalarMultLines(const Matrix<T>& A) {
	T res{ 0 };
	for (size_t col = 0; col < A.ColCnt(); ++col) {
		T mult = 1;
		for (size_t line = 0; line < A.LineCnt(); ++line)
			mult *= A.at(line, col);
		res += mult;
	}
	return res;
}


//все столбцы матрицы
template <class T>
T ScalarMultCols(const Matrix<T>& A) {
	T res{ 0 };
	for (size_t line = 0; line < A.LineCnt(); ++line) {
		T mult = 1;
		for (size_t col = 0; col < A.ColCnt(); ++col)
			mult *= A.at(line, col);
		res += mult;
	}
	return res;
}


//только для трехмерного пространства
template <class T>
vector<T> VectorMult(const vector<T>& v1, const vector<T>& v2) {
	if (v1.size() != 3 || v2.size() != 3)
		return vector<T>();
	Matrix<T> tmp(3, 3);
	Matrix<T> buf(2, 2);
	tmp[1] = v1;
	tmp[2] = v2;

	vector<T> res(3);
	for (size_t i = 0; i < 3; ++i) {
		res[i] = tmp.Minor(0, i, buf).value();
		res[i] *= i % 2 ? -1 : 1;
	}
	return res;
}

template <class T>
vector<T> VectorMultLines(const Matrix<T>& A, size_t line_1, size_t line_2) {
	return VectorMult(A[line_1], A[line_2]);
}

template <class T>
vector<T> VectorMultCols(const Matrix<T>& A, size_t col_1, size_t col_2) {
	vector<T> a(3), b(3);
	for (size_t i = 0; i < 3; ++i) {
		a[i] = A.at(i, col_1);
		b[i] = A.at(i, col_2);
	}
	return VectorMult(a, b);
}

template <class T>
ostream& operator<<(ostream& ostr, const vector<T>& v) {
	ostr << "( ";
	bool first_ = true;
	for (auto& i : v) {
		if (!first_)
			ostr << ", ";
		ostr << i;
		first_ = false;
	}
	ostr << " )";
	return ostr;
}


int main() {

	size_t m, n;
	cout << "Input number of lines and number of columns\n";
	cin >> m >> n;
	Matrix<double> A(m, n);
	cout << "Input matrix\n";
	cin >> A;
	cout << "Input command: 1 - to scalar mult, 2 - to vector mult\n";

	int command;
	cin >> command;
	switch (command)
	{
	case 1: {
		cout << "1 - to mult the whole matrix lines\n"
			<< "2 - to mult the whole matrix columns\n"
			<< "3 - to mult two lines\n"
			<< "4 - to mult two columns\n";
		cin >> command;
		switch (command)
		{
		case 1: {
			cout << "Result: " << ScalarMultLines(A);
			break;
		}
		case 2: {
			cout << "Result: " << ScalarMultCols(A);
			break;
		}
		case 3: {
			size_t l1, l2;
			cout << "Input line numbers\n";
			cin >> l1 >> l2;
			cout << "Result: " << ScalarMultLines(A, l1, l2);
			break;
		}
		case 4: {
			size_t c1, c2;
			cout << "Input col numbers\n";
			cin >> c1 >> c2;
			cout << "Result: " << ScalarMultCols(A, c1, c2);
			break;
		}
		default:
			break;
		}
		break;
	}
	case 2: {
		cout << "1 - to mult two lines\n"
			<< "2 - to mult two columns\n";
		cin >> command;
		switch (command)
		{
		case 1: {
			size_t l1, l2;
			cout << "Input line numbers\n";
			cin >> l1 >> l2;
			cout << "Result: " << VectorMultLines(A, l1, l2);
			break;
		}
		case 2: {
			size_t c1, c2;
			cout << "Input col numbers\n";
			cin >> c1 >> c2;
			cout << "Result: " << VectorMultCols(A, c1, c2);
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
}





