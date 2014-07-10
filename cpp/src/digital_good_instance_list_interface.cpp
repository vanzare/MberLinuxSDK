#include "mber.h"
#include "DigitalGoodInstanceListImpl.h"

MBER_DIGITAL_GOOD_INSTANCE_LIST* DigitalGoodInstanceList_Init()
{
	return new MBER_DIGITAL_GOOD_INSTANCE_LIST();
}

void DigitalGoodInstanceList_Free(MBER_DIGITAL_GOOD_INSTANCE_LIST* list)
{
	delete list;
}

void DigitalGoodInstanceList_FreeAll(MBER_DIGITAL_GOOD_INSTANCE_LIST* list)
{
	const unsigned int length = DigitalGoodInstanceList_Length(list);
	for (unsigned int i = 0; i < length; ++i) {
		MBER_DIGITAL_GOOD_INSTANCE* instance = DigitalGoodInstanceList_At(list, i);
		DigitalGoodInstance_Free(instance);
	}
	DigitalGoodInstanceList_Free(list);
}

unsigned int DigitalGoodInstanceList_Length(const MBER_DIGITAL_GOOD_INSTANCE_LIST* const list)
{
	return (list) ? list->length() : 0;
}

void DigitalGoodInstanceList_Pop(MBER_DIGITAL_GOOD_INSTANCE_LIST* const list)
{
	if (list) {
		list->pop();
	}
}

void DigitalGoodInstanceList_Push(MBER_DIGITAL_GOOD_INSTANCE_LIST* const list, MBER_DIGITAL_GOOD_INSTANCE* instance)
{
	if (list && instance) {
		list->push(instance);
	}
}

MBER_DIGITAL_GOOD_INSTANCE* DigitalGoodInstanceList_At(const MBER_DIGITAL_GOOD_INSTANCE_LIST* const list, const unsigned int index)
{
	return (list && index < list->length()) ? list->at(index) : 0;
}
