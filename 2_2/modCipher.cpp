#include "modCipher.h"

modCipher::modCipher(int skey, string text) {
    key = getValidKey(skey, text);
}

string modCipher :: encryption(string &text) {
    string t = getValidOpenText(text);
    int k = 0;
    int simvoli = t.size();
    int stroki = ((simvoli) / key);
    char** tabl = new char* [stroki];
    for (int i = 0; i < stroki; i++)
        tabl[i] = new char [key];
    for (int i = 0; i < stroki; i++)
        for (int j = 0; j < key; j++) {
            if(k < simvoli) {
                tabl[i][j] = t[k];
                k++;
            }
        }
    k = 0;
    for (int j = key - 1; j >= 0 ; j--)
        for (int i = 0; i < stroki; i++) {
            t[k] = tabl[i][j];
            k++;
        }
    for (int i = 0; i < stroki; i++)
        delete[] tabl[i];
    delete[] tabl;
    return t;
}

inline string modCipher::getValidCipherText(string &s, string &open_text) {
    int r1 = s.size();
    int r2 = open_text.size();
    if (r1 != r2)
        throw cipher_error (string ("Неправельный зашифрованный текст: ") + s);
    return s;
}

string modCipher :: transcript(string &text, string &open_text) {
    string t = getValidCipherText(text, open_text);
    int k = 0;
    int simvoli = t.size();
    int stroki = ((simvoli) / key);
    char** tabl = new char* [stroki];
    for (int i = 0; i < stroki; i++)
        tabl[i] = new char [key];
    for (int j = key - 1; j >= 0 ; j--)
        for (int i = 0; i < stroki; i++) {
            tabl[i][j] = t[k];
            k++;
        }
    k = 0;
    for (int i = 0; i < stroki; i++)
        for (int j = 0; j < key; j++) {
            t[k] = tabl[i][j];
            k++;
        }
    for (int i = 0; i < stroki; i++)
        delete[] tabl[i];
    delete[] tabl;
    return t;
}

inline string modCipher::getValidOpenText(string &s) {
    int razmer = s.size();
    for(int i = 0; i < razmer; i++)
        if (s[i] == ' ') {
            s.erase(i, 1);
            i--;
        }
    if (s.empty())
        throw cipher_error("Отсутствует открытый текст!");
    for(int i = 0; i < razmer; i++)
        if(s[i] < 'A' || s[i] > 'z')
            throw cipher_error("В тексте встречены некорректные символы!");
    return s;
}

inline int modCipher::getValidKey(int key, const string &Text) {
    if(key < 2 || key > static_cast<int>(Text.size()))
        throw cipher_error("Ключ некоректного размера");
    return key;
}
