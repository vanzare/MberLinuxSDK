#include "gtest/gtest.h"
#include "mber.h"
#include "MberEnv.h"

#include <string>
#include <sstream>

namespace
{
	const char* const mber_root_application = "'Mber";

	std::string getJsonValue(const std::string& json, const std::string& key)
	{
		if (json.empty() || key.empty()) {
			return "";
		}
		const std::string queryString = "\"" + key + "\":\"";
		size_t searchStart = json.find(queryString);
		if (searchStart == std::string::npos) {
			return "";
		}
		searchStart += queryString.length();
		size_t searchEnd = json.find("\"", searchStart);
		if (searchEnd == std::string::npos) {
			return "";
		}
		searchEnd -= searchStart;
		return json.substr(searchStart, searchEnd);
	}

	class JsonAPITestProduction : public testing::Test
	{
	public:
		JsonAPITestProduction() :
			testing::Test(),
			mAccessToken(),
			mProfileId(),
			mMber(0)
		{
		}

		virtual void SetUp()
		{
			MberTerm(mMber);
			mMber = MberInit(MberEnv::url());
		}

		virtual void TearDown()
		{
			MberTerm(mMber);
		}

		MBER* mber() const
		{
			return mMber;
		}

		const char* const accessToken() const
		{
			return mAccessToken.c_str();
		}

		const char* const profileId() const
		{
			return mProfileId.c_str();
		}

		std::string txnid() const
		{
			char* id = MberJsonTXNID();
			if (!id) {
				return "";
			}
			std::string txn(id);
			MberJsonFREE(id);
			return txn;
		}

		bool login(const std::string& applicationId)
		{
			clear();
			if (applicationId.empty()) {
				return false;
			}

			std::stringstream json;
			json << "{";
			json << "\"username\":\"" << MberEnv::user() << "\"";
			json << ",\"password\":\"" << MberEnv::password() << "\"";
			json << ",\"client_id\":\"" << applicationId << "\"";
			json << ",\"transactionId\":\"" << txnid() << "\"";
			json << ",\"grant_type\":\"password\"";
			json << "}";

			char* res = MberJsonPOST(mber(), "service/json/oauth/accesstoken", json.str().c_str());
			const std::string response(res);
			MberJsonFREE(res);
			const std::string status = getJsonValue(response, "status");
			if (status != "Success") {
				return false;
			}

			mAccessToken = getJsonValue(response, "access_token");
			mProfileId = getJsonValue(response, "profileId");
			return true;
		}

	private:
		void clear()
		{
			mAccessToken.clear();
			mProfileId.clear();
		}

		std::string mAccessToken;
		std::string mProfileId;
		MBER* mMber;
	};

	class JSONGet
	{
	public:
		JSONGet(MBER* mber, const std::stringstream& url, const std::stringstream& json) :
		  mResult(MberJsonGET(mber, url.str().c_str(), json.str().c_str()))
		{
		}
		~JSONGet()
		{
			MberJsonFREE(mResult);
		}
		const char* const c_str() const
		{
			return mResult;
		}
	private:
		char* mResult;
		JSONGet(const JSONGet&);
		JSONGet& operator=(const JSONGet&);
	};
}

TEST_F(JsonAPITestProduction, GetAccessToken)
{
	std::stringstream json;
	json << "{";
	json << "\"username\":\"" << MberEnv::user() << "\"";
	json << ",\"password\":\"" << MberEnv::password() << "\"";
	json << ",\"client_id\":\"" << MberEnv::application() << "\"";
	json << ",\"transactionId\":\"" << txnid() << "\"";
	json << ",\"grant_type\":\"password\"";
	json << "}";

	char* res = MberJsonPOST(mber(), "service/json/oauth/accesstoken", json.str().c_str());
	const std::string response(res);
	MberJsonFREE(res);
	const std::string status = getJsonValue(response, "status");
	ASSERT_STREQ("Success", status.c_str());
}

TEST_F(JsonAPITestProduction, ReadProfile)
{
	ASSERT_TRUE(login(mber_root_application));

	std::stringstream url;
	url << "service/json/account/profile/";
	url << profileId();

	std::stringstream json;
	json << "{";
	json << "\"access_token\":\"" << accessToken() << "\"";
	json << "}";

	char* res = MberJsonGET(mber(), url.str().c_str(), json.str().c_str());
	const std::string response(res);
	MberJsonFREE(res);
	const std::string status = getJsonValue(response, "status");
	ASSERT_STREQ("Success", status.c_str());
}

TEST_F(JsonAPITestProduction, UpdateDocument)
{
	ASSERT_TRUE(login(MberEnv::application()));

	std::stringstream json;
	json << "{";
	json << "\"access_token\":\"" << accessToken() << "\"";
	json << ",\"data\":\"VGhpcyBpcyB1c2VkIGJ5IHRoZSB0ZXN0cyBmb3IgdGhlIEMrKyBTREsu\"";
	json << ",\"name\":\"CppSDKTest\"";
	json << ",\"alias\":\"CppSDKTest\"";
	json << ",\"transactionId\":\"" << txnid() << "\"";
	json << "}";

	char* res = MberJsonPUT(mber(), "service/json/data/document/'CppSDKTest", json.str().c_str());
	const std::string response(res);
	MberJsonFREE(res);
	const std::string status = getJsonValue(response, "status");
	ASSERT_STREQ("Success", status.c_str());
}

TEST_F(JsonAPITestProduction, BadRequests)
{
	ASSERT_TRUE(login(MberEnv::application()));
	std::stringstream url;
	std::stringstream json;

	// Try to read a profile with an invalid JSON string. This shouldn't explode.
	url.str("");
	url << "service/json/account/profile/" << profileId();
	json.str("");
	json << "{";
	json << "\"access_token:\"" << accessToken() << "\"";
	json << "}";
	JSONGet invalidJson(mber(), url, json);
	ASSERT_STREQ("JSON Exception", invalidJson.c_str());

	// Try to read a profile with an invalid URL. This shouldn't explode.
	url.str("");
	url << "services/json/account/profile/" << profileId();
	json.str("");
	json << "{";
	json << "\"access_token\":\"" << accessToken() << "\"";
	json << "}";
	JSONGet invalidUrl(mber(), url, json);
	ASSERT_NE(-1, std::string(invalidUrl.c_str()).find("HTTP ERROR: 404"));

	// Try to read a profile with an invalid access token. This shouldn't explode.
	url.str("");
	url << "service/json/account/profile/" << profileId();
	json.str("");
	json << "{";
	json << "\"access_token\":\"AAAAAAAAAAAAAAAAAAAAAA\"";
	json << "}";
	JSONGet invalidAccessToken(mber(), url, json);
	ASSERT_STREQ("Profile.Read rejected; Token not found", invalidAccessToken.c_str());
}
