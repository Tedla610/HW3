// Name: Tedla Boke
// Netid: uq6435
// Email: tboke@horizon.csueastbay.edu

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Card {
public:
    char suit;
    string rank;

    Card(char s, const string& r) : suit(s), rank(r) {}

    bool operator<(const Card& other) const {
        if (suit == other.suit) {
            return rank < other.rank;
        }
        return suit < other.suit;
    }

    bool operator==(const Card& other) const {
        return suit == other.suit && rank == other.rank;
    }

    bool operator>(const Card& other) const {
        return !(*this < other) && !(*this == other);
    }
};

class CardList {
private:
    Card** cards;
    int size;
    int maxSize;

public:
    CardList(int maxSize) : maxSize(maxSize), size(0) {
        cards = new Card*[maxSize];
    }

    ~CardList() {
        for (int i = 0; i < size; ++i) {
            delete cards[i];
        }
        delete[] cards;
    }

    void putItem(const Card& card) {
        if (size < maxSize) {
            cards[size++] = new Card(card);
            sort(cards, cards + size, [](const Card* a, const Card* b) {
                return *a < *b;
            });
        }
    }

    void deleteItem(const Card& card) {
        int foundIndex = -1;
        for (int i = 0; i < size; ++i) {
            if (*cards[i] == card) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex != -1) {
            delete cards[foundIndex];
            for (int j = foundIndex; j < size - 1; ++j) {
                cards[j] = cards[j + 1];
            }
            size--;
        }
    }

    bool getItem(const Card& card) {
        for (int i = 0; i < size; ++i) {
            if (*cards[i] == card) {
                return true;
            }
        }
        return false;
    }

    void printAll() {
        for (int i = 0; i < size; ++i) {
            cout << cards[i]->suit << cards[i]->rank;
            if (i < size - 1) {
                cout << ",";
            }
        }
        cout << endl;
    }

    int compareTo(const Card& card1, const Card& card2) {
        if (card1 < card2) return -1;
        if (card1 == card2) return 0;
        return 1;
    }

    void clear() {
        for (int i = 0; i < size; ++i) {
            delete cards[i];
        }
        size = 0;
    }
};

int main() {
    ifstream inputFile("DataFile.txt");
    if (!inputFile) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    CardList cardList(20);
    string line;

    // Read and store the first 20 cards
    getline(inputFile, line);
    stringstream ss(line);
    string cardStr;
    while (getline(ss, cardStr, ',')) {
        char suit = cardStr[0];
        string rank = cardStr.substr(1);
        if (rank == "10") {
            rank = "M";
        }
        cardList.putItem(Card(suit, rank));
    }

    cout << "Step 1: ";
    cardList.printAll();

    // Read and delete the cards indicated in the second line
    getline(inputFile, line);
    ss.clear();
    ss.str(line);
    while (getline(ss, cardStr, ',')) {
        char suit = cardStr[0];
        string rank = cardStr.substr(1);
        if (rank == "10") {
            rank = "M";
        }
        cardList.deleteItem(Card(suit, rank));
    }

    cout << "Step 2: ";
    cardList.printAll();

    // Read and put the items from the third line into the list
    getline(inputFile, line);
    ss.clear();
    ss.str(line);
    while (getline(ss, cardStr, ',')) {
        char suit = cardStr[0];
        string rank = cardStr.substr(1);
        if (rank == "10") {
            rank = "M";
        }
        cardList.putItem(Card(suit, rank));
    }

    cout << "Step 3: ";
    cardList.printAll();

    // Read and search for cards in the fourth line
    getline(inputFile, line);
    ss.clear();
    ss.str(line);
    cout << "Step 4: ";
    while (getline(ss, cardStr, ',')) {
        char suit = cardStr[0];
        string rank = cardStr.substr(1);
        if (rank == "10") {
            rank = "M";
        }
        if (cardList.getItem(Card(suit, rank))) {
            cout << suit << rank << " YES, ";
        } else {
            cout << suit << rank << " NO, ";
        }
    }
    cout << endl;

    inputFile.close();

    return 0;
}
























































































