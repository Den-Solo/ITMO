#pragma comment(linker,"/STACK:32000000")
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

namespace timus_1501 {

    struct Pair {
        bool l : 1;
        bool r : 1;
        Pair() : l(0), r(0) {}
        bool operator[](bool is_red) {
            if (is_red)
                return r;
            return l;
        }
        void set(bool is_red, bool ok) {
            if (is_red)
                r = ok;
            l = ok;
        }
    };
    using container = vector<vector<Pair>>;
    size_t pack_size;
    string l_pack, r_pack;
    container is_visited, is_success;

    bool is_full(size_t pack_idx) {
        return pack_idx >= pack_size;
    }
    bool even(size_t a, size_t b) {
        return !((a + b) % 2);
    }
    bool is_ok(bool is_red = false, size_t l_pack_idx = 0, size_t r_pack_idx = 0) {
        if (l_pack_idx == r_pack_idx && l_pack_idx == pack_size)
            return 1;

        if (!is_visited[l_pack_idx][r_pack_idx][is_red]) {
            bool ok = false;

            if (even(l_pack_idx, r_pack_idx)) {
                ok = ok || (!is_full(l_pack_idx) && is_ok(l_pack[l_pack_idx] == '0', l_pack_idx + 1, r_pack_idx));
                ok = ok || (!is_full(r_pack_idx) && is_ok(r_pack[r_pack_idx] == '0', l_pack_idx, r_pack_idx + 1));
            }
            else {
                char color = (is_red ? '1' : '0');
                ok = ok || (!is_full(l_pack_idx) && l_pack[l_pack_idx] == color && is_ok(!is_red, l_pack_idx + 1, r_pack_idx));
                ok = ok || (!is_full(r_pack_idx) && r_pack[r_pack_idx] == color && is_ok(!is_red, l_pack_idx, r_pack_idx + 1));
            }
            is_success[l_pack_idx][r_pack_idx].set(is_red, ok);
            is_visited[l_pack_idx][r_pack_idx].set(is_red, true);
        }

        return is_success[l_pack_idx][r_pack_idx][is_red];
    }
   bool get_success(size_t l, size_t r, bool is_red) {
       if (l == r && l == pack_size)
           return 1;
       return is_success[l][r][is_red];
   }
     string GetRes(bool black_start) {

        size_t l = 0, r = 0;
        bool is_red_nxt = black_start ? false : true;

        string res;
        res.reserve(2 * pack_size + 1);
        while (!(l == pack_size && r == pack_size)) {
            if (even(l ,r)) {
                if (!is_full(l) && get_success(l + 1,r,l_pack[l] == '0')) {
                    res.push_back('1');
                    is_red_nxt = l_pack[l] == '0';
                    ++l;
                }
                else {
                    res.push_back('2');
                    is_red_nxt = r_pack[r] == '0';
                    ++r;
                }
            }
            else {
                char color = (is_red_nxt ? '1' : '0');
                if (!is_full(l) && l_pack[l] == color && get_success(l + 1,r,l_pack[l] == '0')) {
                    res.push_back('1');
                    ++l;
                }
                else {
                    res.push_back('2');
                    ++r;
                }
                is_red_nxt = !is_red_nxt;

            }
        }
        return res;
    }
    void solve() {
        cin >> pack_size >> l_pack >> r_pack;

        is_visited.resize(pack_size + 1, vector<Pair>(pack_size + 1));
        is_success.resize(pack_size + 1, vector<Pair>(pack_size + 1));

        bool black_start = is_ok();
        bool red_start = false;
        if (!black_start)
            red_start = is_ok(true);

        if (!black_start && !red_start) {
            cout << "Impossible";
            return;
        }

        cout << GetRes(black_start);

    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

   // freopen("input.txt", "r", stdin);
    //freopen("output.txt", "card_weights", stdout);

    timus_1501::solve();
}

