#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <utility>
#include <cstring>
#include <cstdint>
#include <inttypes.h>
#include <vector>
#include <algorithm>

using namespace std;

int A[int(1e6 + 1)];
int top = 0;

FILE* input = stdin;
FILE* output = stdout;




int main() {
    
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int n;
    fscanf(input, "%d\n", &n);

    for (auto i = 0; i < n; ++i) {
        char command, dull;
        fscanf(input, "%c%c", &command,&dull);
        if (command == '+') {
            fscanf(input, "%d\n", &A[top++]);
        }
        else {
            fprintf(output, "%d\n", A[--top]);
        }
    }
  
    fclose(input);
    fclose(output);
}