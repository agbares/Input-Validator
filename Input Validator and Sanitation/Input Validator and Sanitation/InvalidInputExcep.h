#pragma once

#include <stdexcept>
#include <string>

class InvalidInputExcep : public std::logic_error
{
public:
	InvalidInputExcep(const std::string& message);
};