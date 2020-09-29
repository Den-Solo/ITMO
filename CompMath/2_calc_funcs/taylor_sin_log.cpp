#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

struct SeriesResult {
    double answer;      //ответ
    double inaccuracy;  //погрешность
    double cmpDefault;  //отличие от стандартной ф-и
};

const double PI = 3.14159265;
SeriesResult SinSeries(double x, size_t n){
    const double PI_2 = 2 * PI;
    if (abs(x) > PI_2) {    //приведение х в (-2*pi,2*pi)
        int k = x / PI_2;   //x = x' + 2*pi*k
        x -= (k - 1) * PI_2;
    }

    SeriesResult sr = {x, 0, 0};
    size_t i = 2;
    double a = -1 * pow(x,3) / 6;
    //второй элемент ряда Тейлора

    while (i < n + 1){
        sr.answer += a;
        ++i;
        a *= -1.0 * x * x /
            static_cast<double>((2 * i - 1) * (2 * i - 2));
    }
    sr.inaccuracy = abs(a);
    sr.cmpDefault = std::sin(x) - sr.answer;

    return sr;
}


SeriesResult LogESeries(double x, size_t n){
    if (x <= 0)
        throw runtime_error("LogESeries: x <= 0");

    auto tmp = x;
    x = (x - 1) / (x + 1);
    SeriesResult sr = {x, 0, 0};

    double a = pow(x, 3) / 3;
    size_t i = 2;
    while (i < n + 1){
        ++i;
        sr.answer += a;
        a *= x * x * (2 * (i - 1) - 1) / (2 * i - 1);
    }
    sr.answer *= 2;
    sr.inaccuracy = abs(2 * a);
    sr.cmpDefault = std::log(tmp) - sr.answer;
    return sr;
}


int main(){
   /* {
        cout << "Calc sin(x)\nInput x:\n";
        double x;
        size_t n;
        cin >> x;
        cout << "Input number of series members:\n";
        cin >> n;
        cout << endl;
        auto resSin = SinSeries(x, n);
        cout << "sin(x) = " << resSin.answer
            << " +- " << resSin.inaccuracy
            << ";\ndifference with std::sin(x) = "
            << resSin.cmpDefault; 
    }*/

     {       
        cout << "Calc log(x)\nInput x:\n";
        double x;
        size_t n;
        cin >> x;
        cout << "Input number of series members:\n";
        cin >> n;
        cout << endl;
        auto res = LogESeries(x, n);
        cout << "Log(x) = " << res.answer
            << " +- " << res.inaccuracy
            << ";\ndifference with std::Log(x) = "
            << res.cmpDefault; 
    }

    {//sin(x)
        vector<vector<double>> y(5), R(5), err(5);
        SeriesResult res;
        int k = 0;
        int max_memb = 15;
        vector<double> xvals 
            = {-34.5, -2.7687, 0.00154, 1.467, 40.75};
        for (double i : xvals){
            for (auto j = 1; j <= max_memb; ++j){
                res = SinSeries(i, j);
                y[k].push_back(res.answer);
                R[k].push_back(res.inaccuracy);
                err[k].push_back(res.cmpDefault);
            }
            ++k;
        }
        vector<vector<vector<double>>> v 
            = {move(R), move(y), move(err)};
        int c = 0;
        for (auto j : v){
            ofstream ofs("sin" + to_string(c++) + ".csv");
            ofs << "MemberCount;";
            for (auto i : xvals)
                ofs << i << ';';
            ofs << '\n';
            for (auto i = 0; i < max_memb; ++i){
                ofs << i + 1 << ';';
                for (auto k = 0; k < xvals.size(); ++k){
                    ofs << j[k][i] << ';';
                }
                ofs << '\n';
            }
        } 
    }

    {//log(x)
        vector<vector<double>> y(5), R(5), err(5);
        SeriesResult res;
        int k = 0;
        int max_memb = 40;
        vector<double> xvals 
            = {0.000001, 0.35486, 0.8434, 1.467, 40.75};
        for (double i : xvals){
            for (auto j = 1; j <= max_memb; ++j){
                res = SinSeries(i, j);
                y[k].push_back(res.answer);
                R[k].push_back(res.inaccuracy);
                err[k].push_back(res.cmpDefault);
            }
            ++k;
        }
        vector<vector<vector<double>>> v 
            = {move(R), move(y), move(err)};
        int c = 0;
        for (auto j : v){
            ofstream ofs("log" + to_string(c++) + ".csv");
            ofs << "MemberCount;";
            for (auto i : xvals)
                ofs << i << ';';
            ofs << '\n';
            for (auto i = 0; i < max_memb; ++i){
                ofs << i + 1 << ';';
                for (auto k = 0; k < xvals.size(); ++k){
                    ofs << j[k][i] << ';';
                }
                ofs << '\n';
            }
        } 
    }
}