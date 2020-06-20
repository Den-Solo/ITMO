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

using namespace std;

namespace timus_1036 {

    int nDigits, sum;
    vector<vector<int>> options_cnt; //[0..sum][0..nDigit * 2]
    vector<int> last_digit;          //[0..sum]


    void calc_options() {

        options_cnt.resize(sum + 1, vector<int>(nDigits * 2 + 1));
        last_digit.resize(sum + 1, 1);

        for (auto i = 0; i <= sum && i < 10; ++i)
            options_cnt[i][1] = 1;

        //long arithmetics
        vector<vector<int>> opt_prev;
        vector<int> ld_prev;
        for (size_t dig = 2; dig < nDigits + 1; ++dig) {
            opt_prev = options_cnt;
            ld_prev = last_digit;
            for (auto s = 1; s < sum + 1; ++s) {
                for (auto s_prev = 0; s_prev < s; ++s_prev) {
                    if (s - s_prev < 10) {
                        auto lim = (last_digit[s] > ld_prev[s_prev]
                            ? last_digit[s]
                            : ld_prev[s_prev]) + 1; //must get to the last meaningful digit
                        for (auto dig_2 = 1; dig_2 < lim; ++dig_2) {                                        // aka long arithmetics //big_intergers
                            options_cnt[s][dig_2] += opt_prev[s_prev][dig_2];
                            options_cnt[s][dig_2 + 1] += options_cnt[s][dig_2] / 10;                        //next digit has exceeded value
                            options_cnt[s][dig_2] %= 10;                                                    //cur degit has mod 10
                        }
                        while (options_cnt[s][last_digit[s] + 1]) ++last_digit[s];
                    }
                }
            }
        }
    }

    vector<int> double_options() {  //take into account the other part of ticket number // each option multiplied by cnt of all options and summed
        vector<int> res = options_cnt[sum];

        for (auto i = last_digit[sum]; i >= 1; --i) {
            for (auto j = last_digit[sum]; j > 1; --j)
                res[i + j - 1] += res[i] * options_cnt[sum][j];
            res[i] *= options_cnt[sum][1];
        }
        return res;
    }

    inline void prettify_res(vector<int>& res) {//make all numbers = [0..9] for output as chars
        size_t accum_sum = 0;
        for (auto j = 1; j < 2 * last_digit[sum] + 1; ++j) {
            accum_sum += res[j];
            res[j] = accum_sum % 10;
            accum_sum /= 10;
        }
    }

    void print_res() {


        vector<int> res = double_options();

        prettify_res(res);

        string res_str;
        res_str.reserve(100);

        for (auto i = 2 * last_digit[sum] + (res[2 * last_digit[sum]] ? 0 : -1); i > 0; --i)
            res_str.push_back(res[i] + '0');
        cout << res_str;

    }


    void solve() {
        cin >> nDigits >> sum;

        if (sum & 1 || nDigits * 9 * 2 < sum || sum / 2 / nDigits >= 10) {
            cout << "0";
            return;
        }
        if (!sum) {
            cout << "1";
            return;
        }
        sum /= 2;

        calc_options();
        print_res();
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("input.txt", "r", stdin);
    //freopen("output.txt", "card_weights", stdout);

    timus_1036::solve();
}

