#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>


int main() {
	int num;
	std::priority_queue<unsigned> data;
	scanf("%d", &num);
	
	unsigned a;
	for (auto i = 0; i < num / 2 + 1; ++i) {
		scanf("%d", &a);
		data.push(a);
	}
		
	for (auto i = num / 2 + 1; i < num; ++i) {
		scanf("%d", &a);
		data.push(a);
		data.pop();
	}
	if (num % 2) {
		printf("%u", data.top());
	}
	else {
		a = data.top();
		data.pop();
		printf("%0.1f", data.top() * 0.5 + a * 0.5);
	}

}