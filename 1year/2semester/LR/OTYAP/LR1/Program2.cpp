#include <fstream>
#include <iostream>

using namespace std;

bool is_ru_vowel(unsigned char c)
{
    return 
    c == 'А' || c == 'Е' || c == 'И' || c == 'О' || c == 'У' || c == 'Ы' || c == 'Э' || c == 'Ю' || c == 'Я' || 
    c == 'а' || c == 'е' || c == 'и' || c == 'о' || c == 'у' || c == 'ы' || c == 'э' || c == 'ю' || c == 'я';
}

//execute algo and print result
void process_word(unsigned char* word, int size)
{
    //algo
    bool does_satisfy = false;
    if (is_ru_vowel(word[0]) && is_ru_vowel(word[size-1]))
    {
        does_satisfy = true;
    }

    //print result
    if (does_satisfy)
    {
        ofstream output("output.txt");
        for (int i = 0; i < size; i++)
        {
            output << word[i];
            cout << word[i];
        }
        cout << ' ';
        output << ' ';
    }
}

int main()
{
    ifstream input("input.txt");

    const int DEFAULT_WORD_ARR_SIZE = 100;
    unsigned char* word = new unsigned char[DEFAULT_WORD_ARR_SIZE];
    int count = 0;
    
    bool reading_word = false;
    bool word_allowed = true;

    unsigned char c;
    while (!input.eof())
    {
        c = input.get();
        //русские буковки
        if ((c >= 0xC0 && c <= 0xFF))
        {
            reading_word = true;
            word[count] = c;
            count++;
        }
        //разделители слов
        else if(c == '\n' || c == '\t' || c == ' ')
        {
            if (reading_word)
            {
                if (word_allowed)
                {
                    process_word(word, count);
                }
                
                word = new unsigned char[DEFAULT_WORD_ARR_SIZE];
                reading_word = false;
            }

            word_allowed = true;
        }
        else
        {
            word_allowed = false;
        }
    }

    if (reading_word && !word_allowed)
    {
        process_word(word, count);
    }
    
    
}

