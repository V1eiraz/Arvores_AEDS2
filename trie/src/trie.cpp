#include "trie.hpp"

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

void Trie::search(std::string key)
{
    TrieNode *current = root;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (index < 0 || index >= Alphabet) {
            std::cout << "Key " << key << " not found." << std::endl;
            return;
        }

        if (current->sons[index] == nullptr)
        {
            std::cout << "Key " << key << " not found." << std::endl;
            return;
        }
        current = current->sons[index];
    }
    if (current != nullptr && current->end)
        std::cout << "Key " << key << " found." << std::endl;
    else
        std::cout << "Key " << key << " not found." << std::endl;
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
    // Note: if the trie becomes completely empty, root might be nullptr, 
    // we should recreate it to avoid crashes on next insert
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

