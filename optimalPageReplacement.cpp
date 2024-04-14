#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

int optimal_page_replacement(vector<int>& pages, int capacity) {
    unordered_map<int, int> nextUse;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); ++i) {
        int page = pages[i];
        if (nextUse.find(page) == nextUse.end()) {
            pageFaults++;
            if (nextUse.size() == capacity) {
                int farthest = INT_MIN;
                int idx = -1;
                for (auto it = nextUse.begin(); it != nextUse.end(); ++it) {
                    if (it->second > farthest) {
                        farthest = it->second;
                        idx = it->first;
                    }
                }
                nextUse.erase(idx);
            }
        }
        nextUse[page] = i;
    }

    return pageFaults;
}

int main() {
    vector<int> pages = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};
    int capacity = 3;

    cout << "Optimal Page Replacement: " << optimal_page_replacement(pages, capacity) << " page faults." << endl;

    return 0;
}
