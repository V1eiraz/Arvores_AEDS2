#include "trie.hpp"
#include <fstream>
#include <iostream>
#include <string>
int main()
{
    Trie Deku;
    std::string word;
    std::fstream file("data/trie1.txt");
    if (!file.is_open())
    {
        std::cerr << "Error: file not find" << std::endl;
    }
    std::cout << "Reading file and insert keys" << std::endl;
    while (std::getline(file, word))
    {
        if (!word.empty())
        {
            Deku.Insert(word);
        }
    }

    std::cout << "SUCCES" << std::endl;
    file.close();

    return 0;
}