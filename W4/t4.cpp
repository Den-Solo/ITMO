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
    vector<T> data_;
    size_t top_ = 0;
public:
    Stack() {
        data_.resize(MAX);
    }
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
class StackMin {
private:
    static const size_t MAX = int(1e6 + 1);
    vector<pair<T,T>> data_;
    size_t top_ = 0;
public:
    StackMin() {
        data_.resize(MAX);
    }
    bool empty() { return top_ == 0; }
    T GetMin() { 
        return empty() 
            ? numeric_limits<T>::max() 
            : data_[top_ - 1].second; 
    }
    void push(int val) { 
        data_[top_++] = { val, min(val, GetMin()) };
    }
    T top() { return data_[top_ - 1].first; }
    void pop() {
        if (!empty())
            --top_;
        else
            throw "AAAA";
    }
    void clear() { top_ = 0; }
};

/*template <class T>
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
};*/

FILE* input = stdin;
FILE* output = stdout;


int main() {
    
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int n;
    fscanf(input, "%d\n", &n);

    StackMin<int> s1, s2;
    for (auto i = 0; i < n; ++i) {
        char command, dull;
        fscanf(input, "%c%c", &command, &dull);
        if (command == '+') {
            int val;
            fscanf(input, "%d\n", &val);
            s1.push(val);
        }
        else if (command == '-') {
            if (s2.empty()) {
                while (!s1.empty()) {
                    s2.push(s1.top());
                    s1.pop();
                }
            }
            s2.pop();
        }
        else {
            auto a = s1.GetMin();
            auto b = s2.GetMin();
            fprintf(output, "%d\n", min(s1.GetMin() ,s2.GetMin()));
        }
    }

  
    fclose(input);
    fclose(output);
}