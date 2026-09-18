#ifndef SPLAY_HPP
#define SPLAY_HPP

#include <iostream>

struct SplayNode {
    int key;
    SplayNode* left;
    SplayNode* right;

    SplayNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    SplayNode* root;

    SplayNode* rightRotate(SplayNode* x);
    SplayNode* leftRotate(SplayNode* x);
    SplayNode* splay(SplayNode* root, int key);
    
    void preOrderAux(SplayNode* root);
    void freeMemory(SplayNode* node);

public:
    SplayTree();
    ~SplayTree();

    void insert(int key);
    void search(int key);
    void remove(int key);
    void preOrder();
};

#endif
