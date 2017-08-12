#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "lzw.h"

using namespace std;

int main() {
    vector<int> vec = LZW::compress("ayy lmao this compression is super dank");
    for(int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }

    string decomp = LZW::decompress(vec);
    cout << endl;
    cout << decomp << endl;

    cout << "Enter a file to be encoded: ";
    string file;
    cin >> file;

    ifstream infile(file);
    LZW::compress(infile, cout);
    
    infile.close();
    cout << "Enter a file to be decoded: ";
    cin >> file;

    infile.open(file);
    LZW::decompress(infile, cout);

    infile.close();
    return 0;
}
