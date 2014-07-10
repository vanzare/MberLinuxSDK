#include "gtest/gtest.h"
#include "mber.h"

namespace
{
	class Property
	{
	public:
		Property() :
			mProperty(Property_Init())
		{
		}
		explicit Property(MBER_PROPERTY* property) :
			mProperty(property)
		{
		}
		~Property()
		{
			Property_Free(mProperty);
		}
		MBER_PROPERTY* const get() const
		{
			return mProperty;
		}
	private:
		MBER_PROPERTY* mProperty;

		Property(const Property&);
		Property& operator=(const Property&);
	};

	class PropertyList
	{
	public:
		PropertyList() :
			mList(PropertyList_Init())
		{
		}
		~PropertyList()
		{
			PropertyList_Free(mList);
		}
		MBER_PROPERTY_LIST* const get() const
		{
			return mList;
		}
	private:
		MBER_PROPERTY_LIST* mList;

		PropertyList(const PropertyList&);
		PropertyList& operator=(const PropertyList&);
	};
}

TEST(PropertyTest, Impl)
{
	Property property;
	ASSERT_TRUE(property.get() != NULL) << "Failed to initialize a property";

	ASSERT_STREQ("", Property_GetKey(property.get())) << "Property didn't default to an empty key";
	Property_SetKey(property.get(), "Rounds");
	ASSERT_STREQ("Rounds", Property_GetKey(property.get())) << "Property key wasn't set";

	ASSERT_STREQ("", Property_GetValue(property.get())) << "Property didn't default to an empty value";
	Property_SetValue(property.get(), "3");
	ASSERT_STREQ("3", Property_GetValue(property.get())) << "Property key wasn't set";
}


TEST(PropertyTest, List)
{
	PropertyList list;
	ASSERT_TRUE(list.get() != NULL) << "Failed to initialize a property list";

	Property roundsProperty;
	Property_SetKey(roundsProperty.get(), "Rounds");
	Property_SetValue(roundsProperty.get(), "7");

	Property gamesProperty;
	Property_SetKey(gamesProperty.get(), "Games");
	Property_SetValue(gamesProperty.get(), "2");

	MBER_PROPERTY* property = NULL;

	// Make sure the default list is empty and you only get NULL properties out of it.
	ASSERT_EQ(0, PropertyList_Length(list.get())) << "Property list was empty by default";
	property = PropertyList_At(list.get(), 0);
	ASSERT_EQ(NULL, property) << "Property list had an entity at index 0";
	property = PropertyList_At(list.get(), 1);
	ASSERT_EQ(NULL, property) << "Property list had an entity at index 1";

	// Add the rounds property and games property to the list.
	PropertyList_Push(list.get(), roundsProperty.get());
	ASSERT_EQ(1, PropertyList_Length(list.get())) << "Rounds property wasn't added to list";
	PropertyList_Push(list.get(), gamesProperty.get());
	ASSERT_EQ(2, PropertyList_Length(list.get())) << "Games property wasn't added to list";

	// Read the games property back and make sure it's valid.
	property = PropertyList_At(list.get(), 1);
	ASSERT_STREQ(Property_GetKey(gamesProperty.get()), Property_GetKey(property)) << "Games property key didn't serialize correctly";
	ASSERT_STREQ(Property_GetValue(gamesProperty.get()), Property_GetValue(property)) << "Games property value didn't serialize correctly";

	// Pop the games property off the list and make sure the size drops.
	PropertyList_Pop(list.get());
	ASSERT_EQ(1, PropertyList_Length(list.get())) << "Property list didn't pop games property";

	// Read the rounds property and make sure it's valid.
	property = PropertyList_At(list.get(), 0);
	ASSERT_STREQ(Property_GetKey(roundsProperty.get()), Property_GetKey(property)) << "Rounds property key didn't serialize correctly";
	ASSERT_STREQ(Property_GetValue(roundsProperty.get()), Property_GetValue(property)) << "Rounds property value didn't serialize correctly";
	
	// Pop the rounds property off the list and make sure the size drops.
	PropertyList_Pop(list.get());
	ASSERT_EQ(0, PropertyList_Length(list.get())) << "Property list didn't pop rounds property";
}
