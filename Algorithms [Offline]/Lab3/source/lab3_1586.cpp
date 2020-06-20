#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker,"/STACK:32000000")
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iterator>

using namespace std;


const unsigned MOD = unsigned(1e9 + 9);


void EratosthenseSieve(vector<vector<int>>& prefs) {
	// preprocess possible summands
	const int LEFT_ = 100;
	const int RIGHT_ = 999;
	vector<int> range(RIGHT_ + 1);

	iota(range.begin() + 2, range.end(), 2);

	for (int i = 4; i <= RIGHT_; i += 2)
		range[i] = 0;
	//get rid of other numbers
	int p = 3;
	while (1) {
		for (auto i = p * p; i <= RIGHT_; i += 2 * p) {
			range[i] = 0;
		}
		auto it = find_if(range.begin() + p + 1, range.end(), [](auto a) { return a != 0; });
		if (it == range.end())
			break;
		p = (*it);
	}
	for (auto i = LEFT_; i <= RIGHT_; ++i) {
		if (range[i]) {
			prefs[i / 10].emplace_back(i % 10);
		}
	}
}


int64_t cntPrimes[10001][100]; // cntPrimes[num of digits][prefix] = num of primes

int64_t CalcPrimes(int n, int prefix, const vector<vector<int>> & prefs) {
	if (!n) 
		return 1;
	if (prefix < 10) 
		return 0;

	auto& cnt = cntPrimes[n][prefix];

	if (cnt == -1) {
		cnt = 0;

		for (auto it = prefs[prefix].rbegin(); it != prefs[prefix].rend(); advance(it, 1)) {
			cnt = (cnt + CalcPrimes(n - 1, (prefix * 10 + *it) % 100, prefs)) % MOD;
		}
	}

	return cnt;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	vector<vector<int>> prefixes(100);
	EratosthenseSieve(prefixes);

	int n;
	uint64_t count = 0;
	cin >> n;
	
	memset(cntPrimes, -1, sizeof(cntPrimes));

	for (size_t i = 10; i < 100; ++i){
		count = (count + CalcPrimes(n - 2, i, prefixes)) % MOD;
	}

	cout << count;

} 