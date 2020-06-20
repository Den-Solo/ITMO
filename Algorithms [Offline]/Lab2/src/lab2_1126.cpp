#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
class SegmentTreeMax {
private:
	std::vector<T> data_;
	size_t size_;

private:
	void build(const vector<T>& preset,
		size_t vert, size_t left, size_t right
	) {
		if (left == right) {
			data_[vert] = preset[left];
		}
		else {
			auto mid = (left + right) / 2;
			build(preset, vert * 2, left, mid);
			build(preset, vert * 2 + 1, mid + 1, right);
			data_[vert] = std::max(data_[vert * 2], data_[vert * 2 + 1]);
		}
	}
	T get_max(size_t vert, size_t left, size_t right, size_t qleft, size_t qright) {
		if (qleft > qright)
			return 0;
		if (left == qleft && right == qright)
			return data_[vert];
		size_t mid = (left + right) / 2;
		return std::max(
			get_max(vert * 2, left, mid, qleft, std::min(mid, qright))
			, get_max(vert * 2 + 1, mid + 1, right, std::max(mid + 1, qleft), qright)
		);
	}
public:
	SegmentTreeMax(const vector<T>& preset) {
		size_ = preset.size();
		data_.resize(size_ * 4);
		build(preset, 1, 0, size_ - 1);
	}
	T GetMax(size_t qleft, size_t qright) {
		return get_max(1, 0, size_ - 1, qleft, qright);
	}
};
int main() {
	int m;
	scanf("%d", &m);

	int val;
	vector<int> values;
	values.reserve(25'000);
	while (scanf("%d", &val) && val != -1) {
		values.push_back(val);
	}
	SegmentTreeMax<int> st(values);

	for (auto i = 0, j = m - 1; j < values.size(); ++i, ++j) {
		printf("%d\n", st.GetMax(i, j));
	}
}
