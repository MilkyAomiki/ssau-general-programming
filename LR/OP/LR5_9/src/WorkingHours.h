#include <vector>
#include <istream>
#include <ostream>

using namespace std;

#ifndef WORKINGHOURS_H
#define WORKINGHOURS_H

struct day_month
{
	int day;
	int month;
};

struct basic_time
{
	int hours;
	int minutes;
};

class WorkingHours
{
	private:
		day_month validate_str_date(string str_date);
		tm validate_str_time(string str_time);
	public:
		//Дата (дд.мм)
		day_month workDate;

		//Время прихода (чч:мм)
		tm arriveTime;

		//Время ухода (чч:мм)
		tm finishTime;
	
		tm calcTimeSpanWorking();

		friend ostream& operator<<(ostream& os, const WorkingHours& obj);
		friend istream& operator>>(istream& is, WorkingHours& obj);
};

ostream& operator<<(ostream& os, const WorkingHours& obj);
istream& operator>>(istream& is, WorkingHours& obj);

void outputWorkingHoursVector(ostream& outp, vector<WorkingHours> working_hours, bool human_readable);
vector<WorkingHours> readWorkingHoursVector(istream& inp, ostream& outp, bool exitOnException = false);

#endif
