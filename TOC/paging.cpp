#include <iostream>
#include <vector>
using namespace std;

int main() {
    int choice;

    cout << "Address Translation\n";
    cout << "1. Paging\n";
    cout << "2. Segmentation\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        int pageSize, logicalAddress, pages;

        cout << "Enter page size: ";
        cin >> pageSize;

        cout << "Enter number of pages: ";
        cin >> pages;

        vector<int> pageTable(pages);

        cout << "Enter frame number for each page:\n";
        for (int i = 0; i < pages; i++) {
            cout << "Page " << i << ": ";
            cin >> pageTable[i];
        }

        cout << "Enter logical address: ";
        cin >> logicalAddress;

        int pageNumber = logicalAddress / pageSize;
        int offset = logicalAddress % pageSize;

        if (pageNumber >= pages) {
            cout << "Invalid Logical Address\n";
        } else {
            int physicalAddress = pageTable[pageNumber] * pageSize + offset;

            cout << "\nPage Number: " << pageNumber << endl;
            cout << "Offset: " << offset << endl;
            cout << "Frame Number: " << pageTable[pageNumber] << endl;
            cout << "Physical Address: " << physicalAddress << endl;
        }
    }
    else if (choice == 2) {
        int segments;

        cout << "Enter number of segments: ";
        cin >> segments;

        vector<int> base(segments), limit(segments);

        cout << "Enter base and limit for each segment:\n";
        for (int i = 0; i < segments; i++) {
            cout << "Segment " << i << " Base: ";
            cin >> base[i];
            cout << "Segment " << i << " Limit: ";
            cin >> limit[i];
        }

        int segmentNumber, offset;

        cout << "Enter segment number: ";
        cin >> segmentNumber;

        cout << "Enter offset: ";
        cin >> offset;

        if (segmentNumber >= segments || offset >= limit[segmentNumber]) {
            cout << "Invalid Logical Address\n";
        } else {
            int physicalAddress = base[segmentNumber] + offset;

            cout << "\nBase Address: " << base[segmentNumber] << endl;
            cout << "Offset: " << offset << endl;
            cout << "Physical Address: " << physicalAddress << endl;
        }
    }
    else {
        cout << "Invalid Choice\n";
    }

    return 0;
}