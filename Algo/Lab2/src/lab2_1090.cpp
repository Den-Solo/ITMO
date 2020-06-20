#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

template <class T>
class FenwickTree {

private:
    vector<T> data_;
    size_t size_;
public:
    FenwickTree(size_t size) : size_(size) {
        data_.assign(size_, 0);
    }
    void assign(size_t size, T val) {
        size_ = size;
        data_.assign(size_, val);
    }
    inline static size_t _F(size_t idx) {
        return idx & (idx + 1);
    }
    inline static size_t _K(size_t idx) {
        return idx | (idx + 1);
    }

    void add(size_t x, T val) {
        for (auto i = x; i < size_; i = _K(i)) {
            data_[i] += val;
        }
    }
    T prefix_sum(size_t x) {
        T res = 0;
        for (int i = x; i >= 0; i = _F(i) - 1) {
            res += data_[i];
        }
        return res;
    }
    T get_sum(size_t x0, size_t x) {
        if (x <= x0 - 1) {
            return 0;
        }
        return prefix_sum(x) - prefix_sum(x0 - 1);
    }
};

int main() {
    int N, K;
    scanf("%d%d", &N, &K);

    int max_jumps_row = -1;
    int row_idx = 1;

    FenwickTree<unsigned> tree(N + 1);

    for (int i = 1; i <= K; ++i) {
        int cur_row_jumps = 0;
        tree.assign(N + 1, 0);

        for (int j = 0; j < N; ++j) {
            int height;
            scanf("%d", &height);
            cur_row_jumps += tree.get_sum(height + 1, N);
            tree.add(height, 1);
        }

        if (cur_row_jumps > max_jumps_row) {
            max_jumps_row = cur_row_jumps;
            row_idx = i;
        }
    }
    printf("%d\n", row_idx);
}