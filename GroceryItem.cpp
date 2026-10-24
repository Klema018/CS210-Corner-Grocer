// * 
// Name: Kailey Lema-Church
// Course: CS 210
// Project: Conrner Grocer
// Description: Defines the GroceryItem class and its member functions.
//*

#include "GroceryItem.h"

// Creates a grocery item with its name and starting quantity.
GroceryItem::GroceryItem(string name, int initialQuantity) {
	itemName = name;
	quantity = initialQuantity;
}

// Returns the name of the grocery item.
string GroceryItem::GetName() const {
	return itemName;
}

// Returns the current quantity of the grocery item.
int GroceryItem::GetQuantity() const {
	return quantity;
}

// Increases the quantity by one when another occurrence is found.
void GroceryItem::AddItem() {
	quantity++;
}