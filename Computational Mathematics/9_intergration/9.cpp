#include <iostream>
#include <cmath>

#define M_PI 3.1415926535 ;

using namespace std;


double Deriv(double(*f)(double), double x, size_t degree) {
	const double eps = 1;
	if (degree == 1)
		return (f(x) - f(x + eps)) / (-eps);
	else
		return (Deriv(f, x + eps, degree - 1)
			- Deriv(f, x, degree - 1)) / eps;
}
double Deriv2(double(*f)(double), double x) {
	const double eps = 1e-6;
	return (f(x + eps) - 2 * f(x) + f(x - eps)) / (eps * eps);
}

double Deriv4(double(*f)(double), double x) {
	const double eps = 1;
	return (f(x + 5 * eps) 
		- 4 * f(x + 4 * eps) 
		+ 6 * f(x + 3 * eps) 
		- 4 * f(x + 2 * eps)
		+ f(x)) / (eps * eps * eps * eps);
}



namespace function
{
	// [-5;5]
	const char* f1_string() { return "x^2"; }
	double f1(double x) { return x * x; }
	double f1_begin() { return -5; }
	double f1_end() { return 5; }

	// [-Pi; Pi]
	const char* f2_string() { return "sin(x)^2"; }
	double f2(double x) { return sin(x) * sin(x); }
	double f2_begin() { return -M_PI; }
	double f2_end() { return M_PI; }

	// [-Pi; Pi]
	const char* f3_string() { return "sin(2x) + cos(7x) + 8"; }
	double f3(double x) { return sin(2 * x) + cos(7 * x) + 8; }
	double f3_begin() { return -M_PI; }
	double f3_end() { return M_PI; }

	// [-1;3]
	const char* f4_string() { return "2x^4 + x^3 + 2x^2 + 3x + 24"; }
	double f4(double x) { return 2 * x * x * x * x + x * x * x + 2 * x * x + 3 * x + 24; }
	double f4_begin() { return -1; }
	double f4_end() { return 3; }

	// [-100;100]
	const char* f5_string() { return "log(x^2 + 1) + sin(x / 3) + 17"; }
	double f5(double x) { return log(x * x + 1) + sin(x / 3) + 17; }
	double f5_begin() { return -100; }
	double f5_end() { return 100; }

	// [-Pi;Pi]
	const char* f6_string() { return "5^x + sin(x) + x + 11"; }
	double f6(double x) { return pow(5, x) + sin(x) + x + 11; }
	double f6_begin() { return -M_PI; }
	double f6_end() { return M_PI; }

	// [-7;7]
	const char* f7_string() { return "x^5 + 2x^4 + 3x^3 + 4x^2 + 5x + 6"; }
	double f7(double x) { return x * x * x * x * x + 2 * x * x * x * x + 3 * x * x * x + 4 * x * x + 5 * x + 6; }
	double f7_begin() { return -7; }
	double f7_end() { return 7; }
}

