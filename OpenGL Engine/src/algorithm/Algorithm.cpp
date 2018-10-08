#include "Algorithm.h"
#include <fstream>

std::vector<std::string> ssplit(const std::string & s, char delim)
{	
	std::vector<std::string> elems;
	tstringsplit(s, delim, std::back_inserter(elems));
	return elems;
}

bool fexists(const std::string& filename)
{
	std::ifstream ifile(filename.c_str());
	return (bool) ifile;
}
