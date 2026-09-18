#ifndef PATRICIA_HPP
#define PATRICIA_HPP

#include <iostream>
#include <string>
#include <vector>

struct PatriciaNode {
    std::string edgeLabel;
    bool isEndOfWord;
    std::vector<PatriciaNode*> children;

    PatriciaNode(std::string label, bool end) : edgeLabel(label), isEndOfWord(end) {}
};

class PatriciaTree {
private:
    PatriciaNode* root;

    void freeMemory(PatriciaNode* node);
    void printAux(PatriciaNode* node, std::string prefix, int level);
    void generateDOTAux(PatriciaNode* node, std::ostream& out, int& nodeCount, int currentId);

public:
    PatriciaTree();
    ~PatriciaTree();

    void insert(std::string key);
    bool search(std::string key);
    void remove(std::string key);
    void print();
    void generateDOT(const std::string& filename);
};

#endif
