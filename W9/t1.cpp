#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <set>
#include <string_view>

using namespace std;



void solve() {
    string p,   //substring 
        t;      //str
    cin >> p >> t;

    vector<size_t> res;
    for (size_t i = 0; i < t.size() - p.size() + 1; ++i) {
        bool ok = true;
        for (size_t j = 0; j < p.size(); ++j) {
            if (t[i + j] != p[j]) {
                ok = false;
                break;
            }
        }
        if (ok)
            res.emplace_back(i + 1);
    }
    cout << res.size() << '\n';
    for (auto i : res)
        cout << i << ' ';
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt","w", stdout);

    solve();
}