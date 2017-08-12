#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "lzw.h"

using namespace std;

static const int kDictSizeLimit = 4096;

vector<int> LZW::compress(string str) {
    map<string, int> codeMap;
    vector<int> codeOutput;
    
    int dictSize = 256;
    for(int ch = 0; ch < dictSize; ch++) {
        string key = "";
        key += (char) ch;
        codeMap[key] = ch;
    }
    
    string soFar = "";
    for(int i = 0; i < str.size(); i++) {
        char ch = str[i];
        string possible = soFar + ch;
        
        if(codeMap.find(possible) != codeMap.end()) {
            soFar = possible;
        } else {
            codeOutput.push_back(codeMap[soFar]);
            if(dictSize <= kDictSizeLimit) {
                codeMap[possible] = dictSize++;
            }

            soFar = "";
            soFar += ch;
        }
    }

    if(soFar.size() != 0) {
        codeOutput.push_back(codeMap[soFar]);
    }

    return codeOutput;
}

void LZW::compress(istream& input, ostream& output) {
    map<string, int> codeMap;

    int dictSize = 256;
    for(int ch = 0; ch < dictSize; ch++) {
        string key = "";
        key += (char) ch;
        codeMap[key] = ch;
    }

    string soFar = "";
    while(!input.eof()) {
        int ch = input.get();
        if(ch != -1) {
            string possible = soFar + (char) ch;
            if(codeMap.find(possible) != codeMap.end()) {
                soFar = possible;
            } else {
                output << codeMap[soFar] << " ";
                if(dictSize <= kDictSizeLimit) {
                    codeMap[possible] = dictSize++;
                }

                soFar = "";
                soFar += (char) ch;
            }
        }
    }

    if(soFar.size() != 0) {
        output << codeMap[soFar];
    }

    output << endl;
}

string LZW::decompress(vector<int> vec) {
    map<int, string> codeMap;
    string result = "";
    
    int dictSize = 256;
    for(int ch = 0; ch < dictSize; ch++) {
        string value = "";
        value += (char) ch;
        codeMap[ch] = value;
    }
    
    string last = "";
    string current = "";
    for(int i = 0; i < vec.size(); i++) {
        if(codeMap.find(vec[i]) != codeMap.end()) {
            current = codeMap[vec[i]];
        } else if(vec[i] == dictSize) {
            current = last + last[0];
        } else {
            throw("Invalid compression sequence.");
        }

        result += current;
        if(last.size() != 0 && dictSize <= kDictSizeLimit) {
            codeMap[dictSize++] = last + current[0];
        }

        last = current;
    }

    return result;
}

void LZW::decompress(istream& input, ostream& output) {
    map<int, string> codeMap;
    
    int dictSize = 256;
    for(int ch = 0; ch < dictSize; ch++) {
        string value = "";
        value += (char) ch;
        codeMap[ch] = value;
    }
    
    string last = "";
    string current = "";
    int code;
    while(input >> code) {
        if(codeMap.find(code) != codeMap.end()) {
            current = codeMap[code];
        } else if(code == dictSize) {
            current = last + last[0];
        } else {
            throw("Invalid compression sequence.");
        }

        output << current;
        if(last.size() != 0 && dictSize <= kDictSizeLimit) {
            codeMap[dictSize++] = last + current[0];
        }

        last = current;
    }

    output << endl;
}
