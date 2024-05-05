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

const char* IF = "if";
const char* ELSE = "el";
const char* THEN = "th";
const char* END = "en";

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
enum lex_state { 
    s_begin, s_id, s_const, s_less_co, s_more_co, s_double_co, s_wl, s_eq, s_ao,
    s_final_co, s_lex_final_id, s_final_wl, s_lex_final_const, s_lex_final_eq, s_final_ao };

/// @brief Список символов
enum lex_symbol { letter, digit, less_co, more_co, eq, arithm, delim, other  };

/// @brief Таблица состояний
const lex_state lex_state_table[8][15] = 
{
    { s_id,      s_id,       s_wl,          s_final_co,  s_final_co,  s_final_co, s_wl,       s_lex_final_eq, s_final_ao  },
    { s_const,   s_id,       s_const,       s_final_co,  s_final_co,  s_final_co, s_wl,       s_lex_final_eq, s_final_ao  },
    { s_less_co, s_lex_final_id, s_lex_final_const, s_final_co,  s_final_co, s_final_co, s_final_wl,  s_lex_final_eq, s_final_ao  },
    { s_more_co, s_lex_final_id, s_lex_final_const, s_double_co, s_final_co,  s_final_co, s_final_wl, s_lex_final_eq, s_final_ao  },
    { s_eq,      s_lex_final_id, s_lex_final_const, s_double_co, s_double_co, s_final_co, s_final_wl, s_lex_final_eq, s_final_ao  },
    { s_ao,      s_lex_final_id, s_lex_final_const, s_final_co,  s_final_co,  s_final_co, s_final_wl, s_lex_final_eq, s_final_ao  },
    { s_begin,   s_lex_final_id, s_lex_final_const, s_final_co,  s_final_co,  s_final_co, s_final_wl, s_lex_final_eq, s_final_ao  },
    { s_wl,      s_wl,       s_wl,          s_final_co,  s_final_co,  s_final_co, s_wl,       s_lex_final_eq, s_final_ao  }
};

/// @brief Список состояний
enum syntax_state { s_if, s_if_operand, s_if_signed_const, s_if_comparison, s_if_operand_R, s_if_signed_const_R, s_then, s_body_id, s_body_eq, s_body_operand, s_body_operand_signed, s_body_arithm_end, s_else_body_id, s_else_eq, s_else_operand, s_else_operand_signed, s_else_arithm_end, s_end, s_final_if, s_final_operand, s_final_id, s_final_const, s_final_comparison, s_final_then, s_final_body_arithm_end, s_final_else_airthm_end, s_final_eq };

/// @brief Список символов
enum syntax_symbol { syntax_if, syntax_else, syntax_then, syntax_end, syntax_id, syntax_const, syntax_co, syntax_eq, syntax_ao, syntax_wl  };

/// @brief Таблица состояний
const syntax_state syntax_state_table[10][17] = 
{
    {  s_if_operand, s_final_operand,   s_final_const,   s_final_comparison, s_final_operand,     s_final_operand, s_final_then, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end },
    {  s_final_if,   s_final_operand,   s_final_const,   s_final_comparison, s_final_operand,     s_final_operand, s_final_then, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_else_body_id,          s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end },
    {  s_final_if,   s_final_operand,   s_final_const,   s_body_id,          s_final_operand,     s_final_operand, s_body_id,    s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end },
    {  s_final_if,   s_final_operand,   s_final_const,   s_final_comparison, s_final_operand,     s_final_operand, s_final_then, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_end,                   s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_end                   },
    {  s_final_if,   s_if_comparison,   s_final_const,   s_final_comparison, s_then,              s_final_operand, s_final_then, s_body_eq,  s_final_eq,     s_body_arithm_end,     s_final_const,     s_final_body_arithm_end, s_else_eq,  s_final_eq,     s_else_arithm_end,     s_final_const,     s_final_else_airthm_end },
    {  s_final_if,   s_if_comparison,   s_if_comparison, s_final_comparison, s_then,              s_then,          s_final_then, s_final_id, s_final_eq,     s_body_arithm_end,     s_body_arithm_end, s_final_body_arithm_end, s_final_id, s_final_eq,     s_else_arithm_end,     s_else_arithm_end, s_final_else_airthm_end },
    {  s_final_if,   s_final_operand,   s_final_const,   s_if_operand_R,     s_final_operand,     s_final_operand, s_final_then, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end },
    {  s_final_if,   s_final_operand,   s_final_const,   s_if_operand_R, s_final_operand,     s_final_operand, s_final_then, s_final_id, s_body_operand, s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_else_operand, s_final_operand,       s_final_const,     s_final_else_airthm_end },
    {  s_final_if,   s_if_signed_const, s_final_const,   s_final_comparison, s_if_signed_const_R, s_final_operand, s_final_then, s_final_id, s_final_eq,     s_body_operand_signed, s_final_const,     s_body_operand,          s_final_id, s_final_eq,     s_else_operand_signed, s_final_const,     s_else_operand          },
    {  s_final_if,   s_final_operand,   s_final_const,   s_final_comparison, s_final_operand,     s_final_operand, s_final_then, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end },
};


bool is_separator(unsigned char c)
{
    return isspace(c) || c == '\0';
}

/// @brief Конверитрует символ в его представление в enum символов
/// @param s символ
/// @return значение в enum символов
lex_symbol char_to_symbol(unsigned char s)
{
    if (isalpha(s)) return letter;
    if (isdigit(s)) return digit;
    if (is_separator(s)) return delim;
    if (s == '<') return less_co;
    if (s == '>') return more_co;
    if (s == '=') return eq;
    if (s == '+' || s == '-') return arithm;
    return other;
}

