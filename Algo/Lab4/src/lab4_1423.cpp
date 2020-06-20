#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:3200000")

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;


namespace timus_1423 {

    const int alphabet = 255 - 33 + 1;
    const int MAX = 250'000 + 1;

    int m;
    int n;

    char t[MAX];
    char s[MAX * 2];

    vector<int> pref;

    void buildPref() {
        pref.resize(m + 1);

        int i = 1, j = 0;
        while (i < m) {
            if (t[i] == t[j]) {
                pref[i + 1] = j + 1;
                ++i, ++j;
            }
            else {
                if (j > 0)
                    j = pref[j];
                else {
                    pref[i + 1] = 0;
                    ++i;
                }
            }
        }
    }


    int find() {//knuth-morris-pratt algorithm

        buildPref();
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (s[i] == t[j]) {
                ++i, ++j;
            }
            else {
                if (j > 0)
                    j = pref[j];
                else
                    ++i;
            }
        }
        if (j == m)
            return i - m;
        else
            return -1;
    }





	void solve() {
	
        scanf("%d", &n);

        scanf("%s\n%s", s, t);
        m = strlen(t);
        n = m * 2;
        

        memcpy(s + m, s, m);
        s[n + 1] = '\0';

        int res = (find());
        if (res == -1) {
            printf("-1");
            return;
        }
        if (!res) {
            printf("0");
            return;
        }
        res -= m;
        if (res < 0) res = -res;
        printf("%d", res);

	}

};


int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	//freopen("input.txt", "r", stdin);

	timus_1423::solve();

}