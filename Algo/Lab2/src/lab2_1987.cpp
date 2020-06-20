#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <vector>

struct Segment {
	unsigned a, b;
};

using namespace std;

int main() {
	
	unsigned num;
	unsigned num2;
	unsigned point;


	scanf("%u", &num);

	vector<Segment> data(num);

	for (auto i = 0; i < num; ++i) {
		scanf("%u", &(data[i].a));
		scanf("%u", &(data[i].b));
	}

	scanf("%u", &num2);

	vector<int> res;
	res.reserve(num2);

	unsigned current_idx = 0;
	bool done = false;
	for (auto i = 0; i < num2; ++i) {
		scanf("%u", &point);

		done = false;
		while (current_idx != num - 1 &&
			data[current_idx].a < point) ++current_idx;
		while (current_idx != num - 1
			&& data[current_idx].a == point) {
			++current_idx;
			done = true;
		}
		if (done && current_idx != num - 1)
			--current_idx;

		if (data[current_idx].a <= point 
			&& data[current_idx].b >= point) {
			res.push_back(current_idx + 1);
		}
		else {
			unsigned tmp_idx = current_idx;

			while (tmp_idx != 0
				&& (data[tmp_idx].b < point
				|| data[tmp_idx].a > point)) --tmp_idx;

			if (data[tmp_idx].a <= point
				&& data[tmp_idx].b >= point) {
				res.push_back(tmp_idx + 1);
			}
			else {
				res.push_back(-1);
			}
			
		}
	}
	for (const auto i : res) {
		printf("%d\n", i);
	}
}
