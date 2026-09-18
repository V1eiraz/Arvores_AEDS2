#include "splay.hpp"
#include <iostream>
#include <fstream>

int main() {
    SplayTree tree;
    int number;
    std::ifstream file("data/numbers.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error: could not open data/numbers.txt" << std::endl;
        return 1;
    }
    
    std::cout << "Reading file and inserting keys into Splay Tree..." << std::endl;
    while (file >> number) {
        tree.insert(number);
    }
    file.close();
    
    std::cout << "Finished insertions. Preorder traversal:" << std::endl;
    tree.preOrder();
    
    return 0;
}
