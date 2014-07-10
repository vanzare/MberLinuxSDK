#include "mber.h"
#include "PropertyImpl.h"

MBER_PROPERTY* Property_Init()
{
	return new MBER_PROPERTY();
}

void Property_Free(MBER_PROPERTY* property)
{
	delete property;
}

void Property_SetKey(MBER_PROPERTY* const property, const char* const key)
{
	if (property && key) {
		property->key(key);
	}
}

void Property_SetValue(MBER_PROPERTY* const property, const char* const value)
{
	if (property && value) {
		property->value(value);
	}
}

const char* const Property_GetKey(const MBER_PROPERTY* const property)
{
	return (property) ? property->key().c_str() : 0;
}

const char* const Property_GetValue(const MBER_PROPERTY* const property)
{
	return (property) ? property->value().c_str() : 0;
}
