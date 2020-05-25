#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <utility>
#include <cstring>
#include <cstdint>
#include <inttypes.h>
#include <vector>
#include <algorithm>


using namespace std;


template <class T>
class Stack {
private:
    static const size_t MAX = int(1e6 + 1);
    T data_[MAX];
    size_t top_ = 0;
public:
    void push(int val) { data_[top_++] = val; }
    T top() { return data_[top_ - 1]; }
    bool empty() { return top_ == 0; }
    void pop() {
        if (!empty())
            --top_;
        else
            throw "AAAA";
    }
    void clear() { top_ = 0; }
};

template <class T>
class Queue {
private:
    static const int MAX = int(1e6);
    T data_[MAX];
    size_t head = 0, tail = 0;
public:
    void push(T val) { data_[tail++ % MAX] = val; }
    bool empty() { return head == tail; }
    T pop() { 
        if (!empty()) return data_[head++ % MAX];
        else throw "AAA";
    }
};
const int MAX = int(1e6 + 1);
int A[MAX];
int head = 0;
int tail = 0;

FILE* input = stdin;
FILE* output = stdout;




int main() {
    
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int n;
    fscanf(input, "%d\n", &n);

    Queue<int> q;
    for (auto i = 0; i < n; ++i) {
        char command, dull;
        fscanf(input, "%c%c", &command, &dull);
        if (command == '+') {
            int val;
            fscanf(input, "%d\n", &val);
            q.push(val);
        }
        else {
            fprintf(output, "%d\n", q.pop());
        }
    }

  
    fclose(input);
    fclose(output);
}