#pragma once

#include <iterator>
#include <vector>

//Returns a T type vector from A array
template<class A, size_t N>
std::vector<A> ArrayToVector(A(&array)[N])
{
	return std::vector<A>(std::begin(array), std::end(array));
}