#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <utility>
#include <cstring>
#include <cstdint>
#include <inttypes.h>
#include <vector>
#include <algorithm>
using namespace std;

int data_[int(1e5 + 10)];
int buf_[int(1e5 + 10)];

FILE* input = stdin;
FILE* output = stdout;

void Merge(int* data, int left, int mid, int right, int step, int* buf) {
    int i = left;
    int j = mid;
    int k = left;


    while (i != mid && j <= right) {
        if (data[i] <= data[j]) {
            buf[k] = data[i], k += step, i += step;
        }
        else {
            buf[k] = data[j], k += step, j += step;
        }
    }
    if (i != mid) {
        while (i != mid) {
            buf[k] = data[i], k += step, i += step;
        }
    }
    else {
        while (j <= right) {
            buf[k] = data[j], k += step, j += step;
        }
    }
    
    for (auto i = left; i <= right; i += step) {
        data[i] = buf[i];
    }
}

void MergeSort(int* data, int left, int right, int step, int* buf) {
    if (left + step > right)
        return;
    else if (left + step == right) {
        if (data[left] > data[right])
            swap(data[left], data[right]);
        return;
    }
    int cnt = (right - left) / step + 1;
    int mid = left + step * (cnt / 2);
    MergeSort(data, left, mid - step, step, buf);
    MergeSort(data, mid, right, step, buf);
    Merge(data, left, mid, right, step, buf);
}
int main() {

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int num, k;
    fscanf(input, "%d%d", &num, &k);

    for (auto i = 1; i != num + 1; ++i) {
        fscanf(input, "%d", &data_[i]);
    } 

    for (auto i = 0; i < k; ++i) {
        MergeSort(data_, 1 + i, num, k, buf_);
    }
    

    bool ok = true;
    for (auto i = 1; i < num; ++i) {
        if (data_[i] > data_[i + 1]) {
            ok = false;
            break;
        }
    }

    if (ok)
        fprintf(output, "%s", "YES");
    else
        fprintf(output, "%s", "NO");

    fclose(input);
    fclose(output);
}