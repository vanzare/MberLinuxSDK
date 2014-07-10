#pragma once

#include "NonCopyable.h"

#include <string>

struct MBER_PROPERTY_LIST;

struct MBER_DIGITAL_GOOD_INSTANCE : private NonCopyable
{
public:
	MBER_DIGITAL_GOOD_INSTANCE();
	~MBER_DIGITAL_GOOD_INSTANCE();

	const std::string& id() const;
	void id(const std::string& id);

	const std::string& definitionId() const;
	void definitionId(const std::string& id);

	const std::string& state() const;
	void state(const std::string& state);

	const std::string& documentId() const;
	void documentId(const std::string& id);

	const std::string& name() const;
	void name(const std::string& name);

	const std::string& scope() const;
	void scope(const std::string& scope);

	const MBER_PROPERTY_LIST* const properties() const;
	void properties(MBER_PROPERTY_LIST* properties);

private:
	std::string mId;
	std::string mDefinitionId;
	std::string mState;
	std::string mDocumentId;
	std::string mName;
	std::string mScope;
	MBER_PROPERTY_LIST* mProperties;
};
