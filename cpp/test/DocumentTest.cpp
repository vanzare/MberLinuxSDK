#include "gtest/gtest.h"
#include "mber.h"
#include "MberEnv.h"

#include <algorithm>
#include <vector>

namespace
{
	class DocumentTestProduction : public testing::Test
	{
	public:
		DocumentTestProduction() :
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

	class DocumentTags
	{
	public:
		DocumentTags() :
			mTags(0)
		{
		}

		~DocumentTags()
		{
			clear();
		}

		MBER_ARRAY* get() const
		{
			return mTags;
		}

		bool add(const std::string& tag)
		{
			if (tag.empty() || (!mTags && !init())) {
				return false;
			}
			const size_t newSize = sizeof(char*) * (mTags->numElements + 1);
			void** tags = (void**)realloc(mTags->elements, newSize);
			if (!tags) {
				return false;
			}
			mTags->elements = tags;
			// +1 to account for the terminating '\0' character.
			const size_t length = tag.length() + 1;
			mTags->elements[mTags->numElements] = (char*)malloc(sizeof(char) * length);
			if (!mTags->elements[mTags->numElements]) {
				return false;
			}
			mTags->numElements += 1;
			return memcpy(mTags->elements[mTags->numElements - 1], tag.c_str(), length) != 0;
		}

		void clear()
		{
			if (mTags) {
				for (int i = 0; i < mTags->numElements; ++i) {
					char* tag = (char*)mTags->elements[i];
					free(tag);
					tag = 0;
				}
				free(mTags->elements);
			}
			free(mTags);
			mTags = 0;
		}

	private:
		bool init()
		{
			clear();
			mTags = (MBER_ARRAY*)malloc(sizeof(tag_MBER_ARRAY));
			if (!mTags) {
				return false;
			}
			mTags->numElements = 0;
			mTags->elements = 0;
			return true;
		}

		DocumentTags(const DocumentTags&);
		DocumentTags& operator=(const DocumentTags&);

		MBER_ARRAY* mTags;
	};

	class Documents
	{
	public:
		Documents() :
		  mDocuments(0)
		{
		}

		~Documents()
		{
			Free_Documents(&mDocuments);
		}

		MBER_ARRAY** get()
		{
			return &mDocuments;
		}

		int length() const
		{
			if (!mDocuments) {
				return 0;
			}
			return mDocuments->numElements;
		}

		const char* const name(const int index) const
		{
			const MBER_DOCUMENT* const document = at(index);
			if (!document) {
				return 0;
			}
			return document->name;
		}

		const char* const alias(const int index) const
		{
			const MBER_DOCUMENT* const document = at(index);
			if (!document) {
				return 0;
			}
			return document->alias;
		}

		bool isNull() const
		{
			return mDocuments == 0;
		}

	private:
		const MBER_DOCUMENT* const at(const int index) const
		{
			if (index >= length()) {
				return 0;
			}
			return (MBER_DOCUMENT*)mDocuments->elements[index];
		}

		MBER_ARRAY* mDocuments;
	};

	class Base64Data
	{
	public:
		explicit Base64Data(const std::string& input) :
			mData(input.length() * 2, '?')
		{
			Base64Encode(input.c_str(), (int)input.length(), mData.data(), (int)mData.size());
		}

		char* data()
		{
			return mData.data();
		}

	private:
		Base64Data(const Base64Data&);
		Base64Data& operator=(const Base64Data&);

		std::vector<char> mData;
	};

	class DocumentDeleter
	{
	public:
		DocumentDeleter(Mber::MberSession* const session, const std::string& id) :
		  mSession(session),
		  mDocumentId(id)
		{
		}

		~DocumentDeleter()
		{
			Mber::Status status = Mber::Status_Failed;
			Document_Delete(mSession, mDocumentId.c_str(), status);
		}
	private:
		DocumentDeleter(const DocumentDeleter&);
		DocumentDeleter& operator=(const DocumentDeleter&);

		Mber::MberSession* mSession;
		std::string mDocumentId;
	};

