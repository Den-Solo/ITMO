#include <fstream>
#include <stdint.h>
using namespace std;

int main() {
    int a[1000];
    int b[1000];
    ifstream ifs("input.txt");
    ofstream ofs("output.txt");

    int num;
    ifs >> num;
    for (auto i = 0; i < num; ++i) {
        ifs >> a[i];
    }

    b[0] = 1;
    int val;
    for (auto i = 1; i < num; ++i) {
        val = a[i];
        int j = i - 1;
        while (val < a[j] && j >= 0) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = val;
        b[i] = j + 2;
    }
    for (auto i = 0; i < num; ++i) {
        ofs << b[i] << ' ';
    }
    ofs << '\n';
    for (auto i = 0; i < num; ++i) {
        ofs << a[i] << ' ';
    }
}