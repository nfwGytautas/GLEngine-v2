#pragma once

#include <iterator>
#include <vector>

//Returns a T type vector from A array
template<typename T, class A, size_t N>
std::vector<T> ArrayToVector(A(&array)[N])
{
	return std::vector<T>(std::begin(array), std::end(array));
}