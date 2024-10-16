#include <iostream>
#include <string>
#include "modCipher.h"
#include <cctype> 

void check(std::string Text, const std::string& keyStr) {
    try {
        int key;
        if (keyStr.empty()) {
            throw std::invalid_argument("Отсутствует ключ!");
        }
        for (char c : keyStr) {
            if (!std::isdigit(c)) {
                throw std::invalid_argument("Неправильный ключ!");
            }
        }
        key = std::stoi(keyStr);

        std::string cipherText;
        std::string decryptedText;
        modCipher cipher(key, Text);
        cipherText = cipher.encryption(Text);
        decryptedText = cipher.transcript(cipherText, Text);
        std::cout << "Ключ = " << key << std::endl;
        std::cout << Text << std::endl;
        std::cout << cipherText << std::endl;
        std::cout << decryptedText << std::endl;
    } catch(const std::exception & e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    try {
        check("kulmination", "6");
        std::cout << "испытание 1\n" << std::endl;
        check("", "6"); 
        std::cout << "испытание 2\n" << std::endl;
        check("1212121212121", "6");
        std::cout << "испытание 3\n" << std::endl;
        check("kulmination", "658567");
        std::cout << "испытание 4\n" << std::endl;
        check("kulmination", "a"); 
        std::cout << "испытание 5\n" << std::endl;
        check("kulmination", ""); 
        std::cout << "испытание 6\n" << std::endl;
    } catch(const std::exception & e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}
