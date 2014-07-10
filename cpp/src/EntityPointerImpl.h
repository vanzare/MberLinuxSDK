#pragma once

#include "NonCopyable.h"

#include <string>

struct MBER_ENTITY_POINTER : private NonCopyable
{
public:
	MBER_ENTITY_POINTER();
	~MBER_ENTITY_POINTER();

	const std::string& id() const;
	void id(const std::string& id);

	const std::string& type() const;
	void type(const std::string& type);

	const std::string& name() const;
	void name(const std::string& name);

private:
	std::string mId;
	std::string mType;
	std::string mName;
};
