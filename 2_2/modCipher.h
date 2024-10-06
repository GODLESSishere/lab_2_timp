#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

class modCipher {
    private:
        int key;
        inline int getValidKey(int key, const string & Text);
        inline string getValidOpenText(string & s);
        inline string getValidCipherText(string & s, string & open_text);
    public:
        modCipher() = delete;
        modCipher(int skey, string text);
        string encryption(string &text);
        string transcript(string &text, string &open_text);
};

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};
