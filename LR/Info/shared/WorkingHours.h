#include <vector>
#include <istream>
#include <ostream>
#include <unordered_map>

using namespace std;

#ifndef WORKINGHOURS_H
#define WORKINGHOURS_H

struct day_month
{
	int day;
	int month;
};

/// @brief Класс, представляющий время проведенное за работой
class WorkingHours
{
	private:
		/// @brief Проверяет является ли строка корректным представлением даты, и конвертирует если все хорошо
		/// @param str_date 
		/// @return дата содержащаяся в строке
		day_month validate_str_date(string str_date);

		/// @brief Проверяет является ли строка корректным представлением времени, и конвертирует если все хорошо
		/// @param str_date 
		/// @return время содержащееся в строке
		tm validate_str_time(string str_time);

		//Дата (дд.мм)
		day_month workDate;

		//Время прихода (чч:мм)
		tm arriveTime;

		//Время ухода (чч:мм)
		tm finishTime;
	public:
		WorkingHours(const day_month* workDate = nullptr, const tm* arriveTime = nullptr, const tm* finishTime = nullptr);
		WorkingHours(const WorkingHours& obj);

		day_month& get_workDate();
		void set_workDate(day_month workDate);

		tm& get_arriveTime();
		void set_arriveTime(tm arriveTime);

		tm& get_finishTime();
		void set_finishTime(tm finishTime);

		/// @brief Считает разницу между arriveTime & finishTime
		tm calcTimeSpanWorking();

		friend ostream& operator<<(ostream& os, const WorkingHours& obj);
		friend istream& operator>>(istream& is, WorkingHours& obj);
};

struct WorkingHoursListInput
{
	vector<WorkingHours> workingHours;
	unordered_map<int, string> whInputErrors;
};

extern string WH_LAST_READ_ERROR;
ostream& operator<<(ostream& os, const WorkingHours& obj);
istream& operator>>(istream& is, WorkingHours& obj);

/// @brief outputs vector of working hours to the stream
/// @param outp any output stream
/// @param working_hours the vector of working hours
/// @param human_readable whether to append human readable text or not
void outputWorkingHoursVector(ostream& outp, WorkingHoursListInput working_hours, bool human_readable);

/// @brief reads vector of working hours from input stream
/// @param inp an input stream
/// @param outp output stream to which human redable text would be outputed 
/// @param exitOnException whether to stop reading if error in formatting of data is found. throws exceptions with readable descriptionif errors occur
/// @return successfuly read vector of working hours
WorkingHoursListInput readWorkingHoursVector(istream& inp, ostream& std_out, ostream& warning_stream, int objects_num = -1, bool retryOnException = false);

#endif
