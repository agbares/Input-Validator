#include "InvalidFlagExcep.h"

InvalidFlagExcep::InvalidFlagExcep(const std::string &message) : logic_error("Invalid Flag Exception: " + message)
{
}