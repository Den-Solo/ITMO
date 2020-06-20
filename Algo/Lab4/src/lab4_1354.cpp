#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>

using namespace std;



pair<int, int> GetTwoMax(const vector<pair<int,int>>& v) {
	if (!v.size())
		return { -1, -1 };
	if (v.size() == 1)
		return { v[0].second - v[0].first, -1 };

	int max1 = v[0].second - v[0].first;//greater
	int max2 = v[1].second - v[1].first;
	if (max2 > max1)
		swap(max1, max2);
	for (size_t i = 2; i < v.size(); ++i) {
		int l = v[i].second - v[i].first;
		if (l > max1) {
			max2 = max1;
			max1 = l;
		}
		else if (l > max2)
			max2 = l;
	}
	return { max1, max2 };

}
namespace timus_1354 {

	vector<pair<int, int>> pals;

    void solve() {

		string s;
		cin >> s;

		if (s.size() == 1) {
			cout << s << s;
			return;
		}
		for (auto i = 0; i < s.size(); ++i) {

			{//even
				int j = i, k = i + 1;
				while (j != -1 && k != s.size() && s[j] == s[k]) {
					--j, ++k;
				}
				++j, --k;
				if (k == s.size() - 1 && j < k) {
					pals.emplace_back(j, k);
				}
			}
			{//odd
				int j = i - 1, k = i + 1;
				while (j != -1 && k != s.size() && s[j] == s[k]) {
					--j, ++k;
				}
				++j, --k;
				if (k == s.size() - 1 && j < k) {
					pals.emplace_back(j, k);
				}
			}
		}


		cout << s;

		int k{ 0 };
		if (pals.empty()) {
			k = 1;
		}
		else {
		
			auto r = GetTwoMax(pals);
			int ml = r.first;
			int ml_p = r.second;

			if (ml == s.size() - 1) {
				if (ml_p != -1) {
					k = ml_p + 1;
				}
				else {
					k = 1;
				}
			}
			else {
				k = ml + 1;
			}
		}

		for (int j = s.size() - k - 1; j > -1; --j) {
			cout << s[j];
		}
    }

};

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	//freopen("in.txt", "r", stdin);

	timus_1354::solve();
}