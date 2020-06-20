#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <cstdio>
#include <cstddef>

using namespace std;

const size_t MOD = 1'000'000'000;

template <class T>
class FenwickTree {
private:
    vector<T> data;
    size_t size_;
public:
    FenwickTree(size_t size) : size_(size) {
        data.assign(size_, 0);
    }
    inline static size_t _F(size_t idx) {
        return idx & (idx + 1);
    }
    inline static size_t _K(size_t idx) {
        return idx | (idx + 1);
    }
   
    void add(size_t x, T val) {
        for (auto i = x; i < size_; i = _K(i)) {
            data[i] += val;
            data[i] %= MOD;
        }
    }
    T prefix_sum(size_t x) {
        T res = 0;
        for (int i = x; i >= 0; i = _F(i) - 1) {
            res += data[i];
            res %= MOD;
        }
        return res;
    }
    T get_sum(size_t x0, size_t x) {
        if (x <= x0 - 1) {
            return 0;
        }
        return (prefix_sum(x) - prefix_sum(x0 - 1) + MOD) % MOD;
    }
};

const int MAX = 20001;
size_t cnt_of_invers[MAX][20];

int main() {
    int num, k, val;
    size_t res = 0;
    scanf("%d%d", &num, &k);

    vector<FenwickTree<size_t>> trees(k - 1,num);
    
    for (auto i = 0; i != num; ++i) {
        scanf("%d", &val);
        --val;
        cnt_of_invers[val][0] = 1;
        for (auto j = 1; j < k; ++j) {
            cnt_of_invers[val][j] = trees[j - 1].get_sum(val + 1, num - 1);
            trees[j - 1].add(val, cnt_of_invers[val][j - 1]);
        }
    }
    for (auto i = 0; i < num; ++i) {
        res += cnt_of_invers[i][k - 1];
        res %= MOD;
    }
    printf("%u", res);
}