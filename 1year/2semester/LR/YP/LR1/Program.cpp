//Найти произведение кубов всех положительных элементов массива A={a[i]}

#include <fstream>
#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

const char* INP_FILENAME = "input.txt";
const char* OUTP_FILENAME = "output.txt";
const char* FILE_DELIMETER = " ";

/// @brief Представляет массив с элементами типа double
struct double_array
{
    int size;
    double* array;
};

/// @brief Получает размер файла (считается на стороне жесткого диска)
/// @param filename Путь/название файла
/// @return
int get_filesize(const char* filename)
{
    ifstream is;
    is.open (filename, ios::binary );
    is.seekg (0, ios::end);
    int size = is.tellg();
    is.close();
    
    return size;
}

/// @brief Читает весь файл с данным названием filename в C-строку 
/// @param filename Путь/название файла
/// @return C-строка с содержимым файла
char* read_whole_file(const char* filename)
{
    ifstream input(filename);
    int filesize = get_filesize(filename);

    char* content = new char[filesize+1];
    for (int i = 0; i < filesize; i++)
    {
        input >> noskipws >> content[i];
    }

    input.close();

    content[filesize] = '\0';

    return content;
}

/// @brief Считает количество слов в строке, разделенных знаками пробелов 
/// @param str C-строка
/// @return 
int count_words(char* str)
{
    int count = 0;
    char* curr = str;
    while (*curr)
    {
        if (!isspace(*curr))
        {
            curr++;
            count++;
            while(!isspace(*curr) && *curr) curr++;
        }
        else
        {
            curr++;
        }
    }

    return count;
}

/// @brief Парсит С-строку в массив чисел типа double 
/// @param str C-строка, будет изменена и токенизирована используя strtok!
/// @return 
double_array* get_doubles(char* str) 
{
    int size = count_words(str);
    double* result = new double[size];

    int i = 0;
    char* curr_token = strtok(str, " ");
    while (curr_token != NULL)
    {
        result[i] = atof(curr_token);
        curr_token = strtok(NULL, " ");
        i++;
    }

    double_array* array = new double_array;
    array -> size = size;
    array -> array = result;

    return array;
}

/// @brief Вычислить произведение кубов всех положительный числов в массиве
/// @param arr Массив с исходными числами
/// @param size Размер массива
/// @return
double calc_product_of_cubes(double* arr, int size)
{
    double product = 0;
    
    int i = 0;
    for (; i < size && product == 0; i++)
    {
        if (arr[i] > 0)
        {
            product = pow(arr[i], 3);
        }
    }

    for (; i < size; i++)
    {
        product *= arr[i] > 0? pow(arr[i], 3) : 1.0;
    }
    
    return product;
}

bool is_alternating_digits_letters(char* text)
{
    while (*text)
    {
        
        
        text++;
    }
    
}

int main()
{
    char* content = read_whole_file(INP_FILENAME);

    double_array* nums = get_doubles(content);

    delete [] content;

    double product = calc_product_of_cubes(nums->array, nums->size);
    
    ofstream output(OUTP_FILENAME);
    if (product > 1e+12)
    {
        output.precision(10);
    }
    output << product;

    cout << product;

    delete [] nums->array;
    delete nums;

    output.close();

    return 0;
}
