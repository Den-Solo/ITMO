#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

namespace timus_1297 {

	vector<pair<int, int>> pals;
	vector<int> lens;

    void solve() {

		string s;
		cin >> s;

		for (auto i = 0; i < s.size(); ++i) {

			{//even
				int j = i, k = i + 1;
				while (j != -1 && k != s.size() && s[j] == s[k]) {
					--j, ++k;
				}
				++j, --k;
				pals.emplace_back(j, k);
				lens.emplace_back(k - j + 1);
			}
			{//odd
				int j = i - 1, k = i + 1;
				while (j != -1 && k != s.size() && s[j] == s[k]) {
					--j, ++k;
				}
				++j, --k;
				pals.emplace_back(j, k);
				lens.emplace_back(k - j + 1);
			}
		}

		int k = 0; int m = -1;
		for (int j = 0; j < lens.size(); ++j)
			if (lens[j] > m) m = lens[j], k = j;

		cout << s.substr(pals[k].first, lens[k]);
    }

};

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	//freopen("in.txt", "r", stdin);

	timus_1297::solve();
}