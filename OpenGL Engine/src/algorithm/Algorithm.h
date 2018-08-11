#pragma once

#include <iterator>
#include <vector>
#include <sstream>

//Returns a T type vector from A array
template<class A, size_t N>
std::vector<A> arrayToVector(A(&array)[N])
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

template<typename T>
void clamp(T& valueToClamp, T maxValue, T minValue)
{
	if(valueToClamp > maxValue)
	{ 
		valueToClamp = maxValue;
	}
	else if (valueToClamp < minValue)
	{
		valueToClamp = minValue;
	}
}

template<class T>
class continuous2DArray
{
public:
	continuous2DArray()
		:m_rCount(0), m_cLength(0)
	{
	}
	continuous2DArray(unsigned int mRowCount, unsigned int mCollumnLength)
		:m_rCount(mRowCount), m_cLength(mCollumnLength)
	{
		m_array.resize(mCollumnLength * mRowCount);
	}

	void resize(unsigned int mRowCount)
	{
		resize(mRowCount, mRowCount);
	}

	void resize(unsigned int mRowCount, unsigned int mCollumnLength)
	{
		m_rCount = mRowCount;
		m_cLength = mCollumnLength;
		m_array.resize(m_cLength * m_rCount);
	}

	T& get(unsigned int mRowIndex, unsigned int mColIndex)
	{
		return m_array[mRowIndex * m_cLength + mColIndex];
	}

	inline T& operator()(unsigned int mRowIndex, unsigned int mColIndex)
	{
		return get(mRowIndex, mColIndex);
	}

	unsigned int rowCount() const
	{
		return m_rCount;
	}

	unsigned int colCount() const
	{
		return m_cLength;
	}

private:
	std::vector<T> m_array;
	unsigned int m_rCount;
	unsigned int m_cLength;
};