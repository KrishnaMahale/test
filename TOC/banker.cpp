#include <iostream>
#include <vector>
using namespace std;

bool safeState(vector<vector<int>> allocation,
               vector<vector<int>> need,
               vector<int> available,
               vector<int>& safeSeq) {

    int n = allocation.size();
    int m = available.size();

    vector<bool> finish(n, false);
    vector<int> work = available;

    while (true) {
        bool found = false;

        for (int i = 0; i < n; i++) {

            if (!finish[i]) {

                bool possible = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {

                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = true;
                    safeSeq.push_back(i);
                    found = true;
                }
            }
        }

        if (!found)
            break;
    }

    for (int i = 0; i < n; i++) {
        if (!finish[i])
            return false;
    }

    return true;
}

int main() {

    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> maximum(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));

    vector<int> available(m);

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter Maximum Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> maximum[i][j];
        }
    }

    cout << "Enter Available Resources:\n";
    for (int i = 0; i < m; i++) {
        cin >> available[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    vector<int> safeSeq;

    bool safe = safeState(allocation, need, available, safeSeq);

    if (safe) {

        cout << "\nSystem is in SAFE state\n";
        cout << "Safe Sequence: ";

        for (int i = 0; i < safeSeq.size(); i++) {
            cout << "P" << safeSeq[i];

            if (i != safeSeq.size() - 1)
                cout << " -> ";
        }

        cout << endl;

    } else {

        cout << "\nSystem is NOT in safe state\n";
    }

    return 0;
}