#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    ifstream input;
    input.open("INPUT.txt");

    int n;

    input >> n;


    long* coords = new long[n];
    for (int i = 0; i < n; i++)
    {
        input >> coords[i];
    }

    unordered_map<long, int> vals_to_init_index;

    for (int i = 0; i <  n; i++)
    {
        vals_to_init_index[coords[i]] = i;
    }


    sort(coords, coords + n);


    long min_diff = coords[1] - coords[0];
    int min_diff_index = 0;
    for (int i = 2; i < n; i++)
    {
        long curr_diff = coords[i] - coords[i-1];
        if (curr_diff < min_diff)
        {
            min_diff = curr_diff;
            min_diff_index = i-1;
        }
    }

    ofstream output;
    output.open("OUTPUT.txt");
    output << min_diff << endl;

    output << vals_to_init_index[min_diff_index]+1 << " " << vals_to_init_index[min_diff_index+1]+1 << endl;
    
    
}