#include "Database.h"
using namespace std;

Database::Database()
{
    open();
}

Database::~Database()
{
    if (collections != nullptr)
    {
        delete[] collections;
        collections = nullptr;
    }
}

bool Database::open()
{
    collections = new Collection[collection_capacity];
    string response;
    do
    {
        if (current_collection != "")
        {
            cout << "\n***  CURRENTLY CONNECTED TO \"" << current_collection << "\" COLLECTION  ***\n";
        }
        else
        {
            cout << "\n** NOT CONNECTED TO ANY COLLECTION **\n";
        }

        response = input.getString(prompt);

        if (response == "Create")
        {
            create();
        }

        else if (response == "Show")
        {
            show();
        }

        else if (response == "Copy")
        {
            copy();
        }

        else if (response == "Drain")
        {
            drain();
        }

        else if (response == "Upload")
        {
            upload();
        }

        else if (response == "Replace")
        {
            replace();
        }

        else if (response == "Append")
        {
            append();
        }

        else if (response == "Overwrite")
        {
            overwrite();
        }

        else if (response == "Connect")
        {
            if (num_collections == 0)
            {
                cout << "No collections exist yet.\n";
            }

            else
            {
                string name = input.getString("Enter name of collection to connect to: ");
                connect(name);
            }
        }

        else if (response == "Disconnect")
        {
            disconnect();
        }

        else if (response == "List")
        {
            listRecords();
        }

        else if (response == "New")
        {
            addRecord();
        }

        else
        {
            if (response != "Quit")
                cout << "\n***  ERROR: Invalid command \"" << response << "\". Please try again.  ***\n";
        }
    } while (response != "Quit");

    return true;
}

void Database::addRecord()
{
    if (isConnected())
    {
        collections[current_idx].addNewRecord();
    }

    else
    {
        cout << "Must connect to a collection before adding records.\n";
    }
}

bool Database::create()
{
    if (capacityReached())
    {
        increaseCapacity();
    }

    current_idx = num_collections;
    collections[current_idx].open();

    string name = input.getString("New Collection Name: ");

    if (nameExists(name))
    {
        cout << "Collection name " << name << " already exists. \n";
        return false;
    }

    collections[current_idx].setName(name);
    num_collections++;
    connect(collections[current_idx].getName());
    return true;
}

void Database::show()
{
    if (num_collections == 0)
    {
        cout << "No collections to show.\n";
    }
    else
    {
        cout << "Listing collections: \n";
    }
    for (int i = 0; i < num_collections; i++)
    {
        cout << "  " << collections[i].getName();
        cout << " (" << collections[i].getNumRecords() << " records) \n";
    }
}

bool Database::copy()
{
    if (!connected)
    {
        cout << "Must be connected to a collection before copying.\n";
        return false;
    }

    if (capacityReached())
    {
        increaseCapacity();
    }

    string collection_name = input.getString("New Collection Name: ");
    if (nameExists(collection_name))
    {
        cout << "A collection named \"" << collection_name << "\" already exists. ";
        string overwrite = input.getString("Overwrite collection? (Y/N): ");
        if (overwrite == "N")
        {
            return true;
        }
    }

    collections[num_collections] = collections[current_idx]; // Collection assignment operator called
    collections[num_collections].setName(collection_name);
    num_collections++;

    return true;
}

bool Database::drain()
{
    if (collections[current_idx].getNumRecords() > 0)
    {
        collections[current_idx].deleteRecords();
        cout << "All records deleted.\n";
        return true;
    }

    else
    {
        cout << "No records to delete.\n";
    }
    return false;
}

bool Database::replace()
{
    if (isConnected())
    {
        drain();
        return upload();
    }

    return false;
}

bool Database::append()
{
    string filename = input.getString("File name: ");
    collections[current_idx].saveRecords(filename, false);
    return true;
}

bool Database::overwrite()
{
    string filename = input.getString("File name: ");
    collections[current_idx].saveRecords(filename, true);
    return true;
}

bool Database::connect(string name)
{
    if (collections != nullptr)
    {
        if (nameExists(name))
        {
            collections[find(name)].open(); // ensure collection not null
            connected = true;
            current_collection = name;
            current_idx = find(name);
        }

        else
        {
            cout << "Failed to connect. Collection \"" << name << "\" does not exist.\n";
            return false;
        }
    }
    return true;
}

void Database::disconnect()
{
    if (isConnected())
    {
        cout << "Disconnecting from \"" << current_collection << "\".\n";
        current_collection = "";
        current_idx = 0;
        connected = false;
        return;
    }
}

bool Database::isConnected()
{
    if (!connected)
    {
        cout << "Not connected to any collections\n";
        return false;
    }
    return true;
}

bool Database::upload()
{
    bool recordAdded = false;

    /* Data in upload file should be correctly formatted and space delimited. */
    if (isConnected())
    {
        string filename = input.getString("File name: ");
        ifstream file(filename);

        string line;
        if (file.is_open())
        {
            while (getline(file, line))
            {
                recordAdded = collections[current_idx].addExistingRecord(line);
                if (!recordAdded)
                {
                    file.close();
                    cout << "Could not upload from file. \n";
                    return false;
                }
            }
            file.close();
        }

        else
        {
            cout << "Unable to open: " << filename << "\n";
            return false;
        }
    }

    else
    {
        cout << "Must connect to collection before attempting upload.\n";
    }

    return true;
}

int Database::find(string name)
{
    int i;
    for (i = 0; i < num_collections; i++)
    {
        if (collections[i].getName() == name)
        {
            return i;
        }
    }
    return i;
}

void Database::increaseCapacity()
{
    collection_capacity = num_collections * 2;
    Collection *tmp = new Collection[num_collections];

    // deep copy collections memory to tmp
    for (int i = 0; i < num_collections; i++)
    {
        tmp[i] = collections[i];
    }

    // delete existing collections memory
    if (collections != nullptr)
    {
        delete[] collections;
        collections = nullptr;
    }

    // deep copy tmp to new collections aray
    collections = new Collection[collection_capacity];
    for (int i = 0; i < num_collections; i++)
    {
        collections[i] = tmp[i];
    }

    // delete tmp memory
    if (tmp != nullptr)
    {
        delete[] tmp;
        tmp = nullptr;
    }
}

bool Database::capacityReached()
{
    if (num_collections >= collection_capacity)
    {
        return true;
    }
    return false;
}

bool Database::nameExists(string name)
{
    for (int i = 0; i < num_collections; i++)
    {
        if (collections[i].getName() == name)
        {
            return true;
        }
    }
    return false;
}

bool Database::recordsCapacityReached()
{
    if (num_records >= MAX_SIZE)
    {
        return true;
    }
    return false;
}

void Database::listRecords()
{
    if (isConnected())
    {
        collections[current_idx].showRecords();
    }

    else
    {
        cout << "Must connect to a collection before listing records.\n";
    }
}
