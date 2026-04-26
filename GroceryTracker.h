/*
* Daniel Deleon
* 04.19.2026
* CS-220
* This header file defines the GroceryYtacker class,
* It contains the private data members and public function prototypes
* used to load grocery data, search item frequencies, print results,
* and create the backup frequency file. 
*/

#ifndef GROCERYTRACKER_H
#define GROCERYTRACKER_H

#include <map>
#include <string>

class GroceryTracker {
private:
    // map stores the item name and how many times it shows up
    std::map<std::string, int> itemFrequencies;

    // these hold the names of the files we are using
    std::string inputFileName;
    std::string backupFileName;

    // helper function to make words the same format
    std::string NormalizeWord(const std::string& text) const;

public:
    // constructor
    GroceryTracker(const std::string& input = "CS210_Project_Three_Input_File.txt",
        const std::string& backup = "frequency.dat");

    // reads the input file and counts each item
    bool LoadData();

    // writes the backup file
    void WriteBackupFile() const;

    // returns how many times one item appears
    int GetItemFrequency(const std::string& itemName) const;

    // prints all items with their counts
    void PrintAllFrequencies() const;

    // prints the histogram with stars
    void PrintHistogram() const;

    // shows the menu
    void DisplayMenu() const;
};

#endif