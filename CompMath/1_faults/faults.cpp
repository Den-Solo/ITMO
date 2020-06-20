#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

//относительная погрешность
template <class T>
inline T RelDeviation(T absDev, T realVal) {
	if (realVal)
		return absDev / abs(realVal);
	else
		return absDev;
}

//������� ��������������

//c style
double Average(const double* beg, size_t size) {
	size_t count = 0;
	double sum = 0;
	for (; count < size; ++count) {
		sum += beg[count];
	}
	return sum / count;
}


//c++ style
template <class T, class ForwardIt>
T Average(ForwardIt beg, ForwardIt end) {
	size_t count = 0;
	T sum = 0;
	for (; beg != end; beg = next(beg)) {
		sum += *beg;
		++count;
	}
	return sum / count;
}

template <class T>
T Average(const vector<T>& data) {
	size_t count = 0;
	T sum = 0;
	for (const auto el : data) {
		sum += el;
		++count;
	}
	return sum / count;
}

// ������� �������������� ���������� (standart deviation)

//c style
double StdDeviation(const double* beg, size_t size) {
	double sum = 0;
	for (size_t i = 0; i < size; ++i) {
		sum += beg[i] * beg[i];
	}
	return sqrt(sum);
}

//c++ style
template <class T, class ForwardIt>
T StdDeviation(ForwardIt beg, ForwardIt end) {
	T sum = 0;
	for (; beg != end; beg = next(beg)) {
		sum += (*beg) * (*beg);
	}
	return sqrt(sum);
}


template <class T>
T StdDeviation(const vector<T>& data) {
	T sum = 0;
	for (const auto el : data) {
		sum += el * el;
	}
	return sqrt(sum);
}

// погрешности суммы (разности)
//вариант 1 - через итераторы на stl контейнер
//принимаем  абс. Погрешности

//c style
double SumDeviation(const double* beg, size_t size) {
	double sum = 0;
	for (size_t i = 0; i < size; ++i) {
		sum += abs(beg[i]);
	}
	return sum;
}

// погрешности суммы (разности)
//через итераторы на stl контейнер
//принимаем  абс. Погрешности

template <class T, class ForwardIt>
T SumDeviation(ForwardIt beg, ForwardIt end) {
	T sum = 0;
	for (; beg != end; beg = next(beg)) {
		sum += abs(*beg);
	}
	return sum;
}


template <class T>
T SumDeviation(const vector<T>& data) {
	T sum = 0;
	for (const auto el : data)
		sum += abs(el);
	return sum;
}
//��� ������� ���������� ����������� ����������

//случай
//для каждого слагаемого абс. погрешность одинаковая
template <class T>
T SumDeviation(T deviation, size_t count) {
	return deviation * count;
}


//������������� ����������� �����������/��������

//��� ������� ���������� ����������� ������
// ������� ������ - ������ ������������� ������������ ��� ������� ���������
//c style
double MultDeviation(const double* beg, size_t size) {
	double sum = 0;
	for (size_t i = 0; i < size; ++i) {
		sum += beg[i];
	}
	return sum;
}

//c++ style
template <class T, class ForwardIt>
T MultDeviation(ForwardIt beg, ForwardIt end) {
	T sum = 0;
	for (; beg != end; beg = next(beg)) {
		sum += *beg;
	}
	return sum;
}

//relative
//относительная
//даны два контейнера (первый со значениями 
//множителей, второй – с их абс. Погрешностями)
//возвращает относительную погрешность

template <class T>
T MultDeviationRel(const vector<T>& values, const vector<T>& devs) {
	if (values.size() != devs.size())
		return T{ 0 };
	T relDevSum = 0;
	for (size_t i = 0; i < values.size(); ++i) {
		relDevSum += devs[i] / abs(values[i]);
	}
	return relDevSum;
}

//абсолютная
//относительная
//даны два контейнера (первый со значениями 
//множителей, второй – с их абс. Погрешностями)
template <class T>
T MultDeviationAbs(const vector<T>& values, const vector<T>& devs) {
	if (values.size() != devs.size())
		return T{ 0 };
	T mul{ 1 };
	T relDevSum = MultDeviationRel(values, devs);
	for (size_t i = 0; i < values.size(); ++i) {
		mul *= values[i];
	}
	return mul * relDevSum;
}
//��� ������� ��������� ����������� ����������
//относительная
template <class T>
T MultDeviationRel(T value, T absDeviation, size_t count) {
	return count * absDeviation / abs(value);
}
//абсолютная
template <class T>
T MultDeviationAbs(T value, T absDeviation, size_t count) {
	return count * absDeviation / abs(value) * pow(value, count);
}

//c++ style

