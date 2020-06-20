#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <array>

using namespace std;


FILE* input = stdin;
FILE* output = stdout;


namespace timus_1009_1 {

	int K, N;
	unsigned CalcAnswer(int val) {
		if (!val)
			return 1;
		if (val == 1)
			return K - 1;
		return  (CalcAnswer(val - 1) + CalcAnswer(val - 2)) * (K - 1);
	}

	void solve() {
		cin >> N >> K;
		cout << CalcAnswer(N) << '\n';
	}
}

namespace timus_1009_2 {

	void solve() {
		uint64_t n, k;
		cin >> n >> k;

		array<int,21u> data;
		data[0] = 1;
		data[1] = k - 1;
		for (auto i = 2; i <= n; ++i) {
			data[i] = (data[i - 1] + data[i - 2]) * (k - 1);
		}
		cout << data[n];
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	//input = fopen("input.txt", "r");
	//output = fopen("output.txt", "w");



	timus_1009_1::solve();
	//timus_1009_2::solve();


	fclose(input);
	fclose(output);
}