	bool Document_Read_Alias(Mber::MberSession* session, const char* const documentId, Mber::Status& status, char* const alias, const int alias_size)
	{
		std::vector<char> name(65, '?');
		std::vector<char> content(1024, '?');
		return Document_Read_Aliased(session, documentId, status, name.data(), (int)name.size(), alias, alias_size, content.data(), (int)content.size());
	}
}

TEST_F(DocumentTestProduction, FindDocument)
{
	DocumentTags tags;
	ASSERT_TRUE(tags.add("cpp"));
	ASSERT_TRUE(tags.add("sdk"));
	ASSERT_TRUE(tags.add("test"));

	Documents documents;

	int version = -1;
	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Document_Find(session(), version, status, tags.get(), documents.get())) << "Failed to search for documents";
	ASSERT_EQ(Mber::Status_Success, status) << "Failed to find documents";
	ASSERT_EQ(1, documents.length()) << "Found more than one document with the specified set of tags";
	ASSERT_STREQ("CppSDKTest", documents.name(0)) << "Didn't find the right document";
	ASSERT_STREQ("CppSDKTest", documents.alias(0)) << "Document wasn't aliased correctly";
}

TEST_F(DocumentTestProduction, FindDocumentWithoutAlias)
{
	DocumentTags tags;
	ASSERT_TRUE(tags.add("no-alias"));
	ASSERT_TRUE(tags.add("sdk"));
	ASSERT_TRUE(tags.add("test"));

	Documents documents;

	int version = -1;
	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Document_Find(session(), version, status, tags.get(), documents.get())) << "Failed to search for a document without an alias";
	ASSERT_EQ(Mber::Status_Success, status) << "Failed to find a document without an alias";
	ASSERT_EQ(1, documents.length()) << "Found more than one document without an alias";
	ASSERT_STREQ("CppSDKTestNoAlias", documents.name(0)) << "Didn't find the right document without an alias";
	ASSERT_STREQ("", documents.alias(0)) << "Document had an alias";
}

TEST_F(DocumentTestProduction, FindDocumentWithoutTags)
{
	Documents documents;
	int version = -1;
	Mber::Status status = Mber::Status_Failed;
	ASSERT_FALSE(Document_Find(session(), version, status, 0, documents.get())) << "Finding documents without tags should be safe";
}

TEST_F(DocumentTestProduction, FindDocumentThatDoesntExist)
{
	DocumentTags tags;
	ASSERT_TRUE(tags.add("noodles"));
	ASSERT_TRUE(tags.add("pasta"));
	ASSERT_TRUE(tags.add("salad"));

	Documents documents;
	int version = -1;
	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Document_Find(session(), version, status, tags.get(), documents.get())) << "Finding documents that don't match anything should be safe";
	ASSERT_FALSE(documents.isNull()) << "Should get back an non-empty documents array";
	ASSERT_EQ(0, documents.length()) << "But that array should be empty";
}

TEST_F(DocumentTestProduction, CreateDocument)
{
	{
		// Delete the document if it was left over from previous tests.
		DocumentDeleter deleter(session(), "'TempCppSDKTestCreate");
	}
	{
		// Delete the document when this test is done.
		DocumentDeleter deleter(session(), "'TempCppSDKTestCreate");
		DocumentTags tags;
		Base64Data data("This document shouldn't live for very long.");
		Mber::Status status = Mber::Status_Failed;
		std::vector<char> id(33, '?');
		ASSERT_TRUE(Document_Create(session(), "TempCppSDKTestCreate", data.data(), tags.get(), status, id.data(), (int)id.size())) << "Failed to create the document";
		ASSERT_EQ(Mber::Status_Success, status);
		ASSERT_EQ(std::string::npos, std::string(id.begin(), id.end()).find('?')) << "The ID has non-valid Base64 characters";

		// Make sure the alias for the document was set to the document's name.
		status = Mber::Status_Failed;
		std::vector<char> alias(65, '?');
		ASSERT_TRUE(Document_Read_Alias(session(), id.data(), status, alias.data(), (int)alias.size())) << "Failed to read the alias of the document we created";
		ASSERT_EQ(Mber::Status_Success, status) << "Failed to read the alias of the document we created";
		ASSERT_STREQ("TempCppSDKTestCreate", alias.data()) << "Document had a non-default alias";
	}
	// Make sure the deleter did its job and removed the document.
	std::vector<char> name(256, '?');
	std::vector<char> content(5 * 1024, '?');
	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Document_Read(session(), "'TempCppSDKTestCreate", status, name.data(), (int)name.size(), content.data(), (int)content.size())) << "Read something unexpected since the document should be gone";
	ASSERT_EQ(Mber::Status_NotFound, status) << "Document wasn't deleted like we expected";
}

