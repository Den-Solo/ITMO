#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:320000")

//#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;


namespace timus_1102 {



	char s[int(1e7)];

	const char p[] = "put";

	void solve() {
	

		int n;
		scanf("%d", &n);


		
		int last = -1;
		for (auto i = 0; i < n; ++i) {
			scanf("%s", s);
			const int sz = strlen(s);
						
			int last_j = sz - 1;

			bool ok = true;
			for (int j = sz - 1; j > -1;) {
								
				if (j - 2 > -1 && s[j] == 't' && s[j - 1] == 'u') {
					if (s[j - 2] == 'p') {
						if (j - 4 > -1 && s[j - 3] == 'n' && s[j - 4] == 'i') {
							last = j - 4;
							j -= 5;
						}
						else if (j - 5 > -1 && s[j - 3] == 't' && s[j - 4] == 'u' && s[j - 5] == 'o') {
							last = j - 5;
							j -= 6;
						}
					}
					else if (s[j - 2] == 'o') {
						last = j - 2;
						j -= 3;
					}
				}
				else if (j - 2 > -1 && s[j] == 'e' && s[j - 1] == 'n' && s[j - 2] == 'o') {
					last = j - 2;
					j -= 3;
				}
				else if (j - 1 > -1 && s[j] == 'n'){
					if (s[j - 1] == 'i') {
						last = j - 1;
						j -= 2;
					}
					else if (j - 4 > -1 &&  s[j - 1] == 'o' && s[j - 2] == 't' && s[j - 3] == 'u' && s[j - 4] == 'p') {
						last = j - 4;
						j -= 5;
					}
				}
				if (last_j == j) {
					ok = false;
					break;
				}
				else {
					last_j = j;
				}
			}
			ok = ok && (last == 0);
			if (ok)
				printf("YES\n");
			else
				printf("NO\n");
		}
	}

};

int main() {

	//ios_base::sync_with_stdio(false);
	//cin.tie(nullptr);
	//cout.tie(nullptr);

	//freopen("input.txt", "r", stdin);

	timus_1102::solve();
}