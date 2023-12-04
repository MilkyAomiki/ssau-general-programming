#include "shared/IoExtensions.h"

using namespace std;

int main()
{
    bool continue_execution = false;
    
    do
    {
        int k = readIntLine("Enter k: ", cin, cout, false, INT_MAX, 0);
        int max_n = readIntLine("Enter the number of elements to check: ", cin, cout, false, INT_MAX, 0);

        int primes_num = 0;
        for (int n = 1; n <= max_n; n++)
        {
            int an = n*(n-1) + k;

            bool is_prime = true;
            //0 & 1 are not primes
            if (an == 0 || an == 1) {
                is_prime = false;
            }

            // check that n is prime
            //2 is a prime
            for (int i = 3; i <= an/2 && is_prime; i++) {
                if (an % i == 0) {
                    is_prime = false;
                }
            }

            if (is_prime)
                primes_num++;
        }

        cout << "The number of primes: " << primes_num << endl;

        continue_execution = askWhetherToContinue();
    } while (continue_execution);
    
    return 0;
}