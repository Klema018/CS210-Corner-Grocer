// * 
// Name: Kailey Lema-Church
// Course: CS 210
// Project: Conrner Grocer
// Description: Defines the GroceryItem class and its member functions.
//*


#ifndef GROCERYITEM_H
#define GROCERYITEM_H

#include <string>
using namespace std;

// Prevents this header file from being included more than once.
class GroceryItem {
private:
	// Stores the grocery item's name and its total quantity.
	string itemName;
	int quantity;

public:
	// Creates a grocery item with a name and starting quantity.
	GroceryItem(string name, int initialQuantity);

	// Reutrns the name of the grocery item.
	string GetName() const;

	// Returns the current quantity of the grocery item.
	int GetQuantity() const;

	// Increases the quantity when another occurrence is found.
	void AddItem();

};

#endif

