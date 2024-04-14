#include <iostream>
#include <list>
#include <unordered_map>
#include<vector>

using namespace std;

int lru_page_replacement(vector<int>& pages, int capacity) {
    list<int> memory;
    unordered_map<int, list<int>::iterator> memoryMap;
    int pageFaults = 0;

    for (int page : pages) {
        if (memoryMap.find(page) == memoryMap.end()) {
            pageFaults++;
            if (memory.size() == capacity) {
                memoryMap.erase(memory.back());
                memory.pop_back();
            }
        } else {
            memory.erase(memoryMap[page]);
        }
        memory.push_front(page);
        memoryMap[page] = memory.begin();
    }

    return pageFaults;
}

int main() {
    vector<int> pages = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};
    int capacity = 3;

    cout << "LRU Page Replacement: " << lru_page_replacement(pages, capacity) << " page faults." << endl;

    return 0;
}