TEST_F(DocumentTestProduction, CreateDocumentWithAlias)
{
	const std::string document_name = "TempCppSDKTestCreateWithAlias";
	const std::string document_alias = "TempCppSDKTestCreateAliasedDoc";
	const std::string document_id = "'" + document_alias;
	const std::string raw_data = "This document shouldn't live for very long.";
	{
		// Delete the document if it was left over from previous tests.
		DocumentDeleter deleter(session(), document_id);
	}
	{
		// Create a new document with an alias.
		DocumentTags tags;
		Base64Data data(raw_data);
		Mber::Status status = Mber::Status_Failed;
		std::vector<char> id(33, '?');
		ASSERT_TRUE(Document_Create_Aliased(session(), document_name.c_str(), document_alias.c_str(), data.data(), tags.get(), status, id.data(), (int)id.size())) << "Failed to create the aliased document";
		ASSERT_EQ(Mber::Status_Success, status);

		// We've got an ID, so delete the document when the test's done.
		DocumentDeleter deleter(session(), id.data());

		// Make sure the alias for the document was set correctly.
		status = Mber::Status_Failed;
		std::vector<char> alias(65, '?');
		ASSERT_TRUE(Document_Read_Alias(session(), id.data(), status, alias.data(), (int)alias.size())) << "Failed to read the document we just created";
		ASSERT_EQ(Mber::Status_Success, status) << "Failed to read the document we just created";
		ASSERT_STREQ(document_alias.c_str(), alias.data()) << "Document just created didn't have the correct alias";

		// Update the alias with a new value.
		const std::string updated_alias = "TempCppSDKUpdateAliasedDoc";
		ASSERT_STRNE(document_alias.c_str(), updated_alias.c_str()) << "New alias and old alias matched";
		status = Mber::Status_Failed;
		ASSERT_TRUE(Document_Update_Aliased(session(), id.data(), 0, updated_alias.c_str(), 0, tags.get(), status)) << "Failed to update the alias for the document";
		ASSERT_EQ(Mber::Status_Success, status) << "Failed to update the alias for the document";

		// Make sure the alias for the document was updated.
		status = Mber::Status_Failed;
		std::vector<char> new_alias(65, '?');
		ASSERT_TRUE(Document_Read_Alias(session(), id.data(), status, new_alias.data(), (int)new_alias.size())) << "Failed to read the alias of the document we just updated";
		ASSERT_EQ(Mber::Status_Success, status) << "Failed to read the alias of the document we just updated";
		ASSERT_STREQ(updated_alias.c_str(), new_alias.data()) << "Document just updated didn't have the correct alias";

		// Make sure we didn't lose any data, since we passed in NULL pointers for name and data when we updated the alias.
		status = Mber::Status_Failed;
		std::vector<char> new_data(1024, '?');
		std::vector<char> new_name(1024, '?');
		ASSERT_TRUE(Document_Read(session(), id.data(), status, new_name.data(), (int)new_name.size(), new_data.data(), (int)new_data.size())) << "Failed to read the document after we updated its alias";
		ASSERT_EQ(Mber::Status_Success, status) << "Failed to read the document after we updated its alias";
		ASSERT_STREQ(raw_data.c_str(), new_data.data()) << "Updated document didn't have the correct data";
		ASSERT_STREQ(document_name.c_str(), new_name.data()) << "Updated document didn't have the correct name";

		// Update the alias with a NULL value.
		status = Mber::Status_Failed;
		ASSERT_TRUE(Document_Update_Aliased(session(), id.data(), 0, 0, 0, tags.get(), status)) << "Failed to clear the alias for the document";
		ASSERT_EQ(Mber::Status_Success, status) << "Failed to clear the alias for the document";

		// Make sure the alias for the document was cleared.
		status = Mber::Status_Failed;
		std::vector<char> null_alias(65, '?');
		ASSERT_TRUE(Document_Read_Alias(session(), id.data(), status, null_alias.data(), (int)null_alias.size())) << "Failed to read the alias of the document we cleared";
		ASSERT_EQ(Mber::Status_Success, status) << "Failed to read the alias of the document we cleared";
		ASSERT_STREQ("", null_alias.data()) << "Document had an alias after it was cleared";
	}
}

TEST_F(DocumentTestProduction, CreateDocumentWithNullPointers)
{
	Mber::Status status = Mber::Status_Failed;
	ASSERT_FALSE(Document_Create(0, 0, 0, 0, status, 0, 0)) << "Creating a document with NULL pointers should fail";
}

TEST_F(DocumentTestProduction, ReadDocument)
{
	std::vector<char> name(256, '?');
	std::vector<char> content(5 * 1024, '?');
	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Document_Read(session(), "'CppSDKTest", status, name.data(), (int)name.size(), content.data(), (int)content.size())) << "Failed to read the CppSDKTest document";
	ASSERT_EQ(Mber::Status_Success, status);
	ASSERT_STREQ("CppSDKTest", name.data()) << "CppSDKTest document didn't have the correct name";
	ASSERT_STREQ("This is used by the tests for the C++ SDK.", content.data()) << "CppSDKTest document didn't have the correct data";
}

