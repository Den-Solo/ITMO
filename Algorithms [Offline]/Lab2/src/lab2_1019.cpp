#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <map>

using namespace std;

struct Interval {
	int right;
	bool isBlack;
};
#define iter map<int, Interval>::iterator
#define citer map<int, Interval>::const_iterator

map<int, Interval> segments;


void MergeWithLeft(iter it) {
	while (it != segments.begin()) {
		auto prev_it = prev(it);
		if (prev_it->second.isBlack == it->second.isBlack) {
			prev_it->second = it->second;
			segments.erase(it);
		}
		else
			break;
		it = prev_it;
	}
}
void MergeWithRight(iter it) {
	if (it == segments.end())
		return;
	auto next_it = next(it);
	while (next_it != segments.end()) {
		if (next_it->second.isBlack == it->second.isBlack) {
			it->second = next_it->second;
			segments.erase(next_it);
		}
		else
			break;
		next_it = next(it);
	}
}
void MergeWithBoth(iter it) {
	while (it != segments.begin()) {
		auto prev_it = prev(it);
		if (prev_it->second.isBlack == it->second.isBlack) {
			prev_it->second = it->second;
			segments.erase(it);
		}
		else
			break;
		it = prev_it;
	}
	MergeWithRight(it);
}
void Recolor(int left, int right, bool isBlack) {
	auto seg = segments.find(left);
	if (seg != segments.end()) {
		if (seg->second.right == right) {
			seg->second.isBlack = isBlack;
			MergeWithBoth(seg);
		}
		else if (seg->second.right > right) {
			auto it = segments.emplace(right, seg->second).first;
			seg->second = { right, isBlack };
			MergeWithLeft(seg);
			MergeWithLeft(it);
		}
		else {
			auto tmp = seg->second.right;
			seg->second.isBlack = isBlack;
			Recolor(tmp, right, isBlack);
		}
	}
	else {
		seg = segments.emplace(left, Interval{right, isBlack}).first;
		auto prev_seg = prev(seg);

		if (prev_seg->second.right >= right
			&& prev_seg->second.isBlack == isBlack) {
			segments.erase(seg);
			return;
		}
			
		if (prev_seg->second.right == right) {
			prev_seg->second.right = left;
			MergeWithRight(seg);
		}
		else if (prev_seg->second.right > right) {
			segments.emplace(right, Interval{ prev_seg->second.right, prev_seg->second.isBlack });
			prev_seg->second.right = left;
		}
		else {
			auto tmp = prev_seg->second.right;
			prev_seg->second.right = left;
			Recolor(tmp, right, isBlack);
		}
	}

}

auto FindLongest() {
	auto max = segments.cbegin();
	int max_width = max->second.right - max->first;
	for (auto it = segments.cbegin(); it != segments.cend(); ++it) {
		if (!it->second.isBlack 
			&& it->second.right - it->first > max_width) {
			max_width = it->second.right - it->first;
			max = it;
		}
	}
	return max;
}

int main() {
	segments = { {0, {int(1e9), false}} };

	int num;
	scanf("%d", &num);

	int l, r;
	char color;
	for (auto i = 0; i < num; ++i) {
		scanf("%d%d %c", &l, &r, &color);
		Recolor(l, r, color == 'b');
	}
	citer it = FindLongest();
	printf("%d %d", it->first, it->second.right);
}