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
        Node* prnt = nullptr;
        Node* lc = nullptr;
        Node* rc = nullptr;
        size_t idx;
        uint8_t h = 1;

    public:
        Node() = default;
        Node(Node* p) : prnt(p) {}
        Node(const T& k) : key(k) {}
        Node(T&& k) : key(std::move(k)) {}
        Node(const T& k, Node* p) : key(k), prnt(p) {}
        Node(T&& k, Node* p) : key(std::move(k)), prnt(p) {}
        void Swap(Node* node) {

            if (prnt != node && node->prnt != this) {
                if (lc) lc->prnt = node;
                if (rc) rc->prnt = node;
                if (node->lc) node->lc->prnt = this;
                if (node->rc) node->rc->prnt = this;
                if (prnt && prnt->lc == this) prnt->lc = node;
                else if (prnt && prnt->rc == this) prnt->rc = node;
                if (node->prnt && node->prnt->lc == node) node->prnt->lc == this;
                else if (node->prnt && node->prnt->rc == node) node->prnt->rc == this;
                std::swap(prnt, node->prnt);
                std::swap(lc, node->lc);
                std::swap(rc, node->rc);
                std::swap(h, node->h);
            }
            else {
                Node* t_node = this;
                bool left = false;
                if (node->prnt == this) {
                    t_node = node;
                    node = this;
                }
                if (node->lc == t_node) left = true;

                if (node->prnt)
                    if (node->prnt->lc == node)
                        node->prnt->lc = t_node;
                    else if (node->prnt->rc == node)
                        node->prnt->rc = t_node;
                t_node->prnt = node->prnt;
                node->prnt = t_node;
               
                if (left) {
                    if (t_node->lc) t_node->lc->prnt = node;
                    if (t_node->rc) t_node->rc->prnt = node;
                    if (node->rc) node->rc->prnt = t_node;
                    std::swap(node->rc, t_node->rc);
                    node->lc = t_node->lc;
                    t_node->lc = node;
                }
                else {
                    if (t_node->lc) t_node->lc->prnt = node;
                    if (t_node->rc) t_node->rc->prnt = node;
                    if (node->lc) node->lc->prnt = t_node;
                    std::swap(t_node->lc, node->lc);                  
                    node->rc = t_node->rc;
                    t_node->rc = node;
                }
                std::swap(t_node->h, node->h);
            }
            
        }
    };
private:
    size_t sz_ = 0;
    Node* root_ = nullptr;

    mutable size_t idx_ = 1;
    mutable FILE* output_;

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


    void FixHeight(Node* v) {
        v->h = max(GetHeight(v->lc), GetHeight(v->rc)) + 1;
    }
    void SmallLeftRotate(Node* v) {
        auto b = v->rc;
        b->prnt = v->prnt;
        if (v->prnt)
            if (v->prnt->lc == v)
                v->prnt->lc = b;
            else
                v->prnt->rc = b;
        v->prnt = b;
        v->rc = b->lc;
        b->lc = v;
        FixHeight(v);
        FixHeight(b);
    }
    void SmallRightRotate(Node* v) {
        auto b = v->lc;
        b->prnt = v->prnt;
        if (v->prnt)
            if (v->prnt->lc == v)
                v->prnt->lc = b;
            else 
                v->prnt->rc = b;
        v->prnt = b;
        v->lc = b->rc;
        b->rc = v;
        FixHeight(v);
        FixHeight(b);
    }
    void BigLeftRotate(Node* v) {
        if (GetBalance(v) != 2)
            return;
        if (GetBalance(v->rc) != -1) {
            SmallLeftRotate(v);
            return;
        }
        SmallRightRotate(v->rc);
        SmallLeftRotate(v);
    }
    void BigRightRotate(Node* v) {
        if (GetBalance(v) != -2)
            return;
        if (GetBalance(v->lc) != 1) {
            SmallRightRotate(v);
            return;
        }
        SmallLeftRotate(v->lc);
        SmallRightRotate(v);
    }
    void Balance(Node* v) {
        FixHeight(v);
        if (GetBalance(v) == -2)
            BigRightRotate(v);
        if (GetBalance(v) == 2)
            BigLeftRotate(v);
    }
    void BalanceTree(Node* v) {
        if (!v)
            return;
        Node* prev = v;
        while (v) {
            Balance(v);
            prev = v;
            v = v->prnt;
        }
        root_ = prev;
    }
    uint8_t GetHeight(Node* v) const {
        return v ? v->h : 0;
    }
    int GetBalance(Node* v) const {
        return GetHeight(v->rc) - GetHeight(v->lc);
    }
    size_t CntVertInSubTree(Node* v) const {
        if (v == 0)
            return 0;
        return CntVertInSubTree(v->lc) + CntVertInSubTree(v->rc) + 1;
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
    void DeleteNode(Node* node) {
        if (!node)
            return;

        if (!node->lc && !node->rc) {
            if (node->prnt) {
                if (node->prnt->lc == node)
                    node->prnt->lc = nullptr;
                else if (node->prnt->rc == node)
                    node->prnt->rc = nullptr;
            }
            else
                root_ = nullptr;
            delete node;
        }
    }
    static void DeleteRec(Node* node) {
        if (!node)
            return;
        DeleteRec(node->lc);
        DeleteRec(node->rc);
        if (!node->lc && !node->rc) {
            if (node->prnt) {
                if (node->prnt->lc == node)
                    node->prnt->lc = nullptr;
                else
                    node->prnt->rc = nullptr;
            }
            delete node;
        }
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

    Node* Find(const T& key) const {
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
            return v;
        else
            return prev;
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

    Node* insert(const T& key) {
        if (sz_ == 0) {
            assert(!root_);
            ++sz_;
            root_ = MakeNode(root_, false, key);
            return root_;
        }
        Node* v = Find(key);
        bool left = true;
        if (v->key > key) {
            v->lc = MakeNode(v, left, key);
        }
        else {
            v->rc = MakeNode(v, left = false, key);
        }
        ++sz_;
        BalanceTree(v);
        return left ? v->lc : v->rc;
    }
    void erase(Node* v) {
        if (sz_ == 0)
            return;
        if (!v)
            return;
        Node* new_child;
        if (!v->lc && !v->rc)
            new_child = nullptr;
        else if (!v->lc && v->rc)
            new_child = v->rc;
        else if (v->lc && !v->rc)
            new_child = v->lc;
        else {
            //assert(v->lc);
            Node* rightest_node = v->lc;
            while (rightest_node->rc)
                rightest_node = rightest_node->rc;
            if (v == root_)
                root_ = rightest_node;
            v->Swap(rightest_node);
            erase(v);
            return;
        }
        if (v->prnt)
            if (v->prnt->lc == v)
                v->prnt->lc = new_child;
            else
                v->prnt->rc = new_child;
        if (new_child) {
            new_child->prnt = v->prnt;
            if (!v->prnt)
                root_ = new_child;
        }
            
        BalanceTree(v->prnt);
        DeleteNode(v);
        --sz_;
    }
};

FILE* input = stdin;
FILE* output = stdout;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int n;
    fscanf(input, "%d", &n);
    AVLTree<int> t;

    t.Build(n, input);

    int val;
    fscanf(input, "%d", &val);
    t.insert(val);
    fprintf(output, "%d\n", t.size());
    t.PrintVerts(output);

    fclose(input);
    fclose(output);
}