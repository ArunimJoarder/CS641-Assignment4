#include <iostream>
#include <fstream>
#include "des.cpp"
#include "funcs.cpp"

using namespace std;


int main(){
    BYTE key[] = {1,0,-1,-1,1,1,1,0,1,0,0,1,1,0,0,0,0,0,1,1,0,0,1,0,1,0,1,1,1,1,0,0,1,0,-1,0,1,-1,1,0,1,-1,1,-1,0,1,1,0,1,1,1,1,1,1,0,0,1,1,0,0,-1,-1,1,0};
    int bitInd[] = {2, 3, 34, 37, 41, 43, 60, 61};

    int bits[8];
    for(int i = 0; i < 512; i++){
        dec2bin(i, bits, 8);
        for(int j = 0; j < 8; j++){
            key[bitInd[j]] = bits[j];
        }

        set_the_key(0, key, 6);
        des()
    }
}