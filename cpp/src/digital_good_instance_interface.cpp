#include "mber.h"
#include "DigitalGoodInstanceImpl.h"

MBER_DIGITAL_GOOD_INSTANCE* DigitalGoodInstance_Init()
{
	return new MBER_DIGITAL_GOOD_INSTANCE();
}

void DigitalGoodInstance_Free(MBER_DIGITAL_GOOD_INSTANCE* instance)
{
	delete instance;
}

void DigitalGoodInstance_SetId(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const id)
{
	if (instance && id) {
		instance->id(id);
	}
}

void DigitalGoodInstance_SetDefinitionId(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const id)
{
	if (instance && id) {
		instance->definitionId(id);
	}
}

void DigitalGoodInstance_SetState(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const state)
{
	if (instance && state) {
		instance->state(state);
	}
}

void DigitalGoodInstance_SetDocumentId(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const id)
{
	if (instance && id) {
		instance->documentId(id);
	}
}

void DigitalGoodInstance_SetName(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const name)
{
	if (instance && name) {
		instance->name(name);
	}
}

void DigitalGoodInstance_SetScope(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const scope)
{
	if (instance && scope) {
		instance->scope(scope);
	}
}

void DigitalGoodInstance_SetProperties(MBER_DIGITAL_GOOD_INSTANCE* const instance, MBER_PROPERTY_LIST* properties)
{
	if (instance && properties) {
		instance->properties(properties);
	}
}

const char* const DigitalGoodInstance_GetId(const MBER_DIGITAL_GOOD_INSTANCE* const instance)
{
	return (instance) ? instance->id().c_str() : 0;
}

const char* const DigitalGoodInstance_GetDefinitionId(const MBER_DIGITAL_GOOD_INSTANCE* const instance)
{
	return (instance) ? instance->definitionId().c_str() : 0;
}

const char* const DigitalGoodInstance_GetState(const MBER_DIGITAL_GOOD_INSTANCE* const instance)
{
	return (instance) ? instance->state().c_str() : 0;
}

const char* const DigitalGoodInstance_GetDocumentId(const MBER_DIGITAL_GOOD_INSTANCE* const instance)
{
	return (instance) ? instance->documentId().c_str() : 0;
}

const char* const DigitalGoodInstance_GetName(const MBER_DIGITAL_GOOD_INSTANCE* const instance)
{
	return (instance) ? instance->name().c_str() : 0;
}

const char* const DigitalGoodInstance_GetScope(const MBER_DIGITAL_GOOD_INSTANCE* const instance)
{
	return (instance) ? instance->scope().c_str() : 0;
}

const MBER_PROPERTY_LIST* const DigitalGoodInstance_GetProperties(const MBER_DIGITAL_GOOD_INSTANCE* const instance)
{
	return (instance) ? instance->properties() : 0;
}
