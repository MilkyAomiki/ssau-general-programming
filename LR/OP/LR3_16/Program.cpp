#include <iostream>
#include <string>
#include <regex>
#include <stdlib.h>
#include <time.h>

//Quicksort with 3-way partition

using namespace std;

const int ARR_PRINT_MAX_SIZE = 50;
const bool DEBUG = false;

void printArray(vector<int> &arr)
{
	for (int i = 0; i < arr.size() && i < ARR_PRINT_MAX_SIZE; i++)
	{
		cout << arr[i] << " ";
	}
	
	if (arr.size() > ARR_PRINT_MAX_SIZE)
	{
		cout << "... (" << arr.size() - ARR_PRINT_MAX_SIZE << " more)";
	}

	cout << endl;	
}

/// @brief Reads int and performs input validation, asks for input again if needed 
/// @return input int
int readIntLine()
{
	regex reg_matchInts = regex(R"(^[+-]?[0-9]+$)");
	int result = 0;
	bool done = false;
	while (!done)
	{
		try
		{
			string input;
			getline(cin, input);
			result = stoi(input);

			//regex to block the case when input is smth like "100ffas"
			if(!regex_match(input, reg_matchInts))
				throw invalid_argument("");

			done = true;
		}
		catch(const invalid_argument& e)
		{
			cout << "(The number was in invalid format, enter again)\n";
		}
		catch(const out_of_range& e)
		{
			cout << "(The number was way too big, enter again)\n";
		}
	}

	return result;
}

bool askWhetherToContinue()
{
	string str_doContinue;
	while (str_doContinue != "y" && str_doContinue != "Y" && str_doContinue != "n" && str_doContinue != "N")
	{
		//asks whether to execute algo again or not
		cout << "Do you want to try again? (y/n)? ";

		getline(cin, str_doContinue);

		if (str_doContinue == "y" || str_doContinue == "Y")
			return true;
	} 
	return false;
}

vector<int> generateRandomArray(int size)
{
	vector<int> arr (size);
	for (int i = 0; i < size; i++)
	{
		// Get a random number
		int random = rand() % 10;
		arr[i] = random;
	}

	return arr;
}

/// @brief сортирует подмассив заданный аргументами в виде [elements less than pivot, pivots, elements greater than pivot]
/// @param arr массив
/// @param lowerBound нижний индекс массива 
/// @param upperBound верхний индекс массива
/// @return пару {указатель на элемент один правее от {elements less than pivot}, указатель на элемент один левее от {elements greater than pivot}}
pair<int, int> threeWayPartition(vector<int> &arr, int lowerBound, int upperBound)
{
	//выбираем первый элемент как pivot
	int  pivot = arr[lowerBound];
	
	// lessValsPointer - указывает на последний малый элемент
	// greaterValsPointer - указывает на последний больший элемент
	int lessValsPointer = lowerBound, greaterValsPointer = upperBound;

	//i - указывает на текущий элемент который мы рассматриваем
    int i = lessValsPointer;
	
	if (DEBUG)
	{
		cout << "-------------partition run--------------------" << endl;
		cout << "pivot: " << pivot << endl;
		cout << "(lower pointer: " << lowerBound << ", upper pointer: " << upperBound << ")" << endl;
	}

	//Пока итерируемся, arr[i] может быть одним из трех:
	//1. равно pivot - пропускаем 
	//2. меньше pivot - переносим за черту lessValsPointer, за пропущенные pivot
	//3. больше pivot - переносим за черту greaterValsPointer, перед пропущенными pivot и еще не пройденными arr[i]
	//
	// что то такое посреди работы цикла:
	//   lessValsPointer             i             greaterValsPointer
	//[-1, -5, -9, | 4, 4, 4, 4, 4, | 1, 4, 9, 0, 8, 3 |, 12, 41, 49, 50 ]
	//
	// что то такое после работы цикла:
	//   lessValsPointer       greaterValsPointer
	//[-1, -5, -9, | 4, 4, 4, 4, 4 |, 12, 41, 49, 50 ]

	// если i > greaterValsPointer - непройденные arr[i] схлопнулись
    while (i <= greaterValsPointer) {
		if (DEBUG) printArray(arr);

        if (arr[i] < pivot)
            swap(arr[i++], arr[lessValsPointer++]);
        else if (arr[i] > pivot)
            swap(arr[i], arr[greaterValsPointer--]);
        else
            i++;
    }
	
	if (DEBUG)
	{
		printArray(arr);
		cout << "-----------------------------------------------" << endl;
	}

	return {lessValsPointer, greaterValsPointer};
}

/// @brief performs three-way quick sort in-place on arr 
/// @return input int
void quickSort(vector<int> &arr, int lowerBound, int upperBound)
{
	//если верхний указатель достиг нижнего, ничего сортировать не осталось
	//(размер массива для сортировки равен нулю)
	if (lowerBound >= upperBound)
		return;

	pair<int, int> bounds = threeWayPartition(arr, lowerBound, upperBound);
	
	int lowerPointer = bounds.first;
	int upperPointer = bounds.second;

	//сортируем значения, меньшие прошлого pivot
    quickSort(arr, lowerBound, lowerPointer - 1);

	//сортируем значения, большие прошлого pivot
    quickSort(arr, upperPointer + 1, upperBound);
}

/// @brief Count elements of negative and positive integers in a sequence 
int main()
{
	//loop for repeating algo if user needs it
	bool doContinue = false;
	do
	{
		doContinue = false;
		cout << "Enter the number of elements:\n";

		int size = -1;
		while (size < 1)
		{
			size = readIntLine();
			if (size < 1)
				cout << "(The number has to be greater than 0)" << endl;
		}

		// Providing a seed value for random numbers
		srand((unsigned) time(NULL));

		vector<int> arr = generateRandomArray(size);

		cout << "Generated random array: " << endl;
		printArray(arr);

		cout << "Sorted array: " << endl;
		quickSort(arr, 0, size-1);

		printArray(arr);

		doContinue = askWhetherToContinue();
	} while (doContinue);

	return 0;
}
