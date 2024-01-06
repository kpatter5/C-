#pragma once
#include <sstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include "UserInput.h"

class Person
{
public:
    Person();
    bool create();
    void printPerson();
    void printTemp();

    std::string getFirst();
    std::string getLast();
    double getTempNumber();
    std::string getTemp();

    bool setFirst(std::string first);
    bool setLast(std::string last);
    bool setTemp(double temp);

    bool setFirst();
    bool setLast();
    bool setTemp();

private:
    UserInput input = UserInput();
    std::string first;
    std::string last;
    double temperature;

    bool isValidName(std::string);
    bool isValidTemp(double temp);

    friend std::ostream &operator<<(std::ostream &output, Person &person);
    friend std::istream &operator>>(std::istream &input, Person &person);
};
