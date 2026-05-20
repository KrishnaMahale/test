#include <iostream>
#include <vector>
using namespace std;

void firstFit(vector<int> blockSize, int m, vector<int> processSize, int n) {
    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << endl << "First Fit:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated" << endl;
    }
}

void bestFit(vector<int> blockSize, int m, vector<int> processSize, int n) {
    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;

        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIndex == -1 || blockSize[j] < blockSize[bestIndex]) {
                    bestIndex = j;
                }
            }
        }

        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            blockSize[bestIndex] -= processSize[i];
        }
    }

    cout << endl << "Best Fit:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated" << endl;
    }
}

void worstFit(vector<int> blockSize, int m, vector<int> processSize, int n) {
    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++) {
        int worstIndex = -1;

        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIndex == -1 || blockSize[j] > blockSize[worstIndex]) {
                    worstIndex = j;
                }
            }
        }

        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }

    cout << endl << "Worst Fit:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated" << endl;
    }
}

void nextFit(vector<int> blockSize, int m, vector<int> processSize, int n) {
    vector<int> allocation(n, -1);

    int index = 0;

    for (int i = 0; i < n; i++) {
        int checked = 0;

        while (checked < m) {
            if (blockSize[index] >= processSize[i]) {
                allocation[i] = index;
                blockSize[index] -= processSize[i];
                break;
            }
            index = (index + 1) % m;
            checked++;
        }
    }

    cout << endl << "Next Fit:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated" << endl;
    }
}

int main() {
    int m, n;

    cout << "Enter number of blocks: ";
    cin >> m;

    vector<int> blockSize(m);
    cout << "Enter block sizes:" << endl;
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
    }

    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> processSize(n);
    cout << "Enter process sizes:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> processSize[i];
    }

    vector<int> b1 = blockSize;
    vector<int> b2 = blockSize;
    vector<int> b3 = blockSize;
    vector<int> b4 = blockSize;

    firstFit(b1, m, processSize, n);
    bestFit(b2, m, processSize, n);
    worstFit(b3, m, processSize, n);
    nextFit(b4, m, processSize, n);

    return 0;
}