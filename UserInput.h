#pragma once
#include <iostream>

class UserInput
{
public:
    UserInput();
    std::string getString(std::string msg);
    double getNumber(std::string msg);
};


