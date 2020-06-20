#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:2000000")


#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

class Tree {
private:
	vector<vector<pair<int, int>>> con_matrix;
	vector<vector<int>> parent;
	size_t  log_;
	vector<int> depth;
	vector<size_t> weight;
	vector<bool> visited;

private:
	void depth_search_construct(int vert) {
		visited[vert] = true;
		for (int i = 0; i < con_matrix[vert].size(); i++) {
			int v = con_matrix[vert][i].first;

			if (visited[v])
				continue;

			parent[v][0] = vert;
			weight[v] = weight[vert] + con_matrix[vert][i].second;
			depth[v] = depth[vert] + 1;
			depth_search_construct(v);
		}
	}
	void read_edges() {
		for (int i = 0; i < con_matrix.size() - 1; i++) {
			int v1, v2, w;
			scanf("%d%d%d", &v1, &v2, &w);
			con_matrix[v1].push_back({ v2,w });
			con_matrix[v2].push_back({ v1,w });
		}

		{
			depth_search_construct(0);
			for (int j = 1; j < log_; j++) {
				for (int i = 0; i < con_matrix.size(); i++) {
					parent[i][j] = parent[parent[i][j - 1]][j - 1];
				}
			}
		}
	}
	
	int lca(int v1, int v2) {
		if (depth[v1] > depth[v2])
			swap(v1, v2);
		for (int i = log_ - 1; i >= 0; --i) {
			if (depth[parent[v2][i]] - depth[v1] >= 0)
				v2 = parent[v2][i];
		}
		
		if (v1 == v2)
			return v1;

		for (int i = log_ - 1; i >= 0; --i) {
			if (parent[v1][i] != parent[v2][i]) {
				v1 = parent[v1][i];
				v2 = parent[v2][i];
			}
		}
		return parent[v1][0];
	}
public:
	Tree(size_t size) {
		con_matrix	.resize(size);
		depth		.resize(size);
		weight		.resize(size);
		visited		.assign(size, false);
		log_ = static_cast<size_t>(log2(static_cast<double>(size))) + 2;
		parent.resize(size);
		for (auto i = 0; i < size; ++i) {
			parent[i].assign(log_,i);
		}

		read_edges();
	}
	size_t GetWeight(int a, int b) {
		return a == b 
			? 0 
			: weight[a] + weight[b] - 2 * weight[lca(a, b)];
	}
	
};
int main() {
	int num;
	scanf("%d", &num);

	Tree tr(num);

	int num_of_requests;
	scanf("%d", &num_of_requests);

	for (int i = 0; i < num_of_requests; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%u\n", tr.GetWeight(a, b));
	}
	
}