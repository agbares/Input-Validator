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

#include <iostream>
#include <string>
#include <vector>
#include "Flag.h"
#include "InvalidFlagExcep.h"
#include "InvalidInputExcep.h"

namespace AGB 
{

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
		Validator();
		Validator(std::string, std::string);
		Validator(std::string, std::string, bool, bool);
		Validator(std::string, std::string, type, Flag);
		Validator(std::string, std::string, type, Flag, bool, bool);

		// Mutators
		void setUserPrompt(std::string);
		void setInvalidPrompt(std::string);
		void setIsValid(bool);
		void setWillPause(bool);
		void setWillClear(bool);

		// Accessors
		std::string getUserPrompt();
		std::string getInvalidPrompt();
		bool getIsValid();
		bool getWillPause();
		bool getWillClear();

		type getInput(); // Helper function which calls Validator::promptUser()



	};

	// MARK: -- Constructors
	template <class type>
	Validator<type>::Validator()
	{
		userPrompt = "";
		invalidPrompt = "";
	}

	template <class type>
	Validator<type>::Validator(std::string inUserPrompt, std::string inInvalidPrompt)
	{
		userPrompt = inUserPrompt;
		invalidPrompt = inInvalidPrompt;
	}

	template <class type>
	Validator<type>::Validator(std::string inUserPrompt, std::string inInvalidPrompt, bool inWillPause, bool inWillClear)
	{
		userPrompt = inUserPrompt;
		invalidPrompt = inInvalidPrompt;
		willPause = inWillPause;
		willClear = inWillClear;
	}

	template <class type>
	Validator<type>::Validator(std::string inUserPrompt, std::string inInvalidPrompt, type inComparator, Flag inCFlag)
	{
		userPrompt = inUserPrompt;
		invalidPrompt = inInvalidPrompt;
		comparator = inComparator;
		cFlag = inCFlag;
	}

	template <class type>
	Validator<type>::Validator(std::string inUserPrompt, std::string inInvalidPrompt, type inComparator, Flag inCFlag, bool inWillPause, bool inWillClear)
	{
		userPrompt = inUserPrompt;
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
			else if (cFlag != Flag::NONE)
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
			else
				isValid = true;

		} while (!isValid);
	}

	// MARK: -- Mutators
	template <class type>
	void Validator<type>::setUserPrompt(std::string inUserPrompt)
	{
		userPrompt = inUserPrompt;
	}

	template <class type>
	void Validator<type>::setInvalidPrompt(std::string inInvalidPrompt)
	{
		invalidPrompt = inInvalidPrompt;
	}

	template <class type>
	void Validator<type>::setIsValid(bool inIsValid)
	{
		isValid = inIsValid;
	}
	
	template <class type>
	void Validator<type>::setWillPause(bool inWillPause)
	{
		willPause = inWillPause;
	}
	template <class type>
	void Validator<type>::setWillClear(bool inWillClear)
	{
		willClear = inWillClear;
	}

	// Mark: -- Accessors
	template <class type>
	std::string Validator<type>::getUserPrompt()
	{
		return userPrompt;
	}

	template <class type>
	std::string Validator<type>::getInvalidPrompt()
	{
		return invalidPrompt;
	}

	template <class type>
	bool Validator<type>::getIsValid()
	{
		return isValid;
	}

	template <class type>
	bool Validator<type>::getWillPause()
	{
		return willPause;
	}

	template <class type>
	bool Validator<type>::getWillClear()
	{
		return willClear;
	}

	template <class type>
	type Validator<type>::getInput()
	{
		promptUser();
		return input;
	}
}