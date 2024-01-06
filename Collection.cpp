#include "Collection.h"
using namespace std;

Collection::Collection()
{
    if (records == nullptr)
    {
        records = new Record[record_capacity];
    }
}

Collection::~Collection()
{
    if (records != nullptr)
    {
        delete[] records;
        records = nullptr;
    }
}

Collection::Collection(const Collection &source)
{
    // Copy constructor called when LHS of assignment is uninitialized object
    records = new Record[record_capacity];
    *records = *(source.records);
    num_records = source.num_records;
    record_capacity = source.record_capacity;
    name = source.name;
}

Collection &Collection::operator=(const Collection &source)
{
    // Assignment operator method called when LHS of assignment is an initialized object
    if (this != &source) // "this" is LHS of assignment operation
    {
        record_capacity = source.record_capacity;
        num_records = source.num_records;
        name = source.name;

        records = new Record[record_capacity];
        for (int i = 0; i < source.num_records; i++)
        {
            records[i] = source.records[i];
        }
    }

    return *this;
}

int Collection::getNumRecords()
{
    return num_records;
}

string Collection::getName()
{
    return name;
}

bool Collection::capacityReached()
{
    if (num_records >= record_capacity)
    {
        return true;
    }
    return false;
}

void Collection::open()
{
    if (records == nullptr)
    {
        records = new Record[record_capacity];
    }
}

bool Collection::setName()
{
    string response = input.getString("New Collection Name: ");
    return setName(response);
}

bool Collection::setName(string name)
{
    this->name = name;
    return isValidName(name);
}

void Collection::showRecords()
{
    if (records != nullptr && num_records != 0)
    {
        cout << "Listing Records: \n";
        for (int i = 0; i < num_records; i++)
        {
            records[i].printRecord();
        }
    }

    else
    {
        cout << "No records to print.\n";
    }
}

void Collection::addNewRecord()
{
    if (capacityReached())
    {
        increaseCapacity();
    }

    if (records == nullptr)
    {
        records = new Record[record_capacity];
    }

    // records[num_records] = Record();
    int valid_record = records[num_records].addNew();
    if (valid_record)
    {
        num_records++;
    }
    else
    {
        cout << "Unable to add record.\n";
    }
}

bool Collection::addExistingRecord(string text)
{
    if (capacityReached())
    {
        increaseCapacity();
    }

    bool recordAdded = false;

    if (records != nullptr)
    {
        recordAdded = records[num_records].addExisting(text);
    }

    else
    {
        num_records = 0;
        records = new Record[record_capacity];
        recordAdded = records[num_records].addExisting(text);
    }

    if (recordAdded)
    {
        num_records++;
    }
    return recordAdded;
}

void Collection::deleteRecords()
{
    // Delete records memory and set it to empty array of Records
    if (records != nullptr)
    {
        delete[] records;
        records = new Record[record_capacity];
        num_records = 0;
    }
}

bool Collection::saveRecords(string file, bool overwrite)
{
    ofstream output;
    if (overwrite)
    {
        output.open(file, ios::out | ios::trunc);
        if (!output.is_open())
        {
            cout << "Unable to open file.\n";
            return false;
        }
    }

    else
    {
        output.open(file, ios::out | ios::app);
        if (!output.is_open())
        {
            cout << "Unable to open file.\n";
            return false;
        }
    }

    for (int i = 0; i < num_records; i++)
    {
        output << (records[i].getPersonObj()).getFirst() << " ";
        output << (records[i].getPersonObj()).getLast() << " ";
        output << (records[i].getPersonObj()).getTemp() << " ";
        output << (records[i].getLocationObj()).getLocation() << " ";
        output << (records[i].getTimeObj()).getTime() << " ";
        output << (records[i].getTimeObj()).getDate() << "\n";
    }

    output.close();
    return true;
}

void Collection::increaseCapacity()
{
    record_capacity = num_records * 2;
    Record *tmp = new Record[record_capacity];

    // deep copy existing records to tmp
    for (int i = 0; i < num_records; i++)
    {
        tmp[i] = records[i];
    }

    // delete existing records memory
    if (records != nullptr)
    {
        delete[] records;
        records = nullptr;
    }

    // deep copy tmp to new records memory
    records = new Record[record_capacity];
    for (int i = 0; i < record_capacity; i++)
    {
        records[i] = tmp[i];
    }

    // delete tmp memory
    if (tmp != nullptr)
    {
        delete[] tmp;
        tmp = nullptr;
    }
}

bool Collection::isValidName(string name)
{
    if (name.size() > 25)
    {
        cout << "Invalid entry. Collection name must be between 1 and 25 characters.\n";
        return false;
    }

    regex expression("[a-zA-z0-9]+");
    if (regex_match(name, expression))
    {
        return true;
    }

    cout << "Invalid entry. Collection name can only contain alphanumeric characters.\n";

    return false;
}