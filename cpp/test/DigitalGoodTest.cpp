#include "gtest/gtest.h"
#include "mber.h"
#include "MberEnv.h"

namespace
{
	class DigitalGood
	{
	public:
		DigitalGood() :
			mInstance(DigitalGoodInstance_Init())
		{
		}
		~DigitalGood()
		{
			DigitalGoodInstance_Free(mInstance);
		}
		MBER_DIGITAL_GOOD_INSTANCE* const get() const
		{
			return mInstance;
		}
	private:
		MBER_DIGITAL_GOOD_INSTANCE* mInstance;

		DigitalGood(const DigitalGood&);
		DigitalGood& operator=(const DigitalGood&);
	};

	class DigitalGoodList
	{
	public:
		explicit DigitalGoodList(bool freeAll = false) :
			mList(DigitalGoodInstanceList_Init()),
			mFreeAll(freeAll)
		{
		}
		~DigitalGoodList()
		{
			if (mFreeAll) {
				DigitalGoodInstanceList_FreeAll(mList);
			} else {
				DigitalGoodInstanceList_Free(mList);
			}
		}
		MBER_DIGITAL_GOOD_INSTANCE_LIST* const get() const
		{
			return mList;
		}
		MBER_DIGITAL_GOOD_INSTANCE_LIST** addr()
		{
			return &mList;
		}
	private:
		MBER_DIGITAL_GOOD_INSTANCE_LIST* mList;
		const bool mFreeAll;

		DigitalGoodList(const DigitalGoodList&);
		DigitalGoodList& operator=(const DigitalGoodList&);
	};

	class DigitalGoodSession
	{
	public:
		explicit DigitalGoodSession(const std::string& url) :
			mSession(0)
		{
			Session_Create(&mSession, url.c_str());
		}
		~DigitalGoodSession()
		{
			Session_Destroy(mSession);
		}
		Mber::MberSession* get()
		{
			return mSession;
		}
	private:
		Mber::MberSession* mSession;
	};

	class DigitalGoodEntity
	{
	public:
		DigitalGoodEntity() :
			mEntity(EntityPointer_Init())
		{
		}
		~DigitalGoodEntity()
		{
			EntityPointer_Free(mEntity);
		}
		MBER_ENTITY_POINTER* get()
		{
			return mEntity;
		}
	private:
		MBER_ENTITY_POINTER* mEntity;
	};
}

TEST(DigitalGoodTest, Impl)
{
	// Make sure digital goods can be created.
	DigitalGood instance;
	ASSERT_TRUE(instance.get() != NULL) << "Failed to initialize a digital good instance";

	// Make sure instance IDs serialize correctly.
	ASSERT_STREQ("", DigitalGoodInstance_GetId(instance.get())) << "Digital good instance didn't default to an empty ID";
	DigitalGoodInstance_SetId(instance.get(), "'Apple");
	ASSERT_STREQ("'Apple", DigitalGoodInstance_GetId(instance.get())) << "Digital good instance ID wasn't set";

	// Make sure definition IDs serialize correctly.
	ASSERT_STREQ("", DigitalGoodInstance_GetDefinitionId(instance.get())) << "Digital good instance didn't default to an empty definition ID";
	DigitalGoodInstance_SetDefinitionId(instance.get(), "'Fruit");
	ASSERT_STREQ("'Fruit", DigitalGoodInstance_GetDefinitionId(instance.get())) << "Digital good instance definition ID wasn't set";

	// Make sure states serialize correctly.
	ASSERT_STREQ("", DigitalGoodInstance_GetState(instance.get())) << "Digital good instance didn't default to an empty state";
	DigitalGoodInstance_SetState(instance.get(), "Granted");
	ASSERT_STREQ("Granted", DigitalGoodInstance_GetState(instance.get())) << "Digital good instance state wasn't set";

	// Make sure document IDs serialize correctly.
	ASSERT_STREQ("", DigitalGoodInstance_GetDocumentId(instance.get())) << "Digital good instance didn't default to an empty document ID";
	DigitalGoodInstance_SetDocumentId(instance.get(), "'ApplePieRecipe");
	ASSERT_STREQ("'ApplePieRecipe", DigitalGoodInstance_GetDocumentId(instance.get())) << "Digital good instance document ID wasn't set";

	// Make sure names serialize correctly.
	ASSERT_STREQ("", DigitalGoodInstance_GetName(instance.get())) << "Digital good instance didn't default to an empty name";
	DigitalGoodInstance_SetName(instance.get(), "ApplePie");
	ASSERT_STREQ("ApplePie", DigitalGoodInstance_GetName(instance.get())) << "Digital good instance name wasn't set";

	// Make sure scopes serialize correctly.
	ASSERT_STREQ("", DigitalGoodInstance_GetScope(instance.get())) << "Digital good instance didn't default to an empty scope";
	DigitalGoodInstance_SetScope(instance.get(), "'Recipes");
	ASSERT_STREQ("'Recipes", DigitalGoodInstance_GetScope(instance.get())) << "Digital good instance scope wasn't set";

	// Make sure properties serialize correctly.
	MBER_PROPERTY_LIST* properties = PropertyList_Init();
	MBER_PROPERTY* apple = Property_Init();
	Property_SetKey(apple, "type");
	Property_SetValue(apple, "Pink Lady");
	PropertyList_Push(properties, apple);
	ASSERT_TRUE(DigitalGoodInstance_GetProperties(instance.get()) == NULL) << "Digital good instance didn't default to NULL properties";
	DigitalGoodInstance_SetProperties(instance.get(), properties);
	ASSERT_EQ(properties, DigitalGoodInstance_GetProperties(instance.get())) << "Digital good instance properties weren't set.";
}

