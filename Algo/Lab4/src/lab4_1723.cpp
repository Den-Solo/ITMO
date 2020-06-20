#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

namespace timus_1723 {

    const int alpabet = 26;

    void solve() {

        string str;
        vector<int> cnt(alpabet);

        cin >> str;

        for (auto i = 0; i != str.size(); ++i)
            ++cnt[str[i] - 'a'];

        int res{ 0 };

        for (auto i = 1; i != alpabet; ++i)
            if (cnt[i] > cnt[res]) 
                res = i;


        cout << static_cast<char>(res + 'a');

    }

};

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	//freopen("in.txt", "r", stdin);

	timus_1723::solve();
}