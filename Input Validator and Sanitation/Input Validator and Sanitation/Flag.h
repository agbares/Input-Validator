// Flag enumerator class -- Specification & Implementation
// 
// This enumerator class is used for the Input class to
// allow comparing input against a predetermined value
//
// Author: Antonio Garcia Bares Jr.

#pragma once
namespace validator
{
	enum class Flag
	{
		NONE = 0,
		LESSTHAN,
		LESSTHANEQ,
		GREATERTHAN,
		GREATERTHANEQ,
		EQUAL,
		NOTEQUAL
	};
}
