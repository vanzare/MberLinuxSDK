#include "MberImpl.h"

MBER::MBER(const char* const uri) :
	mUri(uri)
{
}

MBER::~MBER()
{
}

std::string MBER::uri() const
{
	return mUri;
}