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
		NulOStream dummy_output;

		//Ввод данных
		cout << "Choose how to read data:" 	<< endl;
		cout << "1. From console (here)" 	<< endl;
		cout << "2. From file (input.txt)" 	<< endl;
		int numberEntered;
		numberEntered = readIntLine("Choose number: ", cin, cout, false, 2, 1);
		cout << endl;

		vector<WorkingHours> workingHours;
		bool continue_execution = true;
		if (numberEntered == 1) //Читаем из консоли
		{
			int objects_num = 0;

			objects_num = readIntLine("Enter the number of objects: ", cin, cout, false, INT_MAX, 1);
			workingHours = readWorkingHoursVector(cin, cout, dummy_output, objects_num, true);
		}
		else if (numberEntered == 2) //Читаем из файла
		{
			ifstream ifout;
			ifout.open("input.txt");

			int number_of_lines = 0;
			std::string line;
			while (std::getline(ifout, line))
				++number_of_lines;
			ifout.close();
			ifout.open("input.txt");

			try
			{
				workingHours = readWorkingHoursVector(ifout, dummy_output, cout, number_of_lines, false);
			}
			catch(const std::exception& e)
			{
				cout << "Error: couldn't read file with the following error: '" << e.what() << "'" << endl;
				continue_execution = false;
			}

			if (ifout.fail() && continue_execution)
			{
				cout << "Error: couldn't read file, wrong format. (succesfully read: " << workingHours.size() << " objects)" << endl;
				continue_execution = false;
			}

			ifout.close();
		}

		//Вывод данных
		if (continue_execution)
		{
			cout << "Choose where to output data:" 	<< endl;
			cout << "1. To console (here)" 		<< endl;
			cout << "2. To file (ouput.txt)"	<< endl;
			numberEntered = readIntLine("Choose number: ", cin, cout, false, 2, 1);
			cout << endl;

			if (numberEntered == 1) //Выводим в консоль
			{
				outputWorkingHoursVector(cout, workingHours, true);
			}
			else if (numberEntered == 2) //Выводим в файл
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
