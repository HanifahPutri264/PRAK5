#include <iostream>
#include <string>
using namespace std;

// Fungsi enkripsi Vigenere Cipher
string encryptVigenere(string plaintext, string key) {
    string ciphertext = "";
    int keyIndex = 0;

    for (int i = 0; i < plaintext.length(); i++) {
        char p = plaintext[i];

        if (isalpha(p)) {
            char k = toupper(key[keyIndex % key.length()]);
            int shift = k - 'A';
            char base = isupper(p) ? 'A' : 'a';
            ciphertext += char((toupper(p) - base + shift) % 26 + base);
            keyIndex++;
        } else {
            ciphertext += p; // spasi/tanda baca tidak berubah
        }
    }

    return ciphertext;
}

// Fungsi dekripsi Vigenere Cipher
string decryptVigenere(string ciphertext, string key) {
    string plaintext = "";
    int keyIndex = 0;

    for (int i = 0; i < ciphertext.length(); i++) {
        char c = ciphertext[i];

        if (isalpha(c)) {
            char k = toupper(key[keyIndex % key.length()]);
            int shift = k - 'A';
            char base = isupper(c) ? 'A' : 'a';
            plaintext += char((toupper(c) - base - shift + 26) % 26 + base);
            keyIndex++;
        } else {
            plaintext += c;
        }
    }

    return plaintext;
}

int main() {
    string plaintext, key;

    cout << "Masukkan teks yang ingin dienkripsi: ";
    getline(cin, plaintext);

    cout << "Masukkan key: ";
    getline(cin, key);

    string ciphertext = encryptVigenere(plaintext, key);
    cout << "\nTeks terenkripsi: " << ciphertext << endl;

    string decryptedText = decryptVigenere(ciphertext, key);
    cout << "Teks terdekripsi: " << decryptedText << endl;

    return 0;
}
