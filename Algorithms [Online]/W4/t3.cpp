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

    Stack<char> s;
    for (auto i = 0; i < n; ++i) {
        char par;
        bool ok = true;
        bool ended = false;
        while (1) {
            if (fscanf(input, "%c", &par) == EOF
                || par == '\n') {
                ended = true;
                break;
            }
                
            if (par == '[' || par == '(') {
                s.push(par);
            }
            else if (!s.empty()) {
                if ((s.top() == '[' && par == ']')
                    || s.top() == '(' && par == ')')
                    s.pop();
                else {
                    ok = false; 
                    break;
                }
                   
            }
            else {
                ok = false;
                break;
            }  
        }
        if (ok && s.empty())
            fprintf(output, "YES\n");
        else {
            char c;
            while (!ended) {
                if (fscanf(input, "%c", &c) == EOF
                    || c == '\n')
                    break;
            }
            fprintf(output, "NO\n");
        }
        s.clear();
    }
  
    fclose(input);
    fclose(output);
}