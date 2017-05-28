#include "InvalidInputExcep.h"

InvalidInputExcep::InvalidInputExcep(const std::string& message) : logic_error("Invalid Input Exception:" + message)
{

}