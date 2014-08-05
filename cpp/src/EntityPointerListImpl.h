#pragma once

#include "MberListImpl.h"

struct MBER_ENTITY_POINTER;

struct MBER_ENTITY_POINTER_LIST : public MberList<MBER_ENTITY_POINTER>
{
public:
	MBER_ENTITY_POINTER_LIST() {}
	virtual ~MBER_ENTITY_POINTER_LIST() {}
};
