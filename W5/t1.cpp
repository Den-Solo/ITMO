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

int A[int(1e6 + 1)];
int size_;
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }
void Heapify(int i, const int size_h) {
    int largest_idx = i;
    bool ok = true;
    while (ok) {
        ok = false;
        int l = left(i); int r = right(i);
        if (l < size_h && A[l] > A[largest_idx]) {
            largest_idx = l;
        }
        if (r < size_h && A[r] > A[largest_idx]) {
            largest_idx = r;
        }
        if (largest_idx != i) {
            swap(A[i], A[largest_idx]);
            i = largest_idx;
            ok = true;
        }
    }
}
void BuildHeap() {
    for (int i = size_ / 2; i > -1; --i) {
        Heapify(i,size_);
    }
}
void HeapSort() {
    BuildHeap();
    int size_to_sort = size_;
    while (size_to_sort > 0) {
        swap(A[0], A[--size_to_sort]);
        Heapify(0,size_to_sort);
    }
}

bool IsHeapMin(int i) {
    int l = left(i);
    int r = right(i);
    bool r1 = true; bool r2 = true;;
    if (l < size_){
        if (A[l] >= A[i]) {
           r1 = IsHeapMin(l);
        }
        else {
            return false;
        }
    }
    if (r < size_) {
        if (A[r] >= A[i]) {
            r2 = IsHeapMin(r);
        }
        else {
            return false;
        }
    }
    if (!r1 || !r2)
        return false;
    else
        return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    
    int n;
    fscanf(input, "%d", &size_);

    for (auto i = 0; i < size_; ++i) {
        fscanf(input, "%d", &A[i]);
    }
    

    if (!IsHeapMin(0)) {
        fprintf(output,"%s", "NO");
        return 0;
    }
    fprintf(output, "%s", "YES");



    fclose(input);
    fclose(output);
}