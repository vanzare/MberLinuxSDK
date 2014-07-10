#include "mber.h"
#include "EntityPointerListImpl.h"

MBER_ENTITY_POINTER_LIST* EntityPointerList_Init()
{
	return new MBER_ENTITY_POINTER_LIST();
}

void EntityPointerList_Free(MBER_ENTITY_POINTER_LIST* list)
{
	delete list;
}

void EntityPointerList_FreeAll(MBER_ENTITY_POINTER_LIST* list)
{
	const unsigned int length = EntityPointerList_Length(list);
	for (unsigned int i = 0; i < length; ++i) {
		MBER_ENTITY_POINTER* entity = EntityPointerList_At(list, i);
		EntityPointer_Free(entity);
	}
	EntityPointerList_Free(list);
}

unsigned int EntityPointerList_Length(const MBER_ENTITY_POINTER_LIST* const list)
{
	return (list) ? list->length() : 0;
}

MBER_ENTITY_POINTER* EntityPointerList_At(const MBER_ENTITY_POINTER_LIST* const list, const unsigned int index)
{
	if (list && list->length() > index) {
		return list->at(index);
	}
	return 0;
}

void EntityPointerList_Pop(MBER_ENTITY_POINTER_LIST* const list)
{
	if (list && list->length() > 0) {
		list->pop();
	}
}

void EntityPointerList_Push(MBER_ENTITY_POINTER_LIST* const list, MBER_ENTITY_POINTER* entity)
{
	if (list && entity) {
		list->push(entity);
	}
}
