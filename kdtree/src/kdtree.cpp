#include "kdtree.hpp"

KDTree::KDTree() {
    root = nullptr;
}

KDTree::~KDTree() {
    freeMemory(root);
}

void KDTree::freeMemory(KDNode* node) {
    if (node) {
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }
}

KDNode* KDTree::insertAux(KDNode* root, std::vector<int> point, unsigned depth) {
    if (root == nullptr)
        return new KDNode(point);

    unsigned cd = depth % K;

    if (point[cd] < root->point[cd])
        root->left = insertAux(root->left, point, depth + 1);
    else
        root->right = insertAux(root->right, point, depth + 1);

    return root;
}

void KDTree::insert(std::vector<int> point) {
    if (point.size() != K) {
        std::cerr << "Error: Point dimension must be " << K << std::endl;
        return;
    }
    root = insertAux(root, point, 0);
}

bool KDTree::arePointsSame(std::vector<int> p1, std::vector<int> p2) {
    for (int i = 0; i < K; ++i)
        if (p1[i] != p2[i])
            return false;
    return true;
}

bool KDTree::searchAux(KDNode* root, std::vector<int> point, unsigned depth) {
    if (root == nullptr)
        return false;
    if (arePointsSame(root->point, point))
        return true;

    unsigned cd = depth % K;

    if (point[cd] < root->point[cd])
        return searchAux(root->left, point, depth + 1);

    return searchAux(root->right, point, depth + 1);
}

void KDTree::search(std::vector<int> point) {
    if (searchAux(root, point, 0)) {
        std::cout << "Point (";
        for (int i = 0; i < K; i++) std::cout << point[i] << (i == K - 1 ? "" : ", ");
        std::cout << ") found." << std::endl;
    } else {
        std::cout << "Point (";
        for (int i = 0; i < K; i++) std::cout << point[i] << (i == K - 1 ? "" : ", ");
        std::cout << ") not found." << std::endl;
    }
}

KDNode* KDTree::minNode(KDNode* x, KDNode* y, KDNode* z, unsigned d) {
    KDNode* res = x;
    if (y != nullptr && y->point[d] < res->point[d])
        res = y;
    if (z != nullptr && z->point[d] < res->point[d])
        res = z;
    return res;
}

KDNode* KDTree::findMinAux(KDNode* root, unsigned d, unsigned depth) {
    if (root == nullptr)
        return nullptr;

    unsigned cd = depth % K;

    if (cd == d) {
        if (root->left == nullptr)
            return root;
        return findMinAux(root->left, d, depth + 1);
    }

    return minNode(root,
                   findMinAux(root->left, d, depth + 1),
                   findMinAux(root->right, d, depth + 1), d);
}

KDNode* KDTree::removeAux(KDNode* root, std::vector<int> point, unsigned depth) {
    if (root == nullptr)
        return nullptr;

    unsigned cd = depth % K;

    if (arePointsSame(root->point, point)) {
        if (root->right != nullptr) {
            KDNode* min = findMinAux(root->right, cd, depth + 1);
            root->point = min->point;
            root->right = removeAux(root->right, min->point, depth + 1);
        }
        else if (root->left != nullptr) {
            KDNode* min = findMinAux(root->left, cd, depth + 1);
            root->point = min->point;
            root->right = removeAux(root->left, min->point, depth + 1);
            root->left = nullptr;
        }
        else {
            delete root;
            return nullptr;
        }
    }
    else if (point[cd] < root->point[cd]) {
        root->left = removeAux(root->left, point, depth + 1);
    }
    else {
        root->right = removeAux(root->right, point, depth + 1);
    }
    return root;
}

void KDTree::remove(std::vector<int> point) {
    root = removeAux(root, point, 0);
}

void KDTree::inorderAux(KDNode* root) {
    if (root != nullptr) {
        inorderAux(root->left);
        std::cout << "(";
        for (int i = 0; i < K; i++) std::cout << root->point[i] << (i == K - 1 ? "" : ", ");
        std::cout << ")" << std::endl;
        inorderAux(root->right);
    }
}

void KDTree::inorder() {
    inorderAux(root);
}
