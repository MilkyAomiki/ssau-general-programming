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

/// @brief Tries to convert string double, throws invalid_argument with readable text if it goes wrong
/// @return converted strNumber of type double
double parseRealNum(string strNumber)
{
	regex reg_matchRealNums = regex(R"(^[+-]?[0-9]+([,.][0-9]+)?$)");
	double result = 0;

	try
	{
		result = stod(strNumber);

		//regex to block the case when input is smth like "100ffas"
		if(!regex_match(strNumber, reg_matchRealNums))
			throw invalid_argument("");
	}
	catch(const invalid_argument& e)
	{
		throw invalid_argument("(The number was in invalid format)");
	}
	catch(const out_of_range& e)
	{
		throw invalid_argument("(The number was way too big)");
	}

	return result;
}

/// @brief shows greetingText to user, then reads entered number of type double
/// @return entered double
double readDouble(string greetingText)
{
	string inp;
	double result;
	bool readValueSuccessfully = false;

	do
	{
		cout << greetingText;
		cin >> inp;
		try
		{
			result = parseRealNum(inp);
			readValueSuccessfully = true;
		}
		catch(invalid_argument& e)
		{
			cout << e.what() << endl;
		}
	} while(!readValueSuccessfully);

	return result;
}

/// @brief shows greetingText to user, then reads entered number of type double
/// @return entered double
double readDoubleBetween0and1(string greetingText)
{
	string inp;
	double result;
	bool readValueSuccessfully = false;

	do
	{
		cout << greetingText;
		cin >> inp;
		try
		{
			result = parseRealNum(inp);
			if (result < -1 || result > 1)
			{
				throw invalid_argument("(The number has to be between -1 and 1, inclusive)");
			}
			
			readValueSuccessfully = true;
		}
		catch(invalid_argument& e)
		{
			cout << e.what() << endl;
		}
	} while(!readValueSuccessfully);

	return result;
}

int countLines(istream &inps)
{
	int number_of_lines = 0;
	string line;
	while (getline(inps, line))
		++number_of_lines;

	return number_of_lines;
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