/*
* Daniel Deleon
* 04.19.2026
* CS-220
* This creates the GroceryTracker object, loads the grocery data,
* displays the menu, and proceses the users menu choices.
*/


#include "GroceryTracker.h"

#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main() {
    GroceryTracker tracker;   // create object
    int menuChoice = 0;       // stores menu choice
    string itemToSearch;      // stores item the user types in

    // load the grocery data when the program starts
    if (!tracker.LoadData()) {
        cout << "Error: Unable to open CS210_Project_Three_Input_File.txt." << endl;
        return 1;
    }

    do {
        tracker.DisplayMenu();
        cout << "Enter your choice: ";

        // makes sure the user enters a number
        while (!(cin >> menuChoice)) {
            cout << "Invalid input. Please enter a number from 1 to 4: ";
            cin.clear(); // clears error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clears bad input
        }

        // clears leftover newline before getline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (menuChoice) {
        case 1:
            cout << "Enter the item name: ";
            getline(cin, itemToSearch);

            // call the function and print how many times the item appears
            cout << itemToSearch << " was purchased "
                << tracker.GetItemFrequency(itemToSearch)
                << " time(s)." << endl;
            break;

        case 2:
            // print all items and counts
            tracker.PrintAllFrequencies();
            break;

        case 3:
            // print histogram
            tracker.PrintHistogram();
            break;

        case 4:
            // exit the program
            cout << "Program ended." << endl;
            break;

        default:
            // handles numbers not on the menu
            cout << "Invalid menu option. Please select 1, 2, 3, or 4." << endl;
            break;
        }

    } while (menuChoice != 4); // keep looping until user picks 4

    return 0;
}