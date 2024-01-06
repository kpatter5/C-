#include "Time.h"
using namespace std;

Time::Time()
{
}

Time::~Time()
{
}

bool Time::create()
{
    if (!setTime() || !setDate())
    {
        return false;
    }
    return true;
}

string Time::getTime()
{
    string time_string;
    string hour = to_string(time.hour);
    string minute = to_string(time.min);
    if (hour.size() == 1)
    {
        hour = "0" + hour;
    }
    if (minute.size() == 1)
    {
        minute = "0" + minute;
    }

    time_string = hour + ":" + minute;
    return time_string;
}

string Time::getDate()
{
    string time_string;
    string month = to_string(time.month);
    string day = to_string(time.day);
    string year = to_string(time.year);
    if (month.size() == 1)
    {
        month = "0" + month;
    }
    if (day.size() == 1)
    {
        day = "0" + day;
    }
    if (year.size() == 1)
    {
        year = "0" + year;
    }
    time_string = month + "/" + day + "/" + year;
    return time_string;
}

bool Time::setTime()
{
    string time_string = input.getString("Time (HH:MM): ");
    if (isValidTime(time_string))
    {
        time.hour = stod(time_string.substr(0, 2));
        time.min = stod(time_string.substr(3, 2));
        return true;
    }
    return false;
}

bool Time::setTime(string ctime)
{
    stringstream stream(ctime);
    string result;
    int count = 0;
    string clock_time[2];
    while (getline(stream, result, ':'))
    {
        clock_time[count] = result;
        count++;
    }

    if (count >= 1)
    {
        time_string = clock_time[0] + ":" + clock_time[1];
        time.hour = stod(clock_time[0]);
        time.min = stod(clock_time[1]);
        return true;
    }

    return false;
}

bool Time::setDate()
{
    string date_string = input.getString("Date (MM/DD/YYYY): ");
    if (isValidDate(date_string))
    {
        time.month = stod(date_string.substr(0, 2));
        time.day = stod(date_string.substr(3, 2));
        time.year = stod(date_string.substr(6, 4));
        return true;
    }

    return false;
}

bool Time::setDate(string date)
{
    string buffer;
    stringstream stream(date);

    string date_results[3];
    string result;
    int count = 0;
    while (getline(stream, result, '/'))
    {
        date_results[count] = result;
        count++;
    }

    if (count < 2)
    {
        cout << "Record contains invalid date.\n";
        return false;
    }

    else
    {
        time.month = stoi(date_results[0]);
        time.day = stoi(date_results[1]);
        time.year = stoi(date_results[2]);
        date_string = date_results[0] + "/" + date_results[1] + "/" + date_results[2];
    }
    return true;
}

void Time::printTime()
{
    cout << time.hour << ":" << time.min;
}

void Time::printDate()
{
    cout << time.month << "/" << time.day << "/" << time.year;
}

bool Time::isValidTime(string time)
{
    regex expression("[0-9]{2}:[0-9]{2}");
    if (regex_match(time, expression))
    {
        return true;
    }

    cout << "Invalid entry. Time must be in HH:MM format.\n";
    return false;
}

bool Time::isValidDate(string date)
{
    regex expression("[0-9]{2}/[0-9]{2}/[0-9]{4}");
    if (regex_match(date, expression))
    {
        int month = stoi(date.substr(0, 2));
        int day = stoi(date.substr(3, 2));
        int year = stoi(date.substr(6, 4));
        if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 2000 && year <= current_year)
        {
            return true;
        }
    }

    cout << "Invalid entry. Date must be in MM/DD/YYYY format.\n";
    return false;
}

ostream &operator<<(ostream &output, Time &time)
{
    output.fill('0');
    output.width(2);
    output << time.time.hour << ":";
    output.fill('0');
    output.width(2);
    output << time.time.min << " ";
    output.fill('0');
    output.width(2);
    output << time.time.month << "/";
    output.fill('0');
    output.width(2);
    output << time.time.day << "/";
    output << time.time.year;
    return output;
}

istream &operator>>(istream &input, Time &time)
{
    bool isValidTime = false;
    bool isValidDate = false;

    while (!isValidTime)
    {
        isValidTime = time.setTime();
    }

    while (!isValidDate)
    {
        isValidDate = time.setDate();
    }

    return input;
}
