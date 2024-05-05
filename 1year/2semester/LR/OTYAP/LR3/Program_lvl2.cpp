#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const char* INP_FILENAME = "input.txt";
const char* OUTP_FILENAME = "output.txt";

const char* CO = "co";
const char* KW = "kw";
const char* ID = "id";
const char* WL = "wl";
const char* VL = "vl";
const char* EQ = "eq";
const char* AO = "ao";

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
enum state { 
    s_begin, s_id, s_const, s_less_co, s_more_co, s_double_co, s_wl, s_eq, s_ao,
    s_final_co, s_final_id, s_final_wl, s_final_const, s_final_eq, s_final_ao };

/// @brief Список символов
enum symbol { letter, digit, less_co, more_co, eq, arithm, delim, other  };

/// @brief Таблица состояний
const state state_table[8][15] = 
{
    { s_id,      s_id,       s_wl,          s_final_co,  s_final_co,  s_final_co, s_wl,       s_final_eq, s_final_ao  },
    { s_const,   s_id,       s_const,       s_final_co,  s_final_co,  s_final_co, s_wl,       s_final_eq, s_final_ao  },
    { s_less_co, s_final_id, s_final_const, s_final_co,  s_final_co, s_final_co, s_final_wl, s_final_eq, s_final_ao  },
    { s_more_co, s_final_id, s_final_const, s_double_co, s_final_co,  s_final_co, s_final_wl, s_final_eq, s_final_ao  },
    { s_eq,      s_final_id, s_final_const, s_double_co, s_double_co, s_final_co, s_final_wl, s_final_eq, s_final_ao  },
    { s_ao,      s_final_id, s_final_const, s_final_co,  s_final_co,  s_final_co, s_final_wl, s_final_eq, s_final_ao  },
    { s_begin,   s_final_id, s_final_const, s_final_co,  s_final_co,  s_final_co, s_final_wl, s_final_eq, s_final_ao  },
    { s_wl,      s_wl,       s_wl,          s_final_co,  s_final_co,  s_final_co, s_wl,       s_final_eq, s_final_ao  }
};

bool is_separator(unsigned char c)
{
    return isspace(c) || c == '\0';
}

bool is_arithmetic_operation(unsigned char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

/// @brief Конверитрует символ в его представление в enum символов
/// @param s символ
/// @return значение в enum символов
symbol char_to_symbol(unsigned char s)
{
    if (isalpha(s)) return letter;
    if (isdigit(s)) return digit;
    if (is_separator(s)) return delim;
    if (s == '<') return less_co;
    if (s == '>') return more_co;
    if (s == '=') return eq;
    if (is_arithmetic_operation(s)) return arithm;
    return other;
}

bool is_final_state(state s)
{
    return 
        s == s_final_co    ||
        s == s_final_id    ||
        s == s_final_wl    ||
        s == s_final_const ||
        s == s_final_eq    ||
        s == s_final_ao
    ;
}

/// @brief Переводит финальное состояние в тип лексемы
/// @param s Состояние
/// @return Тип лексемы, либо пустая строка если состояние - не финальное
const char* final_state_to_lexem_id(state s)
{
    switch (s)
    {
        case s_final_co:
            return CO;
        case s_final_id:
            return ID;
        case s_final_wl:
            return WL;
        case s_final_const:
            return VL;
        case s_final_eq:
            return EQ;
        case s_final_ao:
            return AO;
        default:
            return "";
    }
}

/// @brief Лексема
struct lex
{
    /// @brief Сама лексема
    unsigned char* str;
    /// @brief Тип лексемы
    const char* lex_type;
};

const int KW_COUNT = 6;
/// @brief Разрешенные в языке ключевые слова
const char* keywords[KW_COUNT] =  { "if", "else", "then", "end", "and", "or" };

/// @brief Проводит лексический анализ над текстом
/// @param text Текст
/// @return Список лексем
vector<lex>* analyze_lexems(unsigned char* text)
{
    vector<lex>* lexems = new vector<lex>();
    enum state curr_state = s_begin;
    int i = 0, lex_begin_i = 0, const_count = 0;

    do
    {
        if (curr_state == s_begin)
        {
            lex_begin_i = i;
            const_count = 0;
        }

        curr_state = state_table[char_to_symbol(text[i])][curr_state];
    
        //Если финальное состояние - сохраняем найденную лексему (и сбрасываем автомат в начальное состояние)
        if (is_final_state(curr_state))
        {
            int length = i - lex_begin_i;
            lex lexem;

            lexem.lex_type = final_state_to_lexem_id(curr_state);
            lexem.str = new unsigned char[length + 1];
            lexem.str[length] = '\0';

            memcpy(lexem.str, text + lex_begin_i, length);
            
            //Проверяем, является ли найденная лексема ключевым словом
            if (curr_state == s_final_id)
            {
                int i = 0;
                for (; i < KW_COUNT; i++)
                {
                    if (!strcmp((char*)lexem.str, keywords[i]))
                    {
                        lexem.lex_type = KW;
                        break;
                    }
                }

                //если не ключевое слово - 
                if (i >= KW_COUNT)
                {
                    if (strlen((char*)lexem.str) > 5)
                    {
                        lexem.lex_type = WL;   
                    }
                }
            }
            
            if (curr_state == s_final_const)
            {   
                if (const_count > 5 || (const_count == 5 && atoi((char*)lexem.str) > 32768))
                {
                    lexem.lex_type = WL;
                }
            }

            lexems->push_back(lexem);

            curr_state = s_begin;
            //чтобы текущий символ стал символом для начального состояния на некст автомате
            i--;
        }

        if (curr_state == s_const)
            const_count++;
        
    }
    while (text[i++]);

    return lexems;
}

void output_lexems(vector<lex>& lexems)
{
    ofstream output(OUTP_FILENAME);
    
    //выводим список лексем
    for (size_t i = 0; i < lexems.size(); i++)
    {
        output << lexems[i].str << "[" << lexems[i].lex_type << "]" << ' ';
    }

    output << endl;

    //выводим список идентификаторов
    for (size_t i = 0; i < lexems.size(); i++)
    {
        if (!strcmp(lexems[i].lex_type, ID))
        {
            output << lexems[i].str << ' ';
        }
    }

    output << endl;

    //выводим список констант
    for (size_t i = 0; i < lexems.size(); i++)
    {
        if (!strcmp(lexems[i].lex_type, VL))
        {
            output << lexems[i].str << ' ';
        }
    }

    output.close();
}

int main()
{
    unsigned char* content = read_whole_file(INP_FILENAME);

    vector<lex>* lexems = analyze_lexems(content);

    output_lexems(*lexems);

    delete [] content;

    for (size_t i = 0; i < lexems->size(); i++)
    {
        delete[] (*lexems)[i].str;
    }

    delete lexems;
    
    return 0;
}
