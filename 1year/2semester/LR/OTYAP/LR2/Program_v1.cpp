#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const char* INP_FILENAME = "input.txt";
const char* OUTP_FILENAME = "output.txt";

int get_filesize(const char* filename)
{
    ifstream is;
    is.open (filename, ios::binary );
    is.seekg (0, ios::end);
    int size = is.tellg();
    is.close();
    
    return size;
}

unsigned char* read_whole_file(const char* filename)
{
    ifstream input(filename);
    int filesize = get_filesize(filename);

    unsigned char* content = new unsigned char[filesize+1];
    for (int i = 0; i < filesize; i++)
    {
        input >> noskipws >> content[i];
    }

    input.close();

    content[filesize] = '\0';

    return content;
}

/// @brief Список состояний
enum state { s_begin, s_begin_digit, s_begin_letter, s_digit, s_letter, s_end, s_error, s_deadend };

/// @brief Список символов
enum symbol { letter, digit, delim, other  };

/// @brief Таблица состояний
const state state_table[4][8] = 
{
    { s_begin_letter, s_letter,  s_error,   s_letter, s_error, s_end, s_error,     s_deadend },
    { s_begin_digit,  s_error,   s_digit,   s_error,  s_digit, s_end, s_error,     s_deadend },
    { s_end,          s_deadend, s_deadend, s_end,    s_end,   s_end, s_deadend,   s_deadend },
    { s_error,        s_error,   s_error,   s_error,  s_error, s_end, s_error,     s_deadend }
};

/// @brief Лексема
struct lex
{
    bool is_allowed;
    unsigned char* str;
};

/// @brief Проверяет является ли символ буквой латинского алфавита в кодировке windows-1251
/// @param c символ
/// @return 
bool is_en_letter_windows1251(unsigned char c)
{
    return
        //uppercase latin letters a-z
        (c >= 'a' && c <= 'z') ||
        //lowercase latin letters A-Z
        (c >= 'A' && c <= 'Z');
}

/// @brief Проверяет является ли символ цифрой в кодировке windows-1251
/// @param c символ
/// @return 
bool is_digit_windows1251(unsigned char c)
{
    //digits 0-9
    return (c >= '0' && c <= '9');
}

bool is_separator(unsigned char c)
{
    return isspace(c) || c == '\0';
}

/// @brief Конверитрует символ в его представление в перечислении
/// @param s 
/// @return 
symbol char_to_symbol(unsigned char s)
{
    if (is_en_letter_windows1251(s)) return letter;
    if (is_digit_windows1251(s)) return digit;
    if (is_separator(s)) return delim;
    return other;
}

bool is_begin_state(state s)
{
    switch (s)
    {
        case s_begin:
        case s_begin_digit:
        case s_begin_letter:
            return true;
        default:
            return false;
    }
}

bool is_final_state(state s)
{
    switch (s)
    {
        case s_end:
        case s_deadend:
            return true;
        default:
            return false;
    }
}

bool is_not_allowed_state(state s)
{
    switch (s)
    {
        case s_deadend:
            return true;
        default:
            return false;
    }
}

/// @brief Находит те слова, в которых цифры и буквы латинского алфавита чередуются (слово из одной цифры или буквы не удовлетворяет условию).
/// @param text Текст содержащий слова
/// @return Список лексем
vector<lex> is_alternating_digits_letters(unsigned char* text)
{
    vector<lex> lexems;
    enum state curr_state = s_begin;
    int i = 0, lex_begin_i = 0;
    lex lexem;

    do
    {
        curr_state = state_table[char_to_symbol(text[i])][curr_state];

        if (is_begin_state(curr_state))
        {
            lex_begin_i = i;
            lexem.is_allowed = true;
        }

        if (is_final_state(curr_state))
        {
            if (curr_state == s_deadend)
                lexem.is_allowed = false;

            int length = i - lex_begin_i;

            if (length != 0)
            {
                lexem.str = new unsigned char[length + 1];

                for (int j = 0; j < length; j++)
                {
                    lexem.str[j] = text[lex_begin_i + j];
                }

                lexem.str[length] = '\0';
                lexems.push_back(lexem);
            }

            curr_state = s_begin;
            lexem = lex();
        }
    }
    while (text[i++]);

    return lexems;
}

void output_tokens(vector<lex>& lexems)
{
    ofstream output(OUTP_FILENAME);

    for (size_t i = 0; i < lexems.size(); i++)
    {
        if (lexems[i].is_allowed)
        {
            cout << lexems[i].str << ' ';
            output << lexems[i].str << ' ';
        }
    }

    output.close();
}

int main()
{
    unsigned char* content = read_whole_file(INP_FILENAME);

    vector<lex> lexems = is_alternating_digits_letters(content);

    output_tokens(lexems);

    delete content;
    return 0;
}
