#define _CRT_SECURE_NO_WARNINGS
//#pragma comment(linker,"/STACK:32000000")

#include <cstdio>
#include <iostream>
#include <fstream>
#include <utility>
#include <cstring>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <queue>
#include <stack>
#include <cassert>
#include <forward_list>

using namespace std;

class HashTable {

private:

    vector<int64_t> data_;
    static const int64_t hash_vals[];

private:


    size_t hasher1(int64_t key) {
        return std::abs((key * hash_vals[0]) ^ (key * hash_vals[1]) >> 32) % data_.size();
    }
    size_t hasher2(int64_t key) {
        return std::abs((key * hash_vals[2]) ^ (key * hash_vals[3]) >> 32) % (data_.size() - 1) + 1;
    }

public:
    HashTable(size_t size = (1 << 24)) {
        data_.resize(size);
        memset(data_.data(), -1, sizeof(int64_t) * data_.size());
    }

    int64_t Find(int64_t key) {
        auto h1 = hasher1(key);
        auto h2 = hasher2(key);

        while (data_[h1] != -1) {
            if (data_[h1] == key) {
                return h1;
            }
            h1 += h2;
            ++h2;
            if (h1 >= data_.size()) h1 %= data_.size();
        }
        return h1;
    }


    void insert(int64_t key) {
        auto idx = Find(key);

        if (data_[idx] != -1)
            return;
        data_[idx] = key;
    }
    bool contains(int64_t key) {
        auto idx = Find(key);
        if (data_[idx] == -1)
            return false;
        return true;
    }
};


const int64_t HashTable::hash_vals[] = { 47, 31, 113, 97 };

void solve() {
    int64_t N, X, A, B,
            AC, BC, AD, BD;

    cin >> N >> X >> A >> B
        >> AC >> BC >> AD >> BD;

    HashTable t(2 * N);
    const int64_t M3 = int64_t(1e3);
    const int64_t M15 = int64_t(1e15);

    for (int i = 0; i < N; ++i) {
        if (t.contains(X)) {
            A = (A + AC) % M3;
            B = (B + BC) % M15;
        }
        else {
            t.insert(X);
            A = (A + AD) % M3;
            B = (B + BD) % M15;
        }
        X = (X * A + B) % M15;
    }

    cout << X << ' ' << A << ' ' << B;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    solve();

}