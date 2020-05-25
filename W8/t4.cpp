#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <set>
#include <string_view>

using namespace std;


int hash_string(const string_view& s, int multiple) {//code from task
    int rv = 0;
    for (int i = 0; i < s.length(); ++i) {
        rv = multiple * rv + s[i];
    }
    return rv;
}

int cnt_setbits(int n) {
    int cnt = 0;
    while (n != 0) {
        cnt += (n & 1);
        n = n >> 1;
    }
    return cnt;
}


void solve() {
    const int N = 1 << 11;
    int m1 = 7;
    int n;
    cin >> n;

    string s;
    s.reserve(N);

    vector<pair<int, int>> ans;
    ans.reserve(N);
    unordered_map<int, int> d(2 * N);
    unordered_set<string> uniq(2 * N);

    for (int i = 0; i <= N; i++)
        s.push_back('a' + cnt_setbits(i) % 2);

    for (int i = 0; i < N; i += 16) {
        for (int j = 0; i + j <= N; j += 16) {
            string temp = s.substr(i, j);
            if (uniq.count(temp))
                continue;
            int hash = hash_string(temp, m1);

            if (hash == -1608748800)
                ans.emplace_back(i, j);
            if (d.count(hash)) {
                d[hash]++;
            }
            else {
                d[hash] = 1;
            }
            uniq.emplace(move(temp));
        }
    }

    set<pair<int, int>> temp(ans.begin(), ans.end());
    vector<pair<int, int>> to_erase;
    to_erase.reserve(ans.size());

    for (int i = 2; i < 1024; i++) {
        int hash = hash_string(s.substr(temp.begin()->first, temp.begin()->second), i);
        for (auto it = temp.begin(); it != temp.end(); ++it) {
            if (hash != hash_string(s.substr(it->first, it->second), i))
                to_erase.emplace_back(*it);
        }
    }
    for (auto& pair : to_erase)
        temp.erase(pair);


    int count = 0;
    for (const auto& key1 : temp) {
        for (const auto& key2 : temp) {
            for (const auto& key3 : temp) {
                for (const auto& key4 : temp) {
                    for (const auto& key5 : temp) {
                        for (const auto& key6 : temp) {
                            if (count >= n)
                                break;
                            cout << s.substr(key1.first, key1.second)
                                << s.substr(key2.first, key2.second)
                                << s.substr(key3.first, key3.second)
                                << s.substr(key4.first, key4.second)
                                << s.substr(key5.first, key5.second)
                                << s.substr(key6.first, key6.second) << "\n";
                            count++;
                        }
                        if (count >= n)
                            break;
                    }
                    if (count >= n)
                        break;
                }
                if (count >= n)
                    break;
            }
            if (count >= n)
                break;
        }
        if (count >= n)
            break;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt","w", stdout);

    solve();
}