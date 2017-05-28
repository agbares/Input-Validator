// Menu class -- Specification & Implementation
// 
// This is a basic child class of Validator::Input that takes care of 
// user menu selection.
//
// This is intended for console based programs.
//
// Author: Antonio Garcia Bares Jr.

/* DESCRIPTION:

The class has the following properties that should be initialized:

std::vector userMenu -- The menu that will be displayed to prompt the user for selection.
The Validator can only have either userPrompt or userMenu, not both.
FORMAT:
userMenu[0] - Should hold the text that will be displayed to prompt the user for input
userMenu[n] - (Where n > 0) Should hold the text for the nth menu item

Example:
userMenu[0] - "Please select one of the following food from the menu."
userMenu[1] - "Apple"
userMenu[2] - "Orange"
userMenu[3] - "Steak"
userMenu[4] - "Fried Chicken"

Example Output: (The function that outputs the menu will automatically add the numbering sequence)
Please select one of the following food from the menu.
1) Apple
2) Orange
3) Steak
4) Fried Chicken

std::string invalidPrompt -- The text that will be displayed whenever the user enters an invalid input

bool willPause -- Setting that decides if the prompt will pause when invalidPrompt is displayed
before requesting another input.
DEFAULT VALUE: true

bool willClear -- Setting that decides if the console screen will be cleared before userMenu
is displayed.
DEFAULT VALUE: true

*/


#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Input.h"

namespace Validator 
{
	class Menu : public Input<int>
	{
	private:

		std::vector<std::string> userMenu;
		int input;

		void promptUser(); // Prompts the user for input and runs basic validation

	public:
		// Constructor
		Menu(std::vector<std::string> inUserMenu, std::string inInvalidPrompt)
		{
			userMenu = inUserMenu;
			setInvalidPrompt(inInvalidPrompt);
		}

		int getInput(); // Helper function which calls Menu::promptUser()
	};

	// MARK: -- Private Methods

	void Menu::promptUser()
	{
		do
		{

			if (!userMenu.empty())
			{

				int index;

				for (auto it = userMenu.cbegin(); it != userMenu.cend(); it++)
				{
					index = std::distance(userMenu.cbegin(), it);

					if (index > 0)
						std::cout << index << ") " << *it << std::endl;
					else
						std::cout << *it << std::endl;
				}
			}

			std::cin >> input;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
				std::cout << getInvalidPrompt() << std::endl;

				if (getWillPause() == true)
					std::system("pause");

				if (getWillClear() == true)
					std::system("cls");

				setIsValid(false);
			}
			else if (!userMenu.empty() && (input < 1 || input > userMenu.size() - 1))
			{
				std::cout << getInvalidPrompt() << std::endl;

				if (getWillPause() == true)
					std::system("pause");

				if (getWillClear() == true)
					std::system("cls");

				setIsValid(false);
			}
			else
				setIsValid(true);

		} while (!getIsValid());
	}

	// MARK: -- Helper methods
	int Menu::getInput()
	{
		promptUser();
		return input;
	}

}