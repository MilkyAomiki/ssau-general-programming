#include <iostream>
#include <string>
#include <regex>
#include <stdlib.h>
#include <time.h>

//Quicksort with 3-way partition

using namespace std;

const int ARR_PRINT_MAX_SIZE = 50;

void printArray(int* arr, int size)
{
	for (int i = 0; i < size && i < ARR_PRINT_MAX_SIZE; i++)
	{
		cout << arr[i] << " ";
	}
	
	if (size > ARR_PRINT_MAX_SIZE)
	{
		cout << "... (" << size - ARR_PRINT_MAX_SIZE << " more)";
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

int* generateRandomArray(int size)
{
	int* arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		// Get a random number
		int random = rand() % 10;
		arr[i] = random;
	}

	return arr;
}

int* quickSort(int* arr, int size, int lowerBound, int upperBound)
{
	if (lowerBound >= upperBound)
	{
		return arr;
	}
	
	int pivotIndex = (upperBound+lowerBound)/2;
	int  pivot = arr[pivotIndex];

	cout << "pivot: " << pivot << endl;

	swap(arr[pivotIndex], arr[upperBound]);
	
	int lowerIndex = lowerBound, upperIndex = upperBound-1, pivotsIndex = upperBound;

	while (lowerIndex <= upperIndex)
	{
		//in case pivotsIndex slides more to the left than upperBound
		while (upperIndex >= pivotsIndex)
			upperIndex--;

		while (arr[lowerIndex] < pivot)
            lowerIndex++;

        while (arr[upperIndex] > pivot)
            upperIndex--;

		if (lowerIndex <= upperIndex)
        {
			if (arr[lowerIndex] != pivot && arr[upperIndex] != pivot)
			{
				swap(arr[lowerIndex], arr[upperIndex]);
				lowerIndex++;
				upperIndex--;
			}
			else
			{
				if (arr[lowerIndex] == pivot)
				{
					pivotsIndex--;
					swap(arr[pivotsIndex], arr[lowerIndex]);
				}

				if (arr[upperIndex] == pivot)
				{
					pivotsIndex--;
					swap(arr[pivotsIndex], arr[upperIndex]);
				}
			}
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

		int size;
		size = readIntLine();

		// Providing a seed value for random numbers
		srand((unsigned) time(NULL));

		int* arr = generateRandomArray(size);

		cout << "Generated random array: " << endl;
		printArray(arr, size);
		quickSort(arr, size, 0, size-1);

		printArray(arr, size);

		string str_doContinue;
		while (str_doContinue != "y" && str_doContinue != "Y" && str_doContinue != "n" && str_doContinue != "N")
		{
			//asks whether to execute algo again or not
			cout << "Do you want to try again? (y/n)? ";

			getline(cin, str_doContinue);

			if (str_doContinue == "y" || str_doContinue == "Y")
				doContinue = true;
		}

	} while (doContinue);

	return 0;
}
