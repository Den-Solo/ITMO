#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

string del_spaces(const string& s) {
    string res;
    res.reserve(s.size());
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] != ' ')
            res.push_back(s[i]);
    }
    return res;
}


void solve() {

    string s;
    getline(cin, s);
    s = del_spaces(s);

    int cntLetters[26] = { 0 };
    int64_t diff[26] = { 0 };
    int lastIdxs[26] = { 0 };

    size_t cnt{ 0 };
    for (size_t i = 0; i < s.size(); ++i) {
        int idx = s[i] - 'a';
        int len = i - lastIdxs[idx] - 1;
        if (cntLetters[idx] > 1)
            diff[idx] += cntLetters[idx] - 1;
        diff[idx] += len * cntLetters[idx];
        cntLetters[idx]++;

        cnt += diff[idx];

        lastIdxs[idx] = i;
    }

    cout << cnt;
}
int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    solve();
    
}