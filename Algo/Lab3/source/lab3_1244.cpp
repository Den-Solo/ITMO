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

namespace timus_1244 {

    int pack_w, N, weight_diff;

    vector<int> card_weights;
    vector<vector<int>> cnt_cards;
    vector<vector<bool>> used;

    int calc_cards() {
        cnt_cards.resize(weight_diff + 1, vector<int>(N + 1));
        used.resize(weight_diff + 1, vector<bool>(N + 1));

        fill(cnt_cards[0].begin(), cnt_cards[0].end(), 1);

        for (int w = 1; w <= weight_diff; ++w) {
            for (int i = 0; i < N; i++) {
                cnt_cards[w][i + 1] = cnt_cards[w][i];
                if (w >= card_weights[i]) {
                    cnt_cards[w][i + 1] += cnt_cards[w - card_weights[i]][i];
                    used[w][i + 1] =
                        (cnt_cards[w][i + 1] == 1)
                        && (cnt_cards[w - card_weights[i]][i] == 1);
                }
            }
        }
        return cnt_cards[weight_diff][N];
    }

    void print_res(int sol_count) {

        if (sol_count == 0)     printf("0");
        else if (sol_count > 1) printf("-1");
        else {

            vector<int> res;
            res.reserve(N);

            int weight = weight_diff;
            for (int i = N - 1; i >= 0; i--) {
                if (used[weight][i + 1]) {
                    res.emplace_back(i + 1);
                    weight -= card_weights[i];
                }
            }

            for (auto rit = res.rbegin(); rit != res.rend(); ++rit)
                printf("%d ", *rit);

        }
    }
    void solve() {


        scanf("%d", &pack_w);
        scanf("%d", &N);

        card_weights.resize(N);
        weight_diff = pack_w;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &card_weights[i]);
            weight_diff -= card_weights[i];
        }
        weight_diff = -weight_diff;

        print_res(calc_cards());

    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "card_weights", stdout);

    timus_1244::solve();
}

