#include "modCipher.h"
#include <iostream>
#include <algorithm> 

modCipher::modCipher(int skey, string text) {
    if (text.empty())
        throw cipher_error("Отсутствует открытый текст!");
    key = getValidKey(skey, text);
}

string modCipher :: encryption(string &text) {
    string t = getValidOpenText(text);
    int simvoli = t.size();
    int stroki = (simvoli + key - 1) / key;
    char** tabl = new char* [stroki];
    for (int i = 0; i < stroki; i++)
        tabl[i] = new char [key];
    for (int i = 0; i < stroki; i++)
        for (int j = 0; j < key; j++) {
            if(i * key + j < simvoli) {
                tabl[i][j] = t[i * key + j];
            } else {
                tabl[i][j] = ' ';
            }
        }
    t.clear();
    for (int j = 0; j < key; j++)
        for (int i = 0; i < stroki; i++) {
            if(tabl[i][j] != ' ') { 
                t += tabl[i][j];
            }
        }
    for (int i = 0; i < stroki; i++)
        delete[] tabl[i];
    delete[] tabl;
    return t;
}

inline string modCipher::getValidCipherText(string &s, string &open_text) {
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    int r1 = s.size();
    int r2 = open_text.size();
    if (r1 != r2) {
        std::cerr << "Предупреждение: Длина зашифрованного текста не соответствует длине открытого текста." << std::endl;
        return s; 
    }
    return s;
}

string modCipher :: transcript(string &text, string &open_text) {
    string t = getValidCipherText(text, open_text);
    t.erase(std::remove(t.begin(), t.end(), ' '), t.end());
    int simvoli = t.size();
    int stroki = (simvoli + key - 1) / key;
    char** tabl = new char* [stroki];
    for (int i = 0; i < stroki; i++)
        tabl[i] = new char [key];
    for (int j = 0; j < key; j++)
        for (int i = 0; i < stroki; i++) {
            if(j * stroki + i < simvoli) {
                tabl[i][j] = t[j * stroki + i];
            } else {
                tabl[i][j] = ' ';
            }
        }
    t.clear();
    for (int i = 0; i < stroki; i++)
        for (int j = 0; j < key; j++) {
            if(tabl[i][j] != ' ') { 
                t += tabl[i][j];
            }
        }
    for (int i = 0; i < stroki; i++)
        delete[] tabl[i];
    delete[] tabl;
    return t;
}

inline string modCipher::getValidOpenText(string &s) {
    if (s.empty())
        throw cipher_error("Отсутствует открытый текст!");
    int razmer = s.size();
    for(int i = 0; i < razmer; i++)
        if (s[i] == ' ') {
            s.erase(i, 1);
            i--;
        }
    for(int i = 0; i < razmer; i++)
        if(s[i] < 'A' ||  s[i] > 'z')
            throw cipher_error("В тексте встречены некорректные символы!");
    return s;
}

inline int modCipher::getValidKey(int key, const string &Text) {
    if(key < 2 || key > static_cast<int>(Text.size()))
        throw cipher_error("Ключ некорректного размера");
    return key;
}
