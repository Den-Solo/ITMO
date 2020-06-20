#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <unordered_map>

using namespace std;

struct Interval {
    int l, r;
    bool isOdd;
};

unordered_map<int, Interval> intervals;

bool process(int left, int right, bool isOdd) {
    auto it = intervals.find(left);
    if (it == intervals.end()) {
        intervals[left] = { left, right, isOdd };
        return true; //OK
    }
    else {
        if (it->second.r == right) {
            return it->second.isOdd == isOdd;
        }
        else if (it->second.r < right) {
            return process(it->second.r + 1, right,
                it->second.isOdd != isOdd);
        }
        else {
            return process(right + 1, it->second.r,
                it->second.isOdd != isOdd);
        }
    }
}
int main() {
    while (1) {
        int size, qnum;
        scanf("%d", &size);
  
        if (size == -1)
            break;

        scanf("%d", &qnum);

        if (qnum == 0) {
            printf("%d\n", 0);
            continue;
        }

        intervals.clear();
        intervals.reserve(qnum);

        for (auto i = 0; i < qnum; ++i) {
            int left, right;
            bool isOdd;
            char parity[6];
            scanf("%d%d%s", &left, &right, parity);

            isOdd = parity[0] == 'o';
            if ((left < 1 || right > size) 
                || !process(left, right, isOdd)) {
                printf("%d\n", i);
                while (++i != qnum) {
                    scanf("%d%d%s", &left, &right, parity);
                }
                break;
            }
            if (i == qnum - 1)
                printf("%d\n", qnum);
        }
    }
}