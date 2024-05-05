#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const char* INP_FILENAME = "input.txt";
const char* OUTP_FILENAME = "output.txt";

/// @brief Типы лексем
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
const char* AND = "lo";
const char* OR = "lo";

char* read_whole_file(const char* filename)
{
    ifstream input(filename, ios::binary);

    //Читаем размер файла
    input.seekg(0, ios::end);
    size_t byte_filesize = input.tellg();
    input.seekg(0, ios::beg);

    //Читаем сам файл
    char* content = new char[byte_filesize+1];
    input.read(content, byte_filesize);

    input.close();

    content[byte_filesize] = '\0';

    return content;
}

/// @brief Список состояний лексического анализатора
enum state 
{ 
    s_begin, s_id, s_const, s_less_co, s_co, s_wl, s_eq, s_ao,
    s_final_co, s_lex_final_id, s_final_wl, s_lex_final_const, s_lex_final_eq, s_final_ao 
};

/// @brief Список символов лексического анализатора
enum symbol { letter, digit, less_co, more_co, eq, arithm, delim, other  };

/// @brief Таблица состояний лексического анализатора
const state state_table[8][15] = 
{
    { s_id,      s_id,           s_wl,                s_final_co,  s_final_co, s_wl,       s_lex_final_eq, s_final_ao  },
    { s_const,   s_id,           s_const,             s_final_co,  s_final_co, s_wl,       s_lex_final_eq, s_final_ao  },
    { s_less_co, s_lex_final_id, s_lex_final_const,   s_final_co,  s_final_co, s_final_wl, s_lex_final_eq, s_final_ao  },
    { s_co,      s_lex_final_id, s_lex_final_const,   s_co,        s_final_co, s_final_wl, s_lex_final_eq, s_final_ao  },
    { s_eq,      s_lex_final_id, s_lex_final_const,   s_final_co,  s_final_co, s_final_wl, s_lex_final_eq, s_final_ao  },
    { s_ao,      s_lex_final_id, s_lex_final_const,   s_final_co,  s_final_co, s_final_wl, s_lex_final_eq, s_final_ao  },
    { s_begin,   s_lex_final_id, s_lex_final_const,   s_final_co,  s_final_co, s_final_wl, s_lex_final_eq, s_final_ao  },
    { s_wl,      s_wl,           s_wl,                s_final_co,  s_final_co, s_wl,       s_lex_final_eq, s_final_ao  }
};

/// @brief Список состояний синтаксического анализатора
enum syntax_state 
{ 
    s_if, s_if_operand, s_if_signed_const, s_if_comparison, s_if_operand_R, s_if_signed_const_R, s_if_logexpr_end, s_body_id, s_body_eq, s_body_operand, s_body_operand_signed, s_body_arithm_end, s_else_body_id, s_else_eq, s_else_operand, s_else_operand_signed, s_else_arithm_end,
    s_end, s_final_if, s_final_operand, s_final_id, s_final_const, s_final_comparison, s_final_if_logexpr, s_final_body_arithm_end, s_final_else_airthm_end, s_final_eq 
};

/// @brief Список символов синтаксического анализатора
enum syntax_symbol { syntax_if, syntax_else, syntax_then, syntax_end, syntax_and, syntax_or, syntax_id, syntax_const, syntax_co, syntax_eq, syntax_ao, syntax_ao_ext, syntax_wl  };

