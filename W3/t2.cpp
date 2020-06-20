#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <utility>
#include <cstring>
#include <cstdint>
#include <inttypes.h>
#include <vector>
#include <algorithm>

using namespace std;

char* A[int(1e6 + 1)];
unsigned letters[26];
unsigned C[int(1e6 + 1)];
unsigned C2[int(1e6 + 1)];

FILE* input = stdin;
FILE* output = stdout;


unsigned* RadixSort(char* a[], int str_len, int num, int kmax, unsigned* buf1, unsigned* buf2) {

    for (int k = 0; k < kmax; ++k) {
        memset(letters, 0, sizeof letters);
        int char_idx = str_len - k - 1;
        for (int i = 0; i < num; ++i) {
            ++letters[a[char_idx][i] - 'a'];
        }
        for (int i = 1; i < 26; ++i) {
            letters[i] += letters[i - 1];
        }

        for (int j = num - 1; j != -1; --j) {
            int idx = a[char_idx][buf1[j]] - 'a';
            buf2[--letters[idx]] = buf1[j];
        }
        swap(buf1, buf2);

    }

    return buf1;
}

int main() {
    
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int n, m, k;
    fscanf(input, "%d%d%d\n", &n, &m, &k);

    for (auto i = 0; i < m; ++i) {
        A[i] = new char[n + 1];
    }
    for (auto i = 0; i < n; ++i) {
        C[i] = i;
    }
    for (auto i = 0; i < m; ++i) {
        fscanf(input, "%s", A[i]);
    }

    unsigned* res = RadixSort(A, m, n, k, C, C2);

    for (auto i = 0; i < n; ++i) {
        fprintf(output, "%u ", res[i] + 1);
    }
    
    for (auto i = 0; i < m; ++i) {
        delete[] A[i];
    }
    fclose(input);
    fclose(output);
}