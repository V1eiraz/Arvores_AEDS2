#include "kdtree.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    KDTree tree;
    std::ifstream file("data/points.txt");
    
    if (!file.is_open()) {
        std::cerr << "Error: could not open data/points.txt" << std::endl;
        return 1;
    }
    
    std::cout << "Reading file and inserting points into KD-Tree (K=" << K << ")..." << std::endl;
    int val;
    std::vector<int> point(K);
    while (true) {
        bool completePoint = true;
        for (int i = 0; i < K; i++) {
            if (!(file >> val)) {
                completePoint = false;
                break;
            }
            point[i] = val;
        }
        if (!completePoint) break;
        tree.insert(point);
    }
    file.close();
    
    std::cout << "Finished insertions. Inorder traversal:" << std::endl;
    tree.inorder();
    
    return 0;
}