TEST_F(DocumentTestProduction, ReadDocumentWithNullPointers)
{
	Mber::Status status = Mber::Status_Failed;
	ASSERT_FALSE(Document_Read(0, "'CppSDKTest", status, 0, 0, 0, 0)) << "Reading a document with NULL pointers should fail";
}

TEST_F(DocumentTestProduction, ReadDocumentWithoutID)
{
	std::vector<char> name(256, '?');
	std::vector<char> content(5 * 1024, '?');
	Mber::Status status = Mber::Status_Failed;
	ASSERT_FALSE(Document_Read(session(), "", status, name.data(), (int)name.size(), content.data(), (int)content.size())) << "Read the CppSDKTest document";
}

TEST_F(DocumentTestProduction, ReadInvalidDocument)
{
	std::vector<char> name(256, '?');
	std::vector<char> content(5 * 1024, '?');
	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Document_Read(session(), "'SomeDocumentThatDoesNotExist", status, name.data(), (int)name.size(), content.data(), (int)content.size())) << "Read a document that doesn't exist";
	ASSERT_EQ(Mber::Status_NotFound, status);
}

TEST_F(DocumentTestProduction, UpdateDocument)
{
	DocumentTags tags;
	ASSERT_TRUE(tags.add("cpp"));
	ASSERT_TRUE(tags.add("sdk"));
	ASSERT_TRUE(tags.add("test"));

	Base64Data data("This is used by the tests for the C++ SDK.");

	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Document_Update(session(), "'CppSDKTest", "CppSDKTest", data.data(), tags.get(), status)) << "Failed to update the CppSDKTest document";
	ASSERT_EQ(Mber::Status_Success, status) << "Didn't successfully update the CppSDKTest document";

	// Make sure the alias for the document was set to the document's name.
	status = Mber::Status_Failed;
	std::vector<char> alias(65, '?');
	ASSERT_TRUE(Document_Read_Alias(session(), "'CppSDKTest", status, alias.data(), (int)alias.size())) << "Failed to read the alias of the document we updated";
	ASSERT_EQ(Mber::Status_Success, status) << "Failed to read the alias of the document we updated";
	ASSERT_STREQ("CppSDKTest", alias.data()) << "Document had a non-default alias";
}

TEST_F(DocumentTestProduction, UpdateDocumentWithNullPointers)
{
	Mber::Status status = Mber::Status_Failed;
	ASSERT_FALSE(Document_Update(0, "'CppSDKTest", 0, 0, 0, status)) << "Updating a document with NULL pointers should fail";
}

TEST_F(DocumentTestProduction, UpdateDocumentWithoutID)
{
	DocumentTags tags;
	ASSERT_TRUE(tags.add("cpp"));
	ASSERT_TRUE(tags.add("sdk"));
	ASSERT_TRUE(tags.add("test"));

	Base64Data data("This is used by the tests for the C++ SDK.");

	Mber::Status status = Mber::Status_Failed;
	ASSERT_FALSE(Document_Update(session(), "", "CppSDKTest", data.data(), tags.get(), status)) << "Updated the CppSDKTest document";
}

TEST_F(DocumentTestProduction, UpdateInvalidDocument)
{
	DocumentTags tags;
	tags.add("noodles");

	Base64Data data("This document should never get created.");

	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Document_Update(session(), "'SomeDocumentThatDoesntExist", "SomeDocumentThatDoesntExist", data.data(), tags.get(), status)) << "Updated a document that doesn't exist";
	ASSERT_EQ(Mber::Status_NotFound, status);
}

TEST_F(DocumentTestProduction, FindLargeFile)
{
	DocumentTags tags;
	ASSERT_TRUE(tags.add("3GB"));

	Documents documents;

	int version = -1;
	Mber::Status status = Mber::Status_Failed;
	ASSERT_TRUE(Document_Find(session(), version, status, tags.get(), documents.get())) << "Failed to search for a large document with tags";
	ASSERT_STREQ("", Session_GetLastError(session())) << "Searching for large documents shouldn't result in errors";
	ASSERT_EQ(Mber::Status_Success, status) << "Failed to find a large document with tags";
	ASSERT_EQ(1, documents.length()) << "Found more than one large document with tags";
	ASSERT_STREQ("noise.bin", documents.name(0)) << "Didn't find the right large document";
	ASSERT_STREQ("noise.bin", documents.alias(0)) << "Large ocument wasn't aliased correctly";
}
