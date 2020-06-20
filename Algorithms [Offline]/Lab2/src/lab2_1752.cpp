#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct FarthestNode {
	int vert;
	int lenght;
};
const int MAX = 20'000;
const int LGN = 16;

vector<int> graph[MAX];
FarthestNode fn = { 0,0 };

int parent1[LGN][MAX];
int depth1[MAX] = { 0 };
int parent2[LGN][MAX];
int depth2[MAX] = { 0 };
bool visited1[MAX] = { 0 };
bool visited2[MAX] = { 0 };

int uplift1(int v, int num_steps) {
	for (int i = 0; i < LGN; i++) {
		if (num_steps % 2) 
			v = parent1[i][v];
		if (v == -1)
			break;
		num_steps /= 2;
	}
	return v;
}
int uplift2(int v, int num_steps) {
	for (int i = 0; i < LGN; i++) {
		if (num_steps % 2) 
			v = parent2[i][v];
		if (v == -1)
			break;
		num_steps /= 2;
	}
	return v;
}
void dfs_farthest(int vert) {
	visited1[vert] = true;
	for (int i = 0; i < graph[vert].size(); i++) {
		int v = graph[vert][i];
		if (visited1[v])
			continue;
		depth1[v] = depth1[vert] + 1;
		if (depth1[v] > fn.lenght) {
			fn.lenght = depth1[v];
			fn.vert = v;
		}
		dfs_farthest(v);
	}
}
void depth_search_construct1(int vert) {
	visited1[vert] = true;
	for (int i = 0; i < graph[vert].size(); i++) {
		int v = graph[vert][i];
		if (visited1[v])
			continue;
		parent1[0][v] = vert;
		depth1[v] = depth1[vert] + 1;
		if (depth1[v] > fn.lenght) {
			fn.lenght = depth1[v];
			fn.vert = v;
		}
		depth_search_construct1(v);
	}
}
void depth_search_construct2(int vert) {
	visited2[vert] = true;
	for (int i = 0; i < graph[vert].size(); i++) {
		int v = graph[vert][i];
		if (visited2[v])
			continue;
		parent2[0][v] = vert;
		depth2[v] = depth2[vert] + 1;
		depth_search_construct2(v);
	}
}

int main()
{
	memset(parent1, -1, sizeof(parent1));
	memset(parent2, -1, sizeof(parent2));

	int num, q_num;
	int farthest1, farthest2, max_dist;
	scanf("%d%d", &num, &q_num);

	for (int i = 0; i < num - 1; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		--v1;
		--v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}

	{//preprocessing
		//step find two farthest nodes
		dfs_farthest(0);
		farthest1 = fn.vert;
		fn = { 0, 0 };
		memset(visited1, 0, sizeof visited1);
		memset(depth1, 0, sizeof visited1);

		depth_search_construct1(farthest1); 
		depth_search_construct2(fn.vert);
		
		//find 2^nth parents
		for (int i = 1; i < LGN; i++) {
			for (int j = 0; j < num; j++) {//correction
				if (parent1[i - 1][j] != -1) {
					parent1[i][j] = parent1[i - 1][parent1[i - 1][j]];
				}
			}
		}
		for (int i = 1; i < LGN; i++) {
			for (int j = 0; j < num; j++) {//correction
				if (parent2[i - 1][j] != -1) {
					parent2[i][j] = parent2[i - 1][parent2[i - 1][j]];
				}
			}
		}
	}


	vector<unsigned> answ(q_num);

	for (int i = 0; i < q_num; i++) {
		int vert_q, len_q;
		scanf("%d%d", &vert_q, &len_q);
		--vert_q;
		if (len_q > fn.lenght) {
			continue;
		}
		int r = uplift1(vert_q, len_q);
		if (r != -1)
			answ[i] = r + 1;
		else {
			r = uplift2(vert_q, len_q);
			if (r != -1)
				answ[i] = r + 1;
		}

	}
	for (const auto i : answ) {
		printf("%d\n", i);
	}
}