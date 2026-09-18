#include "patricia.hpp"
#include <fstream>

PatriciaTree::PatriciaTree() {
    root = new PatriciaNode("", false);
}

PatriciaTree::~PatriciaTree() {
    freeMemory(root);
}

void PatriciaTree::freeMemory(PatriciaNode* node) {
    if (!node) return;
    for (PatriciaNode* child : node->children) {
        freeMemory(child);
    }
    delete node;
}

void PatriciaTree::insert(std::string key) {
    PatriciaNode* current = root;
    int i = 0;
    while (i < (int)key.length()) {
        bool matchFound = false;
        for (PatriciaNode* child : current->children) {
            int j = 0;
            while (j < (int)child->edgeLabel.length() && i + j < (int)key.length() && child->edgeLabel[j] == key[i + j]) {
                j++;
            }

            if (j > 0) {
                matchFound = true;
                if (j == (int)child->edgeLabel.length()) {
                    current = child;
                    i += j;
                } else {
                    std::string commonPrefix = child->edgeLabel.substr(0, j);
                    std::string remainingChildLabel = child->edgeLabel.substr(j);
                    std::string remainingKey = key.substr(i + j);

                    PatriciaNode* splitNode = new PatriciaNode(remainingChildLabel, child->isEndOfWord);
                    splitNode->children = child->children; 

                    child->edgeLabel = commonPrefix;
                    child->isEndOfWord = false;
                    child->children.clear();
                    child->children.push_back(splitNode);

                    if (remainingKey.empty()) {
                        child->isEndOfWord = true;
                    } else {
                        PatriciaNode* newNode = new PatriciaNode(remainingKey, true);
                        child->children.push_back(newNode);
                    }
                    return;
                }
                break;
            }
        }
        if (!matchFound) {
            PatriciaNode* newNode = new PatriciaNode(key.substr(i), true);
            current->children.push_back(newNode);
            return;
        }
    }
    current->isEndOfWord = true;
}

bool PatriciaTree::search(std::string key) {
    PatriciaNode* current = root;
    int i = 0;
    while (i < (int)key.length()) {
        bool matchFound = false;
        for (PatriciaNode* child : current->children) {
            int j = 0;
            while (j < (int)child->edgeLabel.length() && i + j < (int)key.length() && child->edgeLabel[j] == key[i + j]) {
                j++;
            }
            if (j > 0) {
                if (j == (int)child->edgeLabel.length()) {
                    current = child;
                    i += j;
                    matchFound = true;
                    break;
                } else {
                    return false;
                }
            }
        }
        if (!matchFound) {
            return false;
        }
    }
    return current->isEndOfWord;
}

void PatriciaTree::remove(std::string key) {
    PatriciaNode* current = root;
    int i = 0;
    while (i < (int)key.length()) {
        bool matchFound = false;
        for (PatriciaNode* child : current->children) {
            int j = 0;
            while (j < (int)child->edgeLabel.length() && i + j < (int)key.length() && child->edgeLabel[j] == key[i + j]) {
                j++;
            }
            if (j > 0) {
                if (j == (int)child->edgeLabel.length()) {
                    current = child;
                    i += j;
                    matchFound = true;
                    break;
                } else {
                    return; 
                }
            }
        }
        if (!matchFound) return;
    }
    if (current->isEndOfWord) {
        current->isEndOfWord = false;
        if (current->children.size() == 1) {
            PatriciaNode* child = current->children[0];
            current->edgeLabel += child->edgeLabel;
            current->isEndOfWord = child->isEndOfWord;
            current->children = child->children;
            delete child;
        }
    }
}

void PatriciaTree::printAux(PatriciaNode* node, std::string prefix, int level) {
    if (node->isEndOfWord && level > 0) {
        std::cout << prefix << std::endl;
    }
    for (PatriciaNode* child : node->children) {
        printAux(child, prefix + child->edgeLabel, level + 1);
    }
}

void PatriciaTree::print() {
    printAux(root, "", 0);
}

void PatriciaTree::generateDOTAux(PatriciaNode* node, std::ostream& out, int& nodeCount, int currentId) {
    if (node->isEndOfWord && currentId != 0) {
        out << "    node" << currentId << " [label=\"\", style=filled, fillcolor=lightgrey, shape=doublecircle];\n";
    } else if (currentId != 0) {
        out << "    node" << currentId << " [label=\"\", shape=circle];\n";
    }

    for (PatriciaNode* child : node->children) {
        int childId = ++nodeCount;
        out << "    node" << currentId << " -> node" << childId << " [label=\"" << child->edgeLabel << "\"];\n";
        generateDOTAux(child, out, nodeCount, childId);
    }
}

void PatriciaTree::generateDOT(const std::string& filename) {
    std::ofstream out(filename);
    if (out.is_open()) {
        out << "digraph PatriciaTree {\n";
        if (root == nullptr || root->children.empty()) {
            out << "    empty [label=\"Empty\"];\n";
        } else {
            int nodeCount = 0;
            out << "    node0 [label=\"root\", shape=rect];\n";
            generateDOTAux(root, out, nodeCount, 0);
        }
        out << "}\n";
        out.close();
    }
}
