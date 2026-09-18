#include "splay.hpp"
#include <fstream>

SplayTree::SplayTree() {
    root = nullptr;
}

SplayTree::~SplayTree() {
    freeMemory(root);
}

void SplayTree::freeMemory(SplayNode* node) {
    if (node) {
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }
}

SplayNode* SplayTree::rightRotate(SplayNode* x) {
    SplayNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayNode* SplayTree::leftRotate(SplayNode* x) {
    SplayNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayNode* SplayTree::splay(SplayNode* root, int key) {
    if (root == nullptr || root->key == key)
        return root;

    if (root->key > key) {
        if (root->left == nullptr) return root;

        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }

        return (root->left == nullptr) ? root : rightRotate(root);
    } else {
        if (root->right == nullptr) return root;

        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr)
                root->right = rightRotate(root->right);
        } else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

void SplayTree::search(int key) {
    root = splay(root, key);
    // Silent search for benchmarks
}

void SplayTree::insert(int key) {
    if (root == nullptr) {
        root = new SplayNode(key);
        return;
    }

    root = splay(root, key);

    if (root->key == key) return;

    SplayNode* newNode = new SplayNode(key);
    if (root->key > key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }
    root = newNode;
}

void SplayTree::remove(int key) {
    if (root == nullptr) return;

    root = splay(root, key);

    if (key != root->key) return;

    SplayNode* temp;
    if (root->left == nullptr) {
        temp = root;
        root = root->right;
    } else {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }
    delete temp;
}

void SplayTree::preOrderAux(SplayNode* root) {
    if (root != nullptr) {
        std::cout << root->key << " ";
        preOrderAux(root->left);
        preOrderAux(root->right);
    }
}

void SplayTree::preOrder() {
    preOrderAux(root);
    std::cout << std::endl;
}

void SplayTree::generateDOTAux(SplayNode* root, std::ostream& out) {
    if (root != nullptr) {
        if (root->left) {
            out << "    " << root->key << " -> " << root->left->key << ";\n";
            generateDOTAux(root->left, out);
        }
        if (root->right) {
            out << "    " << root->key << " -> " << root->right->key << ";\n";
            generateDOTAux(root->right, out);
        }
    }
}

void SplayTree::generateDOT(const std::string& filename) {
    std::ofstream out(filename);
    if (out.is_open()) {
        out << "digraph SplayTree {\n";
        if (root == nullptr) {
            out << "    empty [label=\"Empty\"];\n";
        } else if (root->left == nullptr && root->right == nullptr) {
            out << "    " << root->key << ";\n";
        } else {
            generateDOTAux(root, out);
        }
        out << "}\n";
        out.close();
    }
}
