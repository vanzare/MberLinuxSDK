#pragma once

#include "Poco/Net/HTTPClientSession.h"
#include "Poco/URI.h"

class PocoSessionWrapper
{
public:
	explicit PocoSessionWrapper(const Poco::URI& uri);
	~PocoSessionWrapper();

	bool operator!() const;
	Poco::Net::HTTPClientSession* const operator->();
	Poco::Net::HTTPClientSession* const operator*();
private:
	Poco::Net::HTTPClientSession* mClientSession;
	PocoSessionWrapper(const PocoSessionWrapper&);
	PocoSessionWrapper& operator=(const PocoSessionWrapper&);
};
