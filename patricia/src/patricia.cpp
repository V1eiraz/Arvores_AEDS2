#include "patricia.hpp"

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
            // Find common prefix length
            while (j < (int)child->edgeLabel.length() && i + j < (int)key.length() && child->edgeLabel[j] == key[i + j]) {
                j++;
            }

            if (j > 0) {
                matchFound = true;
                if (j == (int)child->edgeLabel.length()) {
                    // Fully matched child edge, continue down
                    current = child;
                    i += j;
                } else {
                    // Partial match, split the edge
                    std::string commonPrefix = child->edgeLabel.substr(0, j);
                    std::string remainingChildLabel = child->edgeLabel.substr(j);
                    std::string remainingKey = key.substr(i + j);

                    PatriciaNode* splitNode = new PatriciaNode(remainingChildLabel, child->isEndOfWord);
                    splitNode->children = child->children; // move old children

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
            // No matching child edge, add a new child
            PatriciaNode* newNode = new PatriciaNode(key.substr(i), true);
            current->children.push_back(newNode);
            return;
        }
    }
    // If key is fully consumed
    current->isEndOfWord = true;
}

void PatriciaTree::search(std::string key) {
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
                    // Mismatched before consuming full child edge
                    std::cout << "Key " << key << " not found." << std::endl;
                    return;
                }
            }
        }
        if (!matchFound) {
            std::cout << "Key " << key << " not found." << std::endl;
            return;
        }
    }
    if (current->isEndOfWord) {
        std::cout << "Key " << key << " found." << std::endl;
    } else {
        std::cout << "Key " << key << " not found." << std::endl;
    }
}

void PatriciaTree::remove(std::string key) {
    // Simplified removal for Patricia/Radix Tree
    // To properly remove and compact, it requires more logic, 
    // but setting isEndOfWord = false is a common simple approach.
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
                    return; // Not found
                }
            }
        }
        if (!matchFound) return;
    }
    if (current->isEndOfWord) {
        current->isEndOfWord = false;
        // Optional: compact the tree if this node has only 1 child and is not end of word.
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
