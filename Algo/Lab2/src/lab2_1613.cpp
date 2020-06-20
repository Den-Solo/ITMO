#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

int main() {
	int num1, num2;
	int l, r, amount;
	scanf("%d", &num1);
	
	array<pair<unsigned, unsigned>, 70000> ppl;

	for (auto i = 0; i < num1; ++i) {
		scanf("%u", &amount);
		ppl[i] = {amount, i + 1};
	}

	stable_sort(ppl.begin(), ppl.begin() + num1, [](const auto& a, const auto& b)
	{
		return a.first < b.first;
	});

	scanf("%d", &num2);
	bool done = false;

	string res;
	res.resize(num2);

	for (auto i = 0; i < num2; ++i) {
		done = false;
		scanf("%u%u%u", &l, &r, &amount);

		auto it = lower_bound(ppl.begin(), ppl.begin() + num1,
			pair<unsigned, unsigned>{ amount, l });
		if (it != ppl.begin() + num1 
			&& it->first == amount
			&& it->second >= l
			&& it->second <= r)
			res[i] = '1';
		else
			res[i] = '0';
	}
	printf("%s", res.c_str());
}
