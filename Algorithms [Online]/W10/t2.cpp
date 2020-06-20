#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>

using namespace std;



vector<int> buildPref(const string& s) {//knutt - morrise - pratt
    vector<int> pref(s.size() + 1);

    int i = 1, j = 0;
    while (i < s.size()) {
        if (s[i] == s[j]) {
            pref[i + 1] = j + 1;
            ++i, ++j;
        }
        else {
            if (j > 0)
                j = pref[j];
            else {
                pref[i + 1] = 0;
                ++i;
            }
        }
    }
    return pref;
}

vector<int> build_Z_func(const string& s) {
    int n = s.size();
    vector<int> Z(n);
    int L = 0, R = 0;
    for (int i = 1; i < n; ++i) {
        if (i >= R) {
            int j = 0;
            while (i + j < n && s[i + j] == s[j])
                ++j;
            L = i, R = i + j;
            Z[i] = j;
        }
        else {
            if (Z[i - L] < R - i)
                Z[i] = Z[i - L];
            else {
                int j = R - i;
                while (i + j < n && s[i + j] == s[j])
                    ++j;
                L = i, R = i + j;
                Z[i] = j;
            }
        }
    }
    return Z;
}
void solve() {
    string s;
    cin >> s;

    auto pref = build_Z_func(s);

    for (auto i = 1; i < pref.size(); ++i)
        cout << pref[i] << ' ';
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    solve();
    
}