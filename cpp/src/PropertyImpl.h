#pragma once

#include "NonCopyable.h"

#include <string>

struct MBER_PROPERTY : private NonCopyable
{
public:
	MBER_PROPERTY();
	~MBER_PROPERTY();

	const std::string& key() const;
	void key(const std::string& key);

	const std::string& value() const;
	void value(const std::string& value);

private:
	std::string mKey;
	std::string mValue;
};
