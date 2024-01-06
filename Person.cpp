#include "Person.h"
using namespace std;

Person::Person()
{
}

string Person::getFirst()
{
    return first;
}

string Person::getLast()
{
    return last;
}

double Person::getTempNumber()
{
    return temperature;
}

string Person::getTemp()
{
    stringstream stream;
    stream << fixed << setprecision(2) << temperature;
    string temp_str = stream.str();
    return temp_str;
}

bool Person::create()
{
    if (!setFirst() || !setLast() || !setTemp())
    {
        return false;
    }
    return true;
}

bool Person::setFirst()
{
    first = input.getString("First Name: ");
    return isValidName(first);
}

bool Person::setFirst(string first)
{
    this->first = first;
    return isValidName(first);
}

bool Person::setLast()
{
    last = input.getString("Last Name: ");
    return isValidName(last);
}

bool Person::setLast(string last)
{
    this->last = last;
    return isValidName(last);
}

bool Person::setTemp()
{
    temperature = input.getNumber("Temperature (deg F): ");
    return isValidTemp(temperature);
}

bool Person::setTemp(double temp)
{
    this->temperature = temp;
    return isValidTemp(temperature);
}

void Person::printPerson()
{
    cout << first << " ";
    cout << last;
}

void Person::printTemp()
{
    cout << temperature;
}

bool Person::isValidName(string name)
{
    if (name.size() > 50)
    {
        cout << "Invalid entry. Name must be between 1 and 50 characters.\n";
        return false;
    }

    regex expression("[a-zA-z]+");
    if (regex_match(name, expression))
    {
        return true;
    }

    cout << "Invalid entry. Name can only contain alphabetic characters.\n";
    return false;
}

bool Person::isValidTemp(double temp)
{
    if (temp > 50 && temp < 120)
    {
        return true;
    }

    cout << "Invalid entry. Temperature must be between 51 and 119.\n";
    return false;
}

ostream &operator<<(ostream &output, Person &person)
{
    output << person.first << " " << person.last << " ";
    output.precision(4);
    output << person.temperature;
    return output;
}

istream &operator>>(istream &input, Person &person)
{
    bool isValidFirst = false;
    bool isValidLast = false;
    bool isValidTemp = false;

    while (!isValidFirst)
    {
        isValidFirst = person.setFirst();
    }

    while (!isValidLast)
    {
        isValidLast = person.setLast();
    }

    while (!isValidTemp)
    {
        isValidTemp = person.setTemp();
    }

    return input;
}