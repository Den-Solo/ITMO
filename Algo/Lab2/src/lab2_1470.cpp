#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
using namespace std;


class FenwickTree3D {
    using Cube = vector<vector<vector<int>>>;
private:
    Cube data;
    size_t size_;
public:
    FenwickTree3D(size_t size) : size_(size) {
        data.resize(size_);
        for (auto& v1 : data) {
            v1.resize(size_);
            for (auto& v2 : v1) {
                v2.assign(size_, 0);
            }
        }
    }
    inline static size_t _F(size_t idx) {
        return idx & (idx + 1);
    }
    inline static size_t _K(size_t idx) {
        return idx | (idx + 1);
    }
    void add(int x, int y, int z, int val) {

        for (int i = x; i < size_; i = _K(i)) {
            for (int j = y; j < size_; j = _K(j)) {
                for (int k = z; k < size_; k = _K(k))
                    data[i][j][k] += val;
            }
        }
    }
    int prefix_sum(int x, int y, int z) {
        int res = 0;
        for (int i = x; i >= 0; i = _F(i) - 1)
            for (int j = y; j >= 0; j = _F(j) - 1)
                for (int k = z; k >= 0; k = _F(k) - 1)
                    res += data[i][j][k];
        return res;
    }

    int get_sum(int x0, int y0, int z0, int x, int y, int z) {
        return
            prefix_sum(x, y, z)
            - prefix_sum(x0 - 1, y, z)
            - prefix_sum(x, y0 - 1, z)
            - prefix_sum(x, y, z0 - 1)
            - prefix_sum(x0 - 1, y0 - 1, z0 - 1)
            + prefix_sum(x0 - 1, y0 - 1, z)
            + prefix_sum(x0 - 1, y, z0 - 1)
            + prefix_sum(x, y0 - 1, z0 - 1);
    }
};



int main() {
    size_t size;

    scanf("%u", &size);
    FenwickTree3D tree(size);

    int command;
    int x1, x2, y1, y2, z1, z2, val;
    while (1) {
        scanf("%d", &command);
        if (command == 1) {
            scanf("%d%d%d%d", &x1, &y1, &z1, &val);
            tree.add(x1, y1, z1, val);
        }
        else if (command == 2) {
            scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2,&z2);
            printf("%d\n", 
                tree.get_sum(x1, y1, z1,x2, y2, z2)
            );
        }
        else {
            break;
        }
    }
}