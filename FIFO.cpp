#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int fifo_page_replacement(vector<int>& pages, int capacity) {
    unordered_set<int> memory;
    queue<int> fifoQueue;
    int pageFaults = 0;

    for (int page : pages) {
        if (memory.find(page) == memory.end()) {
            pageFaults++;
            if (memory.size() == capacity) {
                int removedPage = fifoQueue.front();
                fifoQueue.pop();
                memory.erase(removedPage);
            }
            memory.insert(page);
            fifoQueue.push(page);
        }
    }

    return pageFaults;
}

int main() {
    vector<int> pages = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};
    int capacity = 3;

    cout << "FIFO Page Replacement: " << fifo_page_replacement(pages, capacity) << " page faults." << endl;

    return 0;
}