namespace test
{



#define TEST(f_name){											\
cout << #f_name << " method (n = 100):\n";						\
cout << "Test function f(x) = "<< function::f1_string() << '\n';\
f_name(function::f1,function::f1_begin(), function::f1_end());	\
R0(function::f1,function::f1_begin(), function::f1_end());		\
cout << "Test function f(x) = " << function::f2_string()<< '\n';\
f_name(function::f2, function::f2_begin(), function::f2_end());	\
R0(function::f2, function::f2_begin(), function::f2_end());		\
cout << "Test function f(x) = " << function::f3_string()<< '\n';\
f_name(function::f3, function::f3_begin(), function::f3_end());	\
R0(function::f3, function::f3_begin(), function::f3_end());		\
cout << "Test function f(x) = " << function::f4_string()<< '\n';\
f_name(function::f4, function::f4_begin(), function::f4_end());	\
R0(function::f4, function::f4_begin(), function::f4_end());		\
cout << "Test function f(x) = " << function::f5_string()<< '\n';\
f_name(function::f5, function::f5_begin(), function::f5_end());	\
R0(function::f5, function::f5_begin(), function::f5_end());		\
cout << "Test function f(x) = " << function::f6_string()<< '\n';\
f_name(function::f6,function::f6_begin(), function::f6_end());	\
R0(function::f6, function::f6_begin(), function::f6_end());		\
cout << "Test function f(x) = " << function::f7_string()<< '\n';\
f_name(function::f7, function::f7_begin(), function::f7_end());	\
R0(function::f7, function::f7_begin(), function::f7_end());		\
}



	class _9_2
	{
	public:
		static void exec()
		{
			TEST(Rectangle_Intergration);
		}
	private:
		static void Rectangle_Intergration(double (*f)(double), double begin, double end)
		{
			const int n{ 100 };
			const double h{ (end - begin) / n };
			double s{ 0 };
			for (int i = 0; i < n; ++i)
				s += f(begin + (i + 0.5) * h);
			cout << "\tI = " << h * s << '\n';
		}
		static void R0(double (*f)(double), double begin, double end)
		{
			const int n{ 100 };
			const double h{ (end - begin) / n };
			double r{ 0 };
			const double mult = h * h * h / 24;
			for (int i = 0; i < n; ++i)
				r += Deriv2(f, begin + (i + 0.5) * h);
			cout << "\tR = " << r * mult << '\n';
		}
	};

	class _9_3
	{
	public:
		static void exec()
		{
			TEST(Trapecium_Integration);
		}
	private:
		static void Trapecium_Integration(double (*f)(double), double begin, double end)
		{
			const int n{ 100 };
			const double h{ (end - begin) / n };
			double R{ 0 };
			double res{ 0 };
			for (int i = 0; i < n; ++i)
			{
				const double x1 = begin + i * h;
				const double x2 = begin + (i + 1) * h;
				R = 0.5 * (x2 - x1) * (f(x1) + f(x2));
				res += R;
			}
			cout << "\tI = " << res << '\n';
		}
		static void R0(double (*f)(double), double begin, double end)
		{
			const int n{ 100 };
			const double h{ (end - begin) / n };
			double r{ 0 };
			const double mult = h * h * h / 12;
			for (int i = 0; i < n; ++i)
				r += Deriv2(f, begin + (i + 0.5) * h);
			cout << "\tR = " << -r * mult << '\n';
		}
	};

	class _9_4
	{
	public:
		static void exec()
		{
			TEST(Simpson_Integration);
		}
	private:
		static void Simpson_Integration(double (*f)(double), double begin, double end)
		{
			const int n{ 100 };
			const double h{ (end - begin) / n };
			double res{ 0 };

			for (int i = 0; i < n; i += 2) {
				const double x1{ begin + i * h };
				const double x2{ x1 + h };
				const double x3{ x2 + h };
				res +=  h / 3.0 * (f(x1) + 4.0 * f(x2) + f(x3));
			}
			cout << "\tI = " << res << '\n';
		}
		static void R0(double (*f)(double), double begin, double end)
		{
			const int n{ 100 };
			const double h{ (end - begin) / n };
			double r{ 0 };
			const double mult = h * h * h * h * h / 90;
			for (int i = 0; i < n; ++i)
				r += Deriv(f, begin + (i + 0.5) * h,4);
			cout << "\tR = " << -r * mult << '\n';
		}
	};

	class _9_5_1
	{
	public:
		static void exec()
		{
			TEST(Newton_Cotes_Intergtaion_3);
		}
	private:

		static void Newton_Cotes_Intergtaion_3(double (*f)(double), double begin, double end)
		{
			const int n{ 99 }; //кратно 3
			const double h{ (end - begin) / n };
			double res{ 0 };
			for (int i = 0; i < n; i += 3)
			{
				const double x1{ begin + i * h };
				const double x2{ x1 + h };
				const double x3{ x2 + h };
				const double x4{ x3 + h };
				res += 3 * h / 8.0 * (f(x1) + 3.0 * f(x2) + 3.0 * f(x3) + f(x4));
			}
			cout << "\tI = " << res << '\n';
		}

		static void R0(double (*f)(double), double begin, double end)
		{
			const int n{ 100 };
			const double h{ (end - begin) / n };
			double r{ 0 };
			const double mult = h * h * h * h * h * 3.0 / 80.0;
			for (int i = 0; i < n; ++i)
				r += Deriv(f, begin + i * h, 4);
			cout << "\tR = " << -r * mult << '\n';
		}

	};


	class _9_5_2
	{
	public:
		static void exec()
		{
			TEST(Newton_Cotes_Intergtaion_4);
		}
	private:

		static void Newton_Cotes_Intergtaion_4(double (*f)(double), double begin, double end)
		{
			const int n{ 100 }; //кратно 4
			const double h{ (end - begin) / n };
			double res{ 0 };
			for (int i = 0; i < n; i += 4)
			{
				const double x1{ begin + i * h };
				const double x2{ x1 + h };
				const double x3{ x2 + h };
				const double x4{ x3 + h };
				const double x5{ x4 + h };
				res += 2  / 45.0 * h * (7 * f(x1) + 32 * f(x2) + 12 * f(x3) + 32 * f(x4) + 7 * f(x5));
			}
			cout << "\tI = " << res << '\n';
		}

		static void R0(double (*f)(double), double begin, double end)
		{
			const int n{ 100 };
			const double h{ (end - begin) / n };
			double r{ 0 };
			const double mult = pow(h,7) * 8.0 / 945.0;
			for (int i = 0; i < n; ++i)
				r += Deriv(f, begin + i * h, 6);
			cout << "\tR = " << -r * mult << '\n';
		}
	};
}


int main(void)
{
	test::_9_2::exec();
	cout << '\n';

	test::_9_3::exec();
	cout << '\n';

	test::_9_4::exec();
	cout << '\n';
	test::_9_5_1::exec();
	cout << '\n';
	test::_9_5_2::exec();
	cout << '\n';
	return 0;
}
