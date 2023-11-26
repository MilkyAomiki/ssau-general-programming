#include <iostream>
using namespace std;

#ifndef IOREAD_H
#define IOREAD_H

int readIntLine(string messageBefore, istream& inps, ostream& outs, bool exitOnException = true, int maxValue = INT_MAX, int minValue = INT_MIN);
bool askWhetherToContinue();


/// @brief No-op dummy stream
struct NulStreambuf: std::streambuf {
    int overflow(int c) override;
};

/// @brief No-op output stream
class NulOStream : public NulStreambuf, public std::ostream
{
	public:
		NulOStream() : std::ostream( this ) {}
};

#endif
