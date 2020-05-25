#define _CRT_SECURE_NO_WARNINGS
//#pragma comment(linker,"/STACK:32000000")

#include <cstdio>
#include <iostream>
#include <fstream>
#include <utility>
#include <cstring>
#include <string>
#include <cstdint>
#include <inttypes.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <queue>
#include <stack>
#include <cassert>
#include <forward_list>
#include <list>


using namespace std;

struct Node {
    string key;
    string val;
    Node* prev = nullptr;
    Node* next = nullptr;
    bool deleted = false;
};


class LinkedHashTable {

private:

    vector<Node> data_;
    vector<size_t> powers_1;
    static const size_t hash_val_1 = 29;
    static const size_t hash_val_2 = 997;
    Node* last_ = nullptr;

private:

    static void CalcPowers(size_t hash_val, vector<size_t>& powers) {
        powers.resize(20);
        powers[0] = 1;
        for (size_t i = 1; i < 20; ++i) {
            powers[i] = hash_val * powers[i - 1];
        }
    }
    size_t hasher1(const string& val) {
        size_t hsh = 0;
        for (size_t i = 0; i < val.size(); ++i)
            hsh += val[i] * powers_1[i];
        return hsh & ((data_.size() >> 1) - 1);
    }
    size_t hasher2(const string& val) {
        size_t hsh = 0;
        for (size_t i = 0; i < std::min(val.size(), size_t(5)); ++i)
            hsh += val[i] * powers_1[19u - i];
        return (hsh & (hash_val_2 - 1)) + 1;
    }

public:
    LinkedHashTable(size_t size = (1 << 21)) {
        data_.resize(size);
        CalcPowers(hash_val_1, powers_1);
    }
    
    pair<Node*, Node*> Find(const string& key) {
        auto h1 = hasher1(key);
        auto h2 = hasher2(key);

        bool del_found = false;
        size_t deleted = 0;

        while (data_[h1].key.size() || data_[h1].deleted) {
            if (data_[h1].key == key) {
                return { &data_[h1], nullptr };
            }
            if (!del_found && data_[h1].deleted) deleted = h1, del_found = true;
            h1 += h2;
            if (h1 >= data_.size()) h1 %= data_.size();
        }
        return { &data_[h1], (del_found ? &data_[deleted] : nullptr) };
    }


    void put(string&& key, string&& val) {
        auto [node, del] = Find(key);
        
        if (node && !del && node->key.size()) {
            node->val = move(val);
            return;
        }

        Node* elem = (del ? del : node);
        if (elem == nullptr)
            throw runtime_error("not enough space\n");
        *elem = { move(key),move(val),last_,nullptr, false };
        if (last_) last_->next = elem;
        last_ = elem;
    }

    Node* get(const string& key) {
        auto [node, del] = Find(key);
        if (!del && node->key.size())
            return node;
        return nullptr;
    }
    Node* prev(const string& key) {
        Node* n = get(key);
        if (n) return n->prev;
        return nullptr;
    }
    Node* next(const string& key) {
        Node* n = get(key);
        if (n) return n->next;
        return nullptr;
    }
    void del(const string& key) {
        auto [node, del] = Find(key);
        if (!del && node->key == key) {
            if (node->prev) node->prev->next = node->next;
            if (node->next) node->next->prev = node->prev;
            if (last_ == node) last_ = node->prev;
            node->deleted = true;
            node->key.clear();
        }
    }
};



#define ANSWER_(method) {                            \
    auto res = t.method(key);                        \
    if (!res)   printf("<none>");                    \
    else        printf("%s", res->val.data());       \
    printf("\n");                                    \
}

void solve() {
    int n;
    scanf("%d\n", &n);

    LinkedHashTable t;
    

    char command[21];
    char key[21];
    char val[21];
    char c;
    for (int i = 0; i < n; ++i) {
        scanf("%s %s", command, key);
        c = (command[0] == 'p' ? command[1] : command[0]);
        switch (c)
        {
        case 'g':
            ANSWER_(get);
            break;
        case 'n':
            ANSWER_(next);
            break;
        case 'd':
            t.del(key);
            break;
        case 'r':
            ANSWER_(prev);
            break;
        default:
            scanf("%s", val);
            t.put(key, val);
            break;
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w", stdout);


    solve();

}



