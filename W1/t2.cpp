#include <fstream>
#include <stdint.h>
using namespace std;

int main(){
    ifstream ifs("input.txt");
    ofstream ofs("output.txt");
    int64_t a, b;
    ifs >> a >> b;
    ofs << a + b * b;
}