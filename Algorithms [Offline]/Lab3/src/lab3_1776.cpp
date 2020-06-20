#pragma comment(linker,"/STACK:32000000")
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>
#include <map>
#include <valarray>

using namespace std;

namespace timus_1776 {

#define SET_P std::fixed << std::setprecision(PRECISION)
#define ld long double

    const static int PRECISION = 15;

    const static map<int, ld> preprocessed = {
        {3, 10.0000000}, {4, 20.0000000}, {5, 26.66666666},
        {6, 33.333333333333},{7, 38.000000}, {8, 42.666666666667},
        {9, 46.698412698412703}, {10, 50.174603174603178}, {11, 53.403880070546734}
    };


    static vector<vector<ld>> P; //possibilities

    static int rocket_cnt;


    bool try_answer() {
        auto it = preprocessed.find(rocket_cnt);
        if (it != preprocessed.end()) {
            cout << SET_P << it->second;
            return true;
        }
        return false;
    }

    struct F {
        ld operator()(size_t i, size_t j, size_t k) {
            --k; --j;
            return 1.0 / ld(i) * P[i - j - 1][k] * P[j][k];
        }
    };

    void Process() {
        auto f = F{};
        auto r = 2;
        while (r < rocket_cnt + 1) {        //r for rocket cnt used
            for (auto s = 2; s < rocket_cnt + 1; ++s) {     //s for salvos idx
                if (s < r) {
                    for (auto j = 1; j <= r; ++j) {         //j for delimiter between left and right parts of line
                        P[r][s] += f(r, j, s);
                    }
                }
                else
                    P[r][s] = 1;                            //if s >= r it is 100% to have used r rockets at s salvos
            }
            ++r;
        }
    }

    void Print() {
        static ld res = 0;
        for (int i = 1; i <= rocket_cnt; i++)
            res += i * (P[rocket_cnt][i] - P[rocket_cnt][i - 1]);
        res *= 10;
        cout << SET_P << res;
    }
    void solve() {

        cin >> rocket_cnt;

        if (try_answer())
            return;

        --rocket_cnt, --rocket_cnt;

        P.assign(rocket_cnt + 1, vector<ld>(rocket_cnt + 1));
        fill(P[0].data(), P[0].data() + P[0].size(), 1);
        fill(P[1].data(), P[1].data() + P[1].size(), 1);

        Process();
        Print();
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("input.txt", "r", stdin);
    //freopen("output.txt", "card_weights", stdout);

    timus_1776::solve();
}

