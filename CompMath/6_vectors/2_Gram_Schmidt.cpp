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

template <class T>
T ScalarMultLines(const Matrix<T>& A, size_t line_A, const Matrix<T>& B, size_t line_B) {
	T res{ 0 };
	for (size_t col = 0; col < A.ColCnt(); ++col) {
		res += A.at(line_A, col) * B.at(line_B, col);
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



template<class T>
vector<T>& operator-=(vector<T>& a, const vector<T>& b) {
	for (size_t i = 0; i < a.size(); ++i) {
		a[i] -= b[i];
	}
	return a;
}

template<class T>
vector<T> operator-(const vector<T>& a, const vector<T>& b) {
	return vector<T>(a) -= b;
}


template <class T>
T Length(const Matrix<T>& A, size_t col) {
	return sqrt(ScalarMultCols(A, col, col));
}


template <class T>
T ScalarMultCols(
	const Matrix<T>& A, size_t col_A,
	const Matrix<T>& B, size_t col_B
) {
	T res{ 0 };
	for (size_t line = 0; line < A.LineCnt(); ++line) {
		res += A[line][col_A] * B[line][col_B];
	}
	return res;
}


template<class T>
Matrix<T> Gram_Schmidt_Col(const Matrix<T>& A) {
	Matrix<T> res(A);										//первый столбце уже готов
	for (size_t col = 1; col < A.ColCnt(); ++col) {			//col - индекс вектора

		for (size_t line = 0; line < A.LineCnt(); ++line) { //i-я координата вектора 
			res[line][col] = A[line][col];
		}

		for (size_t i = 0; i < col; ++i) {	//индексы векторов b в проекциях
			T proj_mult = ScalarMultCols(A, col, res, i)
				/ ScalarMultCols(res, i, i);
			for (size_t line = 0; line < A.LineCnt(); ++line) //j-я координата вектора
				res[line][col] -= proj_mult * res[line][i];
		}
		
	}
	return res;
}


template<class T>
Matrix<T> Gram_Schmidt_Line(const Matrix<T>& A) {
	Matrix<T> res(A);										//первая строка готова
	for (size_t line = 1; line < A.LineCnt(); ++line) {		//line - индекс вектора

		for (size_t col = 0; col < A.ColCnt(); ++col) { //i-я координата вектора 
			res[line][col] = A[line][col];
		}

		for (size_t i = 0; i < line; ++i) {					//индексы векторов b в проекциях
			T proj_mult = ScalarMultLines(A, line, res, i)
				/ ScalarMultLines(res, i, i);
			for (size_t col = 0; col < A.ColCnt(); ++col) //j-я координата вектора
				res[line][col] -= proj_mult * res[i][col];
		}

	}
	return res;
}

int main() {
	freopen("inp.txt", "r", stdin);

	size_t m, n;

	cout << "Input num of lines and cols\n";
	cin >> m >> n;
	Matrix<double> A(m, n);
	cout << "Input matrix\n";
	cin >> A;
	cout << "Result: \n";
	cout << Gram_Schmidt_Line(A);
}





