#ifndef TREAP_HPP
#define TREAP_HPP

#include <iostream>
#include <cstdlib>
#include <string>

struct TreapNode {
    int key;
    int priority;
    TreapNode* left;
    TreapNode* right;

    TreapNode(int k) : key(k), priority(rand() % 100000), left(nullptr), right(nullptr) {}
};

class Treap {
private:
    TreapNode* root;

    TreapNode* rightRotate(TreapNode* y);
    TreapNode* leftRotate(TreapNode* x);
    TreapNode* insertAux(TreapNode* root, int key);
    TreapNode* removeAux(TreapNode* root, int key);
    TreapNode* searchAux(TreapNode* root, int key);
    void freeMemory(TreapNode* node);
    void inorderAux(TreapNode* root);
    void generateDOTAux(TreapNode* root, std::ostream& out);

public:
    Treap();
    ~Treap();

    void insert(int key);
    void remove(int key);
    void search(int key);
    void inorder();
    void generateDOT(const std::string& filename);
};

#endif
