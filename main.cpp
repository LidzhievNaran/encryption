
#include <iostream>
#include "fstream"
#include <string>
#include <vector>

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: Use three parameters\n";
        return 5;
    }
    const std::string mode(argv[1]); // Режим работы
    const std::string file_name(argv[2]); // Имя файла
    if (mode == "encryption") {
        std::string line;
        std::string key;
        std::cout << "enter a line" << std::endl;
        getline(std::cin, line);
        std::cout << "enter a key(int)" << std::endl;
        getline(std::cin, key);
        srand(static_cast<unsigned int>(stoi(key)));
        std::vector<char> bytes;
        for (int i = 0; i < line.size(); i++) {
            bytes.push_back(static_cast<char>(line[i]));
        }
        std::ofstream f(file_name, std::ios_base::binary);
        for (int i =0; i < bytes.size(); i+=2) {
            unsigned int gamma = rand();
            unsigned int line1;
            if (i+1 < bytes.size()){
                line1 = (static_cast<unsigned int>(bytes[i]) << 8 ) | (static_cast<unsigned int>(bytes[i+1]));
            } else
            {
                line1 =  (static_cast<unsigned int>(bytes[i]) << 8 );
            }
            unsigned int line_with_gamma = line1 ^ gamma & 0xFFFF;
            unsigned int line_encrypted = ((line_with_gamma << 2) & 0xFFFF | (line_with_gamma >> 14) & 0xFFFF);
            char line_encrypted_ch = line_encrypted >> 8;
            char line_encrypted_ch1 = line_encrypted;
            f << line_encrypted_ch << line_encrypted_ch1;
        }
        f.close();
    } else if (mode == "decryption") {
        std::string key;
        std::ifstream f(file_name, std::ios_base::binary);
        std::cout << "enter a key(int)" << std::endl;
        getline(std::cin, key);
        srand(static_cast<unsigned int>(stoi(key)));
        std::string line;
        getline(f, line);
        std::vector<unsigned char> bytes(line.size());
        for (int i = 0; i != line.size(); ++i)
            bytes[i] = line[i];
        for (int i = 0; i < bytes.size(); i += 2) {
            unsigned int gamma = rand();
            unsigned int line_encrypt;
            if (i + 1 < bytes.size())
                line_encrypt = (static_cast<unsigned int>(bytes[i]) << 8) | (static_cast<unsigned int>(bytes[i + 1]));
            else
                line_encrypt = (static_cast<unsigned int>(bytes[i]) << 8);
            unsigned int line_with_gamma =
                    ((line_encrypt >> 2) & 0xFFFF) | ((line_encrypt << (16 - 2)) & 0xFFFF);
            unsigned int line_decrypt = line_with_gamma ^ gamma;
            char ch = line_decrypt >> 8;
            char ch1 = line_decrypt;
            std::cout << ch << ch1;
        }
        f.close();
    }
    return 0;
}

