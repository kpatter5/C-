#include "Location.h"
using namespace std;

Location::Location()
{
}

bool Location::create()
{
    return setLocation();
}

string Location::getLocation()
{
    return this->location;
}

bool Location::setLocation()
{
    this->location = input.getString("Location: ");
    return isValidLocation(this->location);
}

bool Location::setLocation(string location)
{
    this->location = location;
    return isValidLocation(location);
}

void Location::printLocation()
{
    cout << location;
}

bool Location::isValidLocation(string location)
{
    if (location.size() > 50)
    {
        cout << "\nInvalid entry. Location must be < 51 characters.\n";
        return false;
    }

    regex expression("[a-zA-z0-9]+");
    if (regex_match(location, expression))
    {
        return true;
    }

    cout << "Invalid entry. Name can only contain alphanumeric characters.\n";
    return true;
}
