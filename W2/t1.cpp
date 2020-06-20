#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <utility>
#include <cstring>
using namespace std;

int data_[int(1e5)];
int buf_[int(1e5)];
FILE* output = stdout;

void Merge(int* data, int left, int mid, int right, int *buf) {
    int i = left;
    int j = mid;
    int k = left;


    while (i != mid && j != right + 1) {
        if (data[i] <= data[j]) {
            buf[k] = data[i], ++k, ++i;
            data_; buf_;
        }
        else {
            buf[k] = data[j], ++k, ++j;
            data_; buf_;
        }
    }
    if (i != mid) {
        while (i != mid) {
            buf[k] = data[i], ++k, ++i;
        }
    }
    else {
        while (j != right + 1) {
            buf[k] = data[j], ++k, ++j;
        }
    }
    
    memcpy(data + left , buf + left, sizeof(int) * (right - left + 1));
    fprintf(output,
        "%d %d %d %d\n",
        left + 1, right + 1, data[left], data[right]);
}

void MergeSort(int* data, int left, int right, int* buf) {
    if (right <= left)
        return;
    else if (right - left == 1) {
        if (data[left] > data[right])
            swap(data[left], data[right]);
        fprintf(output,
            "%d %d %d %d\n",
            left + 1, right + 1, data[left], data[right]);
        return;
    }
    data_; buf_;
    int mid = (left + right) / 2;
    MergeSort(data, left, mid - 1, buf);
    MergeSort(data, mid, right, buf);
    Merge(data, left, mid, right, buf);
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

    for (auto i = 0; i < num; ++i) {
        fprintf(output, "%d ", data_[i]);
    }
    fclose(input);
    fclose(output);
}