#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>

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

vector<int> BadSymb(const string& t) {
    int m = t.size();
    vector<int> pos(m);
    pos[0] = -1;
    for (int i = 0; i < m; ++i)
        pos[t[i] - 'a'] = i;
    return pos;
}
vector<int> GoodSuffix(const string& t) {
    int m = t.size();
    vector<int> suf(m);
    suf[0] = -1;
    for (int x = 0; x < m - 2; ++x) {
        int i = x;
        int j = m - 1;
        while (i > 0 && t[i] == t[j]) {
            suf[j] = i;
            --i, --j;
        }
    }
    return suf;
}
vector<int> Boyer_Moor(const string& s, const string& t /*template*/) {
    vector<int> res;
    auto suf = GoodSuffix(t);
    auto pos = BadSymb(t);
    res.reserve(s.size() / t.size());
    int n = s.size();
    int m = t.size();
    int i = m - 1;
    while (i < n) {
        int j = m - 1;
        while (s[i] == t[j]) {
            --i, --j;
            if (j == 0)
                res.emplace_back(i);
            i += std::max(j + 1 - suf[j + 1], j - pos[s[i + j]]);
        }
    }
    return res;
}

int cnt_digits(int val) {
    if (val < 10) return 1;
    else if (val < 100) return 2;
    else if (val < 1000) return 3;
    else if (val < 10000) return 4;
    else if (val < 100000) return 5;
    else if (val < 1000000) return 6;
}
void printRes(const vector<string>& parts, const vector<int>& exps, int al) {
    bool plus = false;
    if (parts[0].size() * exps[0] < parts[0].size() + cnt_digits(exps[0]) + 1) {
        for (int i = 0; i < exps[0]; ++i)
            cout << parts[0];
    }
    else {
        cout << parts[0];
        if (exps[0] != 1)
            cout << '*' << exps[0];
        plus = true;
    }

    for (int i = 1; i < al; ++i) {
        if (parts[i].size() * exps[i] <= parts[i].size() + cnt_digits(exps[i]) + 1) {
            if (plus) cout << '+';
            for (int j = 0; j < exps[i]; ++j)
                cout << parts[i];
            plus = false;
        }
        else {
            if (exps[i] != 1) {
                cout << '+' << parts[i] << '*' << exps[i];
                plus = true;
            }
            else {
                if (plus) cout << '+';
                cout << parts[i];
                plus = false;
            }
                
        }
    }
}

void printRes2(const vector<string>& parts, const vector<int>& exps, int al) {
    bool plus = false;
    --al;
    if (parts[al].size() * exps[al] < parts[al].size() + cnt_digits(exps[al]) + 1) {
        for (int i = 0; i < exps[al]; ++i)
            cout << parts[al];
    }
    else {
        cout << parts[al];
        if (exps[al] != 1)
            cout << '*' << exps[al];
        plus = true;
    }
    --al;
    for (int i = al; i >= 0; --i) {
        if (parts[i].size() * exps[i] <= parts[i].size() + cnt_digits(exps[i]) + 1) {
            if (plus) cout << '+';
            for (int j = 0; j < exps[i]; ++j)
                cout << parts[i];
            plus = false;
        }
        else {
            if (exps[i] != 1) {
                cout << '+' << parts[i] << '*' << exps[i];
                plus = true;
            }
            else {
                if (plus) cout << '+';
                cout << parts[i];
                plus = false;
            }

        }
    }
}


void solve2() {

    string s;
    cin >> s;
    int n = s.size();
    int i = 0;

    vector<string> parts(n);
    vector<int> exps(n);
    int al = 0;
    int ans = 0;

    vector<int> p(n + 1);

    while (i < n) {
        int ni = i + 1;
        parts[al].push_back(s[i]);
        exps[al] = 1;

        p[1] = 0;
        int k = 0;
        for (int j = 2; i + j - 1< n; ++j) {
            while (s[i + j - 1] != s[i + k] && k > 0) {
                k = p[k];
            }
            if (s[i + j - 1] == s[i + k]) {
                ++k;
            }
            p[j] = k;
            if (!(j % (j - p[j])) && (p[j] && j)) {
                ni = i + j;
                parts[al] = s.substr(i, (j - p[j]));
                exps[al] = j / (j - p[j]);
            }
        }

        ans += parts[al].size();
        ++al;
        i = ni;
    }
    
    printRes(parts, exps, al);
}

void solve3() {

    string s;
    cin >> s;
    int n = s.length();
    vector<int> d(n + 1);
    vector<int> from(n + 1);
    vector<int> len(n + 1);
    fill(d.data(), d.data() + d.size(), numeric_limits<int>::max());
    d[0] = 0;
    for (int i = 0; i < n; i++) {
        if (d[i + 1] > d[i] + 1) {
            d[i + 1] = d[i] + 1;
            from[i + 1] = i;
            len[i + 1] = 1;
        }

        int* p = new int[n + 1];
        p[1] = 0;
        int k = 0;
        for (int j = 2; i + j - 1 < n; j++) {
            while (s.at(i + j - 1) != s.at(i + k) && k > 0) {
                k = p[k];
            }
            if (s.at(i + j - 1) == s.at(i + k)) {
                k++;
            }
            p[j] = k;
            if (j % (j - p[j]) == 0) {
                if (d[i + j] > d[i] + (j - p[j])) {
                    d[i + j] = d[i] + (j - p[j]);
                    from[i + j] = i;
                    len[i + j] = (j - p[j]);
                }
            }
        }
    }

    //out.println(d[n]);
    vector<string> parts(n);
    vector<int> exps(n);
    int al = 0;
    int p = n;
    while (p > 0) {
        parts[al] = s.substr(from[p], len[p]);
        exps[al] = (p - from[p]) / len[p];
        al++;
        p = from[p];
    }

    printRes2(parts, exps, al);
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

    solve3();
    
}