/// @brief Таблица состояний синтаксического анализатора
const syntax_state syntax_state_table[13][17] = 
{
    {  s_if_operand, s_final_operand,   s_final_const,   s_final_comparison, s_final_operand,     s_final_operand,  s_final_if_logexpr, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end }, 
    {  s_final_if,   s_final_operand,   s_final_const,   s_final_comparison, s_final_operand,     s_final_operand,  s_final_if_logexpr, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_else_body_id,          s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end }, 
    {  s_final_if,   s_final_operand,   s_final_const,   s_body_id,          s_final_operand,     s_final_operand,  s_body_id,          s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end }, 
    {  s_final_if,   s_final_operand,   s_final_const,   s_final_comparison, s_final_operand,     s_final_operand,  s_final_if_logexpr, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_end,                   s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_end                   }, 
    {  s_final_if,   s_final_operand,   s_final_const,   s_if_operand,       s_final_operand,     s_final_operand,  s_if_operand,       s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end }, 
    {  s_final_if,   s_final_operand,   s_final_const,   s_if_operand,       s_final_operand,     s_final_operand,  s_if_operand,       s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end }, 
    {  s_final_if,   s_if_comparison,   s_final_const,   s_final_comparison, s_if_logexpr_end,    s_final_operand,  s_final_if_logexpr, s_body_eq,  s_final_eq,     s_body_arithm_end,     s_final_const,     s_final_body_arithm_end, s_else_eq,  s_final_eq,     s_else_arithm_end,     s_final_const,     s_final_else_airthm_end }, 
    {  s_final_if,   s_if_comparison,   s_if_comparison, s_final_comparison, s_if_logexpr_end,    s_if_logexpr_end, s_final_if_logexpr, s_final_id, s_final_eq,     s_body_arithm_end,     s_body_arithm_end, s_final_body_arithm_end, s_final_id, s_final_eq,     s_else_arithm_end,     s_else_arithm_end, s_final_else_airthm_end }, 
    {  s_final_if,   s_final_operand,   s_final_const,   s_if_operand_R,     s_final_operand,     s_final_operand,  s_final_if_logexpr, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end }, 
    {  s_final_if,   s_final_operand,   s_final_const,   s_if_operand_R,     s_final_operand,     s_final_operand,  s_final_if_logexpr, s_final_id, s_body_operand, s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_else_operand, s_final_operand,       s_final_const,     s_final_else_airthm_end }, 
    {  s_final_if,   s_if_signed_const, s_final_const,   s_final_comparison, s_if_signed_const_R, s_final_operand,  s_final_if_logexpr, s_final_id, s_final_eq,     s_body_operand_signed, s_final_const,     s_body_operand,          s_final_id, s_final_eq,     s_else_operand_signed, s_final_const,     s_else_operand          }, 
    {  s_final_if,   s_final_operand,   s_final_const,   s_final_comparison, s_final_operand,     s_final_operand,  s_final_if_logexpr, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_body_operand,          s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_else_operand          }, 
    {  s_final_if,   s_final_operand,   s_final_const,   s_final_comparison, s_final_operand,     s_final_operand,  s_final_if_logexpr, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_body_arithm_end, s_final_id, s_final_eq,     s_final_operand,       s_final_const,     s_final_else_airthm_end }, 
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
const char* final_state_to_lexem_id(state s)
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
    char* str;
    /// @brief Тип лексемы
    const char* lex_type;
};

/// @brief Конвертирует идентификатор в тип лексемы, соответствующий одному из позволенных ключевых слов
/// @param str Идентификатор
/// @return тип ключевого слова, если str - ключевое слово. тип идентификатора иначе.
const char* id_to_keyword(char* str)
{
    if(!strcmp(str, "if"))   return IF;
    if(!strcmp(str, "else")) return ELSE;
    if(!strcmp(str, "then")) return THEN;
    if(!strcmp(str, "end"))  return END;
    if(!strcmp(str, "and"))  return AND;
    if(!strcmp(str, "or"))  return OR;

    return ID;
}

