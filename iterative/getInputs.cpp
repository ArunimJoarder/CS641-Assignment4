#include <iostream>
#include <fstream>
#include "funcs.cpp"

using namespace std;
using INT = unsigned int;

int main(){

    ofstream fi1("inputs.txt");
    int char1[64], inp[64], inp1[64];

    // Define characteristics and get reverse initial permutation of their values in binary
    string characteristic = "405C000004000000", input, input1;
    hex2bin(characteristic, char1);//    invIP(char1);

    // Generate 350 random input string pairs for each characteristic
    for(int i = 0; i < 100000; i++){
        // Generate any one input
        dec2bin(i, inp, 64);

        // Find pair such that xor with above input is characteristic
        XOR(inp, char1, inp1, 64);

        // apply inverse initial permutation
        invIP(inp); invIP(inp1);

        // convert from binary to hexadecimal
        bin2hex(inp, input);
        bin2hex(inp1, input1);

        // int Xor[64];
        // string hexor;
        // IP(inp);    IP(inp1);   IP(inp2);
        // XOR(inp, inp1, Xor);
        // bin2hex(Xor, hexor);
        // cout << hexor << " ";
        // XOR(inp, inp2, Xor);
        // bin2hex(Xor, hexor);
        // cout << hexor << endl;

        // convert to special hexadecimal as used in assignment (from 'f' to 'u') and write pair to files
        fi1 << toSpHex(input) << endl;
        fi1 << toSpHex(input1) << endl;
    }
    fi1.close();

    return 0;
}