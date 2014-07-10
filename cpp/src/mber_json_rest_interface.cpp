#include "mber.h"
#include "MberImpl.h"
#include "PocoSessionWrapper.h"

#include "Poco/JSON/DefaultHandler.h"
#include "Poco/JSON/JSONException.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/StreamCopier.h"
#include "Poco/URI.h"

namespace
{
	const std::string kUriReserved = "!#$&'()*+,/:;=?@[]";

	Poco::JSON::Object::Ptr toJSONObject(const std::string& json)
	{
		if (json.empty()) {
			return Poco::JSON::Object::Ptr();
		}

		Poco::JSON::Parser parser;
		Poco::JSON::DefaultHandler handler;
		parser.setHandler(&handler);
		parser.parse(json);
		
		const Poco::Dynamic::Var result = handler.result();
		return result.extract<Poco::JSON::Object::Ptr>();
	}

	Poco::JSON::Object::Ptr toJSONObject(const char* const json)
	{
		if (!json) {
			return Poco::JSON::Object::Ptr();
		}
		return toJSONObject(std::string(json));
	}

	std::string toQueryString(const std::string& key, const std::string& value)
	{
		std::string result;
		Poco::URI::encode(key, kUriReserved, result);
		result += "=";
		Poco::URI::encode(value, kUriReserved, result);
		return result;
	}

	void appendQueryString(const std::string& key, const std::string& value, std::string& result)
	{
		if (key.empty() || value.empty()) {
			return;
		}
		if (!result.empty()) {
			result += "&";
		}
		result += toQueryString(key, value);
	}

	void appendQueryString(const std::string& key, const int value, std::string& result)
	{
		std::ostringstream output;
		output << value;
		appendQueryString(key, output.str(), result);
	}

	void appendQueryString(const std::string& key, const double value, std::string& result)
	{
		std::ostringstream output;
		output << value;
		appendQueryString(key, output.str(), result);
	}

	void appendQueryString(const std::string& key, const Poco::Dynamic::Var& value, std::string& result)
	{
		if (key.empty() || value.isEmpty()) {
			return;
		}
		else if (value.isInteger()) {
			appendQueryString(key, value.convert<int>(), result);
		}
		else if (value.isNumeric()) {
			appendQueryString(key, value.convert<double>(), result);
		}
		else if (value.isString()) {
			appendQueryString(key, value.convert<std::string>(), result);
		}
	}

	void appendQueryString(const std::string& key, const Poco::JSON::Array::Ptr& values, std::string& result)
	{
		if (key.empty() || values.isNull()) {
			return;
		}
		for (std::vector<Poco::Dynamic::Var>::const_iterator itr = values->begin(); itr != values->end(); ++itr) {
			appendQueryString(key, *itr, result);
		}
	}

	std::string toQueryString(const Poco::JSON::Object::Ptr& json)
	{
		if (json.isNull()) {
			return "";
		}

		std::vector<std::string> keys;
		json->getNames(keys);

		std::string query;
		for (std::vector<std::string>::const_iterator itr = keys.begin(); itr != keys.end(); ++itr) {
			const std::string key = *itr;
			if (json->isObject(key)) {
				continue;
			}
			if (json->isArray(key)) {
				appendQueryString(key, json->getArray(key), query);
				continue;
			}
			const Poco::Dynamic::Var value = json->get(key);
			appendQueryString(key, value, query);
		}
		return query;
	}

	char* jsonAlloc(const std::string& json)
	{
		try {
			if (json.empty()) {
				return 0;
			}
			// +1 to account for the trailing '\0' character.
			const size_t length = json.length() + 1;
			char* result = (char*)malloc(sizeof(char) * length);
			if (!result) {
				return 0;
			}
			if (!memcpy(result, json.c_str(), length)) {
				return 0;
			}
			return result;
		} catch (...) {
			return 0;
		}
	}

	char* handlePocoResponse(Poco::Net::HTTPClientSession* const session)
	{
		Poco::Net::HTTPResponse response;
		std::istream& output = session->receiveResponse(response);
		std::ostringstream payload;
		Poco::StreamCopier::copyStream(output, payload);
		return jsonAlloc(payload.str());
	}
	
	char* handlePocoRequest(const std::string& type, const MBER* const mber, const char* const endpoint, const char* const request)
	{
		try {
			if (type.empty() || !mber || !endpoint || !request) {
				return 0;
			}

			Poco::URI uri(mber->uri());
			if (uri.empty()) {
				return 0;
			}

			const std::string path(endpoint);
			if (path.empty()) {
				return 0;
			}
			uri.setPath(path);

			if (type == Poco::Net::HTTPRequest::HTTP_GET) {
				Poco::JSON::Object::Ptr requestJson = toJSONObject(request);
				if (requestJson.isNull()) {
					return 0;
				}
				uri.setQuery(toQueryString(requestJson));
			}
		
			PocoSessionWrapper pocoSession(uri);
			if (!pocoSession) {
				return 0;
			}

			Poco::Net::HTTPRequest pocoRequest(type, uri.toString());
			pocoRequest.set("REST-API-Version", MBER_VERSION);
			const std::string requestJson = (type != Poco::Net::HTTPRequest::HTTP_GET) ? request : "";
			if (!requestJson.empty()) {
				pocoRequest.setContentLength64(requestJson.length());
				pocoRequest.setContentType("application/json");
				pocoSession->sendRequest(pocoRequest) << requestJson;
			}
			else {
				pocoSession->sendRequest(pocoRequest);
			}

			return handlePocoResponse(*pocoSession);
		}
		catch (const Poco::JSON::JSONException& e) {
			return jsonAlloc(e.what());
		}
		catch (const Poco::Exception& e) {
			return jsonAlloc(e.what());
		}
		catch (const std::exception& e) {
			return jsonAlloc(e.what());
		}
	}
}

char* MberJsonGET(const MBER* const mber, const char* const endpoint, const char* const request)
{
	return handlePocoRequest(Poco::Net::HTTPRequest::HTTP_GET, mber, endpoint, request);
}

char* MberJsonPUT(const MBER* const mber, const char* const endpoint, const char* const request)
{
	return handlePocoRequest(Poco::Net::HTTPRequest::HTTP_PUT, mber, endpoint, request);
}

char* MberJsonPOST(const MBER* const mber, const char* const endpoint, const char* const request)
{
	return handlePocoRequest(Poco::Net::HTTPRequest::HTTP_POST, mber, endpoint, request);
}

char* MberJsonDELETE(const MBER* const mber, const char* const endpoint, const char* const request)
{
	return handlePocoRequest(Poco::Net::HTTPRequest::HTTP_DELETE, mber, endpoint, request);
}

char* MberJsonTXNID()
{
	try {
		return jsonAlloc(Mber::generateTransactionId());
	} catch (...) {
		return 0;
	}
}

void MberJsonFREE(char* response)
{
	free(response);
	response = NULL;
}
