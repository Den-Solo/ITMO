#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <utility>
#include <cstring>
#include <cstdint>
#include <inttypes.h>
using namespace std;

int data_[int(1e5 + 10)];
int buf_[int(1e5 + 10)];
FILE* output = stdout;

uint64_t inversions = 0;

void Merge(int* data, int left, int mid, int right, int *buf) {

    int i = left;
    int j = mid;
    int k = left;
    int i_prev = left;
    int j_prev = mid;

    data_, buf_;

    while (i != mid && j != right + 1) {
        if (data[i] <= data[j]) {
            buf[k++] = data[i++];
        }
        else {
            inversions += mid - i;
            buf[k++] = data[j++];
        }
    }
    if (i != mid) {
        while (i != mid) {
            buf[k++] = data[i++];
        }
    }
    else {
        while (j != right + 1) {
            buf[k++] = data[j++];
        }
    }
    
    memcpy(data + left , buf + left, sizeof(int) * (right - left + 1));
   
}

void MergeSort(int* data, int left, int right, int* buf) {
    data_, buf_;
    if (right <= left)
        return;
    else if (right - left == 1) {
        if (data[left] > data[right]) {
            swap(data[left], data[right]);
            ++inversions;
        }
        return;
    }
    data_; buf_;
    int mid = (left + right) / 2;
    MergeSort(data, left, mid, buf);
    MergeSort(data, mid + 1, right, buf);
    Merge(data, left, mid + 1, right, buf);
}

int main() {
    auto input = fopen("input.txt", "r");
    

    output = fopen("output.txt", "w");

    int num;
    fscanf(input, "%d", &num);

    for (auto i = 0; i < num; ++i) {
        fscanf(input, "%d", &data_[i]);
    }

    MergeSort(data_, 0, num - 1, buf_);

    fprintf(output, "%" PRIu64, inversions);

    fclose(input);
    fclose(output);
}