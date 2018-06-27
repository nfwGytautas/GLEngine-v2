#include "Algorithm.h"

std::vector<std::string> ssplit(const std::string & s, char delim)
{	
	std::vector<std::string> elems;
	tstringsplit(s, delim, std::back_inserter(elems));
	return elems;
}