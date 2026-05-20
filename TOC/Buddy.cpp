#include <iostream>
#include <vector>
using namespace std;

int nextPowerOfTwo(int n) {
    int power = 1;

    while (power < n) {
        power *= 2;
    }

    return power;
}

int main() {
    int totalMemory, n;

    cout << "Enter total memory: ";
    cin >> totalMemory;

    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> process(n);

    cout << "Enter process sizes:\n";

    for (int i = 0; i < n; i++) {
        cin >> process[i];
    }

    cout << "\nBuddy System Allocation:\n";

    for (int i = 0; i < n; i++) {

        int blockSize = nextPowerOfTwo(process[i]);

        if (blockSize <= totalMemory) {

            cout << "Process " << i + 1
                 << " (" << process[i] << ") "
                 << "allocated block size "
                 << blockSize << endl;

            totalMemory -= blockSize;

        } else {

            cout << "Process " << i + 1
                 << " not allocated\n";
        }
    }

    return 0;
}