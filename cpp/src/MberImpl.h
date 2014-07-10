#pragma once

#include <string>

struct MBER
{
public:
	explicit MBER(const char* const uri);
	~MBER();

	std::string uri() const;

private:
	std::string mUri;

	MBER(const MBER&);
	const MBER& operator=(const MBER&);
};