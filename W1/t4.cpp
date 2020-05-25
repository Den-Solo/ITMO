#include <fstream>
#include <stdint.h>
using namespace std;

struct Node {
    float key;
    int idx;
};

int main() {
    Node a[10000];
    
    ifstream ifs("input.txt");
    ofstream ofs("output.txt");

    int num;
    ifs >> num;
    for (auto i = 0; i < num; ++i) {
        ifs >> a[i].key;
        a[i].idx = i + 1;
    }

    
    Node val;
    for (auto i = 1; i < num; ++i) {
        val = a[i];
        int j = i - 1;
        while (val.key < a[j].key && j >= 0) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = val;
    }
    ofs << a[0].idx << ' ' << a[num / 2].idx << ' ' << a[num - 1].idx;
}