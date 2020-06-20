#include <fstream>
#include <stdint.h>
using namespace std;

struct Node {
    int a, b;
};

int main() {
    int a[5000];
    Node b[5000];
    int bidx = 0;
    
    ifstream ifs("input.txt");
    ofstream ofs("output.txt");

    int num;
    ifs >> num;
    for (auto i = 0; i < num; ++i) {
        ifs >> a[i];
    }

    
    int min;
    for (auto i = 0; i < num - 1; ++i) {
        min = i;
        for (auto j = i + 1; j < num; ++j) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(a[i], a[min]);
            b[bidx] = { i + 1, min + 1 };
            ++bidx;
        }

    }
    for (auto i = 0; i < bidx; ++i) {
        ofs << "Swap elements at indices "
            << b[i].a << " and " << b[i].b <<".\n";
    }
    ofs << "No more swaps needed.\n";
    for (auto i = 0; i < num; ++i) {
        ofs << a[i] << ' ';
    }
}