#include <iostream>
#include <cstring>
using namespace std;

char M[400][4];
char IR[4];
int IC = 0;

// page table
int pageTable[10];

//--------------------------------------------
// Address Mapping
//--------------------------------------------
int mapAddress(int VA) {
    int page = VA / 10;
    int offset = VA % 10;
    return pageTable[page] * 10 + offset;
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

        // DECODE
        if(IR[0]=='H')
            break;

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
// LOAD (Paging)
//--------------------------------------------
void load() {

    // Page table setup
    pageTable[0] = 2;  // program page → frame 2
    pageTable[1] = 5;  // data page → frame 5

    // Load PROGRAM in frame 2 (20–29)
    M[20][0]='P'; M[20][1]='D'; M[20][2]='1'; M[20][3]='0'; // PD10
    M[21][0]='H'; M[21][1]=' '; M[21][2]=' '; M[21][3]=' ';

    // Load DATA in frame 5 (50–59)
    char msg[] = "WELCOME";

    int k = 0;
    for(int i=50; i<60 && msg[k] != '\0'; i++) {
        for(int j=0; j<4 && msg[k] != '\0'; j++) {
            M[i][j] = msg[k++];
        }
    }
}

//--------------------------------------------
int main() {
    load();
    execute();
    return 0;
}