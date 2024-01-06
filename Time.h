#include <iostream>
#include <regex>
#include <ctime>
#include <sstream>
#include "UserInput.h"

class Time
{
public:
    Time();
    ~Time();
    bool create();
    void printTime();
    void printDate();

    std::string getTime();
    std::string getDate();

    bool setTime();
    bool setTime(std::string ctime);

    bool setDate();
    bool setDate(std::string);

private:
    UserInput input = UserInput();
    struct time_struct
    {
        int hour;
        int min;
        int month;
        int year;
        int day;
    };
    time_struct time = {0, 0, 0, 0, 0};
    std::string time_string, date_string;

    std::time_t current_time = std::time(nullptr);
    int seconds_to_years = 60 * 60 * 24 * 365;
    int current_year = 1970 + current_time / seconds_to_years;

    bool isValidTime(std::string time);
    bool isValidDate(std::string date);

    friend std::ostream &operator<<(std::ostream &output, Time &time);
    friend std::istream &operator>>(std::istream &input, Time &time);
};
