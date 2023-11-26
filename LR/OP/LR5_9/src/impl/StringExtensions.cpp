#include "../StringExtensions.h"

/// @brief Converts to string, prefixes single-digit numbers with 0
string to_string_double_digit(int num)
{
    if (num < 10)
    {
        return to_string(0) + to_string(num);
    }

    return to_string(num);
}