/*
* Daniel Deleon
* 04.19.2026
* CS-220
* This source file contains the function definitions for the GroceryTracker class.
* It handles reading the input fle, counting grocery item frequencies,
* writing the frequency.dat backup file, and printing the menu results.
*/

#include "GroceryTracker.h"

#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

// constructor sets the input file and output file names
GroceryTracker::GroceryTracker(const string& input, const string& backup)
    : inputFileName(input), backupFileName(backup) {
}

// this puts the word into a cleaner format so searching works better
string GroceryTracker::NormalizeWord(const string& text) const {
    string normalized;
    bool capitalizeNext = true;  // used to capitalize the first letter

    for (char ch : text) {
        unsigned char currentChar = static_cast<unsigned char>(ch);

        if (isalpha(currentChar)) {
            if (capitalizeNext) {
                normalized += static_cast<char>(toupper(currentChar));
                capitalizeNext = false;
            }
            else {
                normalized += static_cast<char>(tolower(currentChar));
            }
        }
        else if (ch == ' ' || ch == '-' || ch == '\'') {
            // keep spaces, hyphens, or apostrophes if they exist
            normalized += ch;
            capitalizeNext = true;
        }
    }

    return normalized;
}

// opens the input file and counts how many times each item appears
bool GroceryTracker::LoadData() {
    ifstream inputFile(inputFileName);
    string itemName;

    // if the file can't open, return false
    if (!inputFile.is_open()) {
        return false;
    }

    // clears anything old just in case
    itemFrequencies.clear();

    // read each word from the file
    while (inputFile >> itemName) {
        itemName = NormalizeWord(itemName); // clean up the formatting

        if (!itemName.empty()) {
            ++itemFrequencies[itemName]; // add 1 to that item's count
        }
    }

    inputFile.close();

    // once the data is loaded, create the backup file
    WriteBackupFile();
    return true;
}

// writes all items and frequencies into frequency.dat
void GroceryTracker::WriteBackupFile() const {
    ofstream outputFile(backupFileName);

    for (const auto& item : itemFrequencies) {
        outputFile << item.first << " " << item.second << endl;
    }
}

// looks for one item and returns the count
int GroceryTracker::GetItemFrequency(const string& itemName) const {
    string normalizedItem = NormalizeWord(itemName); // format input the same way
    auto itemLocation = itemFrequencies.find(normalizedItem);

    // if item was found, return the count
    if (itemLocation != itemFrequencies.end()) {
        return itemLocation->second;
    }

    // if not found, return 0
    return 0;
}

// prints every item and how many times it appears
void GroceryTracker::PrintAllFrequencies() const {
    cout << "\nItem Purchase Frequencies\n";
    cout << "------------------------\n";

    for (const auto& item : itemFrequencies) {
        cout << item.first << " " << item.second << endl;
    }
}

// prints a histogram using stars instead of just numbers
void GroceryTracker::PrintHistogram() const {
    cout << "\nItem Purchase Histogram\n";
    cout << "-----------------------\n";

    for (const auto& item : itemFrequencies) {
        cout << item.first << " ";

        // print one star for each time the item appears
        for (int i = 0; i < item.second; ++i) {
            cout << "*";
        }

        cout << endl;
    }
}

// prints the menu choices
void GroceryTracker::DisplayMenu() const {
    cout << "\nCorner Grocer Menu\n";
    cout << "------------------\n";
    cout << "1. Search for an item frequency\n";
    cout << "2. Print all item frequencies\n";
    cout << "3. Print histogram\n";
    cout << "4. Exit\n";
}