#include <iostream>
#include <vector>
using namespace std;

void fifo(vector<int> pages, int frames) {
    vector<int> memory;
    int faults = 0;
    int index = 0;

    for (int page : pages) {
        bool found = false;

        for (int x : memory) {
            if (x == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            faults++;

            if (memory.size() < frames) {
                memory.push_back(page);
            } else {
                memory[index] = page;
                index = (index + 1) % frames;
            }
        }
    }

    cout << "FIFO Page Faults: " << faults << endl;
}

void lru(vector<int> pages, int frames) {
    vector<int> memory;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        bool found = false;

        for (int x : memory) {
            if (x == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            faults++;

            if (memory.size() < frames) {
                memory.push_back(page);
            } else {

                int leastRecent = 1000;
                int replaceIndex = -1;

                for (int j = 0; j < memory.size(); j++) {

                    int lastUse = -1;

                    for (int k = i - 1; k >= 0; k--) {
                        if (pages[k] == memory[j]) {
                            lastUse = k;
                            break;
                        }
                    }

                    if (lastUse < leastRecent) {
                        leastRecent = lastUse;
                        replaceIndex = j;
                    }
                }

                memory[replaceIndex] = page;
            }
        }
    }

    cout << "LRU Page Faults: " << faults << endl;
}

void optimal(vector<int> pages, int frames) {
    vector<int> memory;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        bool found = false;

        for (int x : memory) {
            if (x == page) {
                found = true;
                break;
            }
        }

        if (!found) {
            faults++;

            if (memory.size() < frames) {
                memory.push_back(page);
            } else {
                int farthest = -1;
                int replace = 0;

                for (int j = 0; j < memory.size(); j++) {
                    int k;

                    for (k = i + 1; k < pages.size(); k++) {
                        if (memory[j] == pages[k]) {
                            break;
                        }
                    }

                    if (k > farthest) {
                        farthest = k;
                        replace = j;
                    }
                }

                memory[replace] = page;
            }
        }
    }

    cout << "Optimal Page Faults: " << faults << endl;
}

int main() {
    int n, frames;

    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);

    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> frames;

    fifo(pages, frames);
    lru(pages, frames);
    optimal(pages, frames);

    return 0;
}