#include <iostream>
#include <string>
#include <regex>

using namespace std;

//A saddle point of a matrix is an element which is both the largest element in its column and the smallest element in its row.

/// @brief Parses strNumber into double, throws invalid_argument if string is in wrong format 
/// @return parsed double
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
		throw invalid_argument("(The number was in invalid format, enter again)");
	}
	catch(const out_of_range& e)
	{
		throw invalid_argument("(The number was way too big, enter again)");
	}

	return result;
}

/// @brief Parses strNumber into int, throws invalid_argument if string is in wrong format 
/// @return parsed int
int parseIntNum(string strNumber)
{
	regex reg_matchRealNums = regex(R"(^[+-]?[0-9]+$)");
	int result = 0;

	try
	{
		result = stoi(strNumber);

		//regex to block the case when input is smth like "100ffas"
		if(!regex_match(strNumber, reg_matchRealNums))
			throw invalid_argument("");
	}
	catch(const invalid_argument& e)
	{
		throw invalid_argument("(The number was in invalid format, enter again)");
	}
	catch(const out_of_range& e)
	{
		throw invalid_argument("(The number was way too big, enter again)");
	}

	return result;
}

/// @brief Reads int and performs input validation, asks for input again if needed 
/// @return input int
int readInt(string greetingText)
{
	int result;
	bool doneReading = false;
	do
	{
		cout << greetingText;
		string inp;
		cin >> inp;
		try
		{
			result = parseIntNum(inp);
			doneReading = true;
		}
		catch(const invalid_argument& e)
		{
			cout << e.what() << endl;
		}

	} while (!doneReading);

	return result;
}

int readIntGreaterThanZero(string greetingText)
{
	int inp = 0;
	while (inp < 1)
	{
		inp = readInt(greetingText);
		if (inp < 1)
		{
			cout << "(Entered number should be greater than 0)" << endl;
		}
	}

	return inp;
}

/// @brief Reads double and performs input validation, asks for input again if needed 
/// @return input int
double readDouble(string greetingText)
{
	double result;
	bool doneReading = false;
	do
	{
		cout << greetingText;
		string inp;
		cin >> inp;
		try
		{
			result = parseRealNum(inp);
			doneReading = true;
		}
		catch(const invalid_argument& e)
		{
			cout << e.what() << endl;
		}

	} while (!doneReading);

	return result;
}

/// @brief returns index for 1d array that represents matrix  
/// @return single number, that can be used as a [y][x]
int get2dIndex(int y, int x, int sizeVer)
{
	//[y][x]
	//skip y chunks of sizeVer, then get the element at x
	return y*sizeVer+x;
}

void printMatrix(double* matrix, int verSize, int horSize)
{
	for (int y = 0; y < verSize; y++)
	{
		for (int x = 0; x < horSize; x++)
		{
			cout << matrix[get2dIndex(y, x, verSize)]  << "\t";
		}

		cout << endl;
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
		//rows = vertical length, columns = horizontal
		int verSize = 0, horSize = 0;
		
		//read matrix size
		verSize = readIntGreaterThanZero("Enter vertical size: ");
		horSize = readIntGreaterThanZero("Enter horizontal size: ");

		cout << endl << "(Matrix element notation: a_y,x)" << endl;

		double *matrix = new double[horSize*verSize];

		for (int y = 0; y < verSize; y++)
		{
			cout << "------------------Row " << y+1 << "/" << verSize << "------------------" << endl;
			for (int x = 0; x < horSize; x++)
			{
				double currElement = readDouble(
					"Enter a_" + to_string(y+1) + "," + to_string(x+1) +
					" (col " + to_string(x+1) + "/" + to_string(horSize) + ")" +
					": "
				);
				matrix[get2dIndex(y, x, verSize)] = currElement;
			}
		}

		cout << "------------------- Matrix -------------------" << endl;

		printMatrix(matrix, verSize, horSize);

		cout << "----------------------------------------------" << endl;

		//find the saddle point

		//find minimum elements in each row
		//array, [y index] -> [x index of row min element]
        vector<vector<int>> yToRowMinElementIndices (verSize, vector<int>());
		for (int y = 0; y < verSize; y++)
		{
			int rowMinElementIndex = 0;
            yToRowMinElementIndices[y].push_back(0);
			for (int x = 1; x < horSize; x++)
			{
                int currMinElement = matrix[get2dIndex(y, rowMinElementIndex, verSize)];
                int currElement = matrix[get2dIndex(y, x, verSize)];

				if (currElement < currMinElement)
				{
					rowMinElementIndex = x;
                    yToRowMinElementIndices[y].clear();
                    yToRowMinElementIndices[y].push_back(x);
				}
                else if (currElement == currMinElement)
                {
                    yToRowMinElementIndices[y].push_back(x);
                }
			}
		}

        vector<vector<int>> saddlePointsXY;
        //iterate through each column
		for (int x = 0; x < horSize; x++)
		{
			int colMaxElementIndex = 0;
            //array, collects max elements
            vector<int> colMaxElementIndices;
            colMaxElementIndices.push_back(0);
            //iterate through each column element, find max element indices
			for (int y = 1; y < verSize; y++)
			{
                int currElement = matrix[get2dIndex(y, x, verSize)];
                int currMaxElement = matrix[get2dIndex(colMaxElementIndex, x, verSize)];

				if (currElement > currMaxElement)
				{
					colMaxElementIndex = y;
                    colMaxElementIndices.clear();
                    colMaxElementIndices.push_back(y);
				}
                else if (currElement == currMaxElement)
                {
                    colMaxElementIndices.push_back(y);
                }
			}

            //iterate through each max element in current column
            for (int i = 0; i < colMaxElementIndices.size(); i++)
            {
                //current max element
                int maxY = colMaxElementIndices[i];
                //for current max element, get min elements in corresponding row
                vector<int> rowMinElementIndices = yToRowMinElementIndices[maxY];
                //go through min elements in the row
                for (int j = 0; j < rowMinElementIndices.size(); j++)
                {
                    //current min element's index in this row
                    int minX = rowMinElementIndices[j];
 
                    if (minX == x)
                    {
                        vector<int> spCoords (2);
                        spCoords[0] = minX;
                        spCoords[1] = maxY;

                        saddlePointsXY.push_back(spCoords);
                        break;
                    }
                }
            }
		}

		if (saddlePointsXY.size() == 0)
		{
			cout << "Saddle point: not found" << endl;
		}
		else
		{
            for (int i = 0; i < saddlePointsXY.size(); i++)
            {
                int spX = saddlePointsXY[i][0];
                int spY = saddlePointsXY[i][1];
                double value = matrix[get2dIndex(spY, spX, verSize)];
                cout << "Saddle point: " << "a_" << spY+1 << "," << spX+1 << " (" << value << ")" << endl;
            }
		}		

		//asks whether to execute algo again or not
		char char_doContinue = ' ';
		while (char_doContinue != 'y' && char_doContinue != 'Y' && char_doContinue != 'n' && char_doContinue != 'N')
		{
			cout << "Do you want to try again? (y/n)? ";
			cin >> char_doContinue;

			if (char_doContinue == 'y' || char_doContinue == 'Y')
				doContinue = true;
		}

	} while (doContinue);

	return 0;
}
