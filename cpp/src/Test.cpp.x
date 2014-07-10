//
// Test.cpp
//
// This sample demonstrates the simple usage of the Mber client library.
//
// Copyright (c) 2012-2013, FirePub, Inc. All Rights Reserved.
//

#include <sstream>
#include "mber.h"

using Mber::MberPtr;
using namespace Mber::oauth;
using namespace Mber::account;
using namespace Mber::data;

// Universal Mber constant
std::string mberId = "rkQRyRgsSTKF8H9fsJmNGQ";

// Useful App Ids
std::string appId = "exS6RGHyQ8erOk3-eTm7sA";	// CI app
//std::string appId = "n4N6aUqVReuBifZM17_yAQ";	// World of Golf app

// Mber Production instance
//std::string host = "https://member.firepub.net";
std::string host = "http://dev.office.firepub.net";

// Login credentials
MberPtr<std::string> username = new std::string("root");
MberPtr<std::string> password = new std::string("changeme");

Mber::MberSession rootSession(host);
Mber::MberSession appSession(host);

void readProfile(){
	MberPtr<Profile::Read::Response> rsp = rootSession.execute( Profile::Read::Request( *(rootSession.getProfileId()) ) );
	if( rsp->status == Mber::Status_Success ) {
		std::cout << "My Profile\n--------------------------\n";
		std::cout << "accountId = " << rsp->result->accountId << "\n";
		std::cout << "profileId = " << rsp->result->profileId << "\n";
		std::cout << "username = " << rsp->result->username << "\n";
		std::cout << "displayname = " << rsp->result->displayname << "\n";
		if( rsp->result->email.isNull() ){
			std::cout << "(no email returned)\n\n";
		}
	} else {
		std::cout << "Profile read failed: " << rsp->status << "\n\n";
	}
}

void searchProfiles(std::string &field, std::string &name, double similarity){
	Mber::Query query;
	query.field = field;
	query.like = new Mber::FuzzyValue;
	query.like->minSimilarity = new double( similarity );
	query.like->value = name;

	MberPtr<ProfileQuery::Create::Response> rsp = appSession.execute(ProfileQuery::Create::Request( query ) );
	if( rsp->status == Mber::Status_Success ) {
		std::cout << "Search Results: " << rsp->results->size() << "\n--------------------------------\n";
		for (std::list<Mber::Profile>::const_iterator iterator = rsp->results->begin(), end = rsp->results->end(); iterator != end; ++iterator) {
			Mber::Profile next = *iterator;
			std::cout << "accountId = " << next.accountId << "\n";
			std::cout << "profileId = " << next.profileId << "\n";
			std::cout << "username = " << next.username << "\n";
			std::cout << "displayname = " << next.displayname << "\n\n";
		}
	} else {
		std::cout << "Profile search failed: " << rsp->status << "\n\n";
	}
}

MberPtr<std::string> findDocument(int &version){
	MberPtr<std::string> result = NULL;
	std::list<std::string> *tags = new std::list<std::string>();
	tags->push_back("cppTest");
	tags->push_back("sample");
	MberPtr<Document::List::Response> rsp = appSession.execute(Document::List::Request(NULL, tags));
	if( rsp->status == Mber::Status_Success ) {
		std::cout << "Document List Results: " << rsp->results->size() << "\n--------------------------------\n";
		for (std::list<Mber::Document>::const_iterator iterator = rsp->results->begin(), end = rsp->results->end(); iterator != end; ++iterator) {
			Mber::Document next = *iterator;
			std::cout << "documentId = " << next.documentId << "\n";
			std::cout << "name = " << *next.name << "\n";
			result = new std::string(next.documentId);
			version = *next.version;
		}
	} else {
		std::cout << "Document list failed: " << rsp->status << "\n\n";
	}
	return result;
}

void readDocument(std::string docId){
	Mber::EntityID entityId;
	entityId.id = new std::string(docId);
	entityId.name = NULL;

	MberPtr<Document::Read::Response> rsp = appSession.execute(Document::Read::Request(entityId));
	if( rsp->status == Mber::Status_Success ){
		std::cout << "Document read success\n";
		std::cout << "Name: " << *rsp->result->name << "\n";
		std::cout << "Data: " << Mber::base64Decode(*rsp->result->data) << "\n";
	} else {
		std::cout << "Document read failed: " << rsp->status << "\n\n";
	}
}

