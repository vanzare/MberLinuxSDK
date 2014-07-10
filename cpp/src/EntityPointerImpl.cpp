#include "EntityPointerImpl.h"

MBER_ENTITY_POINTER::MBER_ENTITY_POINTER() :
	mId(),
	mType(),
	mName()
{
}

MBER_ENTITY_POINTER::~MBER_ENTITY_POINTER()
{
}

const std::string& MBER_ENTITY_POINTER::id() const
{
	return mId;
}

void MBER_ENTITY_POINTER::id(const std::string& id)
{
	mId = id;
}

const std::string& MBER_ENTITY_POINTER::type() const
{
	return mType;
}

void MBER_ENTITY_POINTER::type(const std::string& type)
{
	mType = type;
}

const std::string& MBER_ENTITY_POINTER::name() const
{
	return mName;
}

void MBER_ENTITY_POINTER::name(const std::string& name)
{
	mName = name;
}
