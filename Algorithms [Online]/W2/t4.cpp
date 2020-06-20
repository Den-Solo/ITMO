#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <utility>
#include <cstring>
#include <cstdint>
#include <inttypes.h>
#include <vector>
#include <algorithm>
using namespace std;

int data_[int(4 * 1e7 + 10)];

FILE* input = stdin;
FILE* output = stdout;

uint64_t cmps = 0;

int nth_order_statistics(int* a, int l, int r, int k) {
    for (;;) {

        if (r <= l + 1) {
            if (r == l + 1 && a[r] < a[l])
                swap(a[l], a[r]);
            return a[k];
        }

		// упорядочиваем a[l], a[l+1], a[r]
		unsigned mid = (l + r) >> 1;
		swap(a[mid], a[l + 1]);
		if (a[l] > a[r])
			swap(a[l], a[r]);
		if (a[l + 1] > a[r])
			swap(a[l + 1], a[r]);
		if (a[l] > a[l + 1])
			swap(a[l], a[l + 1]);

		// выполняем разделение
		// барьером является a[l+1], т.е. медиана среди a[l], a[l+1], a[r]
		unsigned
			i = l + 1,
			j = r;
		const int cur = a[l + 1];
		for (;;) {
			while (a[++i] < cur);
			while (a[--j] > cur);
			if (i > j)
				break;
			swap(a[i], a[j]);
		}

		// вставляем барьер
		a[l + 1] = a[j];
		a[j] = cur;

		// продолжаем работать в той части,
		//	 которая должна содержать искомый элемент
		if (j >= k)
			r = j - 1;
		if (j <= k)
			l = i;
    }
}

void solve(int* a,int size, int k1, int k2) {
	nth_order_statistics(a, 1, size, k1);
	nth_order_statistics(a, k1, size, k2);
	sort(a + k1, a + k2);

	for (int i = k1; i != k2 + 1; ++i) {
		fprintf(output, "%d ", a[i]);
	}
}
int main() {

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int num, k1, k2;
    fscanf(input, "%d%d%d", &num, &k1, &k2);

    int A, B, C, a1, a2;
    fscanf(input, "%d%d%d%d%d", &A, &B, &C, &a1, &a2);

    data_[1] = a1;
    data_[2] = a2;

    for (int i = 3; i != num + 1; ++i) {
        data_[i] = A * data_[i - 2] + B * data_[i - 1] + C;
    }

	solve(data_, num, k1, k2);

    fclose(input);
    fclose(output);
}