#include "PropertyImpl.h"

MBER_PROPERTY::MBER_PROPERTY() :
	mKey(),
	mValue()
{
}

MBER_PROPERTY::~MBER_PROPERTY()
{
}

const std::string& MBER_PROPERTY::key() const
{
	return mKey;
}

void MBER_PROPERTY::key(const std::string& key)
{
	mKey = key;
}

const std::string& MBER_PROPERTY::value() const
{
	return mValue;
}

void MBER_PROPERTY::value(const std::string& value)
{
	mValue = value;
}
