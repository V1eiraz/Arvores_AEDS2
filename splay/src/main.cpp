#include "splay.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

void runBenchmark(int size, bool sorted) {
    SplayTree tree;
    std::vector<int> data(size);
    for(int i=0; i<size; i++) data[i] = i;

    if(!sorted) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(data.begin(), data.end(), g);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) tree.insert(data[i]);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Insert " << size << (sorted ? " sorted" : " random") << ": " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    if(!sorted) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(data.begin(), data.end(), g);
    }
    
    start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) tree.search(data[i]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Search " << size << (sorted ? " sorted" : " random") << ": " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) tree.remove(data[i]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Remove " << size << (sorted ? " sorted" : " random") << ": " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

int main() {
    std::cout << "--- SPLAY TREE BENCHMARK ---\n";
    runBenchmark(10000, false);
    runBenchmark(50000, false);
    // Splay tree can be very deep if inserted sorted, doing a smaller test to avoid stack overflow or long time
    runBenchmark(5000, true);

    SplayTree demoTree;
    demoTree.insert(10);
    demoTree.insert(20);
    demoTree.insert(30);
    demoTree.generateDOT("data/splay_initial.dot");
    demoTree.search(10);
    demoTree.generateDOT("data/splay_after_search.dot");
    demoTree.remove(20);
    demoTree.generateDOT("data/splay_after_remove.dot");
    std::cout << "Generated DOT files for visual tracing in data/ directory.\n";
    return 0;
}
