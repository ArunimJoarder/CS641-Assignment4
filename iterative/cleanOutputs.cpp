#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ofstream out;
    ifstream in;
    in.open("rawoutputs.txt");
    out.open("outputs.txt");

    string temp;
    while(getline(in, temp)){
        // cout << temp << ":::::" << temp.length() << endl;
        if(temp.length() == 19){
            out << temp.substr(2, 19) << endl;
        }
    }
    in.close();
    out.close();

    return 0;
}