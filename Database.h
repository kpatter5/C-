#include "Collection.h"
#define MAX_SIZE 100

class Database
{
public:
    Database();
    ~Database();

private:
    UserInput input = UserInput();
    std::string prompt = "--------------------------------------\n"
                         "Enter one of the following commands:\n\n"
                         " * Collection Commands:\n"
                         "    \"Create\"\t :  Create & connect to an empty tracing record collection \n"
                         "    \"Connect\"\t :  Connect to a different tracing record collection \n"
                         "    \"Disconnect\" :  Disconnect from the current collection \n"
                         "    \"Drain\"\t :  Delete all records from the current collection \n"
                         "    \"Copy\"\t :  Create & name a new collection as a copy of the currently connected collection \n"
                         "    \"Show\"\t :  Display all collections currently in memory, along with the number of records in each \n"
                         "    \"Upload\"\t :  Import records to current collection from a file (append to collection) \n"
                         "    \"Replace\"\t :  Import records to current collection from a file (overwrite collection) \n"
                         "    \"Append\"\t :  Append to a file the contents of the current collection \n"
                         "    \"Overwrite\"\t :  Overwite the contents of a file with the contents of the current collection \n\n"

                         " * Record Commands:\n"
                         "    \"List\"\t :  Show all tracing records in the current collection \n"
                         "    \"New\"\t :  Create & store a new tracing record in the current collection \n\n"

                         " * Program Commands:\n"
                         "    \"Quit\"\t :  Exit the program \n\n"
                         " > ";

    // Collection variables
    int num_collections = 0;
    int collection_capacity = 10;
    int current_idx = -1;
    std::string current_collection = "";
    Collection *collections = nullptr;
    bool connected = false;

    // Record variables
    Record list[MAX_SIZE];
    int num_records = 0;

    // Record methods
    void listRecords();
    void addRecord();
    void showList();
    bool recordsCapacityReached();

    // Collection methods
    bool open();
    bool create();
    void show();
    bool copy();
    bool drain();
    bool upload();
    bool replace();
    bool append();
    bool overwrite();

    bool connect(std::string name);
    void disconnect();

    bool isConnected();
    int find(std::string name);
    void increaseCapacity();
    bool nameExists(std::string name);
    bool capacityReached();
};
