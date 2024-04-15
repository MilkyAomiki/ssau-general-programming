#include "shared/IoExtensions.h"
#include <filesystem>
#include <fstream>
#include <limits>

using namespace std;

struct matrix
{
    //column 1
    double a_r1c1 = 0;
    double a_r2c1 = 0;

    //column 2
    double a_r1c2 = 0;
    double a_r2c2 = 0;
};

void copy_file(string source_filename, string dest_filename)
{  
    ifstream ifout;
    ifout.open(source_filename);

    if (!ifout.is_open())
    {
        throw invalid_argument("Error opening file: " + source_filename);
    }

    if (filesystem::exists(dest_filename) && !filesystem::is_empty(dest_filename))
    {
        throw invalid_argument("Error: destination file not empty");
    }

    ofstream ofout;
    ofout.open(dest_filename);

    string line;

    while (getline(ifout, line))
    {
        ofout << line << endl;
    }

    ifout.close();
    ofout.close();
}

int main()
{
    bool continue_execution = false;

    matrix state_matrix;
    
    do
    {
        string source_filename;
        string dest_filename;

        cout << "Enter source filename: " << endl;
        cin >> source_filename;

        cout << "Enter destination filename: " << endl;
        cin >> dest_filename;
        
        try
        {
            copy_file(source_filename, dest_filename);
        }
        catch(const std::exception& e)
        {
            cout << e.what() << '\n';
        }

        cout << "Completed!" << endl;

        //for some reason there is something stuck in stream at this point
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout.clear();

        continue_execution = askWhetherToContinue();
    } while (continue_execution);
    
    return 0;
}
