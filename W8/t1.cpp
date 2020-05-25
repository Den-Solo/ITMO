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

using namespace std;

template <class T>
class HashTable {

private:
    vector<forward_list<T>> data_;

public:
    HashTable(size_t size = 1000721) {
        data_.resize(size);
    }
    size_t hasher(const T& val) {
        return val % data_.size();
    }
    typename forward_list<T>::iterator find(const T& key) {
        auto hash = hasher(key);
        return std::find(data_[hash].begin(), data_[hash].end(), key);
    }
    void Add(const T& key) {
        auto it = find(key);
        auto hash = hasher(key);
        if (it == data_[hash].end())
            data_[hash].emplace_front(key);
    }
    void Del(const T& key) {
        auto hash = hasher(key);
        data_[hash].remove(key);
    }
    T* Search(const T& key) {
        auto it = find(key);
        auto hash = hasher(key);
        if (it == data_[hash].end())
            return nullptr;
        return &(*it);
        
    }
};

void solve() {
    int n;
    scanf( "%d\n", &n);

    HashTable<int64_t> t(1'000'721);
    
    for (int i = 0; i < n; ++i) {
         char c;
         int64_t val;
         scanf( "%c %lld\n", &c, &val);
         if (c == 'A') {
             t.Add(val);
         }
         else if (c == 'D') {
             t.Del(val);
         }
         else {
             if (t.Search(val))
                 printf( "Y\n");
             else
                 printf( "N\n");
         }
     }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w", stdout);


    solve();

}