#include "../StringExtensions.h"

string to_string_double_digit(int num)
{
    if (num < 10)
    {
        return to_string(0) + to_string(num);
    }

    return to_string(num);
}
