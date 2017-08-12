#include <iostream>
#include <string>
#include <vector>

class LZW {
public:
    static std::vector<int> compress(std::string str);
    static void compress(std::istream& input, std::ostream&);
    static std::string decompress(std::vector<int> vec);
    static void decompress(std::istream& input, std::ostream& output);
};
