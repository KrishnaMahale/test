#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void fcfs(vector<int> requests, int head) {
    int totalSeek = 0;
    int current = head;

    cout << "\nFCFS Order: " << current;

    for (int request : requests) {
        totalSeek += abs(current - request);
        current = request;
        cout << " -> " << current;
    }

    cout << "\nTotal Seek Time: " << totalSeek << "\n";
}

void sstf(vector<int> requests, int head) {
    int totalSeek = 0;
    int current = head;
    vector<bool> visited(requests.size(), false);

    cout << "\nSSTF Order: " << current;

    for (int i = 0; i < requests.size(); i++) {
        int index = -1;
        int minimum = 1e9;

        for (int j = 0; j < requests.size(); j++) {
            if (!visited[j] && abs(current - requests[j]) < minimum) {
                minimum = abs(current - requests[j]);
                index = j;
            }
        }

        visited[index] = true;
        totalSeek += abs(current - requests[index]);
        current = requests[index];

        cout << " -> " << current;
    }

    cout << "\nTotal Seek Time: " << totalSeek << "\n";
}

void scan(vector<int> requests, int head, int diskSize) {
    vector<int> left, right;
    int totalSeek = 0;
    int current = head;

    for (int request : requests) {
        if (request < head)
            left.push_back(request);
        else
            right.push_back(request);
    }

    left.push_back(0);

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "\nSCAN Order: " << current;

    for (int request : right) {
        totalSeek += abs(current - request);
        current = request;
        cout << " -> " << current;
    }

    for (int i = left.size() - 1; i >= 0; i--) {
        totalSeek += abs(current - left[i]);
        current = left[i];
        cout << " -> " << current;
    }

    cout << "\nTotal Seek Time: " << totalSeek << "\n";
}

void cscan(vector<int> requests, int head, int diskSize) {
    vector<int> left, right;
    int totalSeek = 0;
    int current = head;

    for (int request : requests) {
        if (request < head)
            left.push_back(request);
        else
            right.push_back(request);
    }

    left.push_back(0);
    right.push_back(diskSize - 1);

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "\nC-SCAN Order: " << current;

    for (int request : right) {
        totalSeek += abs(current - request);
        current = request;
        cout << " -> " << current;
    }

    current = 0;
    cout << " -> " << current;

    for (int request : left) {
        totalSeek += abs(current - request);
        current = request;
        cout << " -> " << current;
    }

    cout << "\nTotal Seek Time: " << totalSeek << "\n";
}

int main() {
    int n, head, diskSize;

    cout << "Enter number of requests: ";
    cin >> n;

    vector<int> requests(n);

    cout << "Enter disk requests: ";
    for (int i = 0; i < n; i++)
        cin >> requests[i];

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter disk size: ";
    cin >> diskSize;

    fcfs(requests, head);
    sstf(requests, head);
    scan(requests, head, diskSize);
    cscan(requests, head, diskSize);

    return 0;
}