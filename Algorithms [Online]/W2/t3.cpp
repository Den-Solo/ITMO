#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <utility>
#include <cstring>
#include <cstdint>
#include <inttypes.h>
using namespace std;

unsigned data_[int(1e6 + 10)];

FILE* input = stdin;
FILE* output = stdout;

uint64_t cmps = 0;

/*void quickSort(int* data, int l, int r) {
    int key = data[(l + r) / 2];
    int i = l; 
    int j = r;

    do {
        while (data[i] < key) ++i, ++cmps;
        while (data[j] > key) --j, ++cmps;
        if (i <= j) {
            swap(data[i], data[j]);
            ++i;
            --j;
            ++cmps;
        }
    } while (i < j);

    if (l < j) quickSort(data, l, j);
    if (i < r) quickSort(data, i, r);
}*/

int main() {

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int num;
    fscanf(input, "%d", &num);

    if (num == 1) {
        fprintf(output, "%u", 1u);
        return 0;
    }
    data_[1] = 1;
    data_[2] = 2;

    ++num;

    unsigned tmp;
    for (unsigned i = 3; i != num; ++i) {
        tmp = (i + 1) >> 1;
        data_[i] = data_[tmp];
        data_[tmp] = i;
    }
    for (unsigned i = 1; i != num; ++i) {
        fprintf(output,"%u ", data_[i]);
    }


    /*for (auto i = 0; i < num; ++i) {
        fscanf(input, "%d", &data_[i]);
    }

    quickSort(data_, 0, num - 1);

    for (int i = 0; i < num; ++i) {
        printf("%d ", data_[i]);
    }
    fprintf(output, "\n%d", cmps);*/

    fclose(input);
    fclose(output);
}