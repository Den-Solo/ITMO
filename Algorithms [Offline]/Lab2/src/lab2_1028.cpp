#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

class FenwickTree {
    
private:
    vector<int> data;
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
    void inc(int x) {

        for (int i = x; i < size_; i = _K(i)) {
            ++data[i];
        }
    }
    int prefix_sum(int x) {
        int res = 0;
        for (int i = x; i >= 0; i = _F(i) - 1)
            res += data[i];
        return res;
    }

    int get_sum(int x0, int x) {
        return prefix_sum(x) - prefix_sum(x0 - 1);
    }
};

const int MAX = 32001;

int sum_at_level[MAX] = { 0 };

int main() {
    int num;
    int x, y;
    scanf("%d", &num);

    FenwickTree tree(MAX);

    for (auto i = 0; i < num; ++i) {
        scanf("%d%d", &x, &y);
        ++sum_at_level[tree.prefix_sum(x)];
        tree.inc(x);
    }
    for (auto i = 0; i < num; ++i) {
        printf("%d\n", sum_at_level[i]);
    }
}