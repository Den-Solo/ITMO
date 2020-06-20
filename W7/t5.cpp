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

using namespace std;

template <class T>
class AVLTree {
private:
    struct Node {
    public:
        T key;
        Node* lc = nullptr;
        Node* rc = nullptr;
        size_t idx;
        uint8_t h = 1;
        Node* prnt;
    public:
        Node(const T& k) : key(k) {}
        Node(T&& k) : key(std::move(k)) {}
        Node(Node* p) : prnt(p) {}
        Node(const T& k, Node* p) : key(k), prnt(p) {}
    };
private:
    size_t sz_ = 0;
    Node* root_ = nullptr;

    mutable size_t idx_ = 1;
    mutable FILE* output_;

    Node* swapped;
 
    void FixHeight(Node* v) {
        if (!v)
            return;
        v->h = max(GetHeight(v->lc), GetHeight(v->rc)) + 1;
    }


    uint8_t GetHeight(Node* v) const {
        return v ? v->h : 0;
    }


    int GetBalance(Node* v) const {
        return v ? GetHeight(v->rc) - GetHeight(v->lc) : 0;
    }


    Node* LeftRotate_(Node* q) {
        Node* p = q->rc;
        q->rc = p->lc;
        p->lc = q;
        FixHeight(q);
        FixHeight(p);
        return p;
    }
   
    Node* RightRotate_(Node* p) {
        Node* q = p->lc;
        p->lc = q->rc;
        q->rc = p;
        FixHeight(p);
        FixHeight(q);
        return q;
    }


    Node* Balance_(Node* p) {
        if (!p)
            return p;
        FixHeight(p);
        if (GetBalance(p) == 2) {
            if (GetBalance(p->rc) == -1)
                p->rc = RightRotate_(p->rc);
            return LeftRotate_(p);
        }
        else if (GetBalance(p) == -2) {
            if (GetBalance(p->lc) == 1)
                p->lc = LeftRotate_(p->lc);
            return RightRotate_(p);
        }
        return p;
    }


    uint8_t CalcHeights(Node* v) {
        if (!v)
            return 0;
        size_t l = 0, r = 0;
        if (v->lc)
            l = CalcHeights(v->lc);
        if (v->rc)
            r = CalcHeights(v->rc);
        return v->h = max(l, r) + 1;
    }
    
    size_t CntVertInSubTree(Node* v) const {
        if (v == 0)
            return 0;
        return CntVertInSubTree(v->lc) + CntVertInSubTree(v->rc) + 1;
    }

   
    static void DeleteRec(Node* node) {
        if (!node)
            return;
        DeleteRec(node->lc);
        DeleteRec(node->rc);
        delete node;
    }


    void GiveIdxs(Node* n) {
        if (!n)
            return;
        n->idx = idx_++;
        GiveIdxs(n->lc);
        GiveIdxs(n->rc);
    }
    void PrintVert(Node* node) {
        if (!node)
            return;
        fprintf(output_, "%d ", node->key);
        fprintf(output_, "%u ", node->lc ? node->lc->idx : 0);
        fprintf(output_, "%u\n", node->rc ? node->rc->idx : 0);
        PrintVert(node->lc);
        PrintVert(node->rc);
    }
    Node* Find_(const T& key) const {
        if (!root_)
            return nullptr;
        Node* v = root_;
        Node* prev = v;
        bool equal_key = false;
        while (1) {
            if (v->key == key) {
                equal_key = true;
                break;
            }
            if (v->key > key) {
                prev = v;
                v = v->lc;
            }
            else if (v->key < key) {
                prev = v;
                v = v->rc;
            }
            if (!v)
                break;
        }
        if (equal_key)
            return nullptr;
        else
            return prev;
    }


   
    Node* MakeNode(Node* node, bool isLeftChild) {
        if (!node) {
            assert(!root_);
            return root_ = new Node(node);
        }
        if (isLeftChild)
            return node->lc = new Node(node);
        else
            return node->rc = new Node(node);
    }
    Node* MakeNode(Node* node, bool isLeftChild, const T& key) {
        if (!node) {
            assert(!root_);
            return root_ = new Node(key, node);
        }
        if (isLeftChild)
            return node->lc = new Node(key, node);
        else
            return node->rc = new Node(key, node);
    }
    Node* MakeNode(Node* node, bool isLeftChild, T&& key) {
        if (!node) {
            assert(!root_);
            return root_ = new Node(std::move(key), node);
        }
        if (isLeftChild)
            return node->lc = new Node(std::move(key), node);
        else
            return node->rc = new Node(std::move(key), node);
    }

    Node* FindMaxInLeft(Node* p) {
        return p->rc ? FindMaxInLeft(p->rc) : p;
    }
    Node* RemoveMax(Node* p) {
        if (!p->rc)
            return p->lc;
        p->rc = RemoveMax(p->rc);
        return Balance_(p);
    }
public:

