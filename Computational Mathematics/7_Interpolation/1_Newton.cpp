#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <complex>
#include <cassert>
//#define M_PI 3.141592653 //у меня не включаются константы


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

		if (i.imag() >= 0)
			ostr << " + i" << im;
		else
			ostr << " - i" << -im;

		ostr << ";\n";
	}
	return ostr;
}


namespace Function {


	template <typename F>
	vector<double> GenSqnc(F&& f, size_t size) {
		const double beg = f.beg();
		const double h = (f.end() - beg) / (size - 1);
		vector<double> sqnc(size);
		for (size_t i = 0; i < size; ++i)
			sqnc[i] = f(beg + i * h);
		return sqnc;
	}


	struct base_func {
		virtual double operator()(double x) { return 0; }
		virtual double beg() const = 0;
		virtual double end() const = 0;
		virtual const char* name() const { return "base_func"; }
	};
	struct f1 : base_func {
		double operator()(double x) override { return x * x; }
		double beg() const override { return -5; }
		double end() const override { return 5; }
		const char* name() const override { return "x^2"; }
	};
	struct f2 : base_func {
		double operator()(double x) { return sin(x) * sin(x); }
		double beg() const override  { return -M_PI; }
		double end() const override  { return M_PI; }
		const char* name() const override { return "(sin(x))^2"; }
	};
	struct f3 : base_func {
		double operator()(double x) { return sin(2 * x) + cos(7 * x) + 8; }
		double beg() const override { return -M_PI; }
		double end() const override { return M_PI; }
		const char* name() const override { return "sin(2x) + cos(7x) + 8";; }
	};
	struct f4 : base_func {
		double operator()(double x) { return 2 * x * x * x * x + x * x * x + 2 * x * x + 3 * x + 24; }
		double beg() const override { return -1; }
		double end() const override { return 3; }
		const char* name() const override { return "2x^4 + x^3 + 2x^2 + 3x + 24"; }
	};

	double len(base_func* p) {
		return p->end() - p->beg();
	}
	//double Deriv1(double(*f)(double), double x) {
	//	const double eps = 1e-9;
	//	return (f(x) - f(x + eps)) / (-eps);
	//}
	//double Deriv2(double(*f)(double), double x) {
	//	const double eps = 1e-6;
	//	double x0 = x + eps;
	//	return (f(x + eps) - 2 * f(x) + f(x - eps)) / (eps * eps);
	//}
}









namespace HW8 {

	
	


	//левые конечные разности
	class _8_1_1 {

	public:

		static double _deriv(
			const vector<double>& data, size_t degree, 
			size_t pos, double h
		) {
			if (!degree)
				return data[pos];
			return (_deriv(data, degree - 1, pos - 1, h)
				- _deriv(data, degree - 1, pos, h) ) / h;
		}

		static vector<double> deriv(
			const vector<double>& data, size_t degree, double h
		) {
			vector<double> res(data.size() - degree);
			for (size_t i = degree; i < data.size(); ++i) {
				res[i - degree]
					= (_deriv(data, degree - 1, i - 1, h)
						- _deriv(data, degree - 1, i, h))/ h;
			}
			return res;
		}

	};









	//правые конечные разности
	class _8_1_2 {

	public:

		static double _deriv(
			const vector<double>& data, size_t degree,
			size_t pos, double h
		) {
			if (!degree)
				return data[pos];
			return (_deriv(data, degree - 1, pos, h)
				- _deriv(data, degree - 1, pos + 1, h)) / h;
		}

		static vector<double> deriv(
			const vector<double>& data, size_t degree, double h
		) {
			vector<double> res(data.size() - degree);
			for (size_t i = 0; i < data.size() - degree; ++i) {
				res[i] = (_deriv(data, degree - 1, i, h)
						- _deriv(data, degree - 1, i + 1, h)) / h;
			}
			return res;
		}

	};





	//фурье 
	class _8_2 {

	public:

	
		using cd = complex<double>;

		
	private:
		
