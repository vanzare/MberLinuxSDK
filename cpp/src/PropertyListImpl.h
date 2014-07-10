#pragma once

#include "MberListImpl.h"

struct MBER_PROPERTY;

struct MBER_PROPERTY_LIST : public MberList<MBER_PROPERTY>
{
public:
	MBER_PROPERTY_LIST() : MberList() {}
	virtual ~MBER_PROPERTY_LIST() {}
};