    AVLTree() = default;
    ~AVLTree() {
        DeleteRec(root_);
    }

    void Build(size_t size, FILE* in) {
        if (!size)
            return;
        sz_ = size;
        std::vector<Node*> tmp(size + 1, nullptr);
        tmp[1] = root_ = MakeNode(root_, false);
        for (int i = 1; i <= sz_; ++i) {
            Node* p = tmp[i];
            size_t l, r;
            fscanf(in, "%d %u %u", &p->key, &l, &r);
            if (l)
                tmp[l] = p->lc = MakeNode(p, true);
            if (r)
                tmp[r] = p->rc = MakeNode(p, false);
        }
        CalcHeights(root_);
    }


    bool CheckTree(Node* root, T l, T r) const {
        if (root == 0)
            return true;

        if (root->key <= l || root->key >= r)
            return false;

        return
            CheckTree(root->lc, l, root->key)
            && CheckTree(root->rc, root->key, r);
    }


    void PrintVerts(FILE* out) {
        GiveIdxs(root_);
        output_ = out;
        if (!root_)
            return;
        PrintVert(root_);
    }
  
    size_t size() const {
        return sz_;
    }
    Node* Insert(Node* p, const T& key) {
        if (!p) {
            ++sz_;
            return new Node(key);
        }
        if (p->key == key)
            return p;
        if (key < p->key)
            p->lc = Insert(p->lc, key);
        else
            p->rc = Insert(p->rc, key);
        return Balance_(p);
    }
    void Insert(const T& key) {
        if (!root_) {
            root_ = new Node(key);
            ++sz_;
            return;
        }
        if (root_->key == key)
            return;
        if (key < root_->key)
            root_->lc = Insert(root_->lc, key);
        else
            root_->rc = Insert(root_->rc, key);
        root_ = Balance_(root_);
    }
    Node* Remove(Node* p, const T& key) {
        if (!p) return nullptr;
        if (key < p->key)
            p->lc = Remove(p->lc, key);
        else if (key > p->key)
            p->rc = Remove(p->rc, key);
        else {
            Node* p_lc = p->lc;
            Node* p_rc = p->rc;
            delete p;
            --sz_;
            if (!p_lc) return p_rc;
            Node* max_l = FindMaxInLeft(p_lc);
            max_l->lc = RemoveMax(p_lc);
            max_l->rc = p_lc;
            return Balance_(max_l);
        }
        return Balance_(p);
    }
    void Remove(const T& key) {
        root_ = Remove(root_, key);
    }
    Node* SwapWithRight(Node* p, Node* to_swap) {
        if (!(p->rc)) {
            std::swap(p->key, to_swap->key);
            p = Erase(p, p->key);
        }
        else {
            p->rc  = SwapWithRight(p->rc, to_swap);
        }
        return Balance_(p);
    }
    Node* Erase(Node* p, const T& key) {
        if (!p) return nullptr;
        if (p->key > key)
            p->lc = Erase(p->lc, key);
        else if (p->key < key)
            p->rc = Erase(p->rc, key);
        else {                          //p->key == key
            if (!p->lc && !p->rc) {
                delete p;
                --sz_;
                return nullptr;
            }
            else if (!p->lc && p->rc) {
                auto save = p->rc;
                delete p;
                --sz_;
                return save;
            }
            else {
                p->lc = SwapWithRight(p->lc, p);
            }
        }
        return Balance_(p);
    }
    void Erase(const T& k) {
        root_ = Balance_(Erase(root_, k));
    }
    int GetBalanceRoot() {
        return GetBalance(root_);
    }
    Node* Find(const T& key) const {
        if (!root_)
            return nullptr;
        Node* v = root_;
        bool equal_key = false;
        while (1) {
            if (v->key == key) {
                equal_key = true;
                break;
            }
            if (v->key > key) {
                v = v->lc;
            }
            else if (v->key < key) {
                v = v->rc;
            }
            if (!v)
                break;
        }
        if (equal_key)
            return v;
        else
            return nullptr;
    }
};

void solve() {
    int n;
    scanf( "%d\n", &n);
    AVLTree<int> t;

    //t.Build(n, input);

    //int val;
    //fscanf(input, "%d", &val);
    //t.Remove(val);
    //fprintf(output, "%d\n", t.size());
    //t.PrintVerts(output);

    for (int i = 0; i < n; ++i) {
         char c;
         int val;
         scanf( "%c %d\n", &c, &val);
         //printf("%d %c %d    ||", i + 1, c, val);
         if (c == 'A') {
             t.Insert(val);
             printf("%d\n", t.GetBalanceRoot());
         }
         else if (c == 'D') {
             t.Erase(val);
             printf("%d\n", t.GetBalanceRoot());
         }
         else {
             if (t.Find(val))
                 printf( "%c\n", 'Y');
             else
                 printf( "%c\n", 'N');
         }
         //fprintf(output, "%d---%u\n", i + 1,t.size());
     }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w", stdout);


    solve();

}