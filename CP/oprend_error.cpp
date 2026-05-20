#include <iostream>
#include <cstring>
using namespace std;

char M[200][4];
char IR[4], R[4];
int IC = 0;
bool C;

//--------------------------------------------
// ERROR FUNCTION
//--------------------------------------------
void error(string msg) {
    cout << "ERROR: " << msg << endl;
    exit(0);
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

        // OPCODE VALIDATION
        if(!( (IR[0]=='G' && IR[1]=='D') ||
              (IR[0]=='P' && IR[1]=='D') ||
              (IR[0]=='L' && IR[1]=='R') ||
              (IR[0]=='S' && IR[1]=='R') ||
              (IR[0]=='C' && IR[1]=='R') ||
              (IR[0]=='B' && IR[1]=='T') ||
              (IR[0]=='H') ))
        {
            error("Invalid Opcode");
        }

        // HALT
        if(IR[0]=='H') break;

        // OPERAND CHECK
        int loc = (IR[2]-'0')*10 + (IR[3]-'0');

        if(loc >= 200)
            error("Invalid Operand / Memory Address");

        // EXECUTE (minimal)
        if(IR[0]=='L' && IR[1]=='R') {
            for(int i=0;i<4;i++)
                R[i] = M[loc][i];
        }
        else if(IR[0]=='S' && IR[1]=='R') {
            for(int i=0;i<4;i++)
                M[loc][i] = R[i];
        }
        else if(IR[0]=='P' && IR[1]=='D') {
            cout << "OUTPUT: ";
            for(int i=0;i<4;i++)
                cout << M[loc][i];
            cout << endl;
        }
    }
}

//--------------------------------------------
// MAIN
//--------------------------------------------
int main() {

    // Load faulty program
    char program[][4] = {
        {'L','R','1','0'},   // OK
        {'X','X','2','0'},   // Invalid opcode
        {'S','R','3','0'},   // Invalid operand (>199)
        {'H',' ',' ',' '}
    };

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            M[i][j] = program[i][j];

    execute();

    return 0;
}