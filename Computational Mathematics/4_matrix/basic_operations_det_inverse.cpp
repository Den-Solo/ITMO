#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <optional>
using namespace std;

namespace std {


	template <class T>
	complex<T> operator+(complex<T> z1, int x) {
		return { z1.real() + static_cast<double>(x), z1.imag() };
	}

	template <class T>
	complex<T> operator+(int x, complex<T> z1) {
		return { z1.real() + static_cast<double>(x), z1.imag() };
	}
	template <class T>
	complex<T> operator*(int x, complex<T> z1) {
		return { z1.real() * static_cast<double>(x),
			z1.imag() * static_cast<double>(x) };
	}
	template <class T>
	complex<T> operator*(complex<T> z1, int x) {
		return { z1.real() * static_cast<double>(x),
			z1.imag() * static_cast<double>(x) };
	}
	template <class T>
	complex<T> operator/(complex<T> z1, int x) {
		return z1 / complex<T>(x, 0);
	}
	template <class T>
	complex<T> operator/(int x, complex<T> z1) {
		return complex<T>(x, 0) / z1;
	}



	template<typename T>
	class Matrix : public vector<vector<T>> { // a[line][column]

	private:
		bool triangle_ = false;
		bool changed_ = false;
		T det_mult_ = 1;

	private:

		vector<vector<T>>& Base();
		const vector<vector<T>>& Base() const;

	public:
		using vector<vector<T>>::vector;

		Matrix() = default;
		Matrix(size_t m, size_t n);
		virtual ~Matrix() = default;

		vector<T>& operator[](size_t line);
		const vector<T>& operator[](size_t line) const;

		virtual T& at(size_t line, size_t col);
		virtual const T& at(size_t line, size_t col) const;

		bool empty() const;

		virtual size_t LineCnt() const;
		virtual size_t ColCnt() const;
		size_t MaxInColIdx(size_t line, size_t col);

		void Resize(size_t lines, size_t cols);

		bool ToTriangleDown();
		optional<Matrix<T>> GetTriangle() const;
		optional<T> cDet() const;
		optional<T> Det();
		optional<T> Minor(size_t i, size_t j, Matrix<T>& buf) const;
		optional<Matrix<T>> Inverse() const;

		Matrix<T>& operator+=(const Matrix<T>& other);
		Matrix<T> operator+(const Matrix<T>& other) const;
		Matrix<T>& operator-=(const Matrix<T>& other);
		Matrix<T> operator-(const Matrix<T>& other) const;
		Matrix<T>& operator*=(const Matrix<T>& other);
		Matrix<T> operator*(const Matrix<T>& other) const;

		template <class U>
		friend Matrix<U>& operator*=(Matrix<U>& m, U val);
		template <class U>
		friend Matrix<U> operator*(const Matrix<U>& m, U val);
		template <class U>
		friend Matrix<U>& operator*=(U val, Matrix<U>& m);
		template <class U>
		friend Matrix<U> operator*(U val, const Matrix<U>& m);

	};

	template <class T>
	class MatrixCol : public Matrix<T> {

	public:
		MatrixCol(size_t lines) : Matrix<T>(1, lines) {}

		size_t ColCnt() const override {
			return 1;
		}

		size_t LineCnt() const override {
			return Matrix<T>::ColCnt();
		}

		T& at(size_t line, size_t col) override {
			return (*this)[0][line];
		}

		const T& at(size_t line, size_t col) const override {
			return (*this)[0][line];
		}


	};


	template <typename T>
	Matrix<T>::Matrix(size_t m, size_t n) {
		(*this).resize(m, vector<T>(n));
	}


	template <typename T>
	vector<vector<T>>& Matrix<T>::Base() {
		return *this;
	}


	template <typename T>
	const vector<vector<T>>& Matrix<T>::Base() const {
		return *this;
	}

	template <typename T>
	vector<T>& Matrix<T>::operator[](size_t line) {
		changed_ = true, triangle_ = false;
		return Base()[line];
	}


