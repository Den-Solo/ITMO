#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


class SegmentTreeMax {
private:
	size_t size_;
	vector<int> data;
public:
	SegmentTreeMax() = default;
	SegmentTreeMax(size_t size) : size_(size) {
		data.resize(2 * size);
	}
	void resize(size_t size) {
		size_ = size;
		data.resize(2 * size);
	}
	void inc(size_t i, int val) {
		i += size_;
		data[i] += val;
		for (i >>= 1; i; i >>= 1)
			data[i] = std::max(data[2 * i],data[2 * i + 1 ]);
	}
	int getMax(size_t left, size_t right) {
		int N = size_;
		int res = 0;
		for (left += N, right += N; left <= right; left /= 2, right /= 2) {
			if (left % 2 == 1)
				res = max(res, data[left++]);
			if (right % 2 == 0)
				res = max(res, data[right--]);
		}
		return res;
	}
};

class Tree {
	
private:
	size_t size_;
	vector<int> parent;

	vector<int> cnt_children;
	vector<int> hl_roots; //heavy-light decomposition roots
	unsigned hl_tree_cnt = 0;
	vector<int> path_idx;
	vector<int> pos_in_stree;
	vector<int> cnt_verts_in_path;
	vector<SegmentTreeMax> strees;

	int time = 0;
	vector<int> time_in, time_out;

public:
	vector<vector<int>> con_matrix;

private:
	void dfs_construct(int vert, int prnt) {
		time_in[vert] = time;
		++time;
		parent[vert] = prnt;
		cnt_children[vert] = 1;
		for (auto v : con_matrix[vert]) {
			if (v != prnt) {
				dfs_construct(v, vert);
				cnt_children[vert] += cnt_children[v];
			}
		}
		time_out[vert] = time;
		++time;
	}
	int new_path(int vert) {
		hl_roots[hl_tree_cnt] = vert;
		return hl_tree_cnt++;
	}
	void make_heavy_light_dec(int vert, int idx) {
		int x;
		path_idx[vert] = idx;
		pos_in_stree[vert] = cnt_verts_in_path[idx]++;
		for(const auto x : con_matrix[vert])
			if (x  != parent[vert])
				make_heavy_light_dec(
					x
					, 2 * cnt_children[x] > cnt_children[vert] 
					? idx 
					: new_path(x)
				);
	}
	bool IsAncestor(int i, int j) {
		return time_in[i] <= time_in[j] 
			&& time_out[j] <= time_out[i];
	}

public:
	Tree(size_t size) : size_(size) {
		parent				.resize(size_);
		time_in				.resize(size_);
		time_out			.resize(size_);
		path_idx			.resize(size_);
		pos_in_stree		.resize(size_);
		cnt_verts_in_path	.resize(size_);
		cnt_children		.resize(size_);
		hl_roots			.resize(size_); 
		con_matrix			.resize(size_);
	}
	void init(int root = 0) {
		dfs_construct(root, -1);// -1 is for absence of parent
		make_heavy_light_dec(0, new_path(0));
		strees.resize(hl_tree_cnt);
		for (auto i = 0; i < hl_tree_cnt; ++i) {
			strees[i].resize(cnt_verts_in_path[i]);
		}
	}
	void inc(int vert, int val) {
		strees[path_idx[vert]].inc(pos_in_stree[vert], val);
	}
	int get(int i, int l, int r) {
		return strees[i].getMax(l, r);;
	}
	int get_max(int v1, int v2) {
		int res = 0;
		for(auto i = 0; i < 2;++i) {
			int v;
			while (!IsAncestor((v = hl_roots[path_idx[v1]]), v2)) {
				res = max(res, get(path_idx[v1], 0, pos_in_stree[v1]));
				v1 = parent[v];
			}
			std::swap(v1, v2);
		}
		if (pos_in_stree[v1] < pos_in_stree[v2]) {
			return max(res, 
				get(path_idx[v1], pos_in_stree[v1], pos_in_stree[v2]));
		}
		else {
			return max(res,
				get(path_idx[v1], pos_in_stree[v2], pos_in_stree[v1]));
		}
	}
};

int main() {
	int num;
	scanf("%d", &num);

	Tree tree(num);

	for (auto i = 0; i < num - 1; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		--v1;
		--v2;
		tree.con_matrix[v1].push_back(v2);
		tree.con_matrix[v2].push_back(v1);
	}
	
	tree.init();
	
	int q_num;
	scanf("%d", &q_num);

	for (auto i = 0; i < q_num; ++i) {
		char command;
		scanf("\n%c", &command);
		if (command == 'I') {
			int vert, val;
			scanf("%d%d", &vert, &val);
			--vert;
			tree.inc(vert, val);
		}
		else {
			int v1, v2;
			scanf("%d%d", &v1, &v2);
			--v1;
			--v2;
			printf("%d\n",tree.get_max(v1, v2));
		}
	}
}