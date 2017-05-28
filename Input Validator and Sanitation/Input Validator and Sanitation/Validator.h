// Validator class -- Specification & Implementation
// 
// This is an ADT class to work with the primitive datatypes and the std::string class
// for doing input validation. Objects should NOT be initialized to use any other 
// data types other than the primitive data types and std::string class. This class
// is not designed to work with any other types/classes other than the one's stated.
//
// This is intended for console based programs.
//
// Author: Antonio Garcia Bares Jr.

/* DESCRIPTION:

	The class has the following properties that should be initialized:

		std::string userPrompt -- The text that will be displayed to prompt the user for input
			The Validator can only have either userPrompt or userMenu, not both.

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

		bool willClear -- Setting that decides if the console screen will be cleared before userPrompt
			is displayed.
			DEFAULT VALUE: true

		type comparator -- Value that will be used to compare against the user's input. 
			IS OPTIONAL IF a Validator object is initialized without a comparator nor flag value.

		int cFlag -- Value will be used to decide on how to compare the user's input against the comparator
			value. The cFlag value must be a value between 0 to 6, which is mapped to the flag enumerator.
			IS OPTIONAL IF a Validator object is initialized without a comparator nor cFlag value.
			
*/

#pragma once
#pragma warning( disable : 4290 )

#include <iostream>
#include <string>
#include <vector>
#include "Flag.h"
#include "InvalidFlagExcep.h"
#include "InvalidInputExcep.h"

namespace AGB {

	template <class type>
	class Validator
	{
	private:

		std::string userPrompt,
			invalidPrompt;

		std::vector<std::string> userMenu;

		bool isValid = false,
			willPause = true,
			willClear = true;

		type comparator;
		Flag cFlag = Flag::NONE;

		type input;

		void promptUser(); // Prompts the user for input and runs basic validation

	public:
		// Constructors
		Validator(std::string, std::string);
		Validator(std::string, std::string, bool, bool);
		Validator(std::string, std::string, type, Flag);
		Validator(std::string, std::string, type, Flag, bool, bool);

		Validator(std::vector<std::string>, std::string);
		Validator(std::vector<std::string>, std::string, bool, bool);
		Validator(std::vector<std::string>, std::string, type, Flag);
		Validator(std::vector<std::string>, std::string, type, Flag, bool, bool);

		// Setters for prompts
		void setUserPrompt(std::string);
		void setInvalidPrompt(std::string);

		type getInput(); // Helper function which calls Validator::promptUser()



	};

	// MARK: -- Constructors
	template <class type>
	Validator<type>::Validator(std::string inPrompt, std::string inInvalidPrompt)
	{
		userPrompt = inPrompt;
		invalidPrompt = inInvalidPrompt;
	}

	template <class type>
	Validator<type>::Validator(std::string inPrompt, std::string inInvalidPrompt, bool inWillPause, bool inWillClear)
	{
		userPrompt = inPrompt;
		invalidPrompt = inInvalidPrompt;
		willPause = inWillPause;
		willClear = inWillClear;
	}

	template <class type>
	Validator<type>::Validator(std::string inPrompt, std::string inInvalidPrompt, type inComparator, Flag inCFlag)
	{
		userPrompt = inPrompt;
		invalidPrompt = inInvalidPrompt;
		comparator = inComparator;
		cFlag = inCFlag;
	}

	template <class type>
	Validator<type>::Validator(std::string inPrompt, std::string inInvalidPrompt, type inComparator, Flag inCFlag, bool inWillPause, bool inWillClear)
	{
		userPrompt = inPrompt;
		invalidPrompt = inInvalidPrompt;
		willPause = inWillPause;
		willClear = inWillClear;
		comparator = inComparator;
		cFlag = inCFlag;
	}

	template <class type>
	Validator<type>::Validator(std::vector<std::string> inUserMenu, std::string inInvalidPrompt)
	{
		userMenu = inUserMenu;
		invalidPrompt = inInvalidPrompt;
	}

	template <class type>
	Validator<type>::Validator(std::vector<std::string> inUserMenu, std::string inInvalidPrompt, bool inWillPause, bool inWillClear)
	{
		userMenu = inUserMenu;
		invalidPrompt = inInvalidPrompt;
		willPause = inWillPause;
		willClear = inWillClear;
	}

	template <class type>
	Validator<type>::Validator(std::vector<std::string> inUserMenu, std::string inInvalidPrompt, type inComparator, Flag inCFlag)
	{
		userMenu = inUserMenu;
		invalidPrompt = inInvalidPrompt;
		comparator = inComparator;
		cFlag = inCFlag;
	}

	template <class type>
	Validator<type>::Validator(std::vector<std::string> inUserMenu, std::string inInvalidPrompt, type inComparator, Flag inCFlag, bool inWillPause, bool inWillClear)
	{
		userMenu = inUserMenu;
		invalidPrompt = inInvalidPrompt;
		willPause = inWillPause;
		willClear = inWillClear;
		comparator = inComparator;
		cFlag = inCFlag;
	}

	// MARK: -- Private Methods

	template <class type>
	void Validator<type>::promptUser()
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
						std::cout << *it << endl;
				}
			}
			else
				std::cout << userPrompt << endl;

			std::cin >> input;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
				std::cout << invalidPrompt << std::endl;

				if (willPause == true)
					std::system("pause");

				if (willClear == true)
					std::system("cls");

				isValid = false;
			}
			else if (cFlag != Flag::NONE && userMenu.empty())
			{
				if (cFlag == Flag::LESSTHAN && input < comparator)
					isValid = true;
				else if (cFlag == Flag::LESSTHANEQ && input <= comparator)
					isValid = true;
				else if (cFlag == Flag::GREATERTHAN && input > comparator)
					isValid = true;
				else if (cFlag == Flag::GREATERTHANEQ && input >= comparator)
					isValid = true;
				else if (cFlag == Flag::EQUAL && input == comparator)
					isValid = true;
				else if (cFlag == Flag::NOTEQUAL && input != comparator)
					isValid = true;
				else
					isValid = false;
			}
			else if (!userMenu.empty() && (input < 1 || input > userMenu.size() - 1))
			{
				std::cout << invalidPrompt << std::endl;

				if (willPause == true)
					std::system("pause");

				if (willClear == true)
					std::system("cls");

				isValid = false;
			}
			else
				isValid = true;

		} while (!isValid);
	}

	// MARK: -- Pubic Methods
	template <class type>
	void Validator<type>::setUserPrompt(std::string inPrompt)
	{
		userPrompt = inPrompt;
	}

	template <class type>
	void Validator<type>::setInvalidPrompt(std::string inInvalidPrompt)
	{
		invalidPrompt = inInvalidPrompt;
	}

	template <class type>
	type Validator<type>::getInput()
	{
		promptUser();
		return input;
	}
}