		//чуть меньше копирований
		static void _fft(vector<cd>& a, bool invert) {
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
		static vector<cd> _dft(const vector<cd>& data, bool invert) {
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


	public:


		static vector<cd> fft(const vector<cd>& data, bool invert) {
			int n = data.size();
			if (n == 1)
				return data;

			//не степень 2 => наивный подход O(n^2)
			//степень 2 => O(nlog(n))
			if (ceil(log2(n)) != floor(log2(n)))
				return _dft(data,invert);

			vector<cd> a = data;
			_fft(a, invert);
			return a;
		
		}


		//тригонометрическая интерполяция
		template <class T>
		static vector<T> FourierInterpolate(const vector<T>& data) {
			size_t N = data.size();
			assert(ceil(log2(N)) == floor(log2(N))); //только степень двойки (так в условии дз)
			vector<cd> cdata(N);
			for (size_t i = 0; i < N; ++i)
				cdata[i] = { data[i], 0 };
			auto ft_data = fft(cdata, false);
			vector<cd> Y(N * 2);

			for (size_t i = 0; i < N / 2; ++i) //только для четного N
				Y[i] = ft_data[i];
			for (size_t i = 3 * N / 2 + 1; i < 2 * N; ++i)
				Y[i] = ft_data[i - N];

			Y[N / 2] = Y[3 * N / 2] = ft_data[N / 2] / cd(2);

			auto y = fft(Y, true);
			vector<double> res(y.size());
			for (size_t i = 0; i < N; ++i)
				res[i] = y[i].real();
			return res;
		}


		static vector<double> deriv(const vector<double>& data, size_t degree, double h) {
			size_t N = data.size();
			assert(ceil(log2(N)) == floor(log2(N)));
			const double a = x0;
			const double b = a + N * h;
			vector<cd> data_compl(N);
			for (size_t i = 0; i < N; ++i)
				data_compl[i] = { data[i], 0 };
			vector<cd> ft = fft(data_compl, false);

			for (size_t i = 0; i < ft.size(); ++i) {
				complex<double> tmp { 0 , 2 * M_PI * (N / 2 - N + i) / (b - a) };
				pow(tmp, degree);
				ft[i] *= tmp;
			}

			auto res_compl = fft(ft, true);
			vector<double> res(res_compl.size());
			for (size_t i = 0; i < res.size(); ++i)
				res[i] = abs(res_compl[i]);
			return res;
		}
	};














	//первая формула ньютона (для левого конца таблицы)
	class _8_3_1 {

		static vector<vector<double>> fin_diff_cache;  
	public:

		//считает интерполированный полином, только для первой формулы ньютона

		static double Poly(
			double q, size_t pos, size_t limit
		) {
			double res{ fin_diff_cache[0][pos] };
			size_t fact{ 1 };
			for (size_t i = 1; i < limit; ++i) {
				res += fin_diff_cache[i][pos] * q / fact;
				q *= q - 1.0;
				fact *= i + 1;
			}
			return res;
		}

		static vector<double> NewtonInterpolateSequence(
			const vector<double>& y, double x0, double h, size_t limit
		) {
			//расчет всех иксов 
			vector<double> X(y.size());
			for (size_t i = 0; i < X.size(); ++i)
				X[i] = x0 + i * h;

			//расчет таблицы конечных разностей
			fin_diff_cache.assign(y.size() + 1, vector<double>(y.size() + 1));
			for (size_t pos = 0; pos < y.size() - limit; ++pos) {
				for (size_t deg = 0; deg < limit; ++deg)
					fin_diff(y, deg, pos);
			}

			vector<double> res;
			res.reserve(y.size() * 2);
			size_t pos = 0;
			for (double x = x0; x <= X.back(); x += h / 2) {
				while ((pos != X.size() - 1) && X[pos + 1] < x) ++pos;
				double q = (x - X[pos]) / h;
				res.emplace_back(Poly(q, pos, limit));
			}
			return res;
		}

		/*static double _deriv(const vector<double>& N_poly, size_t degree, double q, double h) {
			const double EPS = h / ((h < 0.1) ?  1000 : 1e6);
			if (!degree) {
				return Poly(N_poly, q, 4);
			}
			else {
				return (_deriv(N_poly, degree - 1, q, h)
					- _deriv(N_poly, degree - 1, q + EPS, h)) / -EPS;
			}
		}*/
		
		
		static double fin_diff(const vector<double>& data, size_t degree, size_t pos) {
			if (fin_diff_cache[degree][pos] != 0)
				return fin_diff_cache[degree][pos];
			if (!degree)
				return fin_diff_cache[degree][pos] = data[pos];
			return fin_diff_cache[degree][pos] 
					= fin_diff(data, degree - 1, pos + 1)
						- fin_diff(data, degree - 1, pos);
		}
	



		/*static vector<double> deriv(const vector<double>& data, size_t degree, double h) {
			vector<double> res(data.size());
			const vector<double> poly = _8_3_1::NewtonInterpolate_1(data, 0);

			double x = x0;
			for (size_t i = 0; i < res.size(); ++i) {
				res[i] = _deriv(poly, degree, (x - x0) / h, h) / pow(h, degree);
				x += h;
			}

			return res;
		}*/

	};

	namespace Test_8 {

		using deriv_f_ptr = vector<double> (*) (const vector<double>& data, size_t degree, double h);

		void test(
			deriv_f_ptr deriv,
			size_t degree,
			size_t func_idx,
			ostream& ostr
		)
		{
			static auto _1 = Function::f1{}; static auto _2 = Function::f2{};
			static auto _3 = Function::f3{}; static auto _4 = Function::f4{};

			static const vector<Function::base_func*> funcs = { &_1, &_2, &_3, &_4 };

			static const size_t cnt_intervals = 32;
			static const double h = Function::len(funcs[func_idx]) / cnt_intervals;
			
		
			const auto seq = Function::GenSqnc(*funcs[func_idx], cnt_intervals);
			auto res = deriv(seq, degree, h);


			const double h2 = Function::len(funcs[func_idx]) / res.size();
			for (size_t i = 0; i < res.size(); ++i) {
				ostr << funcs[func_idx]->beg() + i  * h2 << ';'
					<< res[i] << ";\n";
			}
		}
		
		void PrepareCSVs() {
			static const map<string, deriv_f_ptr>
				deriv_funcs = { {"_8_1_1::deriv_", _8_1_1::deriv},
								{"_8_1_2::deriv_", _8_1_2::deriv},
								/*{"_8_2::deriv_", _8_2::deriv},
								{"_8_3_first_", _8_3_1::deriv},
								{"_8_3_2", _8_3_2::deriv}*/
									};

			for (auto& f : deriv_funcs)
				for (size_t func_idx = 0; func_idx < 4; ++func_idx)
					for (size_t deg = 1; deg < 4; ++deg) {
						ofstream ofs("HW8" + f.first + to_string(func_idx) + "_d" + to_string(deg) + ".csv");
						if (!ofs.is_open()) throw runtime_error("file not opened");
						Test_8::test(f.second, deg, func_idx, ofs);
					}

		}
	};


	
};





void test_6_3();
void test_7_1_1();
void test_7_1_2();
void micro_test_8_3_first();


int main() {
	using namespace HW8;
	using namespace Function;


	{ //интерполяция ньютоном // в a.csv - исходный график (x,y) //в b.csv -интерполированный результат с удвоенным числом точек
		//как и ожидалось на концах интерполированного интервала плохо с точностью а в целом очень даже
		auto f = f1{};
		auto y = GenSqnc(f, 32);
		double h = len(&f) / 32;

		vector<double> x(32);
		ofstream of1("a.csv");
		for (size_t i = 0; i < y.size(); ++i) {
			of1 << f.beg() + i * h  << ';'
				<< y[i] << '\n';
			x[i] = f.beg() + i * h;
		}

		auto res = _8_3_1::NewtonInterpolateSequence(y, f.beg(), h, 4);
		ofstream ofs("b.csv");
		for (size_t i = 0; i < res.size(); ++i) {
			ofs << f.beg() + i * h / 2 << ';'
				<< res[i] << '\n';
		}
	}













	//Test_8::PrepareCSVs(); //там надо графики строить сравнительные, вот
	
	{
		//Test_8::test(_8_3_2::deriv, 1, 0, cout);
	}



	/*{
		auto f = Function::f2{};
		vector<double> a = Function::GenSqnc(f,32);
		
	
		auto res = _8_2::FourierInterpolate(a);

		double h = Function::len(&f) / res.size();
		for (size_t i = 0; i < res.size(); ++i) {
			cout << f.beg() + i * h << ' '
				<< res[i] << '\n';
		}
	}*/

	//тестирование 6.3, 7.1, 7.4
	//test_6_3();
	//test_7_1_1();
	//test_7_1_2();

	//micro_test_8_3_first();
}





//тестирование 6.3, 7.1, 7.4
/*

struct ff : Function::base_func {
	double operator()(double x) { return exp(x); }
	double beg() const override { return 3.5; }
	double end() const override { return 3.7; }
};



void test_6_3() {
	using namespace HW8;
	vector<complex<double>> a = { 0.8427, 0.8802, 0.9103, 0.9340,
							0.9523, 0.9661, 0.9763, 0.9838,
							0.9891, 0.9928, 0.9953 };
	a = _8_2::fft(a, false);

	cout << a << "\n\n";

	a = _8_2::fft(a, true);
	cout << a;
}




void test_7_1_1() {
	using namespace HW8;
	{//works fine
		x0 = ff{}.beg();
		auto seq = Function::GenSqnc(ff{}, 5);
		fin_diff_cache.resize(5 + 1, vector<double>(5 + 1));
		const double h = (ff{}.end() - ff{}.beg()) / (seq.size() - 1);
		auto res = _8_3_1::NewtonInterpolate_1(seq);
		cout << res << "\n\n";
		cout << _8_3_1::Poly(res, (3.55 - x0) / h);
	}
	
	
	
	{//works fine x = [0, 5] (аналитический вид неизвестен)
		vector<double> seq = { 5.2, 8.0, 10.4, 12.4, 14.0, 15.2 };
		fin_diff_cache.resize(6 + 1, vector<double>(6 + 1));
		const double h = 1;
		x0 = 0;
		auto res = _8_3_1::NewtonInterpolate_1(seq);
		cout << res << "\n\n";
		cout << _8_3_1::Poly(res, (2.5 - x0) / h);
	}


	{//works fine - интеграл вероятностей //x = [1.0, 2.0]
		vector<double> seq = {  0.8427, 0.8802, 0.9103, 0.9340,
								0.9523, 0.9661, 0.9763, 0.9838,
								0.9891, 0.9928, 0.9953};
		fin_diff_cache.resize(11 + 1, vector<double>(11 + 1));
		const double h = 0.1;
		x0 = 1.4;
		const size_t idx = 4;//номер значения из seq для которого вычисляются конечные разности
							//чем ближе x0 к числу x, тем выше точность
		auto res = _8_3_1::NewtonInterpolate_1(seq, idx);
		cout << res << "\n\n";
		cout << _8_3_1::Poly(res, (1.43 - x0) / h); //0.95686
	}
}






void micro_test_8_3_first()
{
	using namespace HW8;
	size_t cnt_intervals = 3;
	double h = 5;
	x0 = 50;
	vector<double> seq = { 1.6990, 1.7404, 1.7782, 1.8129 };
	fin_diff_cache.resize(cnt_intervals + 2, vector<double>(cnt_intervals + 2));


	vector<vector<double>> a;
	for (size_t i = 0; i < cnt_intervals / 2; ++i)
		a.emplace_back(_8_3_1::NewtonInterpolate_1(seq, i));

	//auto res = _8_3_1::NewtonInterpolate_1(seq);
	//auto res1 = _8_3_1::NewtonInterpolate_1(seq,  1);
	//auto res2 = _8_3_1::NewtonInterpolate_1(seq,  2);
	//auto res3 = _8_3_1::NewtonInterpolate_1(seq,  3);

	size_t i = 0, c = 0;

	auto k = fin_diff_cache;
	for (double x = x0; x <= 65; x += h) {
		cout << x << ' ';
		cout << _8_3_1::Poly(a[c], (x - x0) / h, 4) << "   ";
		cout << _8_3_1::_deriv(a[c], 1, (x - x0) / h, h) / pow(h, 1) << "\n";
	}
	cout << "\n\n\n";

	{
		auto f = Function::f1{};
		size_t cnt_intervals = 30;
		double h = Function::len(&f) / 30;
		x0 = f.beg();
		auto seq = (Function::GenSqnc(f, 30));
		fin_diff_cache.resize(cnt_intervals + 2, vector<double>(cnt_intervals + 2));

		vector<vector<double>> a;
		for (size_t i = 0; i < cnt_intervals - 15; ++i)
			a.emplace_back(_8_3_1::NewtonInterpolate_1(seq, i));

		//auto res = _8_3_1::NewtonInterpolate_1(seq, h);
		//auto res1 = _8_3_1::NewtonInterpolate_1(seq, h, 1);
		//auto res2 = _8_3_1::NewtonInterpolate_1(seq, h, 2);
		//auto res3 = _8_3_1::NewtonInterpolate_1(seq, h, 3);

		size_t i = 0, c = 0;

		auto k = fin_diff_cache;
		for (double x = x0; x < f.end() - h; x += h) {
			cout << x << ' ';
			cout << _8_3_1::Poly(a[c], (x - x0) / h, 4) << "   ";
			cout << _8_3_1::_deriv(a[c], 1, (x - x0) / h, h)  * 2.9 << "\n";
		}
		cout << "\n\n\n";

	}
}*/