#include "gtest/gtest.h"
#include "mber.h"

namespace
{
	class EntityPointer
	{
	public:
		EntityPointer() :
			mEntity(EntityPointer_Init())
		{
		}
		explicit EntityPointer(MBER_ENTITY_POINTER* entity) :
			mEntity(entity)
		{
		}
		~EntityPointer()
		{
			EntityPointer_Free(mEntity);
		}
		MBER_ENTITY_POINTER* const get() const
		{
			return mEntity;
		}
	private:
		MBER_ENTITY_POINTER* mEntity;

		EntityPointer(const EntityPointer&);
		const EntityPointer operator=(const EntityPointer&);
	};

	class EntityPointerList
	{
	public:
		EntityPointerList() :
			mList(EntityPointerList_Init())
		{
		}
		~EntityPointerList()
		{
			EntityPointerList_Free(mList);
		}
		MBER_ENTITY_POINTER_LIST* const get() const
		{
			return mList;
		}
	private:
		MBER_ENTITY_POINTER_LIST* mList;

		EntityPointerList(const EntityPointerList&);
		const EntityPointerList operator=(const EntityPointerList&);
	};
}

TEST(EntityPointerTest, Impl)
{
	EntityPointer pointer;
	ASSERT_TRUE(pointer.get() != NULL) << "Failed to initialize an entity pointer";

	ASSERT_STREQ("", EntityPointer_GetId(pointer.get())) << "Entity pointer didn't default to an empty ID";
	EntityPointer_SetId(pointer.get(), "'MberCppSDK");
	ASSERT_STREQ("'MberCppSDK", EntityPointer_GetId(pointer.get())) << "Entity pointer ID wasn't set";

	ASSERT_STREQ("", EntityPointer_GetType(pointer.get())) << "Entity pointer didn't default to an empty type";
	EntityPointer_SetId(pointer.get(), "Application");
	ASSERT_STREQ("Application", EntityPointer_GetId(pointer.get())) << "Entity pointer type wasn't set";

	ASSERT_STREQ("", EntityPointer_GetName(pointer.get())) << "Entity pointer didn't default to an empty name";
	EntityPointer_SetName(pointer.get(), "MberCppSDK");
	ASSERT_STREQ("MberCppSDK", EntityPointer_GetName(pointer.get())) << "Entity pointer name wasn't set";
}

TEST(EntityPointerTest, List)
{
	EntityPointerList list;
	ASSERT_TRUE(list.get() != NULL) << "Failed to initialize an entity pointer list";

	EntityPointer appEntity;
	EntityPointer_SetId(appEntity.get(), "'MberCppSDK");
	EntityPointer_SetType(appEntity.get(), "Application");
	EntityPointer_SetName(appEntity.get(), "MberCppSDK");

	EntityPointer profileEntity;
	EntityPointer_SetId(profileEntity.get(), "'MberCppSDK2");
	EntityPointer_SetType(profileEntity.get(), "Profile");
	EntityPointer_SetName(profileEntity.get(), "MberCppSDK2");

	MBER_ENTITY_POINTER* pointer = NULL;

	// Make sure the default list is empty and you only get NULL entites out of it.
	ASSERT_EQ(0, EntityPointerList_Length(list.get())) << "Entity pointer list was empty by default";
	pointer = EntityPointerList_At(list.get(), 0);
	ASSERT_EQ(NULL, pointer) << "Entity pointer list had an entity at index 0";
	pointer = EntityPointerList_At(list.get(), 1);
	ASSERT_EQ(NULL, pointer) << "Entity pointer list had an entity at index 1";

	// Add the app entity and profile entity to the list.
	EntityPointerList_Push(list.get(), appEntity.get());
	ASSERT_EQ(1, EntityPointerList_Length(list.get())) << "Application entity pointer wasn't added to list";
	EntityPointerList_Push(list.get(), profileEntity.get());
	ASSERT_EQ(2, EntityPointerList_Length(list.get())) << "Profile entity pointer was added to list";

	// Read the app entity back and make sure it's valid.
	pointer = EntityPointerList_At(list.get(), 0);
	ASSERT_STREQ(EntityPointer_GetId(appEntity.get()), EntityPointer_GetId(pointer)) << "Application entity pointer ID didn't serialize correctly";
	ASSERT_STREQ(EntityPointer_GetType(appEntity.get()), EntityPointer_GetType(pointer)) << "Application entity pointer type didn't serialize correctly";
	ASSERT_STREQ(EntityPointer_GetName(appEntity.get()), EntityPointer_GetName(pointer)) << "Application entity pointer name didn't serialize correctly";

	// Read the profile entity back and make sure it's valid.
	pointer = EntityPointerList_At(list.get(), 1);
	ASSERT_STREQ(EntityPointer_GetId(profileEntity.get()), EntityPointer_GetId(pointer)) << "Profile entity pointer ID didn't serialize correctly";
	ASSERT_STREQ(EntityPointer_GetType(profileEntity.get()), EntityPointer_GetType(pointer)) << "Profile entity pointer type didn't serialize correctly";
	ASSERT_STREQ(EntityPointer_GetName(profileEntity.get()), EntityPointer_GetName(pointer)) << "Profile entity pointer name didn't serialize correctly";

	// Pop the entities off the list and make sure the size drops.
	ASSERT_EQ(2, EntityPointerList_Length(list.get())) << "Entity pointer list didn't have 2 entries";
	EntityPointerList_Pop(list.get());
	ASSERT_EQ(1, EntityPointerList_Length(list.get())) << "Entity pointer list didn't pop profile entity";
	EntityPointerList_Pop(list.get());
	ASSERT_EQ(0, EntityPointerList_Length(list.get())) << "Entity pointer list didn't pop app entity";
}
