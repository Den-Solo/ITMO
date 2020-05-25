#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <utility>
#include <cstring>
#include <cstdint>
#include <inttypes.h>
#include <vector>
#include <algorithm>

using namespace std;

uint16_t A[int(6000)];
uint16_t B[int(6000)];
unsigned Rad[256];
unsigned* C;
unsigned* C2;

FILE* input = stdin;
FILE* output = stdout;


unsigned* RadixSort(unsigned* a, int len, unsigned* buf) {
    int x = 0;
    for (int k = 0; k < 4; ++k) {
        memset(Rad, 0, sizeof Rad);
        for (int i = 0; i < len; ++i) {
            ++Rad[(a[i] >> x) & 255];
        }
        for (int i = 1; i < 256; ++i) {
            Rad[i] += Rad[i - 1];
        }

        for (int j = len - 1; j != -1; --j) {
            int idx = (a[j] >> x) & 255;
            buf[--Rad[idx]] = a[j];
        }
        swap(a, buf);

        x += 8;
    }

    return a;
}

int main() {
    
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int n, m;
    fscanf(input, "%d%d", &n, &m);

    for (auto i = 0; i < n; ++i) {
        fscanf(input, "%" PRId16, &A[i]);
    }
    for (auto i = 0; i < m; ++i) {
        fscanf(input, "%" PRId16, &B[i]);
    }
    size_t c_size = n * m;
    C = new unsigned[c_size * 2];
    C2 = C + c_size;

    int t = 0;
    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < m; ++j) {
            C[t++] = static_cast<unsigned>(A[i]) 
                * static_cast<unsigned>(B[j]);
        }
    }

    unsigned* RES = RadixSort(C, c_size, C2);

    uint64_t res = 0;

    for (auto i = 0; i < c_size; i += 10) {
        res += RES[i];
    }

    fprintf(output, "%llu", res);

    delete[] C;
    fclose(input);
    fclose(output);
}