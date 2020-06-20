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
    int h = -1;
    int idx = 0;
};
const int sz = 2 * 1e5;
Node A[sz + 2];
int B[sz + 2];

int Height(int v) {
    if (v == 0)
        return 0;
    int l = 0, r = 0;
    if (A[v].l)
        l = Height(A[v].l);
    if (A[v].r)
        r = Height(A[v].r);
    return A[v].h = max(l, r) + 1;
}
int GetHeight(int v) {
    if (v == 0)
        return 0;
    return A[v].h;
}
int GetBalance(int v) {
    return GetHeight(A[v].r) - GetHeight(A[v].l);
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
void SmallLeftRotate(int v) {
    if (GetBalance(v) < 2)
        return;
    auto b = A[v].r;
    swap(A[v].p, A[b].p);
    A[v].r = A[b].l;
    A[b].l = v;
}
void BigLeftRotate(int v) {
    if (GetBalance(v) < 2)
        return;
    if (GetBalance(A[v].r) != -1) {
        SmallLeftRotate(v);
        return;
    }
    int b = A[v].r;
    int c = A[b].l;

    A[c].p = A[v].p;
    A[v].p = c;
    A[b].p = c;
    A[v].r = A[c].l;
    A[c].l = v;
    A[b].l = A[c].r;
    A[c].r = b;

    
}

void PrintVerts1(int root, FILE* output) {
    if (root == 0)
        return;
    fprintf(output, "%d %d %d\n", A[root].k, A[A[root].l].idx, A[A[root].r].idx);
    PrintVerts1(A[root].l, output);
    PrintVerts1(A[root].r, output);
}
void PrintVerts(int sz,  FILE* out) {
    for (auto i = 1; i <= sz; ++i) {
        fprintf(out, "%d %d %d\n", A[B[i]].k, A[A[B[i]].l].idx, A[A[B[i]].r].idx);
    }
}
int idx = 1;
void GiveIdxs(int root) {
    if (root == 0)
        return;
    A[root].idx = idx;
    B[idx++] = root;
    GiveIdxs(A[root].l);
    GiveIdxs(A[root].r);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    int n;

    fscanf(input, "%d", &n);

    if (n == 0) {
        fprintf(output, "%d\n", 0);
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

    Height(root);

    if (abs(GetBalance(root)) > 1) {
        if (GetBalance(A[root].r) == -1) {
            BigLeftRotate(root);
        }
        else {
            SmallLeftRotate(root);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (A[i].p == -1) {
            root = i;
            break;
        }
    }
    GiveIdxs(root);
    fprintf(output, "%d\n", n);
    PrintVerts(n,output);

    fclose(input);
    fclose(output);
}