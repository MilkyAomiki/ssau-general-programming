#include "shared/IoExtensions.h"
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

void print_matrix(matrix m)
{
    cout << "┌" << "\t" << " " << "\t" << " " << "\t" << "┐" << endl;
    cout << "│" << "\t" << m.a_r1c1 << "\t" << m.a_r1c2 << "\t" << "│" << endl;
    cout << "│" << "\t" << m.a_r2c1 << "\t" << m.a_r2c2 << "\t" << "│" << endl;
    cout << "└" << "\t" << " " << "\t" << " " << "\t" << "┘" << endl;
}

int main()
{
    bool continue_execution = false;

    matrix state_matrix;
    
    do
    {
        string curr_opearand;
        matrix m;

        cout << "Current state: " << endl;
        print_matrix(state_matrix);

        cout << "Input an operation (+/*):" << endl;
        
        bool read_successfully = true;

        do
        {
            cin >> curr_opearand;
            if (curr_opearand != "+" && curr_opearand != "*")
            {
                cout << "It looks weird, try again" << endl;
                read_successfully = false;
            }
            else
            {
                read_successfully = true;
            }
        } while (!read_successfully);

        m.a_r1c1 = readDouble("Enter a_11: ");
        m.a_r1c2 = readDouble("Enter a_12: ");
        cout << endl;
        m.a_r2c1 = readDouble("Enter a_21: ");
        m.a_r2c2 = readDouble("Enter a_22: ");

        cout << endl;

        if (curr_opearand == "+")
        {
            state_matrix.a_r1c1 += m.a_r1c1;
            state_matrix.a_r2c1 += m.a_r2c1;
            state_matrix.a_r1c2 += m.a_r1c2;
            state_matrix.a_r2c2 += m.a_r2c2;
        }
        else
        {
            matrix product_result;
            
                // Transforming column 1 of the state matrix
            product_result.a_r1c1 = (state_matrix.a_r1c1 * m.a_r1c1) + (state_matrix.a_r1c2 * m.a_r2c1);
            product_result.a_r2c1 = (state_matrix.a_r2c1 * m.a_r1c1) + (state_matrix.a_r2c2 * m.a_r2c1);

            // Transforming column 2 of the state matrix
            product_result.a_r1c2 = (state_matrix.a_r1c1 * m.a_r1c2) + (state_matrix.a_r1c2 * m.a_r2c2);
            product_result.a_r2c2 = (state_matrix.a_r2c1 * m.a_r1c2) + (state_matrix.a_r2c2 * m.a_r2c2);

            state_matrix = product_result;
        }

        cout << "Current state: " << endl;
        print_matrix(state_matrix);

        //for some reason there is something stuck in stream at this point
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout.clear();

        continue_execution = askWhetherToContinue();
        cout << endl;
    } while (continue_execution);
    
    return 0;
}
