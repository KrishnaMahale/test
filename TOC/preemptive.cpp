#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process {
    int pid, at, bt, pr;
};

void fcfs(vector<Process> p) {

    int time = 0;

    cout << "\nFCFS Scheduling\n";

    for (int i = 0; i < p.size(); i++) {

        if (time < p[i].at)
            time = p[i].at;

        int ct = time + p[i].bt;
        int tat = ct - p[i].at;
        int wt = tat - p[i].bt;

        time = ct;

        cout << "P" << p[i].pid
             << " WT=" << wt
             << " TAT=" << tat << endl;
    }
}

void sjfNonPreemptive(vector<Process> p) {

    int n = p.size();
    vector<bool> done(n, false);

    int completed = 0, time = 0;

    cout << "\nSJF Non-Preemptive\n";

    while (completed < n) {

        int idx = -1;
        int minBT = 1e9;

        for (int i = 0; i < n; i++) {

            if (!done[i] && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        int ct = time + p[idx].bt;
        int tat = ct - p[idx].at;
        int wt = tat - p[idx].bt;

        time = ct;

        done[idx] = true;
        completed++;

        cout << "P" << p[idx].pid
             << " WT=" << wt
             << " TAT=" << tat << endl;
    }
}

void sjfPreemptive(vector<Process> p) {

    int n = p.size();

    vector<int> rt(n);

    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;

    int completed = 0, time = 0;

    cout << "\nSJF Preemptive (SRTF)\n";

    while (completed < n) {

        int idx = -1;
        int minRT = 1e9;

        for (int i = 0; i < n; i++) {

            if (p[i].at <= time && rt[i] > 0 && rt[i] < minRT) {
                minRT = rt[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        rt[idx]--;
        time++;

        if (rt[idx] == 0) {

            completed++;

            int ct = time;
            int tat = ct - p[idx].at;
            int wt = tat - p[idx].bt;

            cout << "P" << p[idx].pid
                 << " WT=" << wt
                 << " TAT=" << tat << endl;
        }
    }
}

void roundRobin(vector<Process> p, int tq) {

    int n = p.size();

    vector<int> rt(n);

    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;

    queue<int> q;

    int time = 0, completed = 0;

    vector<bool> added(n, false);

    q.push(0);
    added[0] = true;

    cout << "\nRound Robin\n";

    while (completed < n) {

        int i = q.front();
        q.pop();

        if (rt[i] > tq) {

            time += tq;
            rt[i] -= tq;

        } else {

            time += rt[i];

            int ct = time;
            int tat = ct - p[i].at;
            int wt = tat - p[i].bt;

            rt[i] = 0;
            completed++;

            cout << "P" << p[i].pid
                 << " WT=" << wt
                 << " TAT=" << tat << endl;
        }

        for (int j = 0; j < n; j++) {

            if (!added[j] && p[j].at <= time) {
                q.push(j);
                added[j] = true;
            }
        }

        if (rt[i] > 0)
            q.push(i);
    }
}

void priorityNonPreemptive(vector<Process> p) {

    int n = p.size();

    vector<bool> done(n, false);

    int completed = 0, time = 0;

    cout << "\nPriority Non-Preemptive\n";

    while (completed < n) {

        int idx = -1;
        int high = 1e9;

        for (int i = 0; i < n; i++) {

            if (!done[i] && p[i].at <= time && p[i].pr < high) {
                high = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        int ct = time + p[idx].bt;
        int tat = ct - p[idx].at;
        int wt = tat - p[idx].bt;

        time = ct;

        done[idx] = true;
        completed++;

        cout << "P" << p[idx].pid
             << " WT=" << wt
             << " TAT=" << tat << endl;
    }
}

void priorityPreemptive(vector<Process> p) {

    int n = p.size();

    vector<int> rt(n);

    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;

    int completed = 0, time = 0;

    cout << "\nPriority Preemptive\n";

    while (completed < n) {

        int idx = -1;
        int high = 1e9;

        for (int i = 0; i < n; i++) {

            if (p[i].at <= time && rt[i] > 0 && p[i].pr < high) {
                high = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        rt[idx]--;
        time++;

        if (rt[idx] == 0) {

            completed++;

            int ct = time;
            int tat = ct - p[idx].at;
            int wt = tat - p[idx].bt;

            cout << "P" << p[idx].pid
                 << " WT=" << wt
                 << " TAT=" << tat << endl;
        }
    }
}

int main() {

    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter AT BT Priority:\n";

    for (int i = 0; i < n; i++) {

        p[i].pid = i + 1;

        cin >> p[i].at
            >> p[i].bt
            >> p[i].pr;
    }

    fcfs(p);

    sjfNonPreemptive(p);

    sjfPreemptive(p);

    int tq;

    cout << "\nEnter Time Quantum: ";
    cin >> tq;

    roundRobin(p, tq);

    priorityNonPreemptive(p);

    priorityPreemptive(p);

    return 0;
}