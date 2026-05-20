#include <iostream>
using namespace std;

char M[200][4];   // Memory
char IR[4], R[4];
int IC = 0;
bool C;

//--------------------------------------------
void execute() {
    while(true) {

        // FETCH
        for(int i=0;i<4;i++)
            IR[i] = M[IC][i];
        IC++;

        // DECODE
        if(IR[0]=='H') {
            break;
        }

        else if(IR[0]=='L' && IR[1]=='R') {
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');
            for(int i=0;i<4;i++)
                R[i] = M[loc][i];
        }

        else if(IR[0]=='S' && IR[1]=='R') {
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');
            for(int i=0;i<4;i++)
                M[loc][i] = R[i];
        }

        else if(IR[0]=='P' && IR[1]=='D') {
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');
            cout << "OUTPUT: ";
            for(int i=0;i<4;i++)
                cout << M[loc][i];
            cout << endl;
        }

        // ⭐ NEW INSTRUCTION: AD
        else if(IR[0]=='A' && IR[1]=='D') {
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');

            int num1 = atoi(R);
            int num2 = atoi(M[loc]);
            int sum = num1 + num2;

            sprintf(R, "%d", sum);
        }
    }
}

//--------------------------------------------
int main() {

    // preload program
    char program[][4] = {
        {'L','R','1','0'},
        {'A','D','1','1'},
        {'S','R','1','2'},
        {'P','D','1','2'},
        {'H',' ',' ',' '}
    };

    for(int i=0;i<5;i++)
        for(int j=0;j<4;j++)
            M[i][j] = program[i][j];

    // preload data
    M[10][0]='0'; M[10][1]='5';  // 5
    M[11][0]='0'; M[11][1]='3';  // 3

    execute();

    return 0;
}