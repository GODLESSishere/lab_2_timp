#include <iostream>
#include <string>
#include "modCipher.h"

void check(string Text, int key) {
    try {
        string cipherText;
        string decryptedText;
        modCipher cipher(key, Text);
        cipherText = cipher.encryption(Text);
        decryptedText = cipher.transcript(cipherText, Text);
        cout << "Ключ = " << key << endl;
        cout << Text << endl;
        cout << cipherText << endl;
        cout << decryptedText << endl;
    } catch(const cipher_error & e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    try {
        check("kulmination", 6);
        check("", 6); 
        check("1212121212121", 6);
        check("kulmination", 658567);
    } catch(const cipher_error & e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}
