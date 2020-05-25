#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <queue>
#include <iostream>
#include <cmath>
#include <string_view>
#include <cstdio>

using namespace std;

vector<int64_t> powers;
const int64_t x_hash = 67;
const int64_t base = int64_t(1e7 + 123);

void GenPowers(size_t len) {
    ++len;
    powers.resize(len);
    powers[0] = 1;
    for (size_t i = 1; i < len; ++i) {
        powers[i] = (powers[i - 1] * x_hash) % base;
    }
}

int64_t hash_str(const string& s, size_t len) {
    size_t res = 0;
    for (size_t i = 0; i < len; ++i) {
        res = (res + (s[i] - 'A') * powers[len - 1 - i]) % base;
    }
    return res;
}

int64_t rehash(int64_t old_hash, const string& s, size_t len, size_t pos) {
    if (!pos) return old_hash;
    int64_t res = ((old_hash * x_hash) - ((s[pos - 1] - 'A') * powers.back()) + (s[pos + len - 1] - 'A')) % base;
    while (res < 0) res += base;
    return res;
}

void solve() {
    string p,   //substring 
        t;      //str

    cin >> p >> t;

    GenPowers(p.size());
    const auto p_hash = hash_str(p, p.size());
    auto t_hash = hash_str(t, p.size());

    vector<size_t> res;
    for (size_t i = 0; i < t.size() - p.size() + 1; ++i) {
        if (p_hash != (t_hash = rehash(t_hash, t, p.size(), i)))
            continue;
        bool ok = true;

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
    freopen("output.txt", "w", stdout);

    solve();

}