#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <algorithm>

using namespace std;

namespace timus_1073 {

	int n;

	vector<int> preproc() {// preprocess possible summands
		int sq = sqrt(n);
		vector<int> sqrs(sq + 1);
		for (auto i = 0; i <= sq; ++i) {
			sqrs[i] = i * i;
		}
		return sqrs;
	}
	void solve() {

		
		cin >> n;
		vector<int> sqrs = preproc();

		vector<int> minPapers(n + 1, numeric_limits<int>::max() - 1); //sum => num of papers
		minPapers[0] = 0;
		if (n > 0) minPapers[1] = 1;
		for (auto i = 2; i <= n; ++i) {
			for (auto j : sqrs) {
				if (j > i)
					break;
				minPapers[i] = min(minPapers[i], minPapers[i - j] + 1);
			}
		}
		cout << minPapers[n];
	}
}




int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	timus_1073::solve();
}