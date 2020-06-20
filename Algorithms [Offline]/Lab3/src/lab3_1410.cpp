#pragma comment(linker,"/STACK:32000000")
#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

namespace timus_1410 {


    void solve() {

        bool alpha{ false };
        bool time_has_come{ false };
        size_t word_len{ 0 };
        size_t word_cnt{ 0 };
        size_t accum_word_len[3] = { 0 };

        char c = getchar();
        while (!isalpha(c) && c != EOF) c = getchar();
        for (;;) {
            
            if (!isalpha(c) && alpha) {
                alpha = false;
                accum_word_len[word_cnt % 3] = word_len + std::max(accum_word_len[word_cnt % 3], accum_word_len[(word_cnt + 1) % 3]);
                word_len = 0;
                ++word_cnt;
                while (!isalpha(c) && c != EOF) c = getchar();
            }
            else if (isalpha(c)) {
                while (isalpha(c)) { ++word_len, c = getchar(); }
                alpha = true;
            }

            if (time_has_come) break;
            if (c == EOF) time_has_come = true;
        }
        cout << std::max(accum_word_len[0], std::max(accum_word_len[1], accum_word_len[2]));
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    timus_1410::solve();
    //cout << boolalpha << (bool)isalpha('$');
}


