#pragma comment(linker,"/STACK:32000000")
#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

namespace timus_1326 {

    const uint32_t MAX = 1 << 20;
    const uint32_t MAX_PRICE = uint32_t(1e6);

    struct offer {
        uint32_t b_mask;
        uint32_t price;
        offer() = default;
        offer(uint32_t m, int p) : b_mask(m), price(p) {}
    };

    vector<uint32_t> prices(MAX, MAX_PRICE);
    vector<offer> offers;
    int needed_caps;
    


    inline unsigned SetBits(unsigned m, int l, int r) {
        for (auto i = l; i <= r; ++i)
            m |= (1 << (i));
        return m;
    }
    inline unsigned ResetBits(unsigned m, int l, int r) {
        for (auto i = l; i <= r; ++i)
            m &= ~(1 << (i));
        return m;
    }
    inline uint32_t intersect(uint32_t a, uint32_t b) {
        return a & ~b;
    }

    uint32_t find_solution(uint32_t mask) {
        if (!mask || prices[mask] != MAX_PRICE)
            return prices[mask];
        for (size_t i = 0; i < offers.size(); ++i) {
            if (intersect(mask, offers[i].b_mask) != mask) {//at least one cap matches
                prices[mask] = std::min(
                    prices[mask],
                    find_solution(intersect(mask, offers[i].b_mask)) + offers[i].price
                );
            }
        }
        return prices[mask];
    }

    uint32_t read() {
        scanf("%d", &needed_caps);
        offers.reserve(needed_caps);
        prices[0] = 0;
        for (size_t i = 0; i < needed_caps; ++i) {
            uint32_t price;
            scanf("%u", &price);
            offers.emplace_back(SetBits(0, i, i), price);
        }

        {
            uint32_t offer_cnt;
            scanf("%u", &offer_cnt);
            for (size_t i = 0; i < offer_cnt; ++i) {
                uint32_t price, cap_cnt;
                scanf("%u %u", &price, &cap_cnt);
                uint32_t mask{ 0 };
                for (size_t j = 0; j < cap_cnt; ++j) {
                    int cap_idx;
                    scanf("%d", &cap_idx);
                    --cap_idx;
                    mask = SetBits(mask, cap_idx, cap_idx);
                }
                offers.emplace_back(mask, price);
            }
        }
        uint32_t mask{ 0 };
        {
            int cap_cnt;
            scanf("%d", &cap_cnt);
            for (size_t i = 0; i < cap_cnt; ++i) {
                int cap_idx;
                scanf("%d", &cap_idx);
                --cap_idx;
                mask = SetBits(mask, cap_idx, cap_idx);
            }
        }
        return mask;
    }
    void solve() {
 
        auto task_mask = read();

        find_solution(task_mask);

        printf("%d", prices[task_mask]);
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    timus_1326::solve();
}


