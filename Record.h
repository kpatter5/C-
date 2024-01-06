#include <iostream>
#include <string>
#include <sstream>

#include "Location.h"
#include "Time.h"
#include "Person.h"

class Record
{
public:
    Record();
    Record(const Record &source);            // Copy constructor
    Record &operator=(const Record &source); // Assignment operator

    bool addNew();
    bool addExisting(std::string text);
    void printRecord();

    Person getPersonObj();
    Location getLocationObj();
    Time getTimeObj();

private:
    Location location;
    Time time;
    Person person;

    bool setPerson();
    bool setPerson(std::string first, std::string last, double temp);

    bool setLocation();
    bool setLocation(std::string location);

    bool setTime();
    bool setTime(std::string time, std::string date);
};
