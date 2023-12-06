#include <iostream>
#include <climits>
using namespace std;

#ifndef IOREAD_H
#define IOREAD_H

/// @brief Читает целое число из потока и проводит на нем валидацию
/// @param messageBefore Сообщение, которое следует вывести в ostream, перед получением значения
/// @param inps Поток, из которого следует читать значение
/// @param outs Поток, в который выводить значение
/// @param exitOnException Не пытаться запрашивать значение заново, если возникла ошибка при чтении
/// @param maxValue Максимально разрешенное значение вводимого числа
/// @param minValue Минимально разрешенное значение вводимого числа
/// @return Успешно сконвертированное число
int readIntLine(string messageBefore, istream& inps, ostream& outs, bool exitOnException = true, int maxValue = INT_MAX, int minValue = INT_MIN);

/// @brief shows greetingText to user, then reads entered number of type double
/// @return entered double
double readDouble(string greetingText);

/// @brief shows greetingText to user, then reads entered number of type double
/// @return entered double
double readDoubleBetween0and1(string greetingText);

int countLines(istream& inps);

/// @brief Спрашивает продолжить ли выполнение программы
/// @return true если да, false иначе
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
