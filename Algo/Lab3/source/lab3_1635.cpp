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

namespace timus_1635 {

    const int MAX = 4001;
    bool is_pal[MAX][MAX];
    string s;

    void preproc() {
        memset(is_pal, 0, sizeof(is_pal));
        for (int i = 0; i < s.size(); ++i) {
            is_pal[i][i] = true;
            int l = i - 1;
            int r = i + 1;
            while (l > -1 && r < s.size() && is_pal[l + 1][r - 1] && s[l] == s[r]) //odd num of chars
                is_pal[l][r] = true, --l, ++r;

            l = i - 1;
            r = i;
            if (l > -1 && s[l] == s[r]) {       //even num of chars
                is_pal[l][r] = true;
                --l, ++r;
                while (l > -1 && r < s.size() && is_pal[l + 1][r - 1] && s[l] == s[r])
                    is_pal[l][r] = true, --l, ++r;
            }
        }
    }

    void find_borders(vector<int>& slices, vector<int>& borders) {
        slices.resize(s.size()); //number of pals at [i..n]
        borders.reserve(s.size() + 2);
        borders.resize(s.size() + 1, -1);
        
        borders.emplace_back(s.size());

        {
            for (int i = s.size() - 1; i > -1; --i) {
                if (is_pal[i][s.size() - 1]) {
                    slices[i] = 0;
                }
                else {
                    slices[i] = numeric_limits<int>::max() - 10;
                    int border{ -2 };
                    for (int j = s.size() - 1; j > i; --j) {
                        if (is_pal[i][j - 1] && slices[j] + 1 < slices[i]) {
                            slices[i] = 1 + slices[j];
                            border = j;
                        }
                    }
                    borders[i] = border;
                }
            }
        }
    }

    void print_res(vector<int>& slices, vector<int>& borders) {

        cout << slices.front() + 1 << '\n'; // number of splits

        int i = 0;
        for (; borders[i] != -1; i = borders[i]) {
            cout << s.substr(i, borders[i] - i) << ' ';
        }
        cout << s.substr(i, s.size() - i) << '\n';

    }
    void solve() {
        
        cin >> s;

        preproc();

        vector<int> slices; //number of pals at [i..n]
        vector<int> borders;
        
        find_borders(slices, borders);

        print_res(slices, borders);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    timus_1635::solve();
}


