#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker,"/STACK:32000000")
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <numeric>


using namespace std;

namespace timus_1152 {

    const unsigned MAX_M_CNT = 1 << 20;
    unsigned n;
    int max_dmg = 0;
    int cntM[21];
    int hits[MAX_M_CNT];
    int saved_dmg[MAX_M_CNT];


    unsigned SetBits(unsigned m, int l, int r) {
        for (auto i = l; i <= r; ++i)
            m |= (1 << (i % n));
        return m;
    }
    unsigned ResetBits(unsigned m, int l, int r) {
        for (auto i = l; i <= r; ++i)
            m -= (1 << (i % n));
        return m;
    }
    int CntSum(unsigned m, int l, int r) {
        int sum = 0;
        for (auto i = l; i <= r; ++i)
            if (!(m & (1 << i % n)))
                sum += cntM[i % n];
        return sum;
    }
    int GetDmg(unsigned m, int mnstrs) {
        if (m == ((1 << n) - 1)) return 0;
        if (hits[m] == -1)
            hits[m] = mnstrs;
        if (saved_dmg[m] == -1) {
            saved_dmg[m] = 20000;
            for (auto i = 0; i < n; ++i) {
                saved_dmg[m] = std::min(
                    saved_dmg[m], GetDmg(SetBits(m, i, i + 2), hits[m] - CntSum(m, i, i + 2))
                );
            }
        }

        return mnstrs + saved_dmg[m];
    }

    void solve() {
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", &cntM[i]);
        }

        max_dmg = CntSum(0, 0, n - 1);
        memset(hits, -1, sizeof(hits));
        memset(saved_dmg, -1, sizeof(saved_dmg));

        printf("%d\n", GetDmg(0, max_dmg) - max_dmg);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    timus_1152::solve();

}
