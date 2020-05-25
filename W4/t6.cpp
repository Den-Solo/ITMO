#define _CRT_SECURE_NO_WARNINGS
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


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    
    int n;
    fscanf(input, "%d", &n);

    stack<int> data_;
    char command[12];
    for (auto i = 0; i < n; ++i) {
        fscanf(input, "%s", command);
        if (command[0] == '+') {
            int v1 = data_.top(); data_.pop();
            int v2 = data_.top(); data_.pop();
            data_.push(v1 + v2);
        }
        else if (command[0] == '-') {
            int v1 = data_.top(); data_.pop();
            int v2 = data_.top(); data_.pop();
            data_.push(v2 - v1);
        }
        else if (command[0] == '*') {
            int v1 = data_.top(); data_.pop();
            int v2 = data_.top(); data_.pop();
            data_.push(v1 * v2);
        }
        else {
            data_.push(stoi(command));
        }
    }
    fprintf(output, "%d", data_.top());
    fclose(input);
    fclose(output);
}