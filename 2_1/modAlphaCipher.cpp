#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>

locale loc("ru_RU.UTF-8");

wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
using namespace std;

modAlphaCipher::modAlphaCipher(const string& skey) {
    for (unsigned i=0; i < numAlpha.size(); i++)
        alphaNum[numAlpha[i]]=i;
    key = convert(getValidKey(skey));
}

string modAlphaCipher::encrypt(const string& open_text) {
    vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i=0; i < work.size(); i++)
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    return convert(work);
}

string modAlphaCipher::decrypt(const string& cipher_text) {
    vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i=0; i < work.size(); i++)
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    return convert(work);
}

inline vector<int> modAlphaCipher::convert(const string& s) {
    wstring ws = codec.from_bytes(s);
    vector<int> result;
    for(auto c:ws)
        result.push_back(alphaNum[c]);
    return result;
}

inline string modAlphaCipher::convert(const vector<int>& v) {
    wstring ws;
    for(auto i:v)
        ws.push_back(numAlpha[i]);
    return codec.to_bytes(ws);
}

inline string modAlphaCipher::getValidKey(const string & s) {
    wstring ws = codec.from_bytes(s);
    if (ws.empty())
        throw cipher_error("Пустой ключ");
    int razmer = ws.size();
    for (int i = 0; i < razmer; i++) {
        if(ws[i] < L'А' || ws[i] > L'Я')
            throw cipher_error(string ("Неверный ключ: ") + s);
        if (ws[i] >= L'а' && ws[i] <= L'я')
            ws[i] -= 32;
    }
    return codec.to_bytes(ws);
}

inline string modAlphaCipher::getValidOpenText(const string & s) {
    wstring ws = codec.from_bytes(s);
    wstring tmp;
    for (auto c:ws) {
        if (c >= L'А' && c <= L'Я' || c >= L'а' && c <= L'я') {
            if (c >= L'а' && c <= L'я')
                tmp.push_back(c -= 32); 
            else
                tmp.push_back(c);
        } else if (c == L' ') {
        } else {
            throw cipher_error("Недопустимый символ в тексте");
        }
    }
    if (tmp.empty())
        throw cipher_error("Надо текст!"); 
    return codec.to_bytes(tmp);
}

inline string modAlphaCipher::getValidCipherText(const string & s) {
    wstring ws = codec.from_bytes(s);
    return codec.to_bytes(ws);
}
