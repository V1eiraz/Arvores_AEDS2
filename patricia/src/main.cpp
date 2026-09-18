#include "patricia.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main() {
    PatriciaTree tree;
    std::string word;
    std::ifstream file("data/words.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error: could not open data/words.txt" << std::endl;
        return 1;
    }
    
    std::cout << "Reading file and inserting keys into Patricia Tree..." << std::endl;
    while (file >> word) {
        if (!word.empty()) {
            tree.insert(word);
        }
    }
    file.close();
    
    std::cout << "Finished insertions. Printing all words (or part of them):" << std::endl;
    tree.print();
    
    return 0;
}
