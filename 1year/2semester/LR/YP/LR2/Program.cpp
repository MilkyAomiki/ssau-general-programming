#include <fstream>
#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;

const char* INP_FILENAME = "input.txt";
const char* OUTP_FILENAME = "output.txt";
const char* FILE_DELIMETER = " ";

/// @brief Представляет 2x2 матрицу с элементами типа double
struct double_matrix
{
    int sizeX, sizeY;
    double** matrix;
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

/// @brief Парсит С-строку в двумерную матрицу
/// @param str C-строка, будет изменена и токенизирована используя strtok!
/// @return 
double_matrix* get_matrix(char* str) 
{
    int y, x;

    char* curr_token = strtok(str, " ");
    y = atoi(curr_token);

    curr_token = strtok(NULL, " ");
    x = atoi(curr_token);

    curr_token = strtok(NULL, " ");
    
    //2 на 2 массив - y указателей на массивы длины x
    double **result = new double * [y];

    int iY = 0;
    while (curr_token != NULL)
    {
        result[iY] = new double[x];
        for (int iX = 0; iX < x; iX++)
        {
            result[iY][iX] = atof(curr_token);
            curr_token = strtok(NULL, " ");
        }

        iY++;
    }

    double_matrix* matrix = new double_matrix;
    matrix -> sizeX = x;
    matrix -> sizeY = y;
    matrix -> matrix = result;

    return matrix;
}

/// @brief Вычислить среднее арифметическое каждой строки
/// @param arr Исходная матрица
/// @param sizeX Размер по X (кол-во столбцов)
/// @param sizeY Размер по Y (кол-во строк)
/// @return
double* calc_average_on_each_y(double** matrix, int sizeX, int sizeY)
{
    double* averages = new double[sizeY];

    for (int iY = 0; iY < sizeY; iY++)
    {
        averages[iY] = 0;
        for (int iX = 0; iX < sizeX; iX++)
        {
            averages[iY] += matrix[iY][iX];
        }

        averages[iY] /= sizeX;
    }

    return averages;
}

int main()
{
    char* content = read_whole_file(INP_FILENAME);

    double_matrix* nums = get_matrix(content);

    delete [] content;

    double* averages = calc_average_on_each_y(nums->matrix, nums->sizeX, nums->sizeY);
    
    ofstream output(OUTP_FILENAME);
    
    if (nums->sizeY > 0)
    {
        cout << averages[0];
        output << " " << averages[0];
    }

    for (int i = 1; i < nums->sizeY; i++)
    {
        cout << " " << averages[i];
        output << " " << averages[i];
    }

    for (int iY = 0; iY < nums->sizeY; iY++)
    {
        delete[] nums->matrix[iY];
    }

    delete [] nums->matrix;
    delete nums;

    output.close();
    delete [] averages;

    return 0;
}
