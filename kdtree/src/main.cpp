#include "kdtree.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

void runBenchmark(int size) {
    KDTree tree;
    std::vector<std::vector<int>> data(size, std::vector<int>(K));
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> dist(0, 1000000);

    for(int i=0; i<size; i++) {
        for(int j=0; j<K; j++) {
            data[i][j] = dist(g);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) tree.insert(data[i]);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Insert " << size << " random points: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    std::shuffle(data.begin(), data.end(), g);
    
    start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) tree.search(data[i]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Search " << size << " random points: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) tree.remove(data[i]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Remove " << size << " random points: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

int main() {
    std::cout << "--- KDTREE BENCHMARK ---\n";
    runBenchmark(10000);
    runBenchmark(50000);

    KDTree demoTree;
    demoTree.insert({30, 40});
    demoTree.insert({5, 25});
    demoTree.insert({10, 12});
    demoTree.insert({70, 70});
    demoTree.insert({50, 30});
    demoTree.generateDOT("data/kdtree_initial.dot");
    demoTree.search({10, 12});
    demoTree.generateDOT("data/kdtree_after_search.dot");
    demoTree.remove({10, 12});
    demoTree.generateDOT("data/kdtree_after_remove.dot");
    std::cout << "Generated DOT files for visual tracing in data/ directory.\n";
    return 0;
}
