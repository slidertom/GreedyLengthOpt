#include "stdafx.h"
#include "LengthOptResults.h"

#include "algorithm"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace internal
{
	static size_t GetAllLen(const CLenArray &len_array, size_t nSaw) {
		size_t nAllLen = 0;
		for (size_t nLen : len_array) {
			nAllLen += nLen;
			nAllLen += nSaw;
		}
		return nAllLen;
	}

	static inline bool TryToAdd(size_t nAllLen, size_t nTotalLen, size_t nLen) {
		nAllLen += nLen;
		if ( nAllLen <= nTotalLen ) {
			return true;
		}
		return false;
	}

	static inline bool TryToAdd2(size_t nAllLen, size_t nTotalLen, size_t nLen, size_t &diff) {
		nAllLen += nLen; // nAllLen already contains saw length added
		if ( nAllLen <= nTotalLen ) {
			diff = nTotalLen - nAllLen;
			return true;
		}
		return false;
	}
}

CLengthOptResults::CLengthOptResults()
{

}

CLengthOptResults::~CLengthOptResults()
{
	DeleteAll();
}

void CLengthOptResults::DeleteAll()
{
	for (auto *pLenArray : *this) {
		delete pLenArray;
	}
	clear();
}

void CLengthOptResults::AddEx(CLenArray::value_type nLen, CLenArray::value_type nTotalLen, CLenArray::value_type nSaw)
{
	// find out the best len array for the add -> compacting
	CLenArray::value_type diff = nTotalLen;
	CLenArray *pAdd = nullptr;
	for (CLenArray *pLenArray : *this) {
		//auto nAllLen = internal::GetAllLen(*pLenArray, nSaw);
		auto nAllLen = pLenArray->m_nAllLen; // 3-7 times faster optimization
		CLenArray::value_type tmp_diff;
		if ( !internal::TryToAdd2(nAllLen, nTotalLen, nLen, tmp_diff) ) {
			continue;
		}
		if ( tmp_diff < diff  ) {
			diff = tmp_diff;
			pAdd = pLenArray;
			if ( diff == 0 ) {
				break; // the best choice
			}
		} 
	}

	if ( pAdd ) {
		pAdd->push_back(nLen, nSaw);
		return;
	}

	CLenArray *pArr = new CLenArray;
	pArr->reserve(3); // at least it's expected 2 elements (RemoveMatch almostly eliminates 1 length possibility in the CLenArray)
	this->push_back(pArr);
	pArr->push_back(nLen, nSaw);
}

void CLengthOptResults::Add(CLenArray::value_type nLen, CLenArray::value_type nSaw)
{
	CLenArray *pArr = new CLenArray;
	this->push_back(pArr);
	pArr->push_back(nLen, nSaw);
}

void CLengthOptResults::AddTotalLengths(CLenArray::value_type nTotalLen, size_t nCount)
{
	this->reserve(nCount);
	CLenArray *pArray = nullptr;
	for (size_t i1 = 0; i1 < nCount; ++i1) {
		 pArray = new CLenArray;
		 pArray->push_back(nTotalLen, 0);
		 this->push_back(pArray);
	}
}

size_t CLengthOptResults::GetAllLength() const
{
	size_t nAllLen = 0;
	for (const CLenArray *pLenArray : *this) {
		nAllLen += internal::GetAllLen(*pLenArray, 0);
	}
	return nAllLen;
}

size_t CLengthOptResults::GetLengthsCount() const
{
	size_t nCount = 0;
	for (CLenArray *pLenArray : *this) {
		nCount += pLenArray->size();
	}
	return nCount;
}

CLengthOptResults &CLengthOptResults::operator=(const CLengthOptResults &r)
{
	DeleteAll();
	reserve(r.size());
	
	CLenArray *pArray = nullptr;

	auto end_it = r.end();
	for (auto it = r.begin(); it != end_it; ++it) {
		pArray = new CLenArray; 
		*pArray = **it; // possible optimization: do use shared_ptr std::vector<std::shared_ptr<...
		ASSERT(pArray->size() > 0);
		this->push_back(pArray);
	}

	return *this;
}

namespace internal {
	static bool CompareImpl(const CLenArray *pArr1, const CLenArray *pArr2)  {
		const size_t nSize1 = pArr1->size();
		const size_t nSize2 = pArr2->size();
		return nSize1 < nSize2;
	}
}

