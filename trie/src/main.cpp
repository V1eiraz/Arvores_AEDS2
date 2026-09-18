#include "trie.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

std::string generateRandomString(int length) {
    static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(length);

    for (int i = 0; i < length; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

void runBenchmark(int size) {
    Trie tree;
    std::vector<std::string> data(size);
    for(int i=0; i<size; i++) data[i] = generateRandomString(5 + rand() % 10);

    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) tree.Insert(data[i]);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Insert " << size << " random strings: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);

    start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) tree.search(data[i]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Search " << size << " random strings: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<size; i++) tree.remove(data[i]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Remove " << size << " random strings: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

int main() {
    srand(42);
    std::cout << "--- TRIE BENCHMARK ---\n";
    runBenchmark(10000);
    runBenchmark(50000);

    Trie demoTree;
    demoTree.Insert("car");
    demoTree.Insert("cat");
    demoTree.Insert("dog");
    demoTree.generateDOT("data/trie_initial.dot");
    demoTree.search("cat");
    demoTree.generateDOT("data/trie_after_search.dot");
    demoTree.remove("cat");
    demoTree.generateDOT("data/trie_after_remove.dot");
    std::cout << "Generated DOT files for visual tracing in data/ directory.\n";
    return 0;
}
