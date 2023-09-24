// Name: Tedla Boke
// Netid: uq6435
// Email: tboke@horizon.csueastbay.edu

#include <iostream>
#include <fstream>
using namespace std;

const int MAX_ITEMS = 20;

enum RelationType { LESS, GREATER, EQUAL };

class ItemType
{
public:
    ItemType();
    RelationType ComparedTo(ItemType) const;
    void Initialize(int number);
    friend ostream& operator<<(ostream& os, const ItemType& item);
private:
    int value;
};

ItemType::ItemType()
{
    value = 0;
}

RelationType ItemType::ComparedTo(ItemType otherItem) const
{
    if (value < otherItem.value)
        return LESS;
    else if (value > otherItem.value)
        return GREATER;
    else
        return EQUAL;
}

void ItemType::Initialize(int number)
{
    value = number;
}

ostream& operator<<(ostream& os, const ItemType& item)
{
    os << item.value;
    return os;
}

class SortedType
{
public:
    SortedType();
    ItemType GetItem(ItemType item, bool& found);
    void PutItem(ItemType item);
    void DeleteItem(ItemType item);
    void PrintAll() const;
private:
    int length;
    ItemType info[MAX_ITEMS];
    int currentPos;
};

SortedType::SortedType()
{
    length = 0;
}

ItemType SortedType::GetItem(ItemType item, bool& found)
{
    int midPoint;
    int first = 0;
    int last = length - 1;
    bool moreToSearch = first <= last;
    found = false;
    while (moreToSearch && !found)
    {
        midPoint = (first + last) / 2;
        switch (item.ComparedTo(info[midPoint]))
        {
            case LESS: last = midPoint - 1;
                moreToSearch = first <= last;
                break;
            case GREATER: first = midPoint + 1;
                moreToSearch = first <= last;
                break;
            case EQUAL: found = true;
                item = info[midPoint];
                break;
        }
    }
    return item;
}

void SortedType::DeleteItem(ItemType item)
{
    int location = 0;
    while (item.ComparedTo(info[location]) != EQUAL)
        location++;
    for (int index = location + 1; index < length; index++)
        info[index - 1] = info[index];
    length--;
}

void SortedType::PutItem(ItemType item)
{
    bool moreToSearch;
    int location = 0;
    moreToSearch = (location < length);
    while (moreToSearch)
    {
        switch (item.ComparedTo(info[location]))
        {
            case LESS: moreToSearch = false;
                break;
            case GREATER: location++;
                moreToSearch = (location < length);
                break;
        }
    }
    for (int index = length; index > location; index--)
        info[index] = info[index - 1];
    info[location] = item;
    length++;
}

void SortedType::PrintAll() const
{
    for (int i = 0; i < length; i++)
    {
        cout << info[i];
        if (i < length - 1)
            cout << ",";
    }
    cout << endl;
}

int main()
{
    ifstream inputFile("DataFile.txt");
    if (!inputFile)
    {
        cerr << "Error opening the file." << endl;
        return 1;
    }

    SortedType list;

    // Read the first 20 cards and put them into the list
    for (int i = 0; i < 20; i++)
    {
        char suit, value;
        inputFile >> suit >> value;
        ItemType item;
        item.Initialize(value - '0'); // Convert character to integer
        list.PutItem(item);
    }

    cout << "List after inserting the first 20 cards: ";
    list.PrintAll();

    // Delete the cards indicated in the second line of the file
    for (int i = 0; i < 4; i++)
    {
        char suit, value;
        inputFile >> suit >> value;
        ItemType item;
        item.Initialize(value - '0'); // Convert character to integer
        list.DeleteItem(item);
    }

    cout << "List after deleting specified cards: ";
    list.PrintAll();

    // Put the items in the third line into the list
    for (int i = 0; i < 2; i++)
    {
        char suit, value;
        inputFile >> suit >> value;
        ItemType item;
        item.Initialize(value - '0'); // Convert character to integer
        list.PutItem(item);
    }

    cout << "List after inserting the third line cards: ";
    list.PrintAll();

    // Search for the elements in the list
    ItemType searchItem;
    searchItem.Initialize(9); // Example card to search for
    bool found;
    list.GetItem(searchItem, found);

    cout << "C9 " << (found ? "YES" : "NO") << ", ";

    searchItem.Initialize(10); // Example card to search for
    list.GetItem(searchItem, found);
    cout << "C10 " << (found ? "YES" : "NO") << endl;

    return 0;
}



























































