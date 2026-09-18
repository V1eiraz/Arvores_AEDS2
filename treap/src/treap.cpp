#include "treap.hpp"
#include <fstream>

Treap::Treap() {
    root = nullptr;
}

Treap::~Treap() {
    freeMemory(root);
}

void Treap::freeMemory(TreapNode* node) {
    if (node) {
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }
}

TreapNode* Treap::rightRotate(TreapNode* y) {
    TreapNode* x = y->left;
    TreapNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

TreapNode* Treap::leftRotate(TreapNode* x) {
    TreapNode* y = x->right;
    TreapNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

TreapNode* Treap::insertAux(TreapNode* root, int key) {
    if (!root)
        return new TreapNode(key);

    if (key <= root->key) {
        root->left = insertAux(root->left, key);
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    } else {
        root->right = insertAux(root->right, key);
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }
    return root;
}

void Treap::insert(int key) {
    root = insertAux(root, key);
}

TreapNode* Treap::removeAux(TreapNode* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = removeAux(root->left, key);
    else if (key > root->key)
        root->right = removeAux(root->right, key);
    else {
        if (root->left == nullptr) {
            TreapNode* temp = root->right;
            delete root;
            root = temp;
        } else if (root->right == nullptr) {
            TreapNode* temp = root->left;
            delete root;
            root = temp;
        } else if (root->left->priority < root->right->priority) {
            root = leftRotate(root);
            root->left = removeAux(root->left, key);
        } else {
            root = rightRotate(root);
            root->right = removeAux(root->right, key);
        }
    }
    return root;
}

void Treap::remove(int key) {
    root = removeAux(root, key);
}

TreapNode* Treap::searchAux(TreapNode* root, int key) {
    if (root == nullptr || root->key == key)
        return root;
    
    if (root->key < key)
        return searchAux(root->right, key);
    
    return searchAux(root->left, key);
}

void Treap::search(int key) {
    searchAux(root, key); // Silent search
}

void Treap::inorderAux(TreapNode* root) {
    if (root) {
        inorderAux(root->left);
        std::cout << "key: " << root->key << " | priority: " << root->priority << std::endl;
        inorderAux(root->right);
    }
}

void Treap::inorder() {
    inorderAux(root);
}

void Treap::generateDOTAux(TreapNode* root, std::ostream& out) {
    if (root != nullptr) {
        out << "    " << root->key << " [label=\"" << root->key << "\\n(" << root->priority << ")\"];\n";
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

void Treap::generateDOT(const std::string& filename) {
    std::ofstream out(filename);
    if (out.is_open()) {
        out << "digraph Treap {\n";
        if (root == nullptr) {
            out << "    empty [label=\"Empty\"];\n";
        } else {
            generateDOTAux(root, out);
        }
        out << "}\n";
        out.close();
    }
}
