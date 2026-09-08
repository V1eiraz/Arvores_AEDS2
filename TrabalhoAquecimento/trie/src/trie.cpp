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
        char letter = key[i];

        int index = letter - 'a';

        if (current->sons[index] == nullptr)
        {
            current->sons[index] = new TrieNode();
        }
        current = current->sons[index];
    }

    current->end = true;
}
