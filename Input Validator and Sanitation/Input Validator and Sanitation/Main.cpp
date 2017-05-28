// Main.cpp
//
// Just a source file to test my classes
//
// Author: Antonio Garcia Bares Jr.

#include <iostream>
#include <string>
#include <vector>

#include "Menu.h"
#include "Flag.h"

using namespace std;

int main()
{
	
	int selection;
		
	vector<string> menu;
	menu.push_back("Please select one of the following food from the menu.");
	menu.push_back("Apple");
	menu.push_back("Orange");
	menu.push_back("Steak");
	menu.push_back("Fried Chicken");

	Validator::Menu inputSelection(menu, "\n\t**Invalid Input**\n");

	selection = inputSelection.getInput();

	system("pause");
	return 0;
}