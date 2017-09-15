#ifndef __LENGTH_OPT_RESULTS_H__
#define __LENGTH_OPT_RESULTS_H__
#pragma once

#ifndef __GREEDY_LENGTH_OPT_DEF_H__
    #include "../GreedyLengthOptDef.h"
#endif

#include "vector"

// we calculations based on the int value
class CLenArray : public std::vector<size_t> { 
public:
	CLenArray() : m_nAllLen(0) { }

	void RemoveAt(size_t nAt, CLenArray::value_type nSaw) {
		m_nAllLen -= (*this)[nAt];
		m_nAllLen -= nSaw;
		erase(begin()+nAt);
	}

	void push_back(size_t nVal, size_t nSaw) {
		std::vector<size_t>::push_back(nVal);
		m_nAllLen += nVal;
		m_nAllLen += nSaw;
	}

	size_t m_nAllLen; // => all length + saw = length1 + saw + length2 + saw + length3 + saw
};

class GREEDY_LENGTH_OPT_API CLengthOptResults : public std::vector<CLenArray *> 
{
// Construction/Destruction
public:
	CLengthOptResults();
	virtual ~CLengthOptResults();

// Operations
public:
	void DeleteAll();

	void Add(CLenArray::value_type nLen, CLenArray::value_type nSaw);
	void AddEx(CLenArray::value_type nLen, CLenArray::value_type nTotalLen, CLenArray::value_type nSaw);
	void AddTotalLengths(CLenArray::value_type nTotalLen, size_t nCount);

	size_t GetLengthsCount() const;
	size_t GetTradeCount() const { return size(); }
	size_t GetAllLength() const;

	// can be be used if AddEx is not used
    void Distribute(size_t nTotalLen, size_t nSaw); // gives more better results vs Compact -> Distribute works in more accurate way
	void Compact(size_t nTotalLen, size_t nSaw);

	bool Validate(size_t nTotalLen, size_t nSaw) const;

	void Sort();

// Operators
public:
	CLengthOptResults &operator=(const CLengthOptResults &r);

// Attributes
private:
	CLengthOptResults(const CLengthOptResults &r);
};

#endif 
