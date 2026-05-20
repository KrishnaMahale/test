#include <iostream>
using namespace std;

char M[400][4];
char IR[4];
int IC = 0;

// given page table
int pageTable[3] = {11, 23, 5};

//--------------------------------------------
// ADDRESS MAPPING
//--------------------------------------------
int mapAddress(int VA) {
    int page = VA / 10;
    int offset = VA % 10;

    int frame = pageTable[page];

    return frame * 10 + offset;
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
// MAIN
//--------------------------------------------
int main() {

    // Load program in page 0 → frame 11 (110–119)
    M[110][0]='P'; M[110][1]='D'; M[110][2]='1'; M[110][3]='0';
    M[111][0]='P'; M[111][1]='D'; M[111][2]='1'; M[111][3]='1';
    M[112][0]='H'; M[112][1]=' '; M[112][2]=' '; M[112][3]=' ';

    // Load data in page 1 → frame 23 (230–239)
    M[230][0]='W'; M[230][1]='E'; M[230][2]='L'; M[230][3]='C';
    M[231][0]='O'; M[231][1]='M'; M[231][2]='E'; M[231][3]=' ';

    execute();

    return 0;
}