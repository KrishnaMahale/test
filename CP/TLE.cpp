#include <iostream>
using namespace std;

char M[200][4];
char IR[4], R[4];
int IC = 0;
bool C;

// Limits
int TTL = 5;   // Time Limit
int TLL = 3;   // Line Limit

// Counters
int TTC = 0;   // Time Counter
int LLC = 0;   // Line Counter

//--------------------------------------------
// ERROR FUNCTION
//--------------------------------------------
void error(string msg) {
    cout << "ERROR: " << msg << endl;
    exit(0);
}

//--------------------------------------------
// MOS (handles PD)
//--------------------------------------------
void MOS() {

    // Line Limit check BEFORE printing
    if(LLC >= TLL)
        error("Line Limit Exceeded");

    int loc = (IR[2]-'0')*10 + (IR[3]-'0');

    cout << "OUTPUT: ";
    for(int i=0;i<4;i++)
        cout << M[loc][i];
    cout << endl;

    LLC++; // increment after printing
}

//--------------------------------------------
// EXECUTION
//--------------------------------------------
void execute() {

    while(true) {

        // Time Limit check BEFORE execution
        if(TTC >= TTL)
            error("Time Limit Exceeded");

        // FETCH
        for(int i=0;i<4;i++)
            IR[i] = M[IC][i];

        IC++;
        TTC++;  // increment time

        // HALT
        if(IR[0]=='H')
            break;

        // DECODE
        if(IR[0]=='P' && IR[1]=='D') {
            MOS();
        }

        else if(IR[0]=='L' && IR[1]=='R') {
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');
            for(int i=0;i<4;i++)
                R[i] = M[loc][i];
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

    // Program causing Line Limit Exceeded
    char program[][4] = {
        {'P','D','1','0'},
        {'P','D','1','0'},
        {'P','D','1','0'},
        {'P','D','1','0'}, // exceeds TLL
        {'H',' ',' ',' '}
    };

    // Load program
    for(int i=0;i<5;i++)
        for(int j=0;j<4;j++)
            M[i][j] = program[i][j];

    // Data
    M[10][0]='T'; M[10][1]='E'; M[10][2]='S'; M[10][3]='T';

    execute();

    return 0;
}