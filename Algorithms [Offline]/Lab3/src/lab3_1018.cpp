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
#include <utility>

using namespace std;

namespace timus_1018 {

    vector<vector<int>> w_of_del;   // [node][deleted_count] min count of apples at node to be deleted
    vector<int> st_w, st_sz;        //sub-tree weigth / size

    vector<int> weight;
    int node_cnt, edges_to_del;
    vector<vector<pair<int, int>>> edges_weight;


    void preproc(int node = 1, int par = 0) {
        auto& v = edges_weight[node];
        st_w[node] = weight[node];
        for (auto it = v.begin(); it != v.end(); ++it) {
            if (it->first == par) {
                v.erase(it);
                break;
            }
        }
        for (auto& el : v) {
            weight[el.first] = el.second;
            preproc(el.first, node);
            st_w[node] += st_w[el.first];
            st_sz[node] += st_sz[el.first];
        }
    }
    
    
    void find_path(int node = 1) {
        w_of_del[node][st_sz[node]] = st_w[node];

        if (!edges_weight[node].size()) return;
        for (auto& p : edges_weight[node])
            find_path(p.first);

        for (size_t i = 1; i <= edges_to_del; ++i) {
            for (size_t j = 0; j <= i; ++j) {
                w_of_del[node][i] = std::min(
                    w_of_del[node][i],
                    w_of_del[edges_weight[node][0].first][j] + w_of_del[edges_weight[node][1].first][i - j]
                );
            }
        }
    }

    void solve() {
        
        int full_apple_cnt = 0;
        int edges_to_keep;

        scanf("%d %d", &node_cnt, &edges_to_keep);
        edges_weight.resize(node_cnt + 1);
        for (size_t i = 0; i < node_cnt - 1; ++i) {
            int edge1, edge2;
            int weight;
            scanf("%d %d %d", &edge1, &edge2, &weight);
            edges_weight[edge1].emplace_back(edge2, weight);
            edges_weight[edge2].emplace_back(edge1, weight);
            full_apple_cnt += weight;
        }
        edges_to_del = node_cnt - edges_to_keep - 1; //root cannot be deleted
      

        {
            
            w_of_del.resize(node_cnt + 1, vector<int>(node_cnt + 1, int(3e6 + 10) ));
            for (size_t i = 0; i <= node_cnt; ++i) {
                w_of_del[i][0] = 0;
            }
            st_sz.resize(node_cnt + 1, 1);
            st_w.resize(node_cnt + 1);
            weight.resize(node_cnt + 1);

            preproc();
            find_path();

            cout << full_apple_cnt - w_of_del[1][edges_to_del];
        }

    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

     //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "card_weights", stdout);

    timus_1018::solve();
}

