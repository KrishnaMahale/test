#include <iostream>
#include <cstring>
using namespace std;

char M[200][4];
char IR[4], R[4];
int IC = 0;
bool C;

int SI; // Service Interrupt

//--------------------------------------------
// ERROR HANDLING
//--------------------------------------------
void error(string msg) {
    cout << "ERROR: " << msg << endl;
    exit(0);
}

//--------------------------------------------
// MOS
//--------------------------------------------
void MOS() {

    if(SI == 2) { // PD
        int loc = (IR[2]-'0')*10 + (IR[3]-'0');

        if(loc >= 200)
            error("Invalid Memory Access");

        cout << "OUTPUT: ";
        for(int i=0;i<4;i++)
            cout << M[loc][i];
        cout << endl;
    }
}

//--------------------------------------------
// EXECUTION
//--------------------------------------------
void execute() {

    while(true) {

        // FETCH
        for(int i=0;i<4;i++)
            IR[i] = M[IC][i];

        IC++;

        // VALIDATION
        if(!(IR[0]=='G'||IR[0]=='P'||IR[0]=='L'||IR[0]=='S'||IR[0]=='C'||IR[0]=='B'||IR[0]=='H'))
            error("Invalid Opcode");

        // DECODE
        if(IR[0]=='H') break;

        else if(IR[0]=='P' && IR[1]=='D') {
            SI = 2;
            MOS();
        }

        else if(IR[0]=='L' && IR[1]=='R') {
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');

            if(loc >= 200)
                error("Invalid Memory Access");

            for(int i=0;i<4;i++)
                R[i] = M[loc][i];
        }

        else if(IR[0]=='S' && IR[1]=='R') {
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');

            if(loc >= 200)
                error("Invalid Memory Access");

            for(int i=0;i<4;i++)
                M[loc][i] = R[i];
        }

        else if(IR[0]=='C' && IR[1]=='R') {
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');

            if(loc >= 200)
                error("Invalid Memory Access");

            C = true;
            for(int i=0;i<4;i++)
                if(R[i]!=M[loc][i]) C=false;
        }

        else if(IR[0]=='B' && IR[1]=='T') {
            if(C)
                IC = (IR[2]-'0')*10 + (IR[3]-'0');
        }
    }
}

//--------------------------------------------
// MAIN
//--------------------------------------------
int main() {

    // Load program
    char program[][4] = {
        {'P','D','1','0'},
        {'P','D','1','1'},
        {'P','D','1','2'},
        {'H',' ',' ',' '}
    };

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            M[i][j] = program[i][j];

    // Load data (Hello World)
    M[10][0]='H'; M[10][1]='E'; M[10][2]='L'; M[10][3]='L';
    M[11][0]='O'; M[11][1]=' '; M[11][2]='W'; M[11][3]='O';
    M[12][0]='R'; M[12][1]='L'; M[12][2]='D'; M[12][3]=' ';

    execute();

    return 0;
}