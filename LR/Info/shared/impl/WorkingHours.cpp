#include <ctime>
#include <iostream>
#include <vector>
#include <regex>

#include "../WorkingHours.h"
#include "../IoExtensions.h"
#include "../StringExtensions.h"
#include <limits>

using namespace std;


WorkingHours::WorkingHours(const day_month* workDate, const tm* arriveTime, const tm* finishTime)
{
    if (workDate == nullptr)
    {
        day_month dm;
        dm.day = 01;
        dm.month = 01;

        set_workDate(dm);
    }
    else
    {
        set_workDate(*workDate);
    }

    if (arriveTime == nullptr)
    {
        tm arrTime;
        arrTime.tm_hour = 00;
        arrTime.tm_min = 00;

        set_arriveTime(arrTime);
    }
    else
    {
        set_arriveTime(*arriveTime);
    }

    if (finishTime == nullptr)
    {
        tm finTime;
        finTime.tm_hour = 00;
        finTime.tm_min = 00;

        set_finishTime(finTime);
    }
    else
    {
        set_finishTime(*finishTime);
    }
}

WorkingHours::WorkingHours(const WorkingHours& obj) : WorkingHours(&obj.workDate, &obj.arriveTime, &obj.finishTime)
{
}

day_month& WorkingHours::get_workDate()
{
    return workDate;
}

void WorkingHours::set_workDate(day_month workDate)
{
    this->workDate = workDate;
}


tm& WorkingHours::get_arriveTime()
{
    return arriveTime;
}

void WorkingHours::set_arriveTime(tm arriveTime)
{
    this->arriveTime = arriveTime;
}

tm& WorkingHours::get_finishTime()
{
    return finishTime;
}

void WorkingHours::set_finishTime(tm finishTime)
{
    this->finishTime = finishTime;
}

tm WorkingHours::calcTimeSpanWorking()
{
    tm time_diff;
    time_diff.tm_hour = get_finishTime().tm_hour - get_arriveTime().tm_hour;
    time_diff.tm_min = get_finishTime().tm_min - get_arriveTime().tm_min;

    if (time_diff.tm_min < 0)
    {
        time_diff.tm_hour--;
        time_diff.tm_min = 60 + time_diff.tm_min;
    }

    return  time_diff;
}

string WH_LAST_READ_ERROR;

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
        WH_LAST_READ_ERROR = "Field 'Date' - format is invalid";
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
        WH_LAST_READ_ERROR = "Field 'Arrive time' - format is invalid";
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
        WH_LAST_READ_ERROR = "Field 'Finish time' - format is invalid";
        return is;
    }

    obj.set_workDate(date);
    obj.set_arriveTime(arrive_time);
    obj.set_finishTime(depart_time);

    return is;
}

day_month WorkingHours::validate_str_date(string str_date)
{
    //hours:minutes
	regex reg_matchWorkingHoursFormat = regex(R"(^([0-9]{2,2})\.([0-9]{2,2})$)");
    smatch matches;

    if(regex_search(str_date, matches, reg_matchWorkingHoursFormat))
    {
        day_month date;
        date.day = stoi(matches[1].str());
        date.month = stoi(matches[2].str());

        if (date.day > 31 || date.day < 1)
        {
            throw invalid_argument("incorrect values for day");
        }

        if (date.month > 12 || date.month < 1)
        {
            throw invalid_argument("incorrect values for month");
        }

        return date;
    }
    
    throw invalid_argument("");
}

tm WorkingHours::validate_str_time(string str_time)
{
    //hours:minutes
	regex reg_matchWorkingHoursFormat = regex(R"(^([0-9]{2,2}):([0-9]{2,2})$)");
    smatch matches;

    if(regex_search(str_time, matches, reg_matchWorkingHoursFormat))
    {
        tm time;
        time.tm_hour = stoi(matches[1].str());
        time.tm_min = stoi(matches[2].str());

        if (time.tm_hour > 24 || time.tm_hour < 0)
        {
            throw invalid_argument("incorrect values for hour");
        }

        if (time.tm_min >= 60 || time.tm_min < 0)
        {
            throw invalid_argument("incorrect values for minutes");
        }
        
        return time;
    }
    
    throw invalid_argument("");
}

void outputWorkingHoursVector(ostream& outp, WorkingHoursListInput working_hours_res, bool human_readable)
{
	for (int i = 0; i < working_hours_res.workingHours.size(); i++)
	{
		if (human_readable)
		{
			outp << "Working hours " << i+1 << ": "; 
		}

		outp << working_hours_res.workingHours[i];
		tm time_worked = working_hours_res.workingHours[i].calcTimeSpanWorking();
		outp << " (time diff " << to_string_double_digit(time_worked.tm_hour) << ":" << to_string_double_digit(time_worked.tm_min) << ")";
        
        if (working_hours_res.whInputErrors.count(i))
        {
            outp << " | Error: " << working_hours_res.whInputErrors[i];
        }

        outp << endl;
	}
}

WorkingHoursListInput readWorkingHoursVector(istream& inp, ostream& std_out, ostream& warning_stream, int objects_num, bool retryOnException)
{
    WorkingHoursListInput result;

    int i = 0;
    //i всегда будет меньше objects_num, когда objects_num не указан
    if (objects_num < 0) 
        i = -10;

    while (i < objects_num)
    {
		WorkingHours working_hours;

		bool read_again = false;
		do
		{
			std_out << "Enter working hours in format Date(dd:MM) Arriving time(hh:mm) Departure time(hh:mm):" << endl;
			inp >> working_hours;

			if (inp.fail())
			{
				warning_stream << "Object number: " + to_string(result.workingHours.size()+1) + ". There is an error in format. " << endl;
                result.whInputErrors[i] = WH_LAST_READ_ERROR;

                inp.clear();
                inp.ignore(numeric_limits<streamsize>::max(), '\n');

                if (retryOnException)
                {
                    read_again = true;
                    std_out << WH_LAST_READ_ERROR << ". Try again." << endl;
                }
                else
                {
                    working_hours = WorkingHours();
                }
			}
            //if start time is older than finish time, it's weird
            else if (working_hours.get_arriveTime().tm_hour*60+working_hours.get_arriveTime().tm_min 
				> working_hours.get_finishTime().tm_hour*60+working_hours.get_finishTime().tm_min)
            {
                const string error_text = "Starting time is older than finishing time, it doesn't make sense.";
				warning_stream << "Object number: " + to_string(result.workingHours.size()+1) + ". " << error_text << endl;

                result.whInputErrors[i] = error_text;

                inp.clear();
                inp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (retryOnException)
                {
                    read_again = true;
                    std_out << error_text << " Try again." << endl;
                }
                else
                {
                    working_hours = WorkingHours();
                }
            }
			else
			{
				read_again = false;
			}
		} while(read_again);
		
		result.workingHours.push_back(working_hours);

        if (objects_num > 0)
        {
            i++;
        }
	}

	return result;
}