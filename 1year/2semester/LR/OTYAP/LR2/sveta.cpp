#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Перечисление входных символов автомата
enum signals { Vowel, Consonant, Separator };

// Перечисление состояний автомата
enum states { Start, VowelState, Final, ERROR };

// Проверка на гласную букву русского алфавита
bool isVowel(char c)
{
    return (c == 224 || c == 229 || c == 230 || c == 'и' || c == 'о' || c == 'у' || c == 'ы' || c == 'э' || c == 'ю' || c == 'я' ||
        c == 'А' || c == 'Е' || c == 'Ё' || c == 'И' || c == 'О' || c == 'У' || c == 'Ы' || c == 'Э' || c == 'Ю' || c == 'Я');
}
// Проверка на разделитель
bool isSeparator(char a)
{
    return (a == ' ' || a == '\0' || a == '\n' || a == '\t');
}

// Функция проверки типа входного символа
signals check(char c)
{
    if (isVowel(c)) return Vowel;
    if (isSeparator(c)) return Separator;
    return Consonant;
}

// Таблица состояний автомата
void createTable(states(*table)[4])
{
    table[Vowel][Start] = VowelState;
    table[Vowel][VowelState] = VowelState;
    table[Vowel][ERROR] = ERROR;
    table[Vowel][Final] = ERROR;

    table[Consonant][Start] = ERROR;
    table[Consonant][VowelState] = ERROR;
    table[Consonant][ERROR] = ERROR;
    table[Consonant][Final] = ERROR;

    table[Separator][Start] = ERROR;
    table[Separator][VowelState] = Final;
    table[Separator][ERROR] = ERROR;
    table[Separator][Final] = ERROR;
}

// Функция создания массива для подходящей лексемы
unsigned char* createWord(int begin, int end, unsigned char* text)
{
    int lenWord = end - 1 - begin;
    unsigned char* word = new unsigned char[lenWord];
    int cur = 0;
    for (int i = begin; i < end; i++)
    {
        word[cur] = text[i];
        cur++;
    }
    word[cur] = '\0';
    return word;
}

// Функция, обрабатывающая текст и возвращающая список лексем, удовлетворяющих условию задания
vector<unsigned char*> checkText(unsigned char* text, states(*table)[4], int size)
{
    vector<unsigned char*> answer;
    int beg = 0;
    int end = beg;
    enum states current_state = Start;
    unsigned char* t = text;

    while (end < size)
    {
        current_state = table[check(*t)][current_state];

        if (current_state == Final)
        {
            answer.push_back(createWord(beg, end, text));
            current_state = Start;
            beg = end;
        }

        if (current_state == ERROR)
        {
            while (!isSeparator(*t))
            {
                ++t;
                ++end;
            }
            beg = end;
            current_state = Start;
        }

        ++t;
        ++end;
    }
    return answer;
}

// Функция вывода результирующего вектора
void printVector(vector<unsigned char*> answer, ofstream& fout)
{
    fout << answer[0];
    for (unsigned int i = 1; i < answer.size(); ++i)
    {
        fout << answer[i];
    }
}

int main()
{
    ifstream fin("input.txt");

    int size = 0;
    fin.seekg(0, std::ios::end);
    size = (int)fin.tellg() + 1;
    fin.seekg(0, std::ios::beg);

    unsigned char* text = new unsigned char[size];
    fin.getline((char*)text, size, '\0');

    states current_table[3][4];
    createTable(current_table);

    vector<unsigned char*> answer = checkText(text, current_table, size);

    ofstream fout("output.txt");

    if (answer.size() != 0)
    {
        printVector(answer, fout);
    }

    fin.close();
    fout.close();
    delete[] text;

    return 0;
}