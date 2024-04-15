#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

bool is_en_letter_windows1251(char c)
{
    return
        //uppercase 
        (c >= 0x41 && c <= 0x5A) ||
        //lowercase
        (c >= 0x61 && c <= 0x7A);
}

bool is_en_letter(char c)
{
    return is_en_letter_windows1251(c);
}

bool is_digit_windows1251(char c)
{
    return (c >= 0x31 && c <= 0x39);
}

bool is_digit(char c)
{
    return is_digit_windows1251(c);
}


bool is_separator(char c)
{
    switch (c)
    {
        case ' ':
        case '\t':
        case '\n':
            return true;

        default:
            return false;
    }
}

int main()
{
    ifstream input("input.txt");
    //список всех слов из файла
    vector<char*> words;
    
    //размер массива для сохранения отдельного слова, с потолка взят
    const int MIN_WORD_ARR_SIZE = 100;
    int word_size = MIN_WORD_ARR_SIZE;
    //размер слова в массиве
    int word_count = 0;
    //ссылка на создаваемое в цикле слово
    char* word = new char[word_size];
    
    //слово с какими то плохими знаками
    bool is_faulty_word = false;

    //обрабатываем ли в данный слово?
    bool is_word_rn = false;

    char curr_char;
    while (input >> noskipws >> curr_char)
    {
        //наше слово
        if (is_en_letter(curr_char) || is_digit(curr_char))
        {
            is_word_rn = true;

            //делаем массив больше, если кто то реально вставил настолько длинное слово в тесты
            if (word_count > word_size - 2)
            {
                int new_size = word_size + MIN_WORD_ARR_SIZE;
                char* new_word = new char[new_size];
                for (int i = 0; i < word_size; i++)
                {
                    new_word[i] = word[i];
                }

                delete word;
                word = new_word;
                word_size = new_size;
            }

            word[word_count] = curr_char;
            word_count++;
            
            //обозначаем где закончилось слово, чтоб потом понятно было
            word[word_count] = '.';
        }
        //разделители слов ненужные
        else if (is_separator(curr_char))
        {
            //особый случай - предыдущий элемент в потоке был последней буквой слова
            if (is_word_rn)
            {
                //если не было неподходящих символов - добавляем
                if (!is_faulty_word)
                {
                    words.push_back(word);
                }
                is_word_rn = false;
                word_size = MIN_WORD_ARR_SIZE;
                word = new char[word_size];

                word_count = 0;
            }

            //было и было, забываем про неподходящие символы
            is_faulty_word = false;
        }
        //какой то беспредел, неподходящие символы
        else
        {   
            //пропускаем, помечаем что такое было в случае если мы в слове
            is_faulty_word = true;
        }
    }

    //крайний случай, слово было в самом конце файла
    if (word_count > 0)
    {
        if (!is_faulty_word)
        {
            words.push_back(word);
        }

        word_count = 0;
    }

    input.close();
    
    //Свойства найденных слов здесь:
    //1. Каждое минимум один символ латинский или цифра
    //2. Каждое заканчивается точкой
    //(минимальное слово: a.)

    ofstream output("output.txt");

    //чтоб лишний пробел не поставить а то вдруг что
    bool has_outputed_already = false;

    //проходим через слова делаем наш бизнесс
    for (size_t i = 0; i < words.size(); i++)
    {
        char* word = words[i];

        bool is_fitting = true;

        //true = first letter
        //false = second letter
        int j = 0;

        //и таким образом слова длины 1 автоматически не рассматриваются
        char prev_c = word[j];
        char c = word[++j];

        //сам алгоритм - находим чередующиеся цифры буквы
        while (c != '.' && is_fitting)
        {
            //e.g. 1a
            if (is_digit(prev_c))
            {
                if (!is_en_letter(c))
                    is_fitting = false;
            }
            //e.g. a1
            else if (is_en_letter(prev_c))
            {
                if (!is_digit(c))
                    is_fitting = false;
            }

            prev_c = c;
            c = word[++j];
        }

        if (is_fitting)
        {
            if (has_outputed_already)
            {
                cout << ' ';
                output << ' ';
            }

            j = 0;
            c = word[j];
            //выводим че наделали
            while (c != '.')
            {
                cout << c;
                output << c;
                c = word[++j];
            }

            has_outputed_already = true;
        }

        delete word;
    }

    output.close();

    return 0;
}
