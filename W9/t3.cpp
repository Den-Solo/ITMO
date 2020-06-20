#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <cassert>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <iostream>


/*struct PolyHash {
    // -------- Статические переменные класса --------
    static const int mod = (int)1e9 + 123; // простой модуль полиномиального хэширования
    static std::vector<int> pow1;        // степени основания base по модулю mod
    static std::vector<uint64_t> pow2;        // степени основания base по модулю 2^64
    static int base;                     // основание base

    // --------- Статические функции класса ---------
    static inline int diff(int a, int b) { // разность a и b по модуль mod (Предполагается: 0 <= a < mod, 0 <= b < mod)
        return (a -= b) < 0 ? a + mod : a;
    }

    // -------------- Переменные класса -------------
    std::vector<int> pref1; // Полиномиальный хэш на префиксе по модулю mod
    std::vector<uint64_t> pref2; // Полиномиальный хэш на префиксе по модулю 2^64

    // Конструктор от строки:
    PolyHash(const std::string& s)
        : pref1(s.size() + 1u, 0)
        , pref2(s.size() + 1u, 0)
    {
        assert(base < mod);
        const int n = s.size(); // Досчитываем необходимые степени основания по модулям хэширования
        while ((int)pow1.size() <= n) {
            pow1.push_back(1LL * pow1.back() * base % mod);
            pow2.push_back(pow2.back() * base);
        }
        for (int i = 0; i < n; ++i) { // Заполняем массив полиномиальных хэшей на префиксе
            assert(base > s[i]);
            pref1[i + 1] = (pref1[i] + 1LL * s[i] * pow1[i]) % mod;
            pref2[i + 1] = pref2[i] + s[i] * pow2[i];
        }
    }

    // Полиномиальный хэш подпоследовательности [pos, pos+len)
    // Если mxPow != 0, то происходит домножение значения до старшей степени base ^ mxPow
    inline std::pair<int, uint64_t> operator()(const int pos, const int len, const int mxPow = 0) const {
        int hash1 = pref1[pos + len] - pref1[pos];
        uint64_t hash2 = pref2[pos + len] - pref2[pos];
        if (hash1 < 0) hash1 += mod;
        if (mxPow != 0) {
            hash1 = 1LL * hash1 * pow1[mxPow - (pos + len - 1)] % mod;
            hash2 *= pow2[mxPow - (pos + len - 1)];
        }
        return std::make_pair(hash1, hash2);
    }
};

// Инициализация статических объектов класса PolyHash:
int PolyHash::base((int)1e9 + 7);
std::vector<int> PolyHash::pow1{ 1 };
std::vector<uint64_t> PolyHash::pow2{ 1 };

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Чтение данных:
    std::string a;
    std::string b;
    std::cin >> b >> a;


    // Вычисление максимальной степени:
    const int mxPow = std::max((int)a.size(), (int)b.size());

    // Генерация случайного основания хэширования:
    PolyHash::base = 606669519;

    // Создание объектов хэширования:
    PolyHash hash_a(a), hash_b(b);

    // Копируем нужный нам полиномиальный хэш всей строки b:
    const auto need = hash_b(0, (int)b.size(), mxPow);

    // Проходим по хэшам строки a и ищем совпадение с хэшем всей строки b:
    std::vector<int> res;
    res.reserve(500);
    for (int i = 0; i + (int)b.size() <= (int)a.size(); ++i) {
        if (hash_a(i, b.size(), mxPow) == need) {
            res.push_back(i + 1);
        }
    }
    printf("%d\n", res.size());
    for (auto i : res)
        printf("%d ", i);

    return 0;
}*/

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
       /* for (size_t j = 0; j < p.size(); ++j) {
            if (t[i + j] != p[j]) {
                ok = false;
                break;
            }
        }*/
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