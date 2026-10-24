// * 
// Name: Kailey Lema-Church
// Course: CS 210
// Project: Conrner Grocer
// Description:Reads grocery records and displays item frequencies.
//*

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include "GroceryItem.h"

using namespace std;

// Files used to read grocery records and save the backup.
const string INPUT_FILE = "CS210_Project_Three_Input_File.txt";
const string BACKUP_FILE = "frequency.dat";

// The map that connects each grocery item name to its GroceryItem object.
using GroceryMap = map<string, GroceryItem*>;

// Reads the grocery file and counts how many times each item appears.
GroceryMap ReadItems() {
	GroceryMap items;
	ifstream inputFile(INPUT_FILE);
	string name;

	// Cheacks wether the input file opened successfully.
	if (!inputFile.is_open()) {
		cerr << "Error:Could not open " << INPUT_FILE << endl;
		return items;
	}
	// Read one grocery item at a time and update it's quantity.
	while (getline(inputFile, name)) {
		if (name.empty()) {
			continue;
		}

		auto found = items.find(name);

		if (found != items.end()) {
			// The item is already in the map, so increase its quantity.
			found->second->AddItem();
		}
		else {
			// This is the first occurrence of the item.
			items.emplace(name, new GroceryItem(name, 1));
		}
	}

	return items;
}

// Deletes the grocery objects when they are no longer needed.
void DeleteItems(GroceryMap& items) {
	for (auto& entry : items) {
		delete entry.second;
	}
	items.clear();
}

// Saves each grocery item's name and quantity to the backup file.
// Returns 1 if the file is saved successfully or 0 if it fails.
int WriteBackup(const GroceryMap& items) {
	ofstream outputFile(BACKUP_FILE);

	if (!outputFile.is_open()) {
		cerr << "Error: Could not create " << BACKUP_FILE << "." << endl;
		return 0;
	}
	// Write each item's name and quantity to the backup file.
	for (const auto& entry : items) {
		outputFile << entry.first << " "
			<< entry.second->GetQuantity() << endl;
	}

	outputFile.close();

	// Check whether the backup file was written correctly.
	if (outputFile.fail()) {
		cerr << "Error: Could not write to " << BACKUP_FILE << "." << endl;
		return 0;
	}

	return 1;
}

// Looks up one grocery item and displays its frequency.
void SearchItem(const GroceryMap& items) {
	string name;

	cout << "Enter a grocery item: ";
	getline(cin, name);

	auto found = items.find(name);

	if (found != items.end()) {
		cout << name << " appears in the records "
			<< found->second->GetQuantity() << " times." << endl;
	}
	else {
		cout << name << " was not found." << endl;
	}
}

// Displays every grocery item and the number of times it appears.
void PrintFrequencies(const GroceryMap& items) {
	for (const auto& entry : items) {
		cout << entry.first << " "
			<< entry.second->GetQuantity() << endl;
	}
}

// Displays each grocery item with asterisks representing its quantity.
void PrintHistogram(const GroceryMap& items) {
	for (const auto& entry : items) {
		cout << entry.first << " ";

		// Print one asterisk for each occurrence of the item.
		for (int i = 0; i < entry.second->GetQuantity(); i++) {
			cout << '*';
		}

		cout << endl;
	}
}

int main() {

	// Create the backup file when the prograsm starts.
	GroceryMap initialItems = ReadItems();

	if (!initialItems.empty()) {
		WriteBackup(initialItems);
	}

	DeleteItems(initialItems);

	int choice = 0;

	// Keep displaying the menu until user chooses to exit.
	while (true) {
		cout << endl;
		cout << "===== Corner Grocer +++++" << endl;
		cout << "1. Search for an item" << endl;
		cout << "2. Display all item frequencies" << endl;
		cout << "3. Display item histogram" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice: ";

		// Check that user entered a number.
		if (!(cin >> choice)) {
			cout << "Invalid input. Please enter a number from 1 to 4."
				<< endl;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max()), char(10);
			continue;
		}

		// Clear the rest of the line before accepting more input.
		cin.ignore(numeric_limits<streamsize>::max(), char(10));
		
		if (choice == 4) {
			cout << "Goodbye." << endl;
			break;
		}

		// Reject menu choices outside what's allowed.
		if (choice < 1 || choice > 4) {
			cout << "Please pick an option from 1 to 4." << endl;
			continue;
		}
		// Reload the input file so each report uses the current records.
		GroceryMap items = ReadItems();

		if (items.empty()) {
			cout << "No grocery records were found. Check inventory.txt."
				<< endl;

			DeleteItems(items);
			continue;
		}

		// Run the report that matches user's menu choice.
		switch (choice) {
		case 1:
			SearchItem(items);
			break;

		case 2:
			PrintFrequencies(items);
			break;

		case 3:
			PrintHistogram(items);
			break;
		}

		DeleteItems(items);
	}

	return 0;
}