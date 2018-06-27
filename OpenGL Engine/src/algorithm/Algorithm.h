#pragma once

#include <iterator>
#include <vector>
#include <sstream>

//Returns a T type vector from A array
template<class A, size_t N>
std::vector<A> ArrayToVector(A(&array)[N])
{
	return std::vector<A>(std::begin(array), std::end(array));
}


template<typename T>
void tstringsplit(const std::string &s, char delim, T result) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		if (!item.empty()) 
		{
			*(result++) = item;
		}
	}
}

std::vector<std::string> ssplit(const std::string &s, char delim);