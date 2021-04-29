#include<bits/stdc++.h>

using namespace std;

using arr1D = vector<uint64_t>;
using arr2D = vector<arr1D>;
using arr3D = vector<arr2D>;

ostream& operator<<(ostream& out, arr1D arr){
    for(int i = 0; i < arr.size(); i++){
        out << arr[i];
    }
    return out;
}

arr1D bin(uint64_t num, int size){
    arr1D binary(size, 0);
    for(int i = 0; i < size; i++){
        binary[i] = ((num >> (size - i - 1)) & 1);
    }
    return binary;
}

uint64_t dec(arr1D bin){
    uint64_t val = 0;
    for(int i = 0; i < bin.size(); i++){
        val = val*2 + bin[i];
    }
    return val;
}

string str(arr1D bin){
    int n_char = 0;
    string msg = "";
    for(int i = 0; i < bin.size(); i += 8){
        arr1D chr(bin.begin() + i, bin.begin() + i + 8);
        // cout << chr.size() << endl;
        // cout << chr << " : " << dec(chr) <<  endl;
        char c = dec(chr);
        msg += c;
        n_char++;
        if(n_char%16 == 0)
            msg += '\n';
    }

    return msg;
}

class State{
    public:
        arr3D state;

        State(){
            arr1D tempZ(64, 0);
            arr2D tempYZ(5, tempZ);
            state = arr3D(5, tempYZ);
        }

        void hash2state(string hash){
        	int val;
			for(int c = 0; c < 128; c++){
				if(hash[c] >= '0' && hash[c] <= '9')
					val = hash[c] - '0';
				else if(hash[c] >= 'A' && hash[c] <= 'F')
					val = hash[c] - 'A' + 10;

				int k = 4*c;
                arr1D val_b = bin(val, 4);
				for(int j=0 ; j<4 ; j++){
					state[k/(64*5)][(k/64)%5][(k%64) + j] = val_b[3-j];
				}
			}
            return;
        }

        arr2D& operator[](int i){
            return state[i];
        }

        arr1D Column(int i, int k){
            arr1D col(5, 0);
            for(int j = 0; j < 5; j++){
                col[j] = state[i][j][k];
            }
            return col;
        }

        void setColumn(arr1D col, int i, int k){
            for(int j = 0; j < 5; j++){
                state[i][j][k] = col[j];
            }
        }

        arr1D message(){
            arr1D msg(1600, 0);
            for(int k = 0; k < 1600; k++)
            	msg[k] = state[k/(64*5)][(k/64)%5][k%64];
            return msg;
        }
};

uint64_t inv_chi_col[] = {0, 21, 11, 10, 22, 1, 20, 23, 13, 8, 2, 3, 9, 12, 15, 14, 26, 5, 16, 27, 4, 17, 6, 7, 18, 29, 24, 19, 30, 25, 28, 31};

State invChi(State state){
    State temp;
    for(int i = 0; i < 5; i++){
        for(int k = 0; k < 64; k++){
            arr1D col = state.Column(i, k);
            uint64_t inv_col = inv_chi_col[dec(col)];
            temp.setColumn(bin(inv_col, 5), i, k);
        }
    }
    return temp;
}

State invPi(State state){
    State temp;
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            for(int k = 0; k < 64; ++k)
                temp[((j-3*i)/2 + 5*100)%5][i][k] = state[i][j][k];

    return temp;
}

State invTheta(State state){
    State temp;

    arr2D column_parity(5, arr1D(64, 0));
    for(int i = 0; i < 5; i++){
        for(int k = 0; k < 64; k++){
            for(int j = 0; j < 5; j++){
                column_parity[i][k] ^= state[i][j][k];
            }
        }
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 64; k++){
                temp[i][j][k] = state[i][j][k] ^ column_parity[(i+2)%5][k] ^ column_parity[(i+3)%5][k];
            }
        }
    }
    return temp;
}

int main(){
    string hash_val = "696162E4000000000680800A616862EA6FE5EBEE616862EA0684890A616862EA00040900000000000684890A616862EA69656BE400000000696162E400000000";

    State state;
    state.hash2state(hash_val);

    int rounds = 24;
    for(int r = 0; r < rounds; r++){
        state = invChi(state);
        state = invPi(state);
        state = invTheta(state);
    }
    string msg = str(state.message());

    cout << msg << "." << endl;
    // cout << state.message() << endl;
    return 0;
}