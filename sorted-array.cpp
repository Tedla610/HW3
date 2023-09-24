// Name: Tedla Boke
// Netid: uq6435
// Email: tboke@horizon.csueastbay.edu

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 20;

struct Card {
    char suit;
    string value;

    int compareTo(const Card& other) const {
        if (suit != other.suit) {
            if (suit == 'C' || (other.suit != 'C' && suit < other.suit)) {
                return -1;
            }
            return 1;
        }
        return value.compare(other.value);
    }
};

class SortedList {
private:
    Card* data;
    int size;
    int capacity;

public:
    SortedList() {
        capacity = MAX_SIZE;
        data = new Card[capacity];
        size = 0;
    }

    ~SortedList() {
        delete[] data;
    }

    void putItem(const Card& card) {
        if (size >= capacity) {
            cout << "List is full." << endl;
            return;
        }

        int index = size;
        while (index > 0 && card.compareTo(data[index - 1]) < 0) {
            data[index] = data[index - 1];
            index--;
        }

        data[index] = card;
        size++;
    }

    void deleteItem(const Card& card) {
        for (int i = 0; i < size; i++) {
            if (data[i].compareTo(card) == 0) {
                for (int j = i; j < size - 1; j++) {
                    data[j] = data[j + 1];
                }
                size--;
                break;
            }
        }
    }

    bool getItem(const Card& card) {
        for (int i = 0; i < size; i++) {
            if (data[i].compareTo(card) == 0) {
                return true;
            }
        }
        return false;
    }

    void printAll() {
        for (int i = 0; i < size; i++) {
            cout << data[i].suit << data[i].value;
            if (i < size - 1) {
                cout << ",";
            }
        }
        cout << endl;
    }
};

int main() {
    SortedList cardList;

    // Get the file name from the user
    cout << "Enter the file name: ";
    string fileName;
    cin >> fileName;

    // Read the entire file and insert cards
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    stringstream fileContents;
    fileContents << inputFile.rdbuf();  // Read the entire file into stringstream
    inputFile.close();

    string fileData = fileContents.str();

    // Process the contents of the file
    stringstream ss(fileData);
    string cardStr;

    while (getline(ss, cardStr, ',')) {
        Card card;
        card.suit = cardStr[0];
        card.value = cardStr.substr(1);
        cardList.putItem(card);
    }

    // Print the current list
    cout << "Initial List: ";
    cardList.printAll();

    // Read and delete the cards indicated in the second line of the file
    string line;
    getline(fileContents, line);
    ss.clear();
    ss.str(line);

    while (getline(ss, cardStr, ',')) {
        Card card;
        card.suit = cardStr[0];
        card.value = cardStr.substr(1);
        cardList.deleteItem(card);
    }

    // Print the updated list after deletion
    cout << "List after deletion: ";
    cardList.printAll();

    // Read and insert the items from the third line
    getline(fileContents, line);
    ss.clear();
    ss.str(line);

    while (getline(ss, cardStr, ',')) {
        Card card;
        card.suit = cardStr[0];
        card.value = cardStr.substr(1);
        cardList.putItem(card);
    }

    // Print the updated list after insertion
    cout << "List after insertion: ";
    cardList.printAll();

    // Search for elements in the list
    cout << "Search Results:" << endl;
    cout << "C9: " << (cardList.getItem(Card{'C', "9"}) ? "YES" : "NO") << endl;
    cout << "C10: " << (cardList.getItem(Card{'C', "10"}) ? "YES" : "NO") << endl;

    return 0;
}
















