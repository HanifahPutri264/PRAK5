#include <iostream>
#include <string>
using namespace std;

// Fungsi untuk mengenkripsi teks menggunakan Caesar Cipher
string encryptCaesarCipher(string text, int shift) {
    string result = "";

    // Loop melalui setiap karakter dalam teks
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];

        // Jika karakter adalah huruf besar (A-Z)
        if (isupper(c)) {
            result += char(int(c + shift - 65) % 26 + 65);
        }
        // Jika karakter adalah huruf kecil (a-z)
        else if (islower(c)) {
            result += char(int(c + shift - 97) % 26 + 97);
        }
        // Jika karakter bukan huruf, tambahkan tanpa perubahan
        else {
            result += c;
        }
    }

    return result;
}

// Fungsi untuk mendekripsi teks
string decryptCaesarCipher(string text, int shift) {
    // Dekripsi dengan menggeser ke arah sebaliknya
    return encryptCaesarCipher(text, 26 - shift);
}

int main() {
    string text;
    int shift;

    cout << "Masukkan teks yang ingin dienkripsi: ";
    getline(cin, text);

    cout << "Masukkan jumlah shift (0-25): ";
    cin >> shift;

    // Proses enkripsi
    string encryptedText = encryptCaesarCipher(text, shift);
    cout << "Teks terenkripsi: " << encryptedText << endl;

    // Proses dekripsi
    string decryptedText = decryptCaesarCipher(encryptedText, shift);
    cout << "Teks terdekripsi: " << decryptedText << endl;

    return 0;
}

