#include "gtest/gtest.h"
#include "mber.h"
#include "MberEnv.h"

#include <algorithm>
#include <string>
#include <vector>

namespace
{
	class CommerceTest : public testing::Test
	{
	public:
		CommerceTest() :
			testing::Test(),
			mSession(0)
		{
		}

		virtual void SetUp()
		{
			clear();
			Session_Create(&mSession, MberEnv::url());
			Mber::Status status = Mber::Status_Failed;
			Session_Login(session(), "password", MberEnv::application(), 0, 0, 0, MberEnv::user(), MberEnv::password(), 0, 0, status);
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
};

TEST_F(CommerceTest, DeductFromWallet)
{
	const char* const currencyId = "'Nuyen";
	Mber::Status status;
	double oldAmount = 0;
	double newAmount = 0;

	// Try to credit currency to the wallet.
	const double creditAmount = 1.5;
	status = Mber::Status_Failed;
	ASSERT_TRUE(Commerce_WalletCredit(session(), currencyId, Session_GetProfileId(session()), creditAmount, status)) << "Failed to connect to Mber while crediting currency to the wallet";
	ASSERT_EQ(Mber::Status_Success, status) << "Failed to credit currency to the wallet";

	// Make sure the currency was credited to the wallet.
	oldAmount = -1;
	status = Mber::Status_Failed;
	ASSERT_TRUE(Commerce_WalletBalance(session(), currencyId, Session_GetProfileId(session()), oldAmount, status)) << "Failed to connect to Mber while reading the currency amount from the wallet";
	ASSERT_EQ(Mber::Status_Success, status) << "Failed to read the currency amount from the wallet";
	ASSERT_NE(-1, oldAmount) << "Failed to find any currency in the wallet";
	ASSERT_GE(oldAmount, creditAmount) << "Failed to read correct amount of currency from the wallet";

	// Try to debit the credited currency from the wallet.
	status = Mber::Status_Failed;
	ASSERT_TRUE(Commerce_WalletDebit(session(), currencyId, Session_GetProfileId(session()), creditAmount, "For science!", status)) << "Failed to connect to Mber while debiting currency from the wallet";
	ASSERT_EQ(Mber::Status_Success, status) << "Failed to debit currency from the wallet";

	// Make sure the currency was debited from the wallet.
	newAmount = -1;
	status = Mber::Status_Failed;
	ASSERT_TRUE(Commerce_WalletBalance(session(), currencyId, Session_GetProfileId(session()), newAmount, status)) << "Failed to connect to Mber while reading the currency amount from the wallet";
	ASSERT_EQ(Mber::Status_Success, status) << "Failed to read the currency amount from the wallet";
	ASSERT_NE(-1, newAmount) << "Failed to find any currency in the wallet";
	ASSERT_EQ(oldAmount - creditAmount, newAmount) << "Failed to read correct amount of currency from the wallet";
}
