#include <iostream>
#include <cctype>
#include <locale>
#include "modAlphaCipher.h"

using namespace std;

void check(const string& Text, const string& key, const bool destructCipherText=false) {
    try {
        string cipherText;
        string decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        decryptedText = cipher.decrypt(cipherText);

        string decryptedTextNoSpaces;
        for (char c : decryptedText) {
            if (c != ' ') {
                decryptedTextNoSpaces += c;
            }
        }

        cout << "Ключ = " << key << endl;
        cout << "Открытый текст: " << Text << endl;
        cout << "Зашифрованный текст: " << cipherText << endl;
        cout << "Расшифрованный текст: " << decryptedTextNoSpaces << endl;
    } catch (const cipher_error &e) {
        cerr << "Ошибка: " << e.what() << endl;
    } catch (const std::exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

int main() {
    check("ОДИННАДЦАТЬ", "КЛЮЧ");
    cout << "испытание 1\n" << endl;
    check("ОДИННАДЦАТЬ", "Ключ");
    cout << "испытание 2\n" << endl;
    check("ОДИННАДЦАТЬ", "");
    cout << "испытание 3\n" << endl;
    check("ОДИННАДЦАТЬ", "Клю4");
    cout << "испытание 4\n" << endl;
    check("Один надцать", "КЛЮЧ");
    cout << "испытание 5\n" << endl;
    check("11", "КЛЮЧ");
    cout << "испытание 6\n" << endl;
    check("           ", "КЛЮЧ");
    cout << "испытание 7\n" << endl;
    return 0;
}
