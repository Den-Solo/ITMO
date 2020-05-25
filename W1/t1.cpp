#include <fstream>
using namespace  std;

int main(){
    int a,b;
    ifstream inp("input.txt");
    ofstream out("output.txt");
    inp >> a >>b;
    out << a + b;
}
