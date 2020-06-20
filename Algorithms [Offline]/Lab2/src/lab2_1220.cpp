#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <stack>

using namespace std;


const unsigned MAX = 140500;
const uint16_t MAX_STACKS_NUM = 1000;
const uint8_t block_size = 16;
const uint16_t LAST_BLOCK_IDX = MAX / block_size;

unsigned stacks[MAX];
int idxs[MAX_STACKS_NUM];

stack<uint16_t> emptied_blocks;
uint16_t next_empty_block;


inline int stack_offset(int block_num) {
	return block_num * block_size;
}
inline int IsBeginOfBlock(int idx) {
	return !(idx % block_size);
}
inline int GetBlockNum(int idx) {
	return idx / block_size;
}

int main() {

	int num;
	int stack_idx, val;
	char command[6];

	scanf("%d", &num);


	for (auto i = 0; i < MAX; i += block_size) {
		stacks[i] = -1;
	}
	for (auto i = 0; i < MAX_STACKS_NUM; ++i) {
		idxs[i] = i * block_size + 1;
	}
	next_empty_block = MAX_STACKS_NUM;

	for (auto i = 0; i < num; ++i) {
		fgets(command, 2, stdin);
		fgets(command, 5, stdin);

		if (command[1] == 'U') {
			scanf("%d%d", &stack_idx, &val);
			--stack_idx;
			if (!IsBeginOfBlock(idxs[stack_idx])) {
				stacks[idxs[stack_idx]] = val;
				++idxs[stack_idx];
			}
			else {
				if (next_empty_block != LAST_BLOCK_IDX) {
					int offset = stack_offset(next_empty_block);
					++next_empty_block;
					stacks[offset] = idxs[stack_idx] - 1;
					idxs[stack_idx] = ++offset;
					stacks[idxs[stack_idx]] = val;
					++idxs[stack_idx];
				}
				else if (!emptied_blocks.empty()) {
					int empt = emptied_blocks.top();
					emptied_blocks.pop();
					int offset = stack_offset(empt);
					stacks[offset] = idxs[stack_idx] - 1;
					idxs[stack_idx] = ++offset;
					stacks[idxs[stack_idx]] = val;
					++idxs[stack_idx];
				}
			}
		}
		else {
			scanf("%d", &stack_idx);
			--stack_idx;
			if (!IsBeginOfBlock(idxs[stack_idx] - 2)) {
				--idxs[stack_idx];
				printf("%u\n", stacks[idxs[stack_idx]]);
			}
			else {
				--idxs[stack_idx];
				printf("%u\n", stacks[idxs[stack_idx]]);
				if (idxs[stack_idx] - 1 != -1) {
					--idxs[stack_idx];
					if (GetBlockNum(idxs[stack_idx]) == next_empty_block - 1) {
						auto tmp = idxs[stack_idx];
						--next_empty_block;
						idxs[stack_idx] = stacks[idxs[stack_idx]] + 1;
						stacks[tmp] = -1;
					}
					else {
						emptied_blocks.push(GetBlockNum(idxs[stack_idx]));
						auto tmp = idxs[stack_idx];
						idxs[stack_idx] = stacks[idxs[stack_idx]] + 1;
						stacks[tmp] = -1;
					}
				}
			}
		}
	}
}