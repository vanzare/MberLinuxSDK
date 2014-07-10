#pragma once

#include "NonCopyable.h"

#include <vector>

template <typename T>
class MberList : private NonCopyable
{
public:
	MberList() :
		mItems()
	{
	}

	virtual ~MberList()
	{
	}

	unsigned int length() const
	{
		return (unsigned int)mItems.size();
	}

	void push(T* item)
	{
		mItems.push_back(item);
	}

	void pop()
	{
		mItems.pop_back();
	}

	T* at(const unsigned int index) const
	{
		return mItems.at(index);
	}

private:
	std::vector<T*> mItems;
};
