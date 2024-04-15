#include <fstream>
#include <iostream>

using namespace std;

bool is_ru_vowel(unsigned char c) {
    return
        c == 0xC0 || c == 0xC5 || c == 0xC8 || c == 0xCE || c == 0xD3 || c == 0xD9 || c == 0xE1 || c == 0xD7 || c == 0xDF || c == 0xE0 || c == 0xE5 || c == 0xE8 || c == 0xEE || c == 0xF3 || c == 0xF9 || c == 0xF1 || c == 0xF7 || c == 0xFF;
}

void process_word(unsigned char* word, int size, ofstream& output) {
    bool does_satisfy = false;
    if (is_ru_vowel(word[0]) && is_ru_vowel(word[size - 1])) {
        does_satisfy = true;
    }

    if (does_satisfy) {
        for (int i = 0; i < size; i++) {
            output << word[i];
            cout << word[i];
        }
        cout << ' ';
        output << ' ';
    }
}

int main() {
    SetConsoleOutputCP(1251);
    ifstream input("input2.txt");
    ofstream output("output.txt");

    const int DEFAULT_WORD_ARR_SIZE = 100;
    unsigned char* word = new unsigned char[DEFAULT_WORD_ARR_SIZE];
    int count = 0;
    bool reading_word = false;
    bool word_allowed = true;
    unsigned char c;

    while (input >> noskipws >> c) {
        if (c >= 0xC0 && c <= 0xFF) {
            reading_word = true;
            word[count] = c;
            count++;
        }
        else if (c == '\n' || c == '\t' || c == ' ') {
            if (reading_word) {
                if (word_allowed) {
                    process_word(word, count, output);
                }
                word = new unsigned char[DEFAULT_WORD_ARR_SIZE];
                count = 0;
                reading_word = false;
            }
            word_allowed = true;
        }
        else {
            word_allowed = false;
        }
    }
    if (reading_word && word_allowed) {
        process_word(word, count, output);
    }
    delete[] word;

}
