#ifndef SPLAY_HPP
#define SPLAY_HPP

#include <iostream>
#include <string>

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
    void freeMemory(SplayNode* node);
    void preOrderAux(SplayNode* root);
    void generateDOTAux(SplayNode* root, std::ostream& out);

public:
    SplayTree();
    ~SplayTree();

    void insert(int key);
    void search(int key);
    void remove(int key);
    void preOrder();
    void generateDOT(const std::string& filename);
};

#endif
