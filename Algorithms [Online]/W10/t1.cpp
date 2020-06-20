#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>

using namespace std;

vector<int> pref;

void buildPref(const string& s) {
    pref.resize(s.size() + 1);

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
}

void solve() {
    string s;
    cin >> s;

    buildPref(s);

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