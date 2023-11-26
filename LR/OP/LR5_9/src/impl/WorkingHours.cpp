#include <ctime>
#include <iostream>
#include <vector>
#include <regex>

#include "../WorkingHours.h"
#include "../IoExtensions.h"
#include "../StringExtensions.h"

using namespace std;

tm WorkingHours::calcTimeSpanWorking()
{
    tm time_diff;
    time_diff.tm_hour = finishTime.tm_hour - arriveTime.tm_hour;
    time_diff.tm_min = finishTime.tm_min - arriveTime.tm_min;

    if (time_diff.tm_min < 0)
    {
        time_diff.tm_hour--;
        time_diff.tm_min = 60 + time_diff.tm_min;
    }
    

    return  time_diff;
}

ostream& operator<<(ostream& os, const WorkingHours& obj)
{
    os << to_string_double_digit(obj.workDate.day) << "." << to_string_double_digit(obj.workDate.month) << " ";

    os << to_string_double_digit(obj.arriveTime.tm_hour) << ":" << to_string_double_digit(obj.arriveTime.tm_min) << " ";
    os << to_string_double_digit(obj.finishTime.tm_hour) << ":" << to_string_double_digit(obj.finishTime.tm_min) << " ";

    return os;
}

istream& operator>>(istream& is, WorkingHours& obj)
{
    string input;
    is >> input;

    day_month date;

    try
    {
        date = obj.validate_str_date(input);
    }
    catch(invalid_argument e)
    {
        is.setstate(ios::failbit);
        return is;
    }

    is >> input;
    tm arrive_time;

    try
    {
        arrive_time = obj.validate_str_time(input);
    }
    catch(invalid_argument e)
    {
        is.setstate(ios::failbit);
        return is;
    }

    is >> input;
    tm depart_time;

    try
    {
        depart_time = obj.validate_str_time(input);
    }
    catch(invalid_argument e)
    {
        is.setstate(ios::failbit);
        return is;
    }

    obj.workDate = date;
    obj.arriveTime = arrive_time;
    obj.finishTime = depart_time;

    return is;
}

day_month WorkingHours::validate_str_date(string str_date)
{
    //hours:minutes
	regex reg_matchWorkingHoursFormat = regex(R"(^([0-9]{1,2})\.([0-9]{1,2})$)");
    smatch matches;

    if(regex_search(str_date, matches, reg_matchWorkingHoursFormat))
    {
        day_month date;
        date.day = stoi(matches[1].str());
        date.month = stoi(matches[2].str());
        return date;
    }
    
    throw invalid_argument("");
}

tm WorkingHours::validate_str_time(string str_time)
{
    //hours:minutes
	regex reg_matchWorkingHoursFormat = regex(R"(^([0-9]{1,2}):([0-9]{1,2})$)");
    smatch matches;

    if(regex_search(str_time, matches, reg_matchWorkingHoursFormat))
    {
        tm time;
        time.tm_hour = stoi(matches[1].str());
        time.tm_min = stoi(matches[2].str());
        return time;
    }
    
    throw invalid_argument("");
}

void outputWorkingHoursVector(ostream& outp, vector<WorkingHours> working_hours, bool human_readable)
{
	for (int i = 0; i < working_hours.size(); i++)
	{
		if (human_readable)
		{
			outp << "Working hours (" << i+1 << "): "; 
		}

		outp << working_hours[i];
		tm time_worked = working_hours[i].calcTimeSpanWorking();
		outp << " (" << time_worked.tm_hour << ":" << time_worked.tm_min << ")" << endl;
	}
}

vector<WorkingHours> readWorkingHoursVector(istream& inp, ostream& outp, bool exitOnException)
{
	vector<WorkingHours> input_vec;
	int objects_num = 0;
	try
	{
		objects_num = readIntLine("Enter the number of objects: ", inp, outp, exitOnException);
	}
	catch(const exception& e)
	{
        inp.setstate(ios::failbit);
		return input_vec;
	}
	
	for (int i = 0; i < objects_num; i++)
	{
		WorkingHours working_hours;

		bool read_again = false;
		do
		{
			outp << "Enter working hours in format Date(dd:MM) Arriving time(hh:mm) Departure time(hh:mm):" << endl;
			inp >> working_hours;

			if (inp.fail() ||
				//if start time is older than finish time, it's weird
				working_hours.arriveTime.tm_hour*60+working_hours.arriveTime.tm_min 
				> working_hours.finishTime.tm_hour*60+working_hours.finishTime.tm_min)
			{
				if (exitOnException) return input_vec;

				read_again = true;

				inp.clear();
				inp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				outp << "Wrong format! Try again." << endl;
			}
			else
			{
				read_again = false;
			}
		} while(read_again);
		
		input_vec.push_back(working_hours);
	}

	return input_vec;
}