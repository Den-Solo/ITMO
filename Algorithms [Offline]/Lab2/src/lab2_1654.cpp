#include <string>
#include <iostream>
#include <stack>

using namespace std;

struct Node {
	unsigned idx;
	char c;
};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string cipher;
	getline(cin, cipher);

	stack<Node> box;

	for (unsigned i = 0; i < cipher.size() - 1; ++i) {
		if (cipher[i] == cipher[i + 1]) {
			cipher[i] = cipher[i + 1] = '0';
			++i;
		}
		else if (!box.empty() && box.top().c == cipher[i]) {
			auto tmp = box.top();
			cipher[tmp.idx] = cipher[i] = '0';
			box.pop();
		}
		else {
			box.push({ i ,cipher[i] });
		}
	}
	if (!box.empty() && cipher[cipher.size() - 1] == box.top().c) {
		auto tmp = box.top();
		cipher[tmp.idx] = cipher[cipher.size() - 1] = '0';
	}

	string res;
	res.reserve(cipher.size());
	for (unsigned i = 0; i < cipher.size(); ++i) {
		if (cipher[i] != '0')
			res += cipher[i];
	}
	cout << res;
}
