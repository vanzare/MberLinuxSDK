#include "gtest/gtest.h"
#include "mber.h"
#include "MberEnv.h"

namespace
{
	class MberEnvironment : public testing::Environment
	{
	public:
		virtual void SetUp()
		{
			MberStartup();
		}

		virtual void TearDown()
		{
			MberShutdown();
		}
	};
}

GTEST_API_ int main(int argc, char** argv)
{
  std::cout << "MBER_URL: " << MberEnv::url() << std::endl;
  std::cout << "MBER_APPLICATION: " << MberEnv::application() << std::endl;
  std::cout << "MBER_USER: " << MberEnv::user() << std::endl;
  std::cout << "MBER_USER2: " << MberEnv::user2() << std::endl;
  std::cout << std::endl;

  testing::InitGoogleTest(&argc, argv);
  testing::AddGlobalTestEnvironment(new MberEnvironment());
  return RUN_ALL_TESTS();
}
