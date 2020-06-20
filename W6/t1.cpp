#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker,"/STACK:32000000")

#include <cstdio>
#include <iostream>
#include <fstream>
#include <utility>
#include <cstring>
#include <string>
#include <cstdint>
#include <inttypes.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <queue>
#include <stack>

using namespace std;



FILE* input = stdin;
FILE* output = stdout;

int A[int(1e5)];

int lb(int left, int right, int val) {
    int count, step;
    count = right - left + 1;
    while (count > 0) {
        auto m = left;
        step = count / 2;
        m += step;
        if (A[m] < val) {
            left = ++m;
            count -= step + 1;
        }
        else {
            count = step;
        }
    }
    if (left == right + 1 || A[left] != val)
        return -2;
    return left;
}
int ub(int left, int right, int val) {
    int count, step;
    count = right - left + 1;
    while (count > 0) {
        auto m = left;
        step = count / 2;
        m += step;
        if (A[m] <= val) {
            left = ++m;
            count -= step + 1;
        }
        else {
            count = step;
        }
    }
    if (left == right + 1 && A[right] != val)
        return -2;
    return left;
}
struct Node {
    int l, r;
};

Node eq_range(int l, int r, int val) {
    int l1 = lb(l, r, val);
    if (l1 == -2)
        return { -2,-2 };
    return { l1, ub(l1, r, val) - 1 };
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    
    int n, m;
    fscanf(input, "%d\n", &n);

    for (auto i = 0; i < n; ++i) {
        fscanf(input, "%d", &A[i]);
    }

    fscanf(input, "%d", &m);
    
    for (auto i = 0; i < m; ++i) {
        int val;
        fscanf(input, "%d", &val);
        auto res = eq_range(0, n - 1, val);
        fprintf(output, "%d %d\n", res.l + 1, res.r + 1);
    }
    

    fclose(input);
    fclose(output);
}