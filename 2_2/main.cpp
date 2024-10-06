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
        cerr << "Ошибка: " << e.what() << endl;
    }
}

int main() {
    try {
        check("Kulmination", 6);
    } catch(const cipher_error & e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    return 0;
}
