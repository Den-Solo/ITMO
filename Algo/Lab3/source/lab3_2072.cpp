#define _CRT_SECURE_NO_WARNINGS
//#pragma comment(linker,"/STACK:32000000")
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

namespace timus_2072 {

    const int MAX = int(1e5 + 5);
    unsigned n;
    int wetness[MAX];
    unordered_map<int, vector<int>> dists;

    size_t read() {
        scanf("%d", &n);

        size_t wet_size = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            if (!dists[x].size())
                wetness[wet_size++] = x;
            dists[x].emplace_back(i);
        }
        sort(wetness, wetness + wet_size);
        return wet_size;
    }

    pair<int64_t, int64_t> calc(size_t wet_size) {
        

        vector<pair<int, int>> lr_pos(wet_size);
        for (size_t i = 0; i < wet_size; ++i)
            lr_pos[i] = { dists[wetness[i]].front(), dists[wetness[i]].back() };

        int
            l_pos{ 0 },
            r_pos{ 0 },
            l_pos_prev,
            r_pos_prev;
        int64_t
            l_sum{ 0 }, //ends at left point
            r_sum{ 0 }, //ends at right point
            l_sum_prev,
            r_sum_prev;

        for (size_t i = 0; i < wet_size; ++i) {
            l_pos_prev = l_pos;
            r_pos_prev = r_pos;
            l_sum_prev = l_sum;
            r_sum_prev = r_sum;
            l_pos = lr_pos[i].first;
            r_pos = lr_pos[i].second;

            l_sum = std::min(r_sum_prev + std::abs(r_pos_prev - r_pos),
                l_sum_prev + std::abs(l_pos_prev - r_pos));
            r_sum = std::min(r_sum_prev + std::abs(r_pos_prev - l_pos),
                l_sum_prev + std::abs(l_pos_prev - l_pos));
            l_sum += r_pos - l_pos;
            r_sum += r_pos - l_pos;
        }
        return make_pair(r_sum, l_sum);
    }
    void solve() {
        auto res = calc(read());
        cout << std::min(res.first, res.second) + n << '\n'; // n - time to water plants
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    timus_2072::solve();
}