void readRootDocument(std::string docId){
	Mber::EntityID entityId;
	entityId.id = new std::string(docId);
	entityId.name = NULL;

	MberPtr<Document::Read::Response> rsp = rootSession.execute(Document::Read::Request(entityId));
	if( rsp->status == Mber::Status_Success ){
		std::cout << "Document read success\n";
		std::cout << "Name: " << *rsp->result->name << "\n";
		// @TODO: Explain what this does
		if (!(rsp->result->data.isNull())){
			std::cout << "Data: " << Mber::base64Decode(*rsp->result->data) << "\n"; // base64 encoded
		} else {
			std::cout << "Content: " << *rsp->result->content << "\n"; // json string
		}
	} else {
		std::cout << "Document read failed: " << rsp->status << "\n\n";
	}
}
MberPtr<std::string> createDocument(){
	MberPtr<std::string> result = NULL;
	char buffer[] = "This is a document created by the CPP Test Client";
	std::string base64 = Mber::base64Encode(buffer, strlen(buffer));
	std::list<std::string> *tags = new std::list<std::string>();
	tags->push_back("cppTest");
	tags->push_back("sample");

	MberPtr<Document::Create::Response> rsp = appSession.execute(Document::Create::Request("testDoc", new std::string(base64), new std::string(appId), tags, NULL, NULL, NULL));
	if( rsp->status == Mber::Status_Success ) {
		std::cout << "Document created: " << *rsp->documentId << "\n\n";
		result = rsp->documentId;
	} else {
		std::cout << "Document created failed: " << rsp->status << "\n\n";
	}
	return result;
}

void updateDocument(std::string docId, int num){
	Mber::EntityID entityId;
	entityId.id = new std::string(docId);
	entityId.name = NULL;

	std::stringstream stream;
	stream << "This is a document created by the CPP Test Client. I have been updated " << num << " times!";
	std::string str = stream.str();
	std::string base64 = Mber::base64Encode(str.data(), str.length());
	std::list<std::string> *tags = new std::list<std::string>();
	tags->push_back("cppTest");
	tags->push_back("sample");
	MberPtr<Document::Update::Response> rsp = appSession.execute( Document::Update::Request(new std::string("testDoc"),entityId,NULL,new std::string(base64),tags,NULL,NULL ) );
	if( rsp->status == Mber::Status_Success ){
		std::cout << "Document updated.\n";
	} else {
		std::cout << "Document update filed: " << rsp->status << "\n";
	}
}

int main(){
	appSession.init();
	rootSession.init();
	// Login
	std::cout << "Logging in...\n\n";
	Mber::Status loginResult = appSession.login( AccessToken::Create::Request("password",appId,NULL,NULL,NULL,username,password,NULL,NULL) );
	Mber::Status loginResult2 = rootSession.login( AccessToken::Create::Request("password",mberId,NULL,NULL,NULL,username,password,NULL,NULL) );
	if( loginResult == Mber::Status_Success ){
		std::cout << "Profile = " << *appSession.getProfileId() << "\n";
		std::cout << "Token = " << *appSession.getToken() << "\n\n";

		// Read profile data with a root session... No good reason. Just because.
		if( loginResult2 == Mber::Status_Success ){
			std::cout << "Root session authenticated\n";
			std::cout << "Reading profile...\n";
			readProfile();
		}

		// Search profiles. Again, for no good reason. Just because.
		std::cout << "Searching profiles...\n";
		std::string searchField = "displayName";
		std::string searchValue = "test";
		searchProfiles(searchField, searchValue, 0.5);

		// Does the test document exist?
		std::cout << "Finding document...\n\n";
		int updateCount = 0;
		MberPtr<std::string> docId = findDocument(updateCount);
		if( docId.isNull() ){
			std::cout << "Doc not found\n";
			// Create a new document
			std::cout << "Creating document...\n\n";
			docId = createDocument();
			std::cout << "Created document: " << *docId << "\n\n";
		} else {
			std::cout << "Found document: " << *docId << "\n\n";
		}

		// Read the document
		if( !docId.isNull() ){
			std::cout << "Updating document...\n";
			updateDocument(*docId,updateCount);

			std::cout << "Reading document...\n\n";
			readDocument(*docId);
		}

		// Read the Mber (aliased) document
// ci
		MberPtr<std::string> mberConfigDocId = new std::string("'config");
		readRootDocument(*mberConfigDocId);

// production 
//		MberPtr<std::string> mberConfigDocId = new std::string("'character doc");
	} else {
		std::cout << "Failed to log in";
	}
	rootSession.term();
	appSession.term();
	return 0;
}
