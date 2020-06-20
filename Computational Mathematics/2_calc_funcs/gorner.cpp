#include <iostream>
#include <vector>
#include <cmath>
#include <optional>

using namespace std;

struct GornerResult {
    vector<double> ratio;//коэффициенты многочлена-частного
    double excess;       //остаток
};

GornerResult GornerScheme(const vector<double>& coefs, double eps){
    GornerResult res;
    res.ratio.emplace_back(coefs.front());

    for (size_t i = 1; i < coefs.size() - 1; ++i)
        res.ratio.emplace_back(coefs[i] + res.ratio.back() * eps);
    
    res.excess = coefs.back() + res.ratio.back() * eps;
    return res;
}

bool GornerCheck(
    const GornerResult& res, 
    const vector<double>& coefs, const double e
    ){
    if (res.ratio.front() != coefs.front())
        return false;
    for (size_t i = 0; i < res.ratio.size() - 1; ++i){
        if (coefs[i + 1] != res.ratio[i] * (-e) + res.ratio[i + 1])
            return false;
    }
    return coefs.back() == res.ratio.back() * (-e) + res.excess; 
}

int main(){
    //Gorner
    vector<double> taskG = {5,5,1,0,-12}; //5x^4 + 5x^3 + x^2 -11
    double eG = 1; // (x - 1)
    auto resG = GornerScheme(taskG, eG);
    bool ok = GornerCheck(resG, taskG, eG);

    cout << "Is correct: " << boolalpha << ok << endl;
    cout << "Coefs in gorner: ";
    for (size_t i = 0; i < resG.ratio.size(); ++i){
        if (i != 0)
            cout << " + ";
        cout << resG.ratio[i] << "x^" << resG.ratio.size() - 1 - i;
    }
    cout << "\nexcess: " << resG.excess << '\n';
}