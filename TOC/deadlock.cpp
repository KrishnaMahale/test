#include <iostream> 
#include <vector> 
using namespace std;

int main()
{
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;
    
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> request(n, vector<int>(m));
    vector<int> available(m);

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];

    cout << "Enter Request Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> request[i][j];

    cout << "Enter Available Resources:\n";
    for (int i = 0; i < m; i++)
        cin >> available[i];
    vector<int> work = available;
    vector<bool> finish(n, false);

    bool found;
    do
    {
        found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canProceed = true;

                for (int j = 0; j < m; j++)
                {
                    if (request[i][j] > work[j])
                    {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed)
                {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    finish[i] = true;
                    found = true;
                }
            }
        }

    } while (found);

    bool deadlock = false;
    cout << "Deadlock Detected:\n";
    cout << "\nDeadlocked processes: ";
    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            cout << "P" << i << " ";
            deadlock = true;
        }
    }

    if (!deadlock)
        cout << "None (No Deadlock)";

    cout << endl;

    return 0;
}