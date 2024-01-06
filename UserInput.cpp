#include "UserInput.h"

using namespace std;

UserInput::UserInput()
{
}

string UserInput::getString(string prompt)
{
    cin.clear();
    string input_string;
    cout << "\n"
         << prompt;
    cin >> input_string;
    cout << "\n";
    return input_string;
}

double UserInput::getNumber(string prompt)
{
    cin.clear();
    double input_num;
    cout << "\n"
         << prompt;
    cout << "in try userinput.cpp\n";
    cin >> input_num;
    cout << "input_num =" << input_num;
    cout << "\n";

    return input_num;
}