//emplate <class T>
// MultDeviationRel(T rel_deviation, size_t count) {
//	return rel_deviation * count;
//
//
//emplate <class T>
// MultDeviationAbs(T abs_deviation, T real_val, size_t count) {
//	return abs_deviation / abs(real_val) * count * abs(real_val);
//


int main() {
	

	//Опыт – измерение длины столешницы линейкой.
	//Линейка 20см, погрешность линейки 1мм, 
	//погрешность совмещения начала линейки с точкой конца 
	//предыдущего измерения 2мм.
	//Т. о. абс погрешность 1-го измерения = 1мм, остальных  1 + 2 = 3мм
	//Длина стола = 1210мм, 6 измерений

		
	double L1 = 1210.0;
	vector<double> deviations1 = { 1.0, SumDeviation<double>(3.0, 5) };
	// равен {1, 3, 3, 3, 3, 3}
	//т.е. не все погрешности равны
	double AbsDevSum1 = SumDeviation(deviations1);
	cout << "Experiment 1 deviations: " << AbsDevSum1 << "mm; ("
		<< L1 << "+-" << AbsDevSum1 << ")mm" << endl;


	//���� 2 - ������� 10��, ����������� ������� 0.5��, ����������� ���������� 
	//������ ������� � ������ ����� ����������� ��������� 2��

	//��� ����������� 1-�� ��������� == 0.5��, ��������� == 0.5 + 2 = 2.5��
	//L2 = 1215��, 12 ���������
	double L2 = 1215.0;

	vector<double> sum_dev_2 = { 0.5, SumDeviation<double>(2.5, 11) }; // Equal to {0.5, 2.5 x 11}
	double SumDev2 = SumDeviation<double>(begin(sum_dev_2), end(sum_dev_2));
	cout << "Experiment 2 deviations: " << SumDev2 << "mm; " 
		<< L2 << "+-" << SumDev2 << "mm" << endl; //28��


	//��������� ����� 1212�� (�������� �������)
	//L1 = 1210�16mm, L2 = 1215�28mm
	//����� - �������� ��������� ������������� ������������� ����������

	//������������� - ����� ������� �����
	vector<double> ExpLengths = { L1, L2 };
	double AvgLen = Average<double>(ExpLengths.begin(), ExpLengths.end());
	vector<double> ExpDevs = { AbsDevSum1, SumDev2 };
	double AvgDev = Average<double>(ExpDevs.begin(), ExpDevs.end());
	cout << "Average Value: " << AvgLen << "+-"  << AvgDev << "mm" << endl; 
	cout << endl;
	/////////////////////////////////////////////////////////////////////////////
	// ���� � �������������� ������������� �������� � ������������
	// �������� �����������, ������ ����� ������� (������� ��������)
	//����� �������� �������� (�������) 325�190�116��
	double V = 325 * 190 * 116;

	//����� �������� �������� 10��
	// a = 326mm, b = 190mm, c = 115mm
	double a = 326;
	double b = 190;
	double c = 115;
	double ExpV = a * b * c; //экспериментально полученный объем

	// ����������� ��� ������ ��������� 1��
	// ��� ����������� = 1 + 2 = 3�� (������ ��� � �����)
	
	//погрешность измерения длины (a)
	//2 измерения линейкой 
	//(погрешность линейки + погрешность совмещения конца 
	//предыдущего измерения)
	vector<double> boxDev_a = { 1, 3 }; 
	
	//абсолютные погрешности
	double AbsDev1 = SumDeviation<double>(boxDev_a); //погрешность суммы а
	double AbsDev2 = 1.0; // погрешность b
	double AbsDev3 = 1.0; // погрешность c

	vector<double> ExpVals = { a , b ,c }; //измеренные значения
	vector<double> AbsDeviations 
		= { AbsDev1 , AbsDev2 ,AbsDev3 }; //полученные погрешности
										  //по каждому измерению	

	// погрешность произведения
	double AbsDevV = MultDeviationAbs<double>(ExpVals, AbsDeviations);

	cout << "MultDev Experiment" << endl;
	cout << "Real Value: " << V / 1'000'000'000 << "m^3" << endl;
	cout << "Experimential Value: (" << ExpV / 1'000'000'000 << "+-" 
		<< AbsDevV / 1'000'000'000 << ")m^3"<< endl;

	//����������� �����������
	cout << "Growing Deviation: " << endl;
	cout << "Real Value * 10000: " 
		<< V * 10'000 / 1'000'000'000 << "m^3" << endl;
	cout << "Experimental: Value * 10000: ("
		<< ExpV * 10'000 / 1'000'000'000 
		<< "+-" << SumDeviation(AbsDevV, 10000) / 1'000'000'000 
		<<")m^3" << endl;
}