void CLengthOptResults::Sort()
{
	std::sort(this->begin(), this->end(), internal::CompareImpl);

	for (CLenArray *pLenArray : *this) {
		std::sort(pLenArray->begin(), pLenArray->end());
	}
}

void CLengthOptResults::Compact(size_t nTotalLen, size_t nSaw)
{
   size_t nCnt = size();
   if ( nCnt < 2 )  {
       return;
   }

   bool bDo = true;
   while (bDo) 
   {
       bDo  = false;
       const size_t nLast = nCnt - 1;
       if ( nLast < 2 ) {
           return;
       }

       CLenArray *pLastLenArray = (*this)[nLast]; 
       size_t nLastSize = pLastLenArray->size();
       for (int i1 = 0; i1 < nLast; ++i1) {
		   CLenArray *pCurrLenArray = (*this)[i1];
           CLenArray::value_type nAllLen = internal::GetAllLen(*pCurrLenArray, nSaw);
           for (int i2 = 0; i2 < nLastSize; ++i2) {
               const CLenArray::value_type nLen = (*pLastLenArray)[i2];
               if ( internal::TryToAdd(nAllLen, nTotalLen, nLen) ) { 
                   nAllLen += nLen;
                   pLastLenArray->RemoveAt(i2, nSaw);
				   pCurrLenArray->push_back(nLen, nSaw);
                   --nLastSize;
                   --i2;
				   bDo = true; // try to continue -> even not all elements can be distributed from the last_len_array 
               }               // -> but maybe we will find the right one if currently something can be distributed (assumtion)
           }
           if ( nLastSize == 0 ) {
               break; // all elements of the last length array can be distributed
           }
       }

	   if ( nLastSize == 0 ) {
		   delete (*this)[nLast];
           erase(begin()+nLast);
		   nCnt = size();
	   } 
	   //else { // -> iteration through all the elements does not provide better resutls
	   //	   nCnt = nLast;
	   //	   bDo = true;
	   //}
	   // if bDo == false -> we have failed to find the smallest piece which can be compacted
   }
}

void CLengthOptResults::Distribute(size_t nTotalLen, size_t nSaw)
{
   // Distribution could be hardcoded into the CLengthOptResults::Add -> do include nLen to the right bar at the first step.
   // Current implementation is more "optimal" -> we do stop at the first fail instead of checking every time.
   // Try to distribute the smallest one pieces:
   size_t nCnt = size();
   if ( nCnt < 2 )  {
       return;
   }

   bool bDo = true;
   while (bDo) 
   {
       bDo  = false;
       const size_t nLast = nCnt - 1;
       if ( nLast < 2 ) {
           return;
       }

       CLenArray last_len_array = *(*this)[nLast]; // copy
       size_t nLastSize = last_len_array.size();
       std::vector<std::pair<CLenArray *, size_t>> distribution;
       for (int i1 = 0; i1 < nLast; ++i1) {
		   CLenArray *pCurrLenArray = (*this)[i1];
           CLenArray::value_type nAllLen = internal::GetAllLen(*pCurrLenArray, nSaw);
           for (int i2 = 0; i2 < nLastSize; ++i2) {
               const CLenArray::value_type nLen = last_len_array[i2];
               if ( internal::TryToAdd(nAllLen, nTotalLen, nLen) ) { 
                   nAllLen += nLen;
                   last_len_array.RemoveAt(i2, nSaw);
                   --nLastSize;
                   --i2;
                   distribution.push_back(std::make_pair(pCurrLenArray, nLen));
				   bDo = true; // try to continue -> even not all elements can be distributed from the last_len_array 
               }               // -> but maybe we will find the right one if currently something can be distributed (assumtion)
           }
           if ( nLastSize == 0 ) {
               break; // all elements of the last length array can be distributed
           }
       }

       if ( nLastSize == 0 ) { // do distribute
           for (auto pair_el : distribution) {
               pair_el.first->push_back(pair_el.second, nSaw);
           }
           delete (*this)[nLast];
           erase(begin()+nLast);
		   nCnt = size();
       }
	   else {  
		   //bDo = true; //-> try all variations
		   nCnt = nLast;
	   }
	   // if bDo == false -> we have failed to find the smallest piece which can be distributed
   }
}

bool CLengthOptResults::Validate(size_t nTotalLen, size_t nSaw) const
{
	for (auto *pLenArray : *this) {
		auto nAllLen = internal::GetAllLen(*pLenArray, nSaw);
		nAllLen -= nSaw;
		if ( nAllLen > nTotalLen ) {
			return false;
		}
	}
	return true;
}