bool is_final_state(lex_state s)
{
    return 
        s == s_final_co    ||
        s == s_lex_final_id    ||
        s == s_final_wl    ||
        s == s_lex_final_const ||
        s == s_lex_final_eq    ||
        s == s_final_ao
    ;
}

/// @brief Переводит финальное состояние в тип лексемы
/// @param s Состояние
/// @return Тип лексемы, либо пустая строка если состояние - не финальное
const char* final_state_to_lexem_id(lex_state s)
{
    switch (s)
    {
        case s_final_co:
            return CO;
        case s_lex_final_id:
            return ID;
        case s_final_wl:
            return WL;
        case s_lex_final_const:
            return VL;
        case s_lex_final_eq:
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

const char* id_to_keyword(char* str)
{
    if(!strcmp(str, "if"))   return IF;
    if(!strcmp(str, "else")) return ELSE;
    if(!strcmp(str, "then")) return THEN;
    if(!strcmp(str, "end"))  return END;

    return ID;
}

/// @brief Проводит лексический анализ над текстом
/// @param text Текст
/// @return Список лексем
vector<lex>* analyze_lexems(unsigned char* text)
{
    vector<lex>* lexems = new vector<lex>();
    enum lex_state curr_state = s_begin;
    int i = 0, lex_begin_i = 0;

    do
    {
        if (curr_state == s_begin)
        {
            lex_begin_i = i;
        }

        curr_state = lex_state_table[char_to_symbol(text[i])][curr_state];
    
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
            if (curr_state == s_lex_final_id)
            {
                lexem.lex_type = id_to_keyword((char*)lexem.str);
            }

            lexems->push_back(lexem);

            curr_state = s_begin;
            //чтобы текущий символ стал символом для начального состояния на некст автомате
            i--;
        }
    }
    while (text[i++]);

    return lexems;
}

syntax_symbol lexem_to_table_symbol(lex& lexem)
{
    if(!strcmp((char*)lexem.lex_type, IF))   return syntax_if;
    if(!strcmp((char*)lexem.lex_type, ELSE)) return syntax_else;
    if(!strcmp((char*)lexem.lex_type, THEN)) return syntax_then;
    if(!strcmp((char*)lexem.lex_type, END))  return syntax_end;

    if(!strcmp((char*)lexem.lex_type, CO))   return syntax_co;
    if(!strcmp((char*)lexem.lex_type, EQ))   return syntax_eq;
    if(!strcmp((char*)lexem.lex_type, AO))   return syntax_ao;
    if(!strcmp((char*)lexem.lex_type, WL))   return syntax_wl;
    if(!strcmp((char*)lexem.lex_type, ID))   return syntax_id;
    if(!strcmp((char*)lexem.lex_type, VL))   return syntax_const;

    throw exception();
}

bool is_syntax_final_state(syntax_state s)
{
    return s == s_end
        || s == s_final_if
        || s == s_final_operand
        || s == s_final_id
        || s == s_final_const
        || s == s_final_comparison
        || s == s_final_then
        || s == s_final_body_arithm_end
        || s == s_final_else_airthm_end
        || s == s_final_eq;
}

const char* final_state_to_required_lexems(syntax_state state)
{
    switch (state)
    {
        case s_final_if:
            return "if";
        case s_final_operand:
            return "id vl";
        case s_final_id:
            return "id";
        case s_final_const:
            return "vl";
        case s_final_comparison:
            return "co then";
        case s_final_then:
            return "then";
        case s_final_body_arithm_end:
            return "ao else end";
        case s_final_else_airthm_end:
            return "ao end";
        case s_final_eq:
            return "eq";
        default:
            return "";
    }
}

struct syntax_analysis_res
{
    bool successful;
    int position;
    const char* required_lexems;

    syntax_analysis_res(): successful(false), position(0), required_lexems(NULL)
    {}
};

syntax_analysis_res analyze_syntax(vector<lex>& lexems)
{
    enum syntax_state curr_state = s_if;
    syntax_analysis_res res;

    for (size_t i = 0; i < lexems.size(); i++)
    {
        curr_state = syntax_state_table[lexem_to_table_symbol(lexems[i])][curr_state];    

        if (is_syntax_final_state(curr_state))
        {
            res.position = i;
            if (curr_state == s_end) //success
            {
                res.successful = true;
                curr_state = s_if;
            }
            else
            {
                res.successful = false;
                res.required_lexems = final_state_to_required_lexems(curr_state);
                break;
            }
        }
    }

    return res;
}

void output_lexems(syntax_analysis_res analysis_res, vector<lex>& lexems)
{
    ofstream output(OUTP_FILENAME);
    
    //выводим список лексем
    for (size_t i = 0; i < lexems.size(); i++)
    {
        output << lexems[i].str << "[" << lexems[i].lex_type << "]" << ' ';
    }

    output << endl;

    if (analysis_res.successful)
    {
        output << "OK";
    }
    else
    {
        output << analysis_res.position << " " << analysis_res.required_lexems;
    }

    output.close();
}

int main()
{
    unsigned char* content = read_whole_file(INP_FILENAME);

    vector<lex>* lexems = analyze_lexems(content);
    syntax_analysis_res res = analyze_syntax(*lexems);

    output_lexems(res, *lexems);

    delete [] content;

    for (size_t i = 0; i < lexems->size(); i++)
    {
        delete[] (*lexems)[i].str;
    }

    delete lexems;
    
    return 0;
}