/// @brief Проводит лексический анализ над текстом
/// @param text Текст
/// @return Список лексем
vector<lex>* analyze_lexems(char* text)
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
            lexem.str = new char[length + 1];
            lexem.str[length] = '\0';

            memcpy(lexem.str, text + lex_begin_i, length);
            
            //Проверяем, является ли найденная лексема ключевым словом
            if (curr_state == s_lex_final_id)
            {
                lexem.lex_type = id_to_keyword(lexem.str);

                //если не ключевое слово
                if (!strcmp(lexem.lex_type, ID))
                {
                    if (strlen(lexem.str) > 5)
                    {
                        lexem.lex_type = WL;   
                    }
                }
            }

            if (curr_state == s_lex_final_const && const_count > 5)
            {   
                lexem.lex_type = WL;
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

/// @brief Конвертирует лексему в символ синтаксического анализатора
syntax_symbol lexem_to_table_symbol(lex& lexem)
{
    if(!strcmp(lexem.lex_type, IF))   return syntax_if;
    if(!strcmp(lexem.lex_type, ELSE)) return syntax_else;
    if(!strcmp(lexem.lex_type, THEN)) return syntax_then;
    if(!strcmp(lexem.lex_type, END))  return syntax_end;
    if(!strcmp(lexem.lex_type, AND))  return syntax_and;
    if(!strcmp(lexem.lex_type, OR))   return syntax_or;

    if(!strcmp(lexem.lex_type, CO))   return syntax_co;
    if(!strcmp(lexem.lex_type, EQ))   return syntax_eq;
    if(!strcmp(lexem.lex_type, AO))   return syntax_ao;
    if(!strcmp(lexem.lex_type, WL))   return syntax_wl;
    if(!strcmp(lexem.lex_type, ID))   return syntax_id;
    if(!strcmp(lexem.lex_type, VL))   return syntax_const;

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
        || s == s_final_if_logexpr
        || s == s_final_body_arithm_end
        || s == s_final_else_airthm_end
        || s == s_final_eq;
}

bool is_syntax_signed_const_state(syntax_state s)
{
    return s == s_if_signed_const 
        || s == s_if_signed_const_R 
        || s == s_body_operand_signed 
        || s == s_else_operand_signed;
}

/// @brief Конвертирует состояние в строку ожидаемых лексем на его месте
/// @param state Состояние синтаксического анализатора
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
            return "co th";
        case s_final_if_logexpr:
            return "th lo";
        case s_final_body_arithm_end:
            return "ao el en";
        case s_final_else_airthm_end:
            return "ao en";
        case s_final_eq:
            return "eq";
        default:
            return "";
    }
}

/// @brief Результат синтаксического анализа
struct syntax_analysis_res
{
    /// @brief Ошибок в списке лексем не было
    bool successful;

    /// @brief Если ошибка была, ее позиция
    int position;

    /// @brief Лексемы, ожидаемые на месте ошибки
    const char* required_lexems;

    syntax_analysis_res(): successful(false), position(0), required_lexems(NULL)
    {}
};

/// @brief Функция производящая синтаксический анализ
/// @param lexems Список лексем
syntax_analysis_res analyze_syntax(vector<lex>& lexems)
{
    enum syntax_state curr_state = s_if;
    syntax_analysis_res res;

    for (size_t i = 0; i < lexems.size(); i++)
    {
        //для проверки констант
        syntax_state prev_state = curr_state;

        //переходим в следующее состояние
        syntax_symbol symbol = lexem_to_table_symbol(lexems[i]);
        curr_state = syntax_state_table[symbol][curr_state];

        //проверяем что число в разрешенном диапазоне
        if (symbol == syntax_const)
        {
            lex vl_lex = lexems[i];
            int vl = atoi(vl_lex.str);

            if(is_syntax_signed_const_state(prev_state) && !strcmp(lexems[i-1].str, "-"))
                vl = -vl;

            if (vl < -32768 || vl > 32767)
                curr_state = s_final_const;   
        }

        if (is_syntax_final_state(curr_state))
        {
            res.position = i;
            if (curr_state == s_end) //конструкция успешно пройдена
            {
                res.successful = true;
                curr_state = s_if;
            }
            else //нашлись ошибки
            {
                res.successful = false;
                res.required_lexems = final_state_to_required_lexems(curr_state);
                break;
            }
        }
    }

    //конструкция оборвалась
    if (!is_syntax_final_state(curr_state) && curr_state != s_if)
    {
        //у нас по сути wl сейчас
        curr_state = syntax_state_table[syntax_wl][curr_state];

        res.successful = false;
        res.position = lexems.size();
        res.required_lexems = final_state_to_required_lexems(curr_state);
    }

    return res;
}

/// @brief Выводит результат синтаксического анализа
/// @param analysis_res 
/// @param lexems 
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
    char* content = read_whole_file(INP_FILENAME);

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