	template <typename T>
	const vector<T>& Matrix<T>::operator[](size_t line) const {
		return Base()[line];
	}


	template <typename T>
	T& Matrix<T>::at(size_t line, size_t col) {
		return (*this)[line][col];
	}


	template <typename T>
	const T& Matrix<T>::at(size_t line, size_t col) const {
		return (*this)[line][col];
	}


	template <typename T>
	bool Matrix<T>::empty() const {
		return this->size() == 0;
	}


	template <typename T>
	size_t Matrix<T>::LineCnt() const {
		return this->size();
	}


	template <typename T>
	size_t Matrix<T>::ColCnt() const {
		return !this->empty() ? (*this)[0].size() : 0;
	}


	template <typename T>
	size_t Matrix<T>::MaxInColIdx(size_t line, size_t col) {
		size_t max_idx = line;
		for (; line < this->size(); ++line) {
			if (abs((*this)[line][col]) > abs((*this)[max_idx][col]))
				max_idx = line;
		}
		return max_idx;
	}


	template <typename T>
	Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
		if (LineCnt() != other.LineCnt() || ColCnt() != other.ColCnt())
			throw runtime_error("Incorrect matrixes for summarizing");
		triangle_ = false;
		for (size_t line = 0; line < LineCnt(); ++line) {
			for (size_t col = 0; col < ColCnt(); ++col) {
				(*this).at(line, col) += other.at(line, col);
			}
		}
		return *this;
	}


	template <typename T>
	Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
		if (LineCnt() != other.LineCnt() || ColCnt() != other.ColCnt())
			throw runtime_error("Incorrect matrixes for summarizing");
		Matrix<T> new_m(*this);
		return new_m += other;
	}


	template <typename T>
	Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
		if (LineCnt() != other.LineCnt() || ColCnt() != other.ColCnt())
			throw runtime_error("Incorrect matrixes for subtraction");
		triangle_ = false;
		for (size_t line = 0; line < LineCnt(); ++line) {
			for (size_t col = 0; col < ColCnt(); ++col) {
				(*this).at(line, col) -= other.at(line, col);
			}
		}
		return *this;
	}


	template <typename T>
	Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
		if (LineCnt() != other.LineCnt() || ColCnt() != other.ColCnt())
			throw runtime_error("Incorrect matrixes for subtraction");
		Matrix<T> new_m(*this);
		return new_m -= other;
	}


	template <typename T>
	Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
		if (ColCnt() != other.LineCnt())
			throw runtime_error("Incorrect matrixes for multiplication");
		triangle_ = false;
		vector<T> tmp_line_l(ColCnt());
		for (size_t line_l = 0; line_l < LineCnt(); ++line_l) {
			tmp_line_l = (*this)[line_l];
			for (size_t col_r = 0; col_r < other.ColCnt(); ++col_r) {
				T sum = 0;
				for (size_t col_l = 0, line_r = 0; col_l < ColCnt(); ++col_l, ++line_r) {
					sum += tmp_line_l[col_l] * other.at(line_r, col_r);
				}
				(*this).at(line_l, col_r) = sum;
			}
		}
		this->Resize(this->LineCnt(), other.ColCnt());
		return *this;
	}


	template <typename T>
	Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
		if (ColCnt() != other.LineCnt())
			throw runtime_error("Incorrect matrixes for multiplication");
		Matrix<T> new_m(*this);
		return new_m *= other;
	}


	template <typename T>
	Matrix<T>& operator*=(Matrix<T>& m, T val) {
		for (size_t line = 0; line < m.LineCnt(); ++line)
			for (size_t col = 0; col < m.ColCnt(); ++col)
				m.at(line, col) *= val;
		return m;
	}


	template <typename T>
	Matrix<T> operator*(const Matrix<T>& m, T val) {
		Matrix<T> tmp(m);
		for (size_t line = 0; line < tmp.LineCnt(); ++line)
			for (size_t col = 0; col < tmp.ColCnt(); ++col)
				tmp.at(line, col) *= val;
		return tmp;
	}


	template <typename T>
	Matrix<T>& operator*=(T val, Matrix<T>& m) {
		for (size_t line = 0; line < m.LineCnt(); ++line)
			for (size_t col = 0; col < m.ColCnt(); ++col)
				m.at(line, col) *= val;
		return m;
	}


	template <typename T>
	Matrix<T> operator*(T val, const Matrix<T>& m) {
		Matrix<T> tmp(m);
		for (size_t line = 0; line < tmp.LineCnt(); ++line)
			for (size_t col = 0; col < tmp.ColCnt(); ++col)
				tmp.at(line, col) *= val;
		return tmp;
	}


	template <typename T>
	void Matrix<T>::Resize(size_t lines, size_t cols) {
		(*this).resize(lines);
		for (auto& v : (*this))
			v.resize(cols);
	}


	template <typename T>
	bool Matrix<T>::ToTriangleDown() {
		if (changed_) det_mult_ = 1, changed_ = false;
		for (size_t line = 0; line < LineCnt() - 1; ++line) {
			//change lines if necessary
			if (size_t k = MaxInColIdx(line, line); k != line) {
				swap((*this)[line], (*this)[k]);
				det_mult_ *= -1;
			}

			if (abs((*this)[line][line]) < abs(T{ 1e-9 }))
				return false;

			det_mult_ *= (*this)[line][line];	//line will be devided by m[line][line]
												//so mult res by m[line][line]
			T line_mult = (*this)[line][line];
			for (size_t col = line; col < ColCnt(); ++col)
				(*this)[line][col] /= line_mult;

			//loop goes through all lines with idx less than line 
			for (size_t l = line + 1; l < LineCnt(); ++l) {
				T mult{ (*this)[l][line] };
				for (size_t col = line; col < ColCnt(); ++col)
					(*this)[l][col] -= (*this)[line][col] * mult;
			}
		}
		triangle_ = true;
		return true;
	}


	template <typename T>
	optional<Matrix<T>> Matrix<T>::GetTriangle() const {
		Matrix<T> tmp(*this);
		if (tmp.ToTriangleDown())
			return tmp;
		else
			return nullopt;
	}


	template <typename T>
	optional<T> Matrix<T>::Det() {
		if (!triangle_ || changed_) {
			if (ColCnt() != LineCnt())
				return nullopt;
			ToTriangleDown();
		}
		T det = 1;
		for (size_t line = 0; line < LineCnt(); ++line) {
			det *= (*this)[line][line];
		}
		return det * det_mult_;
	}



	template <typename T>
	optional<T> Matrix<T>::cDet() const {
		Matrix<T> tmp(*this);
		return tmp.Det();
	}

	template <typename T>
	optional<T> Matrix<T>::Minor(size_t i, size_t j, Matrix<T>& buf) const {
		for (size_t line = 0, buf_l = 0; line != LineCnt(); ++line) {
			if (line == i) continue;
			for (size_t col = 0, buf_c = 0; col != ColCnt(); ++col) {
				if (col == j) continue;
				buf[buf_l][buf_c] = (*this)[line][col];
				++buf_c;
			}
			++buf_l;
		}
		return buf.Det();
	}

	template <typename T>
	optional<Matrix<T>> Matrix<T>::Inverse() const {
		auto det_this = cDet();
		if (!det_this)
			return nullopt;
		Matrix<T> inverse(LineCnt(), ColCnt());
		Matrix<T> minor_buf(LineCnt() - 1, ColCnt() - 1);
		for (size_t line = 0; line != LineCnt(); ++line) {
			for (size_t col = 0; col != ColCnt(); ++col) {
				optional<T> min = Minor(line, col, minor_buf);
				if (min.has_value()) {
					inverse[col][line] = min.value();
					inverse[col][line] *= (col - line) % 2 ? -1 : 1;
				}
				else
					return nullopt;
			}
		}
		inverse *= (1 / det_this.value());
		return inverse;
	}


	template <typename T>
	ostream& operator<<(ostream& ostr, const Matrix<T>& m) {
		for (auto i = 0; i < m.LineCnt(); i++) {
			ostr << "| "
				<< setw(8) << setfill('.')
				<< setprecision(6) << m.at(i, 0) << ' ';
			for (auto j = 1; j < m.ColCnt() - 1; j++) {
				ostr << setw(8) << setfill('.') <<
					setprecision(6) << m.at(i, j) << ' ';
			}
			if (m.ColCnt() > 1) {
				ostr << setw(8) << setprecision(6)
					<< setfill('.') << m.at(i, m.ColCnt() - 1);
			}
			ostr << " |\n";
		}
		return ostr;
	}


	template <typename T>
	istream& operator>>(istream& istr, Matrix<T>& m) {
		for (size_t line = 0; line < m.LineCnt(); line++) {
			for (size_t col = 0; col < m.ColCnt(); ++col) {
				istr >> m.at(line, col);
			}
		}
		return istr;
	}



	template <class T>
	Matrix<T> ReadMatrixDialog(istream& istr, ostream& ostr) {
		size_t m, n;

		ostr << "Input Matrix of coefs, please\n";
		ostr << "Number of Lines: ";
		istr >> m;
		ostr << "Number of Columns: ";
		istr >> n;
		ostr << "Input Matrix\n";

		Matrix<T> m1(m, n);
		istr >> m1;
		ostr << '\n';
		return m1;
	}



	template <class T>
	MatrixCol<T> ReadMatrixColDialog(istream& istr, ostream& ostr) {
		size_t n;

		ostr << "Input vector of coefs, please\n";
		ostr << "Input number of coefs\n";
		istr >> n;
		ostr << "Input MatrixColumn\n";

		MatrixCol<T> v(n);
		istr >> v;
		return v;
	}


};

