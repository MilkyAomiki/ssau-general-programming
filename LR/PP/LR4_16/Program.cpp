#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

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
		ifstream ifout;
		ifout.open("input.txt");

		string input;
		char current;
		//This reads the integer and returns the stream. When a stream is used as bool value it checks to see if the stream is valid. Valid means eof() and bad() are both false
		while (ifout >> noskipws >> current)
		{
			input += current;
		}

		ifout.close();

		ofstream ofout;
		ofout.open("output.txt");
		ofout.clear();

		vector<string> nums;
		bool consecutive_nums = false;

		for (int i = 0; i < input.size(); i++)
		{
			char curr = input[i];

			if (!isdigit(curr))
			{
				if (consecutive_nums)
				{
					consecutive_nums = false;
				}

				ofout << curr;
			}
			else
			{
				if (!consecutive_nums)
				{
					consecutive_nums = true;
					nums.push_back("");
				}
				
				nums.back() += curr;
			}
		}

		ofout << endl;

		for (int i = 0; i < nums.size(); i++)
		{
			ofout << "{" << nums[i] << "}";
		}

		ofout << endl;

		ofout.close();

		doContinue = askWhetherToContinue();
	} while (doContinue);

	return 0;
}
