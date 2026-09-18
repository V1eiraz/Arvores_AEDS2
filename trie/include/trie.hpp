#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <string>

const int Alphabet = 26;

struct TrieNode
{
    TrieNode *sons[Alphabet];
    bool end;

    TrieNode()
    {
        end = false;
        for (int i = 0; i < Alphabet; i++)
        {
            sons[i] = nullptr;
        }
    }
};

class Trie
{
private:
    TrieNode *root;

    void AuxPrint(TrieNode *node, std::string word);
    void CleanMemory(TrieNode *node);
    void generateDOTAux(TrieNode* node, std::string prefix, std::ostream& out, int& nodeCount);

public:
    Trie();
    ~Trie();

    void Insert(std::string key);
    bool search(std::string key);
    void remove(std::string key);
    void generateDOT(const std::string& filename);
};

#endif
