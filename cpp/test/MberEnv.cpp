#include "MberEnv.h"

#include <cstdlib>
#include <string>

namespace
{
	std::string getEnvOr(const char* const key, const char* const def)
	{
		std::string result(def);
#ifdef _WIN32
		char* value = 0;
		size_t length = 0;
		if (!_dupenv_s(&value, &length, key) && value && length > 0) {
			result = value;
			free(value);
		}
#else
		const char* const value = getenv(key);
		if (value) {
			result = value;
			free((void*)value); // TODO: double-check this force cast
		}
#endif
		return result;
	}
}

static std::string mUrl;
static std::string mApplication;
static std::string mUser;
static std::string mUser2;
static std::string mPassword;
static std::string mPassword2;

const char* const MberEnv::url()
{
	if (mUrl.empty()) {
		mUrl = getEnvOr("MBER_URL", "https://member.firepub.net");
	}
	return mUrl.c_str();
}

const char* const MberEnv::application()
{
	if (mApplication.empty()) {
		mApplication = getEnvOr("MBER_APPLICATION", "'MberCppSDK");
	}
	return mApplication.c_str();
}

const char* const MberEnv::user()
{
	if (mUser.empty()) {
		mUser = getEnvOr("MBER_USER", "MberCppSDK");
	}
	return mUser.c_str();
}

const char* const MberEnv::user2()
{
	if (mUser2.empty()) {
		mUser2 = getEnvOr("MBER_USER2", "MberCppSDK2");
	}
	return mUser2.c_str();
}

const char* const MberEnv::password()
{
	if (mPassword.empty()) {
		mPassword = getEnvOr("MBER_PASSWORD", "");
	}
	return mPassword.c_str();
}

const char* const MberEnv::password2()
{
	if (mPassword2.empty()) {
		mPassword2 = getEnvOr("MBER_PASSWORD2", "");
	}
	return mPassword2.c_str();
}
