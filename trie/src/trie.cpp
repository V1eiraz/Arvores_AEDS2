#include "trie.hpp"
#include <fstream>

Trie::Trie()
{
    root = new TrieNode;
}
Trie::~Trie()
{
    CleanMemory(root);
}

void Trie::CleanMemory(TrieNode *node)
{
    if (node == nullptr)
        return;

    for (int i = 0; i < Alphabet; i++)
    {
        if (node->sons[i] != nullptr)
        {
            CleanMemory(node->sons[i]);
        }
    }
    delete node;
}

void Trie::Insert(std::string key)
{
    TrieNode *current = root;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (index < 0 || index >= Alphabet) continue; // safety check

        if (current->sons[index] == nullptr)
        {
            current->sons[index] = new TrieNode();
        }
        current = current->sons[index];
    }
    current->end = true;
}

bool Trie::search(std::string key)
{
    TrieNode *current = root;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (index < 0 || index >= Alphabet) {
            return false;
        }

        if (current->sons[index] == nullptr)
        {
            return false;
        }
        current = current->sons[index];
    }
    return (current != nullptr && current->end);
}

bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < Alphabet; i++)
        if (root->sons[i] != nullptr)
            return false;
    return true;
}

TrieNode* removeAux(TrieNode* root, std::string key, int depth)
{
    if (!root)
        return nullptr;

    if (depth == (int)key.size()) {
        if (root->end)
            root->end = false;
        
        if (isEmpty(root)) {
            delete root;
            root = nullptr;
        }
        return root;
    }

    int index = key[depth] - 'a';
    if (index >= 0 && index < Alphabet) {
        root->sons[index] = removeAux(root->sons[index], key, depth + 1);
    }

    if (isEmpty(root) && root->end == false) {
        delete root;
        root = nullptr;
    }

    return root;
}

void Trie::remove(std::string key)
{
    root = removeAux(root, key, 0);
    if (root == nullptr) {
        root = new TrieNode();
    }
}

void Trie::AuxPrint(TrieNode *node, std::string word)
{
    if (node->end)
    {
        std::cout << word << std::endl;
    }
    for (int i = 0; i < Alphabet; i++)
    {
        if (node->sons[i])
        {
            AuxPrint(node->sons[i], word + (char)(i + 'a'));
        }
    }
}

void Trie::generateDOTAux(TrieNode* node, std::string prefix, std::ostream& out, int& nodeCount) {
    int currentId = nodeCount;
    if (node->end) {
        out << "    node" << currentId << " [label=\"\", style=filled, fillcolor=lightgrey, shape=doublecircle];\n";
    } else {
        out << "    node" << currentId << " [label=\"\", shape=circle];\n";
    }

    for (int i = 0; i < Alphabet; i++) {
        if (node->sons[i]) {
            int childId = ++nodeCount;
            out << "    node" << currentId << " -> node" << childId << " [label=\"" << (char)(i + 'a') << "\"];\n";
            generateDOTAux(node->sons[i], prefix + (char)(i + 'a'), out, nodeCount);
        }
    }
}

void Trie::generateDOT(const std::string& filename) {
    std::ofstream out(filename);
    if (out.is_open()) {
        out << "digraph Trie {\n";
        if (root == nullptr) {
            out << "    empty [label=\"Empty\"];\n";
        } else {
            int nodeCount = 0;
            out << "    node0 [label=\"root\", shape=rect];\n";
            for (int i = 0; i < Alphabet; i++) {
                if (root->sons[i]) {
                    int childId = ++nodeCount;
                    out << "    node0 -> node" << childId << " [label=\"" << (char)(i + 'a') << "\"];\n";
                    generateDOTAux(root->sons[i], std::string(1, (char)(i + 'a')), out, nodeCount);
                }
            }
        }
        out << "}\n";
        out.close();
    }
}
