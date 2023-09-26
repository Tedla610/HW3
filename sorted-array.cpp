#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

// Head_to_val() method assigns an integer value to cards with different heads
int head_to_val(char c) {
    if (c == 'C') return 1;
    else if (c == 'D') return 2;
    else if (c == 'H') return 3;
    else if (c == 'S') return 4;
}

// Tag_to_val() method assigns an integer value to cards of every denomination with a headset
int tag_to_val(char c) {
    if (c == '2') return 1;
    else if (c == '3') return 2;
    else if (c == '4') return 3;
    else if (c == '5') return 4;
    else if (c == '6') return 5;
    else if (c == '7') return 6;
    else if (c == '8') return 7;
    else if (c == '9') return 8;
    else if (c == 'M') return 9; // I have used M for 10
    else if (c == 'J') return 10;
    else if (c == 'Q') return 11;
    else if (c == 'K') return 12;
    else if (c == 'A') return 13;
}

// compareTo method compares two cards
bool compareTo(string s1, string s2) {
    if (head_to_val(s1[0]) == head_to_val(s2[0])) {
        return tag_to_val(s1[1]) < tag_to_val(s2[1]);
    } else {
        return head_to_val(s1[0]) < head_to_val(s2[0]);
    }
}

class CardList {
    string* listarr;
    int n;

public:
    CardList() {
        n = 0;
        listarr = new string[20];
        for (int i = 0; i < 20; i++) {
            listarr[i] = " ";
        }
    }

    void PutItem(string s);
    void DeleteItem(string s);
    void GetItem(string s);
    void printAll();

    ~CardList() {
        delete[] listarr;
    }
};

// PutItem() method inserts a string cards into the sorted Poker cards list.
void CardList::PutItem(string s) {
    if (listarr[0] == " ") {
        listarr[0] = s;
    } else {
        int i = 0;
        while (compareTo(listarr[i], s) && listarr[i] != " ") {
            i++;
        }
        if (listarr[i] == " ") {
            listarr[i] = s;
        } else {
            for (int j = 18; j >= i; j--) {
                listarr[j + 1] = listarr[j];
            }
            listarr[i] = s;
        }
    }
    n += 1;
}

// DeleteItem() method deletes a string (card) s from the sorted Poker cards list.
void CardList::DeleteItem(string s) {
    if (listarr[0] == " ") {
        return;
    } else {
        int i = 0;
        while (listarr[i] != s && i < 20 && listarr[i] != " ") {
            i++;
        }
        if (listarr[i] == s) {
            for (int j = i; j < 19; j++) {
                listarr[j] = listarr[j + 1];
            }
            n -= 1;
        }
    }
}

// Display() method displays the list of cards.
void CardList::printAll() {
    for (int i = 0; i < n - 1; i++) {
        if (listarr[i][1] == 'M') {
            cout << listarr[i][0] << "10,";
            continue;
        }
        cout << listarr[i] << ",";
    }
    cout << listarr[n - 1] << endl;
}

// GetItem() method finds a string (card) s in the sorted Poker cards list.
void CardList::GetItem(string s) {
    if (listarr[0] == " ") {
        cout << s << " NO ";
    } else {
        int i = 0;
        while (listarr[i] != s && i < n && listarr[i] != " ") {
            i++;
        }
        if (listarr[i] == s) {
            cout << s << " YES ";
        } else {
            cout << s << " NO ";
        }
    }
}

int main() {
    ifstream fobj;
    fobj.open("DataFile.txt");

    if (!fobj.good()) {
        cout << "Error opening file!!" << endl;
    } else {
        CardList cardList;
        string str;

        // Read the first 20 cards in the first line of the file and put them one by one into the list
        getline(fobj, str);
        stringstream ss(str);
        int i = 0;
        while (ss.good() && i < 20) {
            string substr;
            getline(ss, substr, ',');
            if (substr[1] == '1' && substr[2] == '0') {
                substr[1] = 'M';
                substr[2] = '\0';
            }
            cardList.PutItem(substr);
            i++;
        }

        cardList.printAll();

        // Delete the cards indicated in the second line of the file
        getline(fobj, str);
        stringstream ss1(str);
        i = 0;
        while (ss1.good() && i < 20) {
            string substr;
            getline(ss1, substr, ',');
            if (substr[1] == '1' && substr[2] == '0') {
                substr[1] = 'M';
                substr[2] = '\0';
            }
            cardList.DeleteItem(substr);
            i++;
        }

        cardList.printAll();

        // Put the items in the third line into the list
        getline(fobj, str);
        stringstream ss2(str);
        i = 0;
        while (ss2.good() && i < 20) {
            string substr;
            getline(ss2, substr, ',');
            if (substr[1] == '1' && substr[2] == '0') {
                substr[1] = 'M';
                substr[2] = '\0';
            }
            cardList.PutItem(substr);
            i++;
        }

        cardList.printAll();

        // Search the current list for the elements in the list
        getline(fobj, str);
        stringstream ss3(str);
        i = 0;
        while (ss3.good() && i < 20) {
            string substr;
            getline(ss3, substr, ',');
            cardList.GetItem(substr);
            i++;
        }

        cout << endl;
    }

    return 0;
}
