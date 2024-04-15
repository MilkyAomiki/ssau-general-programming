#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

bool is_en_letter_windows1251(unsigned char c)
{
    return
        //uppercase 
        (c >= 0x41 && c <= 0x5A) ||
        //lowercase
        (c >= 0x61 && c <= 0x7A);
}

bool is_digit_windows1251(unsigned char c)
{
    return (c >= 0x30 && c <= 0x39);
}


bool is_separator(unsigned char c)
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

unsigned char* resize_arr(unsigned char* arr, int elements_count, int new_size)
{
    unsigned char* new_arr = new unsigned char[new_size];
    for (int i = 0; i < elements_count; i++)
    {
        new_arr[i] = arr[i];
    }

    delete [] arr;

    return new_arr;
}

vector<unsigned char*> read_words(ifstream& input)
{ //список всех слов из файла
    vector<unsigned char*> words;
    
    //размер массива для сохранения отдельного слова, с потолка взят
    const int MIN_WORD_ARR_SIZE = 100;
    int word_size = MIN_WORD_ARR_SIZE;
    //размер слова в массиве
    int word_count = 0;
    //ссылка на создаваемое в цикле слово
    unsigned char* word = new unsigned char[word_size];
    
    //слово с какими то плохими знаками
    bool is_faulty_word = false;

    //обрабатываем ли в данный момент слово?
    bool is_word_rn = false;

    unsigned char curr_char;
    while (input >> noskipws >> curr_char)
    {
        //наше слово
        if (is_en_letter_windows1251(curr_char) || is_digit_windows1251(curr_char))
        {
            is_word_rn = true;

            //делаем массив больше, если кто то реально вставил настолько длинное слово в тесты
            if (word_count > word_size - 2)
            {
                word_size = word_size + MIN_WORD_ARR_SIZE;
                word = resize_arr(word, word_count, word_size);
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
                word = new unsigned char[word_size];

                word_count = 0;
            }

            //было и было, забываем про неподходящие символы
            is_faulty_word = false;
        }
        //какой то беспредел
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

    return words;
}

bool does_word_satisfy_condition(unsigned char* word)
{  
    bool is_fitting = true;

    int j = 0;

    unsigned char prev_c = word[j];
    unsigned char c = word[++j];

    if (prev_c == '.' || c == '.')
    {
        is_fitting = false;
    }

    //сам алгоритм - находим чередующиеся цифры буквы
    while (c != '.' && is_fitting)
    {
        //e.g. 1a
        if (is_digit_windows1251(prev_c))
        {
            if (!is_en_letter_windows1251(c))
                is_fitting = false;
        }
        //e.g. a1
        else if (is_en_letter_windows1251(prev_c))
        {
            if (!is_digit_windows1251(c))
                is_fitting = false;
        }

        prev_c = c;
        c = word[++j];
    }

    return is_fitting;
}

int main()
{
    ifstream input("input.txt");
   
    vector<unsigned char*> words = read_words(input);

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
        unsigned char* word = words[i];

        bool does_satisfy = does_word_satisfy_condition(word);

        if (does_satisfy)
        {
            if (has_outputed_already)
            {
                cout << ' ';
                output << ' ';
            }

            int j = 0;
            char c = word[j];
            //выводим че наделали
            while (c != '.')
            {
                cout << c;
                output << c;
                c = word[++j];
            }

            has_outputed_already = true;
        }

        delete [] word;
    }

    output.close();

    return 0;
}
