#include "treap.hpp"
#include <iostream>
#include <fstream>

int main() {
    srand(1234); // Seed for deterministic priorities
    Treap tree;
    int number;
    std::ifstream file("data/numbers.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error: could not open data/numbers.txt" << std::endl;
        return 1;
    }
    
    std::cout << "Reading file and inserting keys into Treap..." << std::endl;
    while (file >> number) {
        tree.insert(number);
    }
    file.close();
    
    std::cout << "Finished insertions. Inorder traversal:" << std::endl;
    tree.inorder();
    
    return 0;
}
