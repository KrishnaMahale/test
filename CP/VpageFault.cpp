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
// ADDRESS MAPPING + PAGE FAULT
//--------------------------------------------
int mapAddress(int VA) {

    int page = VA / 10;
    int offset = VA % 10;

    // VALID PAGE FAULT
    if(pageTable[page] == -1) {

        cout << "Valid Page Fault on page " << page << endl;

        pageTable[page] = nextFrame++;

        // Load data page from "input"
        if(page == 1) {
            string data = "WELCOME";
            int k = 0;

            for(int i=0;i<10 && data[k] != '\0'; i++) {
                for(int j=0;j<4 && data[k] != '\0'; j++) {
                    M[pageTable[page]*10 + i][j] = data[k++];
                }
            }
        }
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
// LOAD FROM FILE ($AMJ)
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

            // allocate frame for program (page 0)
            pageTable[0] = nextFrame++;
        }

        else if(line.substr(0,4) == "$DTA") {
            execute();
        }

        else if(line.substr(0,4) == "$END") {
            break;
        }

        else {
            // load program into allocated frame
            int frame = pageTable[0];
            int realAddr = frame * 10 + memPtr;

            for(int i=0;i<4;i++)
                M[realAddr][i] = line[i];

            memPtr++;
        }
    }
}

//--------------------------------------------
int main() {
    load();
    return 0;
}