TEST(DigitalGoodTest, List)
{
	DigitalGoodList list;
	ASSERT_TRUE(list.get() != NULL) << "Failed to initialize a digital good instance list";

	DigitalGood apple;
	DigitalGoodInstance_SetId(apple.get(), "'Apple");

	DigitalGood pear;
	DigitalGoodInstance_SetId(pear.get(), "'Pear");

	MBER_DIGITAL_GOOD_INSTANCE* instance = NULL;

	// Make sure the default list is empty and you only get NULL digital goods out of it.
	ASSERT_EQ(0, DigitalGoodInstanceList_Length(list.get())) << "Digital good list wasn't empty by default";
	instance = DigitalGoodInstanceList_At(list.get(), 0);
	ASSERT_EQ(NULL, instance) << "Digital good list had an entity at index 0";
	instance = DigitalGoodInstanceList_At(list.get(), 1);
	ASSERT_EQ(NULL, instance) << "Digital good list had an entity at index 1";

	// Add the apple and pear to the list.
	DigitalGoodInstanceList_Push(list.get(), apple.get());
	ASSERT_EQ(1, DigitalGoodInstanceList_Length(list.get())) << "Apple wasn't added to list";
	DigitalGoodInstanceList_Push(list.get(), pear.get());
	ASSERT_EQ(2, DigitalGoodInstanceList_Length(list.get())) << "Pear wasn't added to list";

	// Read the pear back and make sure it's valid.
	instance = DigitalGoodInstanceList_At(list.get(), 1);
	ASSERT_STREQ(DigitalGoodInstance_GetId(pear.get()), DigitalGoodInstance_GetId(instance)) << "Pear ID didn't serialize correctly";

	// Pop the pear off the list and make sure the size drops.
	DigitalGoodInstanceList_Pop(list.get());
	ASSERT_EQ(1, DigitalGoodInstanceList_Length(list.get())) << "Digital good list didn't pop pear";

	// Read the apple back and make sure it's valid.
	instance = DigitalGoodInstanceList_At(list.get(), 0);
	ASSERT_STREQ(DigitalGoodInstance_GetId(apple.get()), DigitalGoodInstance_GetId(instance)) << "Apple ID didn't serialize correctly";

	// Pop the pear off the list and make sure the size drops.
	DigitalGoodInstanceList_Pop(list.get());
	ASSERT_EQ(0, DigitalGoodInstanceList_Length(list.get())) << "Digital good list didn't pop apple";
}

TEST(DigitalGoodInstanceTest, List)
{
	const char* const definition_id = "NuiTj15jRiaP5pjHbBl6qA";
	Mber::Status status = Mber::Status_Failed;

	// Set up a session for testing.
	DigitalGoodSession session(MberEnv::url());
	ASSERT_TRUE(Session_Login(session.get(), "password", MberEnv::application(), 0, 0, 0, MberEnv::user(), MberEnv::password(), 0, 0, status)) << "Failed to log in with password";
	ASSERT_EQ(Mber::Status_Success, status) << "Unexpected status logging in with password";

	// Set up an entity pointer for the user.
	DigitalGoodEntity entity;
	EntityPointer_SetId(entity.get(), Session_GetProfileId(session.get()));
	EntityPointer_SetType(entity.get(), "Profile");

	{
		DigitalGoodList goods(true);

		// Get the unfiltered list of digital goods the user has.
		status = Mber::Status_Failed;
		ASSERT_TRUE(DigitalGoodInstance_List(session.get(), entity.get(), 0, 0, goods.addr(), status)) << "Failed to get the unfiltered list of digital goods";
		ASSERT_EQ(Mber::Status_Success, status) << "Unexpected status getting the unfiltered list of digital goods";
		ASSERT_EQ(DigitalGoodInstanceList_Length(goods.get()), (unsigned)4) << "Didn't get the right number of unfiltered digital goods";
	}
	{
		DigitalGoodList goods(true);

		// Get the filtered list of digital goods the user has.
		status = Mber::Status_Failed;
		ASSERT_TRUE(DigitalGoodInstance_List(session.get(), entity.get(), &definition_id, 1, goods.addr(), status)) << "Failed to get the filtered list of digital goods";
		ASSERT_EQ(Mber::Status_Success, status) << "Unexpected status getting the filtered list of digital goods";
		const unsigned int length = DigitalGoodInstanceList_Length(goods.get());
		ASSERT_EQ(length, (unsigned)2) << "Didn't get the right number of filtered digital goods";

		// Make sure the digital good's definition ID matches the one provided.
		for (unsigned int i = 0; i < length; ++i) {
			MBER_DIGITAL_GOOD_INSTANCE* instance = DigitalGoodInstanceList_At(goods.get(), i);
			ASSERT_STREQ(definition_id, DigitalGoodInstance_GetDefinitionId(instance)) << "Filtered digital good didn't have the right definition ID";
		}
	}
}
