#include "gtest/gtest.h"
#include "mber.h"
#include "MberEnv.h"

#include <algorithm>
#include <vector>

namespace
{

	class SessionTest : public testing::Test
	{
	public:
		virtual const char* const getSessionURL() const = 0;

		SessionTest() :
			testing::Test(),
			mSession(0)
		{
		}

		virtual void SetUp()
		{
			clear();
			Session_Create(&mSession, getSessionURL());
		}

		virtual void TearDown()
		{
			clear();
		}

		Mber::MberSession* session() const
		{
			return mSession;
		}

	private:
		void clear()
		{
			Session_Destroy(mSession);
			mSession = 0;
		}

		Mber::MberSession* mSession;
	};

	class SessionTestProduction : public SessionTest
	{
	public:
		virtual const char* const getSessionURL() const
		{
			return MberEnv::url();
		}
	};

	class SessionTestInvalidURL : public SessionTest
	{
		virtual const char* const getSessionURL() const
		{
			return "http://this.is.not.an.mber.url";
		}
	};

	class TempSession
	{
	public:
		explicit TempSession(const std::string& url) :
			mSession(0)
		{
			Session_Create(&mSession, url.c_str());
		}
		~TempSession()
		{
			Session_Destroy(mSession);
			mSession = 0;
		}
		Mber::MberSession* get()
		{
			return mSession;
		}
	private:
		Mber::MberSession* mSession;
	};
}

TEST_F(SessionTestProduction, LoginWithPasswaord)
{
	ASSERT_FALSE(Session_GetOwnedEntities(session())) << "Session shouldn't have owned enties before login";

	Mber::Status status = Mber::Status_Failed;
	ASSERT_FALSE(Session_Login(session(), "password", "", 0, 0, 0, MberEnv::user(), MberEnv::password(), 0, 0, status)) << "Able to log in with an invalid application ID";
	ASSERT_TRUE(Session_Login(session(), "password", MberEnv::application(), 0, 0, 0, MberEnv::user(), MberEnv::password(), 0, 0, status)) << "Unable to login with password";
	ASSERT_EQ(Mber::Status_Success, status) << "Failed to log in with a password";
	ASSERT_STRNE("", Session_GetToken(session())) << "Access token not set after login";
	ASSERT_STRNE("", Session_GetProfileId(session())) << "Profile ID not set after login";
	ASSERT_STRNE("", Session_GetRefreshToken(session())) << "Refresh token not set after login";
	ASSERT_STREQ("", Session_GetLastError(session())) << "Last error not set after login";
	ASSERT_STRNE("", Session_GetDisplayName(session())) << "Display name not set after login";
	ASSERT_FALSE(Session_GetOwnedEntities(session())) << "Session shouldn't have owned enties after login";
}

TEST_F(SessionTestProduction, LoginWithAuthorizationCode)
{
	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Session_Login(session(), "password", MberEnv::application(), 0, 0, 0, MberEnv::user(), MberEnv::password(), 0, 0, status)) << "Unable to login with password";
	const std::string passwordToken(Session_GetToken(session()));

	// Internally, this is using the refresh token to get an authorization token through the OAuth API.
	std::vector<char> token(23, '?');
	ASSERT_FALSE(Session_GetAuthorizationToken(session(), "", token.data())) << "Able to get an authorization token with an invalid application ID";
	ASSERT_TRUE(Session_GetAuthorizationToken(session(), MberEnv::application(), token.data())) << "Authorization token wasn't granted";
	ASSERT_EQ(token.end(), std::find(token.begin(), token.end(), '?')) << "Invalid authorization token generated";

	// The authorization token can be redeamed for an access token.
	ASSERT_TRUE(Session_Login(session(), "authorization_code", MberEnv::application(), 0, token.data(), 0, 0, 0, 0, 0, status)) << "Unable to login with authorization token";
	const std::string accessToken(Session_GetToken(session()));
	ASSERT_STRNE(passwordToken.c_str(), accessToken.c_str()) << "Access token wasn't reset after login with authorization token";

	// Call an API that's invalid to generate a last error message.
	status = Mber::Status_Success;
	ASSERT_TRUE(Document_Delete(session(), "DNE", status)) << "Deleted a document that doesn't exist";
	ASSERT_EQ(Mber::Status_Failed, status) << "Document delete succeeded unexpectedly";
	ASSERT_STRNE("", Session_GetLastError(session())) << "Document delete didn't set last error message";
}

