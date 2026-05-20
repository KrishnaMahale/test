#include <iostream>
#include <fstream>
using namespace std;

char M[400][4];
char IR[4];
int IC = 0;

int pageTable[10]; // -1 = not present
int nextFrame = 5;

ifstream fin("input.txt");

//--------------------------------------------
// ADDRESS MAPPING
//--------------------------------------------
int mapAddress(int VA) {

    int page = VA / 10;
    int offset = VA % 10;

    // INVALID PAGE FAULT CHECK
    if(pageTable[page] == -1) {
        cout << "ERROR: Invalid Page Fault on page " << page << endl;
        exit(0);
    }

    return pageTable[page]*10 + offset;
}

//--------------------------------------------
// EXECUTION
//--------------------------------------------
void execute() {

    while(true) {

        int RA = mapAddress(IC);

        // FETCH
        for(int i=0;i<4;i++)
            IR[i] = M[RA][i];

        IC++;

        // HALT
        if(IR[0]=='H')
            break;

        // PD
        else if(IR[0]=='P' && IR[1]=='D') {

            int VA = (IR[2]-'0')*10 + (IR[3]-'0');
            int realAddr = mapAddress(VA);

            cout << "OUTPUT: ";
            for(int i=0;i<4;i++)
                cout << M[realAddr][i];
            cout << endl;
        }
    }
}

//--------------------------------------------
// LOAD
//--------------------------------------------
void load() {

    string line;
    int memPtr = 0;

    // initialize page table
    for(int i=0;i<10;i++)
        pageTable[i] = -1;

    while(getline(fin, line)) {

        if(line.substr(0,4) == "$AMJ") {

            memPtr = 0;

            // Only allocate page 0 (program)
            pageTable[0] = nextFrame++;
        }

        else if(line.substr(0,4) == "$DTA") {
            execute();
        }

        else if(line.substr(0,4) == "$END") {
            break;
        }

        else {
            // load program in page 0
            int frame = pageTable[0];
            int RA = frame * 10 + memPtr;

            for(int i=0;i<4;i++)
                M[RA][i] = line[i];

            memPtr++;
        }
    }
}

//--------------------------------------------
int main() {
    load();
    return 0;
}