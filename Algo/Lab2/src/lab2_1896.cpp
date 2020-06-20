#define _CRT_SECURE_NO_WARNINGS
#pragma comment (linker, "/STACK:6000000")

//ALERT USE G++ to compile or MSVC (clang fails at t[2 * v] for some reason)
#include <cstdio>
#include <cmath>

using namespace std;


class FenwickTree {
private:
    static const int MAX = 1'100'001;
    int data_[MAX] = { 0 };
    size_t size_;
public:
    FenwickTree(size_t size) : size_(size) {
        for (auto x = 0; x < size_; ++x) {
            for (auto i = x; i < size_; i = _K(i)) {
                ++data_[i];
            }
        }
    }
    inline static size_t _F(size_t idx) {
        return idx & (idx + 1);
    }
    inline static size_t _K(size_t idx) {
        return idx | (idx + 1);
    }
    void dec(size_t x) {
        for (auto i = x; i < size_; i = _K(i)) {
            --data_[i];
        }
    }
    size_t prefix_sum(size_t x) {
        unsigned res = 0;
        for (int i = x; i >= 0; i = _F(i) - 1)
            res += data_[i];
        return res;
    }
    size_t GetPos(size_t x) {
        size_t pos = x - 1;
        int size = size_ - pos + 1;
        
        while (size > 0) {
            int step = size / 2;
            int npos = pos + step;
            if (prefix_sum(npos) < x) {
                pos = ++npos;
                size -= step + 1;
            }
            else
                size = step;
        }
        dec(pos);
        return pos + 1;
    }
};


int main() {
    int n, k;
    scanf("%d%d", &n, &k);

    if (n == 1) {
        printf("%d", 0);
        return 0;
    }
    FenwickTree tree(n);

    int cur = k;
    int res = abs(1 - k);
    //printf("%d ", cur);
    
    tree.dec(cur - 1);
    --k;
    ++n;
    for (int i = 2; i != n; ++i) {
        cur = (cur + k) % (n - i);
        if (cur == 0)
            cur = n - i;

        int preset_pos = tree.GetPos(cur);
        //printf("%d ", preset_pos);
        res ^= abs(i - preset_pos);
    }
    printf("%d", res);
}