TEST_F(SessionTestProduction, GetClientToken)
{
	TempSession user_session(getSessionURL());

	std::vector<char> client_token;
	const char* const invalid_entity_id = "pasta";
	const char* const invalid_entity_type = "NOODLES";
	// TODO: This has to be a UUID not an alias, since the ClientToken API expects an EntityPointer.
	// Once we have DigitalGood definition read in place, we'll be able to look up the UUID from an alias.
	const char* const valid_entity_id = "NuiTj15jRiaP5pjHbBl6qA";
	const char* const valid_entity_type = "DigitalGood";
	const int ttl = 5 * 60; // TTLs are measured in seconds.

	// Login as the second user so we can get an access token.
	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Session_Login(user_session.get(), "password", MberEnv::application(), 0, 0, 0, MberEnv::user2(), MberEnv::password2(), 0, 0, status)) << "Unable to login as second user with password";
	const std::string passwordToken(Session_GetToken(user_session.get()));

	// Use the access token we got from login to get an authorization token.
	std::vector<char> authorization_token(23, '?');
	ASSERT_TRUE(Session_GetAuthorizationToken(user_session.get(), MberEnv::application(), authorization_token.data())) << "Authorization token wasn't granted";
	ASSERT_EQ(authorization_token.end(), std::find(authorization_token.begin(), authorization_token.end(), '?')) << "Invalid authorization token generated";

	// Login as the first user so we have an access token.
	status = Mber::Status_Failed;
	ASSERT_TRUE(Session_Login(session(), "password", MberEnv::application(), 0, 0, 0, MberEnv::user(), MberEnv::password(), 0, 0, status)) << "Unable to login as first user with password";
	ASSERT_EQ(Mber::Status_Success, status) << "Unexpected response while logging in as the first user";

	// Fail to redeam the token if a provided entity type's invalid.
	client_token.clear();
	client_token.resize(23, '?');
	status = Mber::Status_Success;
	ASSERT_FALSE(Session_GetClientToken(session(), authorization_token.data(), "game", ttl, &invalid_entity_id, &invalid_entity_type, 1, client_token.data(), (int)client_token.size(), status)) << "Got a client token with an invalid entity type";
	ASSERT_EQ(Mber::Status_Failed, status) << "Unexpected response while getting a client token with an invalid entity type";
	ASSERT_NE(client_token.end(), std::find(client_token.begin(), client_token.end(), '?')) << "Client token accidentally created from an invalid entity type";

	// Fail to redeam the token if the incorrect number of entity IDs are provided.
	client_token.clear();
	client_token.resize(23, '?');
	status = Mber::Status_Success;
	ASSERT_FALSE(Session_GetClientToken(session(), authorization_token.data(), "game", ttl, NULL, &invalid_entity_type, 1, client_token.data(), (int)client_token.size(), status)) << "Got a client token with an invalid entity ID";
	ASSERT_EQ(Mber::Status_Failed, status) << "Unexpected response while getting a client token with an invalid entity ID";
	ASSERT_NE(client_token.end(), std::find(client_token.begin(), client_token.end(), '?')) << "Client token accidentally created from an invalid entity ID";

	// Redeam the authorization token to get a client token.
	client_token.clear();
	client_token.resize(23, '?');
	status = Mber::Status_Failed;
	ASSERT_TRUE(Session_GetClientToken(session(), authorization_token.data(), "game", ttl, 0, 0, 0, client_token.data(), (int)client_token.size(), status)) << "Unable to get a client token";
	ASSERT_EQ(Mber::Status_Success, status) << "Unexpected response while getting a client token";
	ASSERT_EQ(client_token.end(), std::find(client_token.begin(), client_token.end(), '?')) << "Invalid client token generated";

	// Get a second authorization token, since the first one was consumed.
	std::fill(authorization_token.begin(), authorization_token.end(), '?');
	ASSERT_TRUE(Session_GetAuthorizationToken(user_session.get(), MberEnv::application(), authorization_token.data())) << "Second uthorization token wasn't granted";
	ASSERT_EQ(authorization_token.end(), std::find(authorization_token.begin(), authorization_token.end(), '?')) << "Invalid authorization token generated";

	// Assume we have a digital good, and redeam the authorization token to get a client token.
	std::fill(client_token.begin(), client_token.end(), '?');
	status = Mber::Status_Failed;
	ASSERT_TRUE(Session_GetClientToken(session(), authorization_token.data(), "game", ttl, &valid_entity_id, &valid_entity_type, 1, client_token.data(), (int)client_token.size(), status)) << "Unable to get a client token that requires a digital good";
	ASSERT_EQ(Mber::Status_Success, status) << "Unexpected response while getting a client token that requires a digital good";
	ASSERT_EQ(client_token.end(), std::find(client_token.begin(), client_token.end(), '?')) << "Invalid client token generated";
}


