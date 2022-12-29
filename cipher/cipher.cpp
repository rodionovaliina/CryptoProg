#include <string>
#include <iostream>
#include <fstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/filters.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/cbcmac.h>
using namespace std;
using namespace CryptoPP;

void encrypt()
{
    string str;
    string str1 = "";
    string file;
    cout << "Введите имя файла c исходными данными:";
    cin >> file;
    ifstream f (file);
    char c;
    while (f.get(c)) {
        str1.push_back(c);
    }
    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);
    string text = str1;
    string ciphertext;
    cout << "Открытый текст: " << text << std::endl;
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
    stfEncryptor.Put(reinterpret_cast<const unsigned char*>(text.c_str()), text.length());
    stfEncryptor.MessageEnd();
    cout << "Введите имя файла для записи результата: ";
    string imp, file2;
    cin >> file2;
    cout << "Зашифрованный текст: " << ciphertext << std::endl;
    ofstream f2 (file2);
    for (int i = 0; i < ciphertext.size(); i++) {
        f2 << ciphertext[i];
    }
}

void decrypt()
{
    string str;
    string str1 = "";
    string file;
    cout << "Введите имя файла с исходными данными: ";
    cin >> file;
    ifstream f (file);
    char c;
    while (f.get(c)) {
        str1.push_back(c);
    }
    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
    memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);
    string text = str1;
    string decryptedtext;
    cout << "Текст " << text << std::endl;
    string file2;
    cout << "Введите имя файла для записи результата: ";
    cin >> file2;
    ofstream f2 (file2);
    ifstream f3 (file2);
    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);
    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
    stfDecryptor.Put(reinterpret_cast<const unsigned char*>(text.c_str()), text.size());
    stfDecryptor.MessageEnd();
    cout << decryptedtext << endl;
    f2 << decryptedtext;
}

int main()
{
    ifstream f;
    ofstream f2;
    ifstream f3;
    string str;
    string str1 = "";
    string file;
    int n;
    do {
        cout << "Введите 1 для зашифрования; 2 для расшифрования; 0 для выхода: ";
        cin >> n;
        if (n == 1) {
            encrypt();
        } else  if (n == 2) {
            decrypt();
        }
    } while (n != 0);
    return 0;
}
