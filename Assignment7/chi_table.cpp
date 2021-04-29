#include<bits/stdc++.h>

using namespace std;

ostream& operator<<(ostream& out, vector<uint64_t> arr){
    for(int i = 0; i < arr.size(); i++){
        out << arr[i];
    }
    return out;
}

vector<uint64_t> bin(uint64_t num, int size){
    vector<uint64_t> binary(size, 0);
    for(int i = 0; i < size; i++){
        binary[i] = ((num >> (size - i - 1)) & 1);
    }
    return binary;
}

uint64_t dec(vector<uint64_t> bin){
    uint64_t val = 0;
    for(int i = 0; i < bin.size(); i++){
        val += bin[i]*pow(2, bin.size() - i - 1);
    }
    return val;
}

int main(){
    int size = 5;
    vector<uint64_t> check(pow(2,size), 0);
    for(uint64_t i = 0; i < pow(2,size); i++){
        vector<uint64_t> column = bin(i, size), chi_col(size,0);

        for(int j = 0; j < size; j++){
            chi_col[j] = column[j] ^ (~column[(j+1)%size] & column[(j+2)%size]);
        }
        cout << dec(chi_col) << " : " << dec(column) << endl;
        if(check[dec(chi_col)] == 1){
            cout << "non" << endl;
            break;
        }
        check[dec(chi_col)] = 1;
        // cout << i << " : " << dec(column) << endl;
    }
}