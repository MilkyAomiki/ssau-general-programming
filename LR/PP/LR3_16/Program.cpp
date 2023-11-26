#include <iostream>
#include <string>
#include <regex>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <time.h>
#include <random>

//Quicksort with 3-way partition

using namespace std;

const long ARR_PRINT_MAX_SIZE = 50;
const bool DEBUG = false;

const int MAX_PERCENT_OF_ALMOST_SORTED_ARR_UNSORTED = 15;

void printArray(vector<int> &arr)
{
	for (long i = 0; i < arr.size() && i < ARR_PRINT_MAX_SIZE; i++)
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
long readLongLine()
{
	regex reg_matchInts = regex(R"(^[+-]?[0-9]+$)");
	long result = 0;
	bool done = false;
	while (!done)
	{
		try
		{
			string input;
			getline(cin, input);
			result = stol(input);

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
			result = stol(input);

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

bool askYesNoQuestion(string textQuestion)
{
	string str_doContinue;
	while (str_doContinue != "y" && str_doContinue != "Y" && str_doContinue != "n" && str_doContinue != "N")
	{
		//asks whether to execute algo again or not
		cout << textQuestion << "(y/n)? ";

		getline(cin, str_doContinue);

		if (str_doContinue == "y" || str_doContinue == "Y")
			return true;
	} 
	return false;
}

vector<int> generateRandomArray(long size, mt19937 mt_rand_gen)
{
	uniform_int_distribution<> rand_arr_element(-10, 10);
	vector<int> arr (size);
	for (long i = 0; i < size; i++)
	{
		// Get a random number
		int random = rand_arr_element(mt_rand_gen);
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
	long lessValsPointer = lowerBound, greaterValsPointer = upperBound;

	//i - указывает на текущий элемент который мы рассматриваем
    long i = lessValsPointer;

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
void quickSort(vector<int> &arr, long lowerBound, long upperBound)
{
	//если верхний указатель достиг нижнего, ничего сортировать не осталось
	//(размер массива для сортировки равен нулю)
	if (lowerBound >= upperBound)
		return;

	pair<long, long> bounds = threeWayPartition(arr, lowerBound, upperBound);
	
	long lowerPointer = bounds.first;
	long upperPointer = bounds.second;

	//сортируем значения, меньшие прошлого pivot
    quickSort(arr, lowerBound, lowerPointer - 1);

	//сортируем значения, большие прошлого pivot
    quickSort(arr, upperPointer + 1, upperBound);
}

void shuffleArray(vector<int> &arr, mt19937 mt_rand_gen)
{
	int num_of_swaps = ceil((arr.size() * MAX_PERCENT_OF_ALMOST_SORTED_ARR_UNSORTED / 100.0) / 2.0);
	int middle_index = arr.size() / 2;
	uniform_int_distribution<> first_half_distr(0, middle_index); // define the range
	uniform_int_distribution<> second_half_distr(middle_index, arr.size()-1); // define the range
	for (int i = 0; i < num_of_swaps; i++)
	{
		int first_half_i = first_half_distr(mt_rand_gen);
		int second_half_i = second_half_distr(mt_rand_gen);

		swap(arr[first_half_i], arr[second_half_i]);
	}
}

void fillWithRandomSortedNumbers(vector<int> &arr, long size, mt19937 mt_rand_gen)
{
	uniform_int_distribution<> starting_number_distr(0-size, size/2); // the range for starting number, not far away from 0
	const int starting_number = starting_number_distr(mt_rand_gen);
	uniform_int_distribution<> bool_distr(0, 2); // the random bool
	
	int curr_number = starting_number;
	for (long i = 0; i < size; i++)
	{
		if (bool_distr(mt_rand_gen))
		{
			arr.push_back(++curr_number);
		}
		else
		{
			arr.push_back(curr_number);
		}
	}
	
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

		long size = -1;
		while (size < 1)
		{
			size = readLongLine();
			if (size < 1)
				cout << "(The number has to be greater than 0)" << endl;
		}

		// Providing a seed value for random numbers
		srand((unsigned) time(NULL));
		random_device rd; // obtain a random number from hardware
		mt19937 mt_rand_gen(rd()); // seed the generator
		
		vector<int> arr;
		if (askYesNoQuestion("Enter array manually?"))
		{
			for (long i = 0; i < size; i++)
			{
				cout << "Element " << i <<endl; 
				arr.push_back(readIntLine());
			}
		}
		else
		{
			if (askYesNoQuestion("Generate almost sorted array (up to " + to_string(MAX_PERCENT_OF_ALMOST_SORTED_ARR_UNSORTED) + "% unsorted)? (if no, pure random)"))
			{
				fillWithRandomSortedNumbers(arr, size, mt_rand_gen);

				shuffleArray(arr, mt_rand_gen);
			}
			else
			{
				arr = generateRandomArray(size, mt_rand_gen);
			}
		}

		vector<int> arr_copy(arr.size());

		for (long i = 0; i < arr.size(); i++)
		{
			arr_copy[i] = arr[i];
		}

		cout << "--------------------------------Initial array--------------------------------" << endl;
		printArray(arr);

		cout << "--------------------------------Quick sort with 3-way partitioning--------------------------------" << endl;
		auto start = chrono::high_resolution_clock::now();
		quickSort(arr, 0, size-1);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

		// To get the value of duration use the count()
		// member function on the duration object
		printArray(arr);
		int localSortingTime = duration.count();
		cout << "Time taken: " << localSortingTime << " microseconds" << endl;

		cout << "--------------------------------Standart sorting algorithm--------------------------------" << endl;

		start = chrono::high_resolution_clock::now();
		sort(begin(arr_copy), end(arr_copy));
		stop = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		printArray(arr_copy);
		int librarySortingTime = duration.count();
		cout << "Time taken: " << librarySortingTime << " microseconds" << endl;
		float libraryTimeDifference = localSortingTime - librarySortingTime;
		cout << "C++ standart sorting algorithm is faster by " << libraryTimeDifference << " microseconds" << endl;

		doContinue = askYesNoQuestion("Do you want to continue?");
	} while (doContinue);

	return 0;
}
