#include "mber.h"
#include "DigitalGoodInstanceImpl.h"

MBER_DIGITAL_GOOD_INSTANCE::MBER_DIGITAL_GOOD_INSTANCE() :
	mId(),
	mDefinitionId(),
	mState(),
	mDocumentId(),
	mName(),
	mScope(),
	mProperties(NULL)
{
}

MBER_DIGITAL_GOOD_INSTANCE::~MBER_DIGITAL_GOOD_INSTANCE()
{
	PropertyList_FreeAll(mProperties);
}

const std::string& MBER_DIGITAL_GOOD_INSTANCE::id() const
{
	return mId;
}

void MBER_DIGITAL_GOOD_INSTANCE::id(const std::string& id)
{
	mId = id;
}

const std::string& MBER_DIGITAL_GOOD_INSTANCE::definitionId() const
{
	return mDefinitionId;
}

void MBER_DIGITAL_GOOD_INSTANCE::definitionId(const std::string& id)
{
	mDefinitionId = id;
}

const std::string& MBER_DIGITAL_GOOD_INSTANCE::state() const
{
	return mState;
}

void MBER_DIGITAL_GOOD_INSTANCE::state(const std::string& state)
{
	mState = state;
}

const std::string& MBER_DIGITAL_GOOD_INSTANCE::documentId() const
{
	return mDocumentId;
}

void MBER_DIGITAL_GOOD_INSTANCE::documentId(const std::string& id)
{
	mDocumentId = id;
}

const std::string& MBER_DIGITAL_GOOD_INSTANCE::name() const
{
	return mName;
}

void MBER_DIGITAL_GOOD_INSTANCE::name(const std::string& name)
{
	mName = name;
}

const std::string& MBER_DIGITAL_GOOD_INSTANCE::scope() const
{
	return mScope;
}

void MBER_DIGITAL_GOOD_INSTANCE::scope(const std::string& scope)
{
	mScope = scope;
}

const MBER_PROPERTY_LIST* const MBER_DIGITAL_GOOD_INSTANCE::properties() const
{
	return mProperties;
}

void MBER_DIGITAL_GOOD_INSTANCE::properties(MBER_PROPERTY_LIST* properties)
{
	PropertyList_FreeAll(mProperties);
	mProperties = properties;
}
