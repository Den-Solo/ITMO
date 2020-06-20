#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>

using namespace std;


class DSU {
private:
	vector<size_t> parents_;
	vector<size_t> rank_;
	size_t num_of_sets;
private:
	size_t GetSetByVert(size_t v) {
		if (v != parents_[v])
			parents_[v] = GetSetByVert(parents_[v]);
		return parents_[v];
	}
public:
	DSU(size_t size) : num_of_sets(size) {
		parents_.resize(size);
		rank_.resize(size);
		for (int i = 0; i < size; i++)
			parents_[i] = i;
	}
	void MergeSets(size_t v1, size_t v2) {
		v1 = GetSetByVert(v1);
		v2 = GetSetByVert(v2);
		if (v1 == v2)	
			return;

		if (rank_[v1] > rank_[v2]) {
			parents_[v2] = v1;
		}
		else {
			parents_[v1] = v2;
			if (rank_[v1] == rank_[v2])
				++rank_[v2];
		}
		--num_of_sets;
	}
	size_t GetNumOfSets()const {
		return num_of_sets;
	}
};

vector<unsigned> vertices1;
vector<unsigned> vertices2;
vector<unsigned> edges_to_remove;
vector<bool> deleted_edges;

int main() {

	unsigned num_of_vertices;
	unsigned num_of_edges;
	unsigned n_edges_to_remove;

	scanf("%u%u", &num_of_vertices, &num_of_edges);
	vertices1.resize(num_of_edges);
	vertices2.resize(num_of_edges);
	deleted_edges.resize(num_of_edges);

	for (auto i = 0; i < num_of_edges; i++)
		scanf("%u%u", &vertices1[i], &vertices2[i]);

	scanf("%u", &n_edges_to_remove);
	edges_to_remove.resize(n_edges_to_remove + 1);
	

	for (int i = 0; i < n_edges_to_remove; i++) {
		scanf("%u", &edges_to_remove[i]);
		deleted_edges[--edges_to_remove[i]] = true;
	}

	DSU dsu(num_of_vertices + 1);
	
	for (int i = 0; i < num_of_edges; i++) {
		if (deleted_edges[i] == false) {
			dsu.MergeSets(vertices1[i], vertices2[i]);
		}
	}

	edges_to_remove[n_edges_to_remove] = dsu.GetNumOfSets() - 1; 
	for (int i = n_edges_to_remove - 1; i > 0; i--) {
		dsu.MergeSets(vertices1[edges_to_remove[i]], vertices2[edges_to_remove[i]]);
		edges_to_remove[i] = dsu.GetNumOfSets() - 1;
	}

	for (int i = 1; i <= n_edges_to_remove; i++)
		printf("%u ", edges_to_remove[i]);

}