int main() {

	//freopen("inp.txt", "r", stdin);

	int command;
	cout << "Choose action:\n"
		<< "To make sum of two matrixes: 1\n"
		<< "To make subtraction of two matrixes: 2\n"
		<< "To multiply two matrixes: 3\n"
		<< "To multiply matrix and complex: 4\n"
		<< "To find det: 5\n"
		<< "To get inverse: 6\n";
	cin >> command;

	try {
		switch (command)
		{
		case 1: {
			auto m1 = ReadMatrixDialog<complex<double>>(cin, cout);
			auto m2 = ReadMatrixDialog<complex<double>>(cin, cout);
			cout << "Result\n" << m1 + m2;
			break;
		}
		case 2: {
			auto m1 = ReadMatrixDialog<complex<double>>(cin, cout);
			auto m2 = ReadMatrixDialog<complex<double>>(cin, cout);
			cout << "Result\n" << m1 - m2;
			break;
		}
		case 3: {
			auto m1 = ReadMatrixDialog<complex<double>>(cin, cout);
			auto m2 = ReadMatrixDialog<complex<double>>(cin, cout);
			cout << "Result\n" << m1 * m2;
			break;
		}
		case 4: {
			auto m1 = ReadMatrixDialog<complex<double>>(cin, cout);
			cout << "Input Complex Number\n";
			complex<double> c;
			cin >> c;
			cout << "Result\n" << m1 * c;
			break;
		}
		case 5: {
			auto m1 = ReadMatrixDialog<complex<double>>(cin, cout);
			cout << "Result\n";
			auto r = m1.Det();
			r.has_value() 
				? cout << r.value() 
				: cout << "impossible to compute det";
			break;
		}
		case 6: {
			auto m1 = ReadMatrixDialog<complex<double>>(cin, cout);
			cout << "Result\n";
			auto r = m1.Inverse();
			r.has_value() 
				? cout << r.value() 
				: cout << "impossible to inverse";
			break;
		}
		default:
			throw runtime_error("wrong command number\n");
			break;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << '\n';
	}
}


