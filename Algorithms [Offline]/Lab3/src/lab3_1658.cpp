#pragma comment(linker,"/STACK:32000000")
#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

namespace timus_1658 {
    
    const int MAX_SUM = 9 * 100;
    const int MAX_SQUARE = 9 * 9 * 100;
    const int MAX_DIGITS = 101;

    int cnt_digits[MAX_SUM + 1][MAX_SQUARE + 1];

    int GetCntDigits(int s, int s_sq) {
        if (!(s < MAX_SUM + 1 && s_sq < MAX_SQUARE + 1) || s < 0 || s_sq < 0)
            return MAX_DIGITS;
        if (!s && !s_sq)
            return 0;
        if (cnt_digits[s][s_sq] != -1)
            return cnt_digits[s][s_sq];
        int tmp = MAX_DIGITS;
        for (size_t i = 1; i < 10; ++i)
            tmp = min(tmp, 1 + GetCntDigits(s - i, s_sq - i * i));
        return cnt_digits[s][s_sq] = tmp;
    }


    void PreCalc() {
        memset(cnt_digits, -1, sizeof(cnt_digits));
        cnt_digits[0][0] = 0;
        for (size_t i = 1; i <= MAX_SUM; ++i) {
            for (size_t j = 1; j <= MAX_SQUARE; ++j) {
                if (j >= i) GetCntDigits(i, j);
            }
        }
    }

    void Print(int s, int s_sq) {
        if (!(s < MAX_SUM + 1 && s_sq < MAX_SQUARE + 1) || s < 0 || s_sq < 0)
            return;
        for (; s > 0 && s_sq > 0;) {
            for (int i = 1; i < 10; ++i) {
                if (s >= i && s_sq >= i * i && 1 + cnt_digits[s - i][s_sq - i * i] == cnt_digits[s][s_sq]) {
                    printf("%d", i);
                    s -= i, s_sq -= i * i;
                    break;
                }
            }
        }

    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    timus_1658::PreCalc();

    int N;
    scanf("%d", &N);
    for (; N > 0; --N) {
        int s, s_sq;
        scanf("%d %d", &s, &s_sq);
        if (timus_1658::GetCntDigits(s, s_sq) == timus_1658::MAX_DIGITS)
            printf("No solution");
        else
            timus_1658::Print(s, s_sq);
        printf("\n");
    }
}