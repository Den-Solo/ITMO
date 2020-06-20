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
    int val, idx;
};
int A[int(1e6 + 1)];
Node line_to_idx[int(1e6 + 1)];
int size_ = 0;

int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }
void Heapify(int i, const int size_h) {
    int smallest_idx = i;
    bool ok = true;
    while (ok) {
        ok = false;
        int l = left(i); int r = right(i);
        if (l < size_h && line_to_idx[ A[l]].val < line_to_idx[A[smallest_idx]].val) {
            smallest_idx = l;
        }
        if (r < size_h && line_to_idx[A[r]].val < line_to_idx[A[smallest_idx]].val) {
            smallest_idx = r;
        }
        if (smallest_idx != i) {
            swap(A[i], A[smallest_idx]);
            swap(line_to_idx[A[i]].idx, line_to_idx[A[smallest_idx]].idx);
            i = smallest_idx;
            ok = true;
        }
    }
}

void LiftUp(int idx) {
    int par = (idx - 1) / 2;
    if (par != idx && line_to_idx[A[par]].val > line_to_idx[A[idx]].val) {
        swap(A[par], A[idx]);
        swap(line_to_idx[A[par]].idx, line_to_idx[A[idx]].idx);
        LiftUp(par);
    }
}
void Insert(int val) {
    A[size_++] = val;
    LiftUp(size_ - 1);
}
bool empty() { return size_ == 0; };


int ExtractMin() {
    swap(A[0], A[--size_]);
    swap(line_to_idx[A[0]].idx, line_to_idx[A[size_]].idx);
    Heapify(0,size_);
    return A[size_];
}
void update(int i,int new_val) {
    line_to_idx[A[i]].val = new_val;
    LiftUp(i);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    
    int n;
    fscanf(input, "%d\n", &n);

    for (auto i = 0; i < n; ++i) {
        char c;
        fscanf(input, "%c", &c);
        if (c == 'A') {
            int val;
            fscanf(input, "%d\n", &val);
            line_to_idx[i] = { val, size_ };
            Insert(i);
        }
        else if (c == 'X') {
            if (!empty()) {
                fprintf(output, "%d\n", line_to_idx[ExtractMin()].val);
            }
            else {
                fprintf(output, "%c\n", '*');
            }
            fscanf(input, "\n");
        }
        else {
            int idx, new_val;
            fscanf(input, "%d%d\n", &idx, &new_val);
            update(line_to_idx[idx - 1].idx, new_val);
        }
    }

    

    fclose(input);
    fclose(output);
}