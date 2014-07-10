#include "mber.h"
#include "PropertyListImpl.h"

MBER_PROPERTY_LIST* PropertyList_Init()
{
	return new MBER_PROPERTY_LIST();
}

void PropertyList_Free(MBER_PROPERTY_LIST* list)
{
	delete list;
}

void PropertyList_FreeAll(MBER_PROPERTY_LIST* list)
{
	const unsigned int length = PropertyList_Length(list);
	for (unsigned int i = 0; i < length; ++i) {
		MBER_PROPERTY* property = PropertyList_At(list, i);
		Property_Free(property);
	}
	PropertyList_Free(list);
}

unsigned int PropertyList_Length(const MBER_PROPERTY_LIST* const list)
{
	return (list) ? list->length() : 0;
}

MBER_PROPERTY* PropertyList_At(const MBER_PROPERTY_LIST* const list, const unsigned int index)
{
	if (list && list->length() > index) {
		return list->at(index);
	}
	return 0;
}

void PropertyList_Pop(MBER_PROPERTY_LIST* const list)
{
	if (list && list->length() > 0) {
		list->pop();
	}
}

void PropertyList_Push(MBER_PROPERTY_LIST* const list, MBER_PROPERTY* property)
{
	if (list && property) {
		list->push(property);
	}
}
