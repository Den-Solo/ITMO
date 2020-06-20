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


struct Node {
    int k, p = -1, l, r;
};
const int sz = 2 * 1e5;
Node A[sz + 2];

int Height(int v) {
    int l = 0, r = 0;
    if (A[v].l)
        l = Height(A[v].l);
    if (A[v].r)
        r = Height(A[v].r);
    return max(l, r) + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    int n;

    fscanf(input, "%d", &n);

    if (n == 0) {
        fprintf(output, "%d", 0);
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        fscanf(input, "%d %d %d", &A[i].k, &A[i].l, &A[i].r);
        A[A[i].l].p = A[A[i].r].p = i;
    }
    
    int root;
    for (int i = 1; i <= n; ++i) {
        if (A[i].p == -1) {
            root = i;
            break;
        }
    }

    fprintf(output, "%d", Height(root));

    fclose(input);
    fclose(output);
}