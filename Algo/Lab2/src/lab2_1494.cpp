#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int ball[100'000];
	int current_size = 0;

	bool ok = true;
	int num;
	int max;
	int current;

	scanf("%d", &num);

	scanf("%d", &current);
	max = current;
	for (auto i = 0; i < current - 1; ++i) {
		ball[i] = i + 1;
	}
	current_size += current - 1;

	for (auto i = 1; i < num; ++i) {
		scanf("%d", &current);
		if (current_size != 0) {
			if (ball[current_size - 1] == current) {
				--current_size;
			}
			else if (current > ball[current_size - 1]) {
				int tmp = current_size + current - max - 1;
				for (auto j = current_size; j < tmp; ++j) {
					ball[j] = ++max;
				}
				current_size = tmp;
				++max;
			}
			else {
				ok = false;
				break;
			}
		}
		else if (current > max) {
			int tmp = current_size + current - max - 1;
			for (auto j = current_size; j < tmp; ++j) {
				ball[j] = ++max;
			}
			current_size = tmp;
			++max;
		}
		else {
			ok = false;
			break;
		}
	}
	if (current_size == 0 && ok) {
		printf("%s", "Not a proof");
	}
	else {
		printf("%s", "Cheater");
	}

}