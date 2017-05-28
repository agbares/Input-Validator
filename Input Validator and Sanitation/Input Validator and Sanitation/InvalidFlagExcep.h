#pragma once

#include <stdexcept>
#include <string>

class InvalidFlagExcep : public std::logic_error
{
public:
	InvalidFlagExcep(const std::string &message);
};