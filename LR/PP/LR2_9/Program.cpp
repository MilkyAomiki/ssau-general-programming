#include <iostream>
#include <regex>
#include <vector>

using namespace std;

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

bool askWhetherToContinue()
{
	//asks whether to execute algo again or not
	char char_doContinue = ' ';
	while (char_doContinue != 'y' && char_doContinue != 'Y' && char_doContinue != 'n' && char_doContinue != 'N')
	{
		cout << "Do you want to try again? (y/n)? ";
		cin >> char_doContinue;

		if (char_doContinue == 'y' || char_doContinue == 'Y')
			return true;
	}

	return false;
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

double calcSeriesTermAtN(double x, int n)
{
	return ( pow(-1, n+1) * pow(x, 2*n+1) ) / (4 * pow(n, 2)-1);
}

vector<SeriesTerm> calcAndPrintSeriesSum(double alpha, double x)
{
	int intAlpha = alpha;

	double sum = 0;
	double a_n1 = calcSeriesTermAtN(x, 1);
	vector<SeriesTerm> seriesTerms;
	if (intAlpha == alpha)
	{
		for (int n = 1; n <= intAlpha; n++)
		{
			double a_curr = a_n1;
			a_n1 = calcSeriesTermAtN(x, n+1);

			sum += (x + 2*a_curr);
			double meassError = abs(a_n1/sum);

			SeriesTerm currTerm;
			currTerm.iterationNumber = n;
			currTerm.currentTerm = a_curr;
			currTerm.partialSum = sum;
			currTerm.measurementError;

			seriesTerms.push_back(currTerm);
		}
	}
	else
	{
		int n = 1;
		double meassError = 0;
		do
		{
			double a_curr = a_n1;
			a_n1 = calcSeriesTermAtN(x, n+1);

			sum += (x + 2*a_curr);
			meassError = abs(a_n1/sum);

			cout << "Iteration number: " << n << "; Last summed element: " << a_curr << "; Partial sum: " << sum << "; Measurment error: " << meassError << endl;
			n++;
		} while (meassError > alpha);
	}

	return seriesTerms;
}

class SeriesTerm {
	public: 
		int iterationNumber;
		int currentTerm;
		int partialSum;
		double measurementError;
}

int main() {

	//loop for repeating algo if user needs it
	bool doContinue = false;
	do
	{
		doContinue = false;
		double alpha, x;

		alpha = readDouble("Enter alpha: ");
		x = readDoubleBetween0and1("Enter x: ");

		calcAndPrintSeriesSum(alpha, x);

		return askWhetherToContinue();

	} while (doContinue);
}
