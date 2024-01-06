#include "Record.h"

using namespace std;

Record::Record()
{
}

Record::Record(const Record &source)
{
    // Copy constructor - Initializes a new Record object
    person = source.person;
    location = source.location;
    time = source.time;
}

Record &Record::operator=(const Record &source)
{
    // Assignment operator - Replace contents of existing Record object
    if (this != &source)
    {
        person = source.person;
        location = source.location;
        time = source.time;
    }

    return *this; // assignment to self
}

bool Record::addNew()
{
    if (!setPerson() || !setLocation() || !setTime())
    {
        return false;
    }
    return true;
}

bool Record::addExisting(string text)
{
    int count = 0;
    string buffer;
    stringstream stream(text);

    string record[10];
    while (stream >> buffer)
    {
        if (count > 9)
        {
            cout << "Upload file is formatted incorrectly.\n";
            return false;
        }
        record[count] = buffer;
        count++;
    }

    if (count != 6)
    {
        cout << "Upload file is formatted incorrectly.\n";
        return false;
    }

    string first = record[0];
    string last = record[1];
    double temp = -1;
    try
    {
        temp = stod(record[2]); // check if numerical;
    }
    catch (const std::exception &e)
    {
        cout << "Upload file is formatted incorrectly.\n";
        return false;
    }

    string location = record[3];
    string time = record[4];
    string date = record[5];

    return setPerson(first, last, temp) && setTime(time, date) && setLocation(location);
}

Person Record::getPersonObj()
{
    return person;
}

Location Record::getLocationObj()
{
    return location;
}

Time Record::getTimeObj()
{
    return time;
}

bool Record::setPerson()
{
    person = Person();
    cin >> person;
    return true;
}

bool Record::setPerson(string first, string last, double temp)
{
    person = Person();
    return person.setFirst(first) && person.setLast(last) && person.setTemp(temp);
}

bool Record::setTime()
{
    time = Time();
    cin >> time;
    return true;
}

bool Record::setTime(string time_string, string date_string)
{
    time = Time();
    return time.setTime(time_string) && time.setDate(date_string);
}

bool Record::setLocation()
{
    location = Location();
    return location.create();
}

bool Record::setLocation(string my_location)
{
    return location.setLocation(my_location);
}

void Record::printRecord()
{
    person.printPerson();
    cout << " ";
    person.printTemp();
    cout << " ";
    location.printLocation();
    cout << " ";
    time.printTime();
    cout << " ";
    time.printDate();
    cout << "\n";
}
