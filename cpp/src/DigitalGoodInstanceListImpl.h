#pragma once

#include "MberListImpl.h"

struct MBER_DIGITAL_GOOD_INSTANCE;

struct MBER_DIGITAL_GOOD_INSTANCE_LIST : public MberList<MBER_DIGITAL_GOOD_INSTANCE>
{
public:
	MBER_DIGITAL_GOOD_INSTANCE_LIST() : MberList() {}
	virtual ~MBER_DIGITAL_GOOD_INSTANCE_LIST() {}
};
