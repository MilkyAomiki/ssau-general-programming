#include <iostream>
#include <string>
#include <regex>
#include <stdlib.h>
#include <time.h>

//Quicksort with 3-way partition

using namespace std;

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

		// Providing a seed value
		srand((unsigned) time(NULL));

		int* arr = new int[size];
		for (int i = 0; i < size; i++)
		{
			// Get a random number
			int random = rand();
			arr[i] = random;
		}

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
