#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "src/WorkingHours.h"
#include "src/IoExtensions.h"

using namespace std;

/// @brief Count elements of negative and positive integers in a sequence 
int main()
{
	//loop for repeating algo if user needs it
	bool doContinue = false;
	do
	{
		cout << "Choose how to read data:" 	<< endl;
		cout << "1. From console (here)" 	<< endl;
		cout << "2. From file (input.txt)" 	<< endl;
		int numberEntered;
		numberEntered = readIntLine("Choose number: ", cin, cout, false, 2, 1);
		cout << endl;

		vector<WorkingHours> workingHours;
		bool continue_execution = true;
		if (numberEntered == 1)
		{
			workingHours = readWorkingHoursVector(cin, cout);
		}
		else if (numberEntered == 2)
		{
			ifstream ifout;
			ifout.open("input.txt");

			NulOStream dummy_output;
			workingHours = readWorkingHoursVector(ifout, dummy_output, true);

			if (ifout.fail())
			{
				cout << "Error: couldn't read file, wrong format. (succesfully read: " << workingHours.size() << " objects)" << endl;
				continue_execution = false;
			}

			ifout.close();
		}

		if (continue_execution)
		{
			cout << "Choose where to output data:" 	<< endl;
			cout << "1. To console (here)" 		<< endl;
			cout << "2. To file (ouput.txt)"	<< endl;
			numberEntered = readIntLine("Choose number: ", cin, cout, false, 2, 1);
			cout << endl;

			if (numberEntered == 1)
			{
				outputWorkingHoursVector(cout, workingHours, true);
			}
			else if (numberEntered == 2)
			{
				ofstream ofout;
				ofout.open("output.txt");
				outputWorkingHoursVector(ofout, workingHours, false);

				ofout.close();
			}
		}

		doContinue = askWhetherToContinue();
	} while (doContinue);

	return 0;
}
