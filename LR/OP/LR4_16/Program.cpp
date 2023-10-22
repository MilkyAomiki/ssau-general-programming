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