TEST_F(SessionTestProduction, LoginWithClientToken)
{
	TempSession client_session(getSessionURL());
	TempSession user_session(getSessionURL());
	ASSERT_EQ(0, Session_GetToken(client_session.get())) << "Invalid token in empty session";
	ASSERT_EQ(0, Session_GetProfileId(client_session.get())) << "Invalid profile ID in empty session";
	ASSERT_EQ(0, Session_GetAccountId(client_session.get())) << "Invalid account ID in empty session";
	ASSERT_EQ(0, Session_GetRefreshToken(client_session.get())) << "Invalid refresh token in empty session";
	ASSERT_STREQ("", Session_GetLastError(client_session.get())) << "Invalid error message in empty session";
	ASSERT_STREQ("", Session_GetDisplayName(client_session.get())) << "Invalid display name in empty session";
	ASSERT_FALSE(Session_GetOwnedEntities(client_session.get())) << "Invalid owned enties in empty session";
	const char* const valid_entity_id = "NuiTj15jRiaP5pjHbBl6qA";
	const char* const valid_entity_type = "DigitalGood";
	const char* const valid_entity_name = "Yen";
	const int ttl = 5 * 60; // TTLs are measured in seconds.

	// Login as the second user so we can get an access token.
	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Session_Login(user_session.get(), "password", MberEnv::application(), 0, 0, 0, MberEnv::user2(), MberEnv::password2(), 0, 0, status)) << "Unable to login as second user with password";
	const std::string passwordToken(Session_GetToken(user_session.get()));

	// Use the access token we got from login to get an authorization token.
	std::vector<char> authorization_token(23, '?');
	ASSERT_TRUE(Session_GetAuthorizationToken(user_session.get(), MberEnv::application(), authorization_token.data())) << "Authorization token wasn't granted";
	ASSERT_EQ(authorization_token.end(), std::find(authorization_token.begin(), authorization_token.end(), '?')) << "Invalid authorization token generated";

	// Login as the first user so we have a valid access token.
	status = Mber::Status_Failed;
	ASSERT_TRUE(Session_Login(session(), "password", MberEnv::application(), 0, 0, 0, MberEnv::user(), MberEnv::password(), 0, 0, status)) << "Unable to login as first user with password";
	ASSERT_EQ(Mber::Status_Success, status) << "Unexpected response while logging in as the first user with a password";

	// Redeam the authorization token to get a new session with a client token.
	status = Mber::Status_Failed;
	ASSERT_TRUE(Session_LoginWithClientToken(session(), client_session.get(), authorization_token.data(), "game", ttl, &valid_entity_id, &valid_entity_type, 1, status)) << "Unable to get a new session with a client token";
	ASSERT_EQ(Mber::Status_Success, status) << "Unexpected response while getting a new session with a client token";
	ASSERT_STRNE("", Session_GetToken(client_session.get())) << "Invalid client token generated in new session";
	ASSERT_STREQ(Session_GetProfileId(user_session.get()), Session_GetProfileId(client_session.get())) << "Invalid profile ID generate in new session";
	ASSERT_STREQ(Session_GetAccountId(user_session.get()), Session_GetAccountId(client_session.get())) << "Invalid account ID generated in new session";
	ASSERT_EQ(0, Session_GetRefreshToken(client_session.get())) << "Refresh token generated in client token session";
	ASSERT_STREQ("", Session_GetLastError(client_session.get())) << "Last error not set in client token session";
	ASSERT_STREQ(Session_GetDisplayName(user_session.get()), Session_GetDisplayName(client_session.get())) << "Display name not set in client token session";

	// Make sure the client session sets the list of owned entities.
	const MBER_ENTITY_POINTER_LIST* const entities = Session_GetOwnedEntities(client_session.get());
	ASSERT_TRUE(entities != NULL) << "Din't get a valid list of owned entities from the client session";
	const unsigned int length = EntityPointerList_Length(entities);
	ASSERT_EQ(1, length) << "Got an empty list of owned entities from the client session";
	const MBER_ENTITY_POINTER* const entity = EntityPointerList_At(entities, 0);
	ASSERT_TRUE(entity != NULL) << "Din't get a valid entity from the client session's owned entities list";
	ASSERT_STREQ(valid_entity_id, EntityPointer_GetId(entity)) << "Client session's owned entity's ID wasn't correct";
	ASSERT_STREQ(valid_entity_type, EntityPointer_GetType(entity)) << "Client session's owned entity's type wasn't correct";
	ASSERT_STREQ(valid_entity_name, EntityPointer_GetName(entity)) << "Client session's owned entity's name wasn't correct";
}

TEST_F(SessionTestProduction, NullProfileUnlessLoggedIn)
{
	ASSERT_EQ(0, Session_GetProfileId(session())) << "Invalid session exploded when getting profile";
}

TEST_F(SessionTestProduction, NullTokenUnlessLoggedIn)
{
	ASSERT_EQ(0, Session_GetToken(session())) << "Invalid session exploded when getting access token";
}

TEST_F(SessionTestProduction, NullRefreshTokenUnlessLoggedIn)
{
	ASSERT_EQ(0, Session_GetRefreshToken(session())) << "Invalid session exploded when getting refresh token";
}

TEST_F(SessionTestInvalidURL, LoginFails)
{
	Mber::Status status = Mber::Status_Success;
	ASSERT_FALSE(Session_Login(session(), "password", MberEnv::application(), 0, 0, 0, MberEnv::user(), MberEnv::password(), 0, 0, status)) << "Logged into a URL that does not exist";
	ASSERT_EQ(Mber::Status_Failed, status) << "Session_Login didn't set status correctly";
	ASSERT_STRNE("", Session_GetLastError(session())) << "Session_Login didn't set last error message";
}
