#include "shared/IoExtensions.h"

using namespace std;

struct linSystemSolution
{
    bool exists = true;
    bool inifinitely_many = false;
    double x1;
    double x2;
};

linSystemSolution calcLinSystem(int a11, int a12, int a21, int a22, int b1, int b2)
{
    linSystemSolution solution;
    solution.exists = false;

    if (a11 == 0)
    {
        return solution;
    }

    int x2_numerator = a11*b2 - a21*b1;
    int x2_denominator = a11*a22-a21*a12;

    if (x2_numerator == 0 && x2_denominator == 0)
    {
        solution.exists = true;
        solution.inifinitely_many = true;
        return solution;
    }

    if (x2_denominator == 0)
    {
        return solution;
    }
    
    double x2 = ((double)x2_numerator)/x2_denominator;

    int x1_numerator =  b1-a12*x2;
    double x1 = ((double)x1_numerator) / a11;
    
    solution.exists = true;
    solution.x1 = x1;
    solution.x2 = x2;

    return solution;
}

int main()
{
    bool continue_execution = false;
    
    do
    {
        int 
            a11, a12, b1,
            a21, a22, b2;

        a11 = readIntLine("Enter a_11: ", cin, cout, false);
        a12 = readIntLine("Enter a_12: ", cin, cout, false);
        cout << endl;
        a21 = readIntLine("Enter a_21: ", cin, cout, false);
        a22 = readIntLine("Enter a_22: ", cin, cout, false);
        cout << endl;
        b1 = readIntLine("Enter b_1: ", cin, cout, false);
        b2 = readIntLine("Enter b_2: ", cin, cout, false);
        
        linSystemSolution solution = calcLinSystem(a11, a12, a21, a22, b1, b2);

        if (!solution.exists)
        {
            cout << "No solution" << endl;
        }
        else
        {
            if (solution.inifinitely_many)
            {
                cout << "Infinitely many solutions" << endl;
            }
            else
            {
                cout << "Solution: (" << solution.x1 << ", " << solution.x2 << ")" << endl; 
            }
        }        

        continue_execution = askWhetherToContinue();
    } while (continue_execution);
    
    return 0;
}
