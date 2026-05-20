#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

char M[200][4];
char IR[4], R[4];
int IC;
bool C;

ifstream fin("input.txt");

string data[10];
int dataIndex = 0;
int SI;

//--------------------------------------------
// MOS
//--------------------------------------------
void MOS() {
    switch(SI) {

        case 1: { // GD
            string temp = data[dataIndex++];
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');

            int k = 0;
            for(int i=0;i<temp.size();i++) {
                M[loc + (i/4)][i%4] = temp[i];
            }
            break;
        }

        case 2: { // PD
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');

            cout << "OUTPUT: ";
            for(int i=0;i<4;i++)
                cout << M[loc][i];
            cout << endl;
            break;
        }

        case 3: // H
            exit(0);
    }
}

//--------------------------------------------
// EXECUTE
//--------------------------------------------
void execute() {
    IC = 0;

    while(true) {
        // FETCH
        for(int i=0;i<4;i++)
            IR[i] = M[IC][i];
        IC++;

        // DECODE
        if(IR[0]=='G' && IR[1]=='D') {
            SI=1; MOS();
        }
        else if(IR[0]=='P' && IR[1]=='D') {
            SI=2; MOS();
        }
        else if(IR[0]=='H') {
            SI=3; MOS();
        }
        else if(IR[0]=='L' && IR[1]=='R') {
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');
            for(int i=0;i<4;i++)
                R[i]=M[loc][i];
        }
        else if(IR[0]=='C' && IR[1]=='R') {
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');
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
// LOAD
//--------------------------------------------
void load() {
    string line;
    int memPtr = 0;

    // preload SAME and NOTE
    M[40][0]='S'; M[40][1]='A'; M[40][2]='M'; M[40][3]='E';
    M[50][0]='N'; M[50][1]='O'; M[50][2]='T'; M[50][3]='E';

    while(getline(fin, line)) {

        if(line.substr(0,4) == "$AMJ") {
            memPtr = 0;
        }
        else if(line.substr(0,4) == "$DTA") {

            // read data
            while(getline(fin, line)) {
                if(line.substr(0,4) == "$END")
                    break;
                data[dataIndex++] = line;
            }

            dataIndex = 0;
            execute();
        }
        else {
            // load instructions
            for(int i=0;i<4;i++)
                M[memPtr][i] = line[i];
            memPtr++;
        }
    }
}

//--------------------------------------------
int main() {
    load();
    return 0;
}