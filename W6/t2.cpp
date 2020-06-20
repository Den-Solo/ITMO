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


int n;
double heights[1001];
double eps = 1e-9;

template <class T>
bool Eq(T a, T b) {
    return abs(a - b) <= eps;
}
template <class T>
bool Less(T a, T b) {
    return a < b && !Eq(a,b);
}
template <class T>
bool More(T a, T b) {
    return a > b && !Eq(a, b);
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    

    fscanf(input, "%d %lf", &n, &heights[0]);

    double l = 0;
    double r = heights[0];
    bool fall = false;
    heights[n - 1] = 0;
    double res = 1e9;

    while (Less(l , r)) {
        heights[1] = (l + r) / 2;
        fall = false;
        for (int i = 2; i < n; ++i) {
            heights[i] = 2 * heights[i - 1] - heights[i - 2] + 2;
            if (!More(heights[i],0.0)) {
                fall = true;
                break;
            }
        }
        if (fall)
            l = heights[1];
        else
            r = heights[1];
        if (More(heights[n - 1], 0.0))
            res = min(res, heights[n - 1]);
    }

    fprintf(output, "%0.7lf", res);

    fclose(input);
    fclose(output);
}