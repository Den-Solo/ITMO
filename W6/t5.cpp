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
int cntVertInSubTree(int v) {
    if (v == 0)
        return 0;
    return cntVertInSubTree(A[v].l) + cntVertInSubTree(A[v].r) + 1;
}
int GetIdx(int key, int root) {
    bool ok = true;
    while (A[root].k != key){
        int prev_ = root;
        if (A[root].l && A[root].k > key)
            root = A[root].l;
        if (A[root].r && A[root].k < key)
            root = A[root].r;
        if (prev_ == root) {
            ok = false;
            break;
        }
    }
    if (ok)
        return root;
    else
        return 0;
}
bool CheckTree(int root, int l, int r) {
    if (root == 0)
        return true;

    if (A[root].k <= l || A[root].k >= r)
        return false;

    return
        CheckTree(A[root].l, l, A[root].k)
     && CheckTree(A[root].r, A[root].k, r);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    int n;

    fscanf(input, "%d", &n);

    if (n <= 1) {
        fprintf(output, "%s", "YES");
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        fscanf(input, "%d %d %d", &A[i].k, &A[i].l, &A[i].r);
        A[A[i].l].p = A[A[i].r].p = i;
    }
    
    int root;
    int count_roots = 0;
    for (int i = 1; i <= n; ++i) {
        if (A[i].p == -1) {
            root = i;
            ++count_roots;
            break;
        }
    }


    if (CheckTree(root, numeric_limits<int>::min(), numeric_limits<int>::max()) && count_roots == 1)
        fprintf(output, "%s", "YES");
    else
        fprintf(output, "%s", "NO");

    fclose(input);
    fclose(output);
}