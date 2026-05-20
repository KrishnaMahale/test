#include <iostream>
#include <fstream>
using namespace std;

char M[200][4];  // Memory

ifstream fin("input.txt");

//--------------------------------------------
// LOAD FUNCTION
//--------------------------------------------
void load() {

    string line;
    int memPtr = 0;
    int jobNo = 0;

    while(getline(fin, line)) {

        if(line.substr(0,4) == "$AMJ") {
            cout << "\nLoading Job " << ++jobNo << endl;
            memPtr = jobNo * 20;  // allocate separate block per job
        }

        else if(line.substr(0,4) == "$DTA") {
            continue; // skip data
        }

        else if(line.substr(0,4) == "$END") {
            cout << "Job " << jobNo << " loaded successfully\n";
        }

        else {
            // load instruction into memory
            for(int i=0;i<4;i++)
                M[memPtr][i] = line[i];

            memPtr++;
        }
    }
}

//--------------------------------------------
int main() {
    load();

    // display memory (for verification)
    cout << "\nMemory Content:\n";

    for(int i=0;i<50;i++) {
        cout << i << " : ";
        for(int j=0;j<4;j++)
            cout << M[i][j];
        cout << endl;
    }

    return 0;
}