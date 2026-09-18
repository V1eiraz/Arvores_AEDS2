#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <iostream>
#include <vector>
#include <cmath>

const int K = 2; // Can be changed based on requirement

struct KDNode {
    std::vector<int> point;
    KDNode* left;
    KDNode* right;

    KDNode(std::vector<int> arr) : point(arr), left(nullptr), right(nullptr) {}
};

class KDTree {
private:
    KDNode* root;

    KDNode* insertAux(KDNode* root, std::vector<int> point, unsigned depth);
    bool searchAux(KDNode* root, std::vector<int> point, unsigned depth);
    KDNode* minNode(KDNode* x, KDNode* y, KDNode* z, unsigned d);
    KDNode* findMinAux(KDNode* root, unsigned d, unsigned depth);
    KDNode* removeAux(KDNode* root, std::vector<int> point, unsigned depth);
    void freeMemory(KDNode* node);
    bool arePointsSame(std::vector<int> p1, std::vector<int> p2);
    void inorderAux(KDNode* root);

public:
    KDTree();
    ~KDTree();

    void insert(std::vector<int> point);
    void search(std::vector<int> point);
    void remove(std::vector<int> point);
    void inorder();
};

#endif
