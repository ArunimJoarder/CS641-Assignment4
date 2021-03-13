#include <iostream>
#include <fstream>

using namespace std;
using INT = unsigned int;
using BYTE = unsigned char;

/* PERMUTED CHOICE  PC1 */
INT PC1[] = {
  57, 49, 41, 33, 25, 17, 9,
  1, 58, 50, 42, 34, 26, 18,
  10,  2, 59, 51, 43, 35, 27,
  19, 11,  3, 60, 52, 44, 36,
  63, 55, 47, 39, 31, 23, 15, 
  7, 62, 54, 46, 38, 30, 22, 
  14,  6, 61, 53, 45, 37, 29, 
  21, 13,  5, 28, 20, 12,  4
};

/* Shedule og the left shifts for C and D blocks 
unsigned short shifts[] = {
        2, 13, 13 }; 
*/
unsigned short shifts[] = {
1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

/* PERMUTED CHOICE 2 (PC@) */

INT PC2[] = {
  14, 17, 11, 24,  1, 5, 
  3, 28 ,15,  6, 21, 10, 
  23, 19, 12,  4, 26, 8, 
  16,  7, 27, 20, 13, 2, 
  41, 52, 31, 37, 47, 55, 
  30, 40, 51, 45, 33, 48, 
  44, 49, 39, 56, 34, 53, 
  46, 42, 50, 36, 29, 32
};

/* Key Scedule of 16 48-bit subkey generated from 64-bit key */

BYTE KS[16][48];


// void set_the_key(
//      INT sw1,     /* type of cryption 0= encryption, 1= decryption */
//      BYTE *pkey,
//      INT r)
// {
//   register INT i, j, k, t1, t2;
//   static BYTE key[64];
//   static BYTE CD[56];
  
  
//   /* Unpack KEY from 8 bits/byte into 1 bit/byte */
//   unpack8(pkey, key);
//   /* printf(" key in 56 bits....\n"); */
//   /* permute unpacked key with PC1 to generate C and D*/
//   for (i=0; i<56; i++) {
//     CD[i] = key[PC1[i] -1];
//     /* printf("%d", CD[i]); */
//   }
  
//   /* Rotate and permute C and D to generate 16 subkeys */
//   for ( i=0; i<r; i++) { /**--*/
//     /* Rotate C and D */
//     for (j =0; j <shifts[i]; j++) {
//       t1 = CD[0];
//       t2 = CD[28];
//       for ( k=0; k<27; k++) {
//         CD[k] = CD[k+1];
//         CD[k+28] = CD[k+29];
//       }
//       CD[27] = t1;
//       CD[55] = t2;
//     }
//     /* Set the order of subkeys for type of encryption */
//     j = sw1 ? r-1-i :i ;   /**--*/
    
//     /* Permute C and D with PC2 to generate KS[i] */
//     for (k=0; k< 48 ; k++)  KS[j][k] = CD[PC2[k] -1];
//   }
  
//   return;
  
// }

void getKey(int key6[48]){
    int key[64], CD[56];
    for(int i = 0; i < 56; i++){
        CD[i] = -1;
    }

    for(int k = 0; k < 48; k++){
        CD[PC2[k] -1] = key6[k];
    }

    for(int i = 0; i < 56; i++){
        cout << CD[i];
    }
    cout << endl;

    int t1, t2;
    for (int j = 0; j < shifts[5]; j++) {
      t1 = CD[27];
      t2 = CD[55];
      for (int k = 27; k > 0; k--) {
        CD[k] = CD[k-1];
        CD[k+28] = CD[k+28-1];
      }
      CD[0] = t1;
      CD[28] = t2;
    }
    for(int i = 0; i < 56; i++){
        cout << CD[i];
    }
    cout << endl;

    for(int i = 0; i < 64; i++){
        key[i] = -2;
    }

    for(int i = 0; i < 56; i++){
       key[PC1[i] -1] = CD[i];
    }

    for(int i = 0; i < 64; i++){
        if(key[i] == -2)
            cout << '0';
        else if(key[i] == -1)
            cout << 'X';
        else
            cout << key[i];
    }
    cout << endl;
}

int main(){
    int key6[] =   {0,1,0,1,1,1,
                    1,1,0,1,0,0,
                    0,1,0,0,0,1,
                    1,1,1,1,0,1,
                    0,1,0,1,1,1,
                    1,0,1,0,0,0,
                    1,1,1,0,1,1,
                    1,1,1,1,1,1};
    
    getKey(key6);
}