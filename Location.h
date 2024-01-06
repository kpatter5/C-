#include <iostream>
#include <regex>
#include "UserInput.h"

class Location
{
public:
    Location();
    bool create();
    void printLocation();
    bool setLocation(std::string location);
    std::string getLocation();

private:
    UserInput input = UserInput();
    std::string location;

    bool setLocation();
    bool isValidLocation(std::string location);
};
