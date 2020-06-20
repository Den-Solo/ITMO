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

using namespace std;



FILE* input = stdin;
FILE* output = stdout;

struct Command {
    virtual int execute() = 0;
};

vector<unique_ptr<Command>> prog;
queue<uint16_t> data_;
vector<uint16_t> registers;
unordered_map<string, int> labels;


#define ARITHM auto tmp1 = data_.front(); data_.pop(); \
               auto tmp2 = data_.front(); data_.pop();


struct Sum : Command {
    int execute() override {
        ARITHM;
        data_.push(tmp1 + tmp2);
        return -1;
    }
};
struct Sub : Command {
    int execute() override {
        ARITHM;
        data_.push(tmp1 - tmp2);
        return -1;
    }
};
struct Mul : Command {
    int execute() override {
        ARITHM;
        data_.push(tmp1 * tmp2);
        return -1;
    }
};
struct Div : Command {
    int execute()override {
        ARITHM;
        data_.push(tmp2 != 0 ? tmp1 / tmp2 : 0);
        return -1;
    }
};
struct Mod : Command {
    int execute()override {
        ARITHM;
        data_.push(tmp2 != 0 ? tmp1 % tmp2 : 0);
        return -1;
    }
};
struct MoveToReg : Command{
    char reg;
    MoveToReg(char r) : reg(r) {}
    int execute() override {
        registers[reg - 'a'] = data_.front(); data_.pop();
        return -1;
    }
};
struct MoveFromReg : Command {
    char reg;
    MoveFromReg(char r) : reg(r){}
    int execute() override {
        data_.push(registers[reg - 'a']);
        return -1;
    }
};
struct Print : Command {
    int execute()override {
        fprintf(output, "%hu\n", data_.front());
        data_.pop();
        return -1;
    }
};
struct PrintReg : Command {
    char reg;
    PrintReg(char r) : reg(r) {}
    int execute()override {
        fprintf(output, "%hu\n", registers[reg - 'a']);
        return -1;
    }
};
struct PrintC : Command {
    int execute()override {
        fprintf(output, "%c", static_cast<char>(data_.front() % 256));
        data_.pop();
        return -1;
    }
};
struct PrintRegC : Command {
    char reg;
    PrintRegC(char r) : reg(r) {}
    int execute()override {
        fprintf(output, "%c", static_cast<char>(registers[reg - 'a'] % 256));
        return -1;
    }
};
struct Jump : Command {
    string label;
    Jump(string&& s) : label(move(s)) {}
    int execute()override {
        return labels[label];
    }
};
struct JumpIfReg0 : Command {
    string label;
    char reg;
    JumpIfReg0(string&& s, char r) : label(move(s)), reg(r) {}
    int execute() override {
        return registers[reg - 'a']== 0 ? labels[label] : -1;
    }
};
struct JumpIfRegsEq : Command {
    string label;
    char reg1, reg2;
    JumpIfRegsEq(string&& s, char r1, char r2) : label(move(s)), reg1(r1),reg2(r2) {}
    int execute() override {
        return registers[reg1 - 'a'] == registers[reg2 - 'a'] ? labels[label] : -1;
    }
};
struct JumpIfRegsGr : Command {
    string label;
    char reg1, reg2;
    JumpIfRegsGr(string&& s, char r1, char r2) : label(move(s)), reg1(r1), reg2(r2) {}
    int execute()override {
        return registers[reg1 - 'a'] > registers[reg2 - 'a'] ? labels[label] : -1;
    }
};

struct EndP : Command {
    int execute() override {
        return -2;
    }
};
struct PutNum : Command {
    uint16_t val;
    PutNum(uint16_t n) : val(n) {}
    int execute() override {
        data_.push(val);
        return -1;
    }
};
void Parse(istream& in) {
    string s;
    int str_num = 0;
    while (getline(in, s)) {
        switch (s[0])
        {
        case '+':
            prog.push_back(make_unique<Sum>());
            break;
        case '-':
            prog.push_back(make_unique<Sub>());
            break;
        case '*':
            prog.push_back(make_unique<Mul>());
            break;
        case '/':
            prog.push_back(make_unique<Div>());
            break;
        case '%':
            prog.push_back(make_unique<Mod>());
            break;
        case '>':
            prog.push_back(make_unique<MoveToReg>( s[1] ));
            break;
        case '<':
            prog.push_back(make_unique<MoveFromReg>(s[1]));
            break;
        case 'P':
            if (s.size() == 1)
                prog.push_back(make_unique<Print>());
            else
                prog.push_back(make_unique<PrintReg>(s[1]));
            break;
        case 'C':
            if (s.size() == 1)
                prog.push_back(make_unique<PrintC>());
            else
                prog.push_back(make_unique<PrintRegC>(s[1]));
            break;
        case ':':
            labels[s.substr(1)] = str_num;
            --str_num;
            break;
        case 'J':
            prog.push_back(make_unique<Jump>(s.substr(1)));
            break;
        case 'Z':
            prog.push_back(make_unique<JumpIfReg0>(s.substr(2), s[1]));
            break;
        case 'E':
            prog.push_back(make_unique<JumpIfRegsEq>(s.substr(3),s[1], s[2]));
            break;
        case 'G':
            prog.push_back(make_unique<JumpIfRegsGr>(s.substr(3), s[1], s[2]));
            break;
        case 'Q':
            prog.push_back(make_unique<EndP>());
            break;
        default:
            prog.push_back(make_unique<PutNum>(static_cast<uint16_t>(stoi(s))));
            break;
        }
        ++str_num;
    }
}
void run() {
    int i = 0; 
    while (i < prog.size()) {
        int rval = prog[i]->execute();
        if (rval == -2) break;
        if (rval != -1) i = rval;
        else ++i;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    ifstream in("input.txt");
    //ofstream out("output.txt");
    
    registers.assign('z' - 'a' + 1, 0);
    Parse(in);
    prog;
    run();

    fclose(input);
    fclose(output);
}