#pragma once
#include "Record.h"
#include <iostream>
#include <fstream>

class Collection
{
public:
    Collection();
    ~Collection();
    Collection(const Collection &);
    Collection &operator=(const Collection &);

    void open();
    std::string getName();
    bool setName();
    bool setName(std::string name);

    int getNumRecords();
    void showRecords();
    void addNewRecord();
    bool addExistingRecord(std::string text);
    void deleteRecords();
    bool saveRecords(std::string file, bool overwrite);

private:
    UserInput input = UserInput();
    std::string name = " ";
    Record *records = nullptr;
    int num_records = 0;
    int record_capacity = 3;

    bool capacityReached();
    void increaseCapacity();
    bool isValidName(std::string name);
};