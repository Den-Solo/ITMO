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


const int MAX = int(1e5);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int M;
    vector<pair<int, int>> segments;
    segments.reserve(MAX);

    scanf("%d", &M);
    for (;;) {
        int l, r;
        scanf("%d %d", &l, &r);
        if (!l && !r)
            break;
        if (r <= 0 || l >= M)
            continue;
        segments.emplace_back(l, r);
    }
    sort(segments.begin(), segments.end());

    if (segments.empty() || segments.front().first > 0 || segments.back().second < M) {
        printf("No solution");
        return 0;
    }

    vector<pair<int, int>> rightest_edges(M, { -1,-1 });


    {
        size_t i = 0;
        while (i < segments.size() && segments[i].first <= 0) {
            if (rightest_edges[0].first < segments[i].second) {
                rightest_edges[0].first = segments[i].second;
                rightest_edges[0].second = i;
            }
            ++i;
        }
        
        for (size_t j = 1; j < M; ++j) {
            while (i != segments.size() && segments[i].first <= j) {
                if (rightest_edges[j - 1].first > segments[i].second) {
                    rightest_edges[j].first = rightest_edges[j - 1].first;
                    rightest_edges[j].second = rightest_edges[j - 1].second;
                }
                else {
                    rightest_edges[j].first = segments[i].second;
                    rightest_edges[j].second = i;
                }
                ++i;
            }
            if (rightest_edges[j].second == -1) {
                if (rightest_edges[j - 1].first <= j){
                    printf("No solution");
                    return 0;
                }
                rightest_edges[j].first = rightest_edges[j - 1].first;
                rightest_edges[j].second = rightest_edges[j - 1].second;
            }
        }
    }

    vector<int> min_cover;
    min_cover.reserve(M);
    for (size_t i = 0, j = 0; j < rightest_edges.size();) {
        min_cover.emplace_back(j);
        j = rightest_edges[j].first;
    }
    printf("%d\n", min_cover.size());
    for (auto i : min_cover) {
        printf("%d %d\n", segments[rightest_edges[i].second].first, segments[rightest_edges[i].second].second);
    }
}

