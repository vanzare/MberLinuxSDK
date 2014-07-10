#include "mber.h"
#include "EntityPointerImpl.h"

MBER_ENTITY_POINTER* EntityPointer_Init()
{
	return new MBER_ENTITY_POINTER();
}

void EntityPointer_Free(MBER_ENTITY_POINTER* entity)
{
	delete entity;
}

void EntityPointer_SetId(MBER_ENTITY_POINTER* const entity, const char* const id)
{
	if (entity && id) {
		entity->id(id);
	}
}

void EntityPointer_SetType(MBER_ENTITY_POINTER* const entity, const char* const type)
{
	if (entity && type) {
		entity->type(type);
	}
}

void EntityPointer_SetName(MBER_ENTITY_POINTER* const entity, const char* const name)
{
	if (entity && name) {
		entity->name(name);
	}
}

const char* const EntityPointer_GetId(const MBER_ENTITY_POINTER* const entity)
{
	return (entity) ? entity->id().c_str() : 0;
}

const char* const EntityPointer_GetType(const MBER_ENTITY_POINTER* const entity)
{
	return (entity) ? entity->type().c_str() : 0;
}

const char* const EntityPointer_GetName(const MBER_ENTITY_POINTER* const entity)
{
	return (entity) ? entity->name().c_str() : 0;
}
