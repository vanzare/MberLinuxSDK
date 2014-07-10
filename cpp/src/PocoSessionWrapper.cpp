#include "PocoSessionWrapper.h"

#include "Poco/Net/HTTPSessionFactory.h"

PocoSessionWrapper::PocoSessionWrapper(const Poco::URI& uri) :
	mClientSession(Poco::Net::HTTPSessionFactory::defaultFactory().createClientSession(uri))
{
}

PocoSessionWrapper::~PocoSessionWrapper()
{
	if (mClientSession) {
		delete mClientSession;
		mClientSession = 0;
	}
}

bool PocoSessionWrapper::operator!() const
{
	return mClientSession == 0;
}

Poco::Net::HTTPClientSession* const PocoSessionWrapper::operator->()
{
	return mClientSession;
}

Poco::Net::HTTPClientSession* const PocoSessionWrapper::operator*()
{
	return mClientSession;
}
