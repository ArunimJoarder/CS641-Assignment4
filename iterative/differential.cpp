#include <iostream>
#include <iomanip>
#include <fstream>
#include "funcs.cpp"

using namespace std;
using BYTE = unsigned char;
using INT = unsigned int;

int main(){
    // string num ="\0";
    // cout << "Enter ID of characteristic to be used (1/2): ";
    // cin >> num;
    // if((num.compare("1") != 0) && (num.compare("2") != 0)){
    //     cout << "Please enter valid ID from 1 and 2." << endl;
    //     return 0;
    // }

    string T1, T2;
    ifstream out("outputs.txt");
    ofstream text_keys("keys_distribution.txt"), key_6i("key_6i.txt");

    string characteristic = "405C000004000000";

    int chr[64], cl[32], cr[32];
    hex2bin(characteristic, chr);
    getLR(chr, cl, cr);

    // counter for each S box and each key
    long long int KEY_COUNT[8][64];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 64; j++){
            KEY_COUNT[i][j] = 0;
        }
    }

    int count = 0;

    int iter = 0;
    while(getline(out, T1)){
        
        getline(out, T2);
        // get ciphertexts for both inputs
        
        int t1[64], t2[64], oXOR[64], lXOR[32], rXOR[32], l1[32], r1[32], l2[32], r2[32], El1[48], El2[48], Exor[48];
        
        T1 = fromSpHex(T1);     T2 = fromSpHex(T2);
        hex2bin(T1, t1);        hex2bin(T2, t2);
        
        // inverse final permutation
        invFP(t1);  invFP(t2);
        
        // get left and right halves of the ciphertexts
        getLR(t1, l1, r1);  getLR(t2, l2, r2);
        
        // get XOR value of cihpertexts, along with left and right halves
        XOR(t1, t2, oXOR, 64);
        getLR(oXOR, lXOR, rXOR);

        // print(t1, 64);
        // print(t2, 64);
        // print(oXOR, 64);
        // print(lXOR, 32);
        // print(rXOR, 32);

        // apply expansion to left half of output (right half of input to 5th round)
        E(l1, El1);  E(l2, El2);
        XOR(El1, El2, Exor, 48);
        // print(l1, 32);
        // print(El1, 48);

        int alpha[2][8], betaXOR[8], gammaXOR[8];
        separate(El1, &alpha[0][0], 48, 8);
        separate(El2, &alpha[1][0], 48, 8);
        separate(Exor, betaXOR,     48, 8);

        int Sout[32];
        XOR(rXOR, cr, Sout, 32);
        invP(Sout);
        separate(Sout, gammaXOR,    32, 8);
        // for(int i = 0; i < 2; i++){
        //     for(int j = 0; j < 8; j++){
        //         cout << alpha[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // for(int j = 0; j < 8; j++){
        //     cout << betaXOR[j] << " ";
        // }
        // cout << endl;

        for(int i = 0; i < 8; i++){
            int beta[2], S_b1, S_b2, key;
            for(int b = 0; b < 64; b++){
                beta[0] = b;
                beta[1] = betaXOR[i]^beta[0];
                S_b1 = S[i][S_MAP[beta[0]] - 1];
                S_b2 = S[i][S_MAP[beta[1]] - 1];

                if((S_b1^S_b2) == gammaXOR[i]){
                    key = alpha[0][i]^beta[0];
                    KEY_COUNT[i][key]++;
                }
            }
        }
    
        iter++;
    }

    // output distribution of keys for further processing
    for(int i = 0; i < 8; i++){
        text_keys << "S" << i+1 << "\t";
        for(int j = 0; j < 64; j++){
            text_keys << setw(6) << KEY_COUNT[i][j] << "  ";
        }
        text_keys << "\n";
    }

    // get max key
    for(int i = 0; i < 8; i++){
        int mx = INT32_MIN, ind = -1, key_i[6];
        double sum = 0;
        for(int j = 0; j < 64; j++){
            sum += KEY_COUNT[i][j];
            if(KEY_COUNT[i][j] > mx){
                mx = KEY_COUNT[i][j];
                ind = j;
            }
        }
        dec2bin(ind, key_i, 6);
        cout << "S" << i+1 << "\tkey_max = ";
        print(key_i, 6);
        cout << "freq = " << mx << "\tavg = " << sum/64.0 << endl << endl;

        key_6i << ind << "\t";
        for(int k = 0; k < 6; k++){
            key_6i << key_i[k];
        }
        key_6i << endl;
    }
}