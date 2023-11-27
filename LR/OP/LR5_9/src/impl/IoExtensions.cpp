#include <regex>

#include "../IoExtensions.h"

int readIntLine(string messageBefore, istream& inps, ostream& outs, bool exitOnException, int maxValue, int minValue)
{
	regex reg_matchInts = regex(R"(^[+-]?[0-9]+$)");
	int result = 0;
	bool done = false;
	
	do
	{
		outs << messageBefore;
		try
		{
			string input;
			getline(inps, input);
			result = stoi(input);
			
			//regex to block the case when input is smth like "100ffas"
			if(!regex_match(input, reg_matchInts))
				throw invalid_argument("");

			if (result > maxValue || result < minValue)
			{
				throw out_of_range("");
			}

			done = true;
		}
		catch(const invalid_argument& e)
		{
			string what = "(The number was in invalid format, enter again)";

			outs << what << endl;
			if (exitOnException) throw invalid_argument(what);
		}
		catch(const out_of_range& e)
		{
			string what = "(The number was out of range (" + to_string(minValue) + "<= n <= " + to_string(maxValue) + "), enter again)";

			outs << what << endl;
			
			if (exitOnException) throw out_of_range(what);
		}
	}
	while (!done && !exitOnException);

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

int NulStreambuf::overflow(int c) { return c; }