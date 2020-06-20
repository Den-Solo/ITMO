#define _CRT_SECURE_NO_WARNINGS
#define ll long long
#include <stdio.h>
#include <vector>

using namespace std;


class FenwickTree {
private:
    vector<ll> data_;
    size_t size_;
public:
    FenwickTree(size_t size) : size_(size) {
        data_.resize(size_);
    }
    inline static size_t _F(size_t idx) {
        return idx & (idx + 1);
        
    }
    inline static size_t _K(size_t idx) {
        return idx | (idx + 1);
    }
    void add(int x, long long val) {
        for (int i = x; i < size_; i = _K(i)) 
            data_[i] += val;
    }
    void sub(int x, long long val) {
        for (int i = x; i < size_; i = _K(i))
            data_[i] -= val;
    }
    ll prefix_sum(int x) {
        ll res = 0;
        for (int i = x; i >= 0; i = _F(i) - 1)
            res += data_[i];
        return res;
    }

    int get_sum(int x0, int x) {
        return prefix_sum(x) - prefix_sum(x0 - 1);
    }
};

const int MAX = 300'000;
std::vector<int> Devisors[MAX + 1]; // The divisors of each number
ll preset_vals[MAX + 1];
ll additions[MAX + 1];

int main()
{
    int num;
    scanf("%d", &num);
    
    FenwickTree tree(num + 1);

    {// preprocess divisors for each num
        for (int i = 1; i <= num; i++)
            for (int j = 1, k; (k = j * i) <= num; j++)
                Devisors[k].push_back(i);
    }


    for (int i = 1; i <= num; i++)
        scanf("%d", &preset_vals[i]);
    
    int q_num;
    scanf("%d", &q_num);

    for (auto i = 0; i < q_num; ++i) {
        int command;
        scanf("%d", &command);
        if (command == 1) {
            int idx;
            scanf("%d", &idx);
            
            ll res = preset_vals[idx];
            for (const auto d : Devisors[idx]) {
                res += tree.prefix_sum(d);
            }
            printf("%lld\n", res);
        }
        else {
            int l, r, d;
            scanf("%d%d%d", &l, &r, &d);
            tree.add(l, d);
            tree.sub(r + 1, d);
        }
    }
}