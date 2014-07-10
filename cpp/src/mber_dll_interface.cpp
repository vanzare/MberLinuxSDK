#include "mber.h"
#include "MberImpl.h"
#include "EntityPointerListImpl.h"

#include "Poco/Net/HTTPSessionFactory.h"
#include "Poco/Net/HTTPSSessionInstantiator.h"
#include "Poco/Net/PrivateKeyFactory.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/InvalidCertificateHandler.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
#include "Poco/Net/SSLManager.h"

#include <string>
#include <sstream>

using Mber::MberPtr;
using namespace Mber::oauth;
using namespace Mber::account;
using namespace Mber::data;
using namespace Mber::commerce;

namespace
{

	MberPtr<std::string> MberPtrString(const char* const str)
	{
		return MberPtr<std::string>(new std::string(str));
	}
	#define CheckedMberPtrString(str) ((!str) ? 0 : (std::string(str).empty() ? 0 : MberPtrString(str)))

	typedef std::list<std::string> TagList;
	typedef MberPtr<TagList> TagListPtr;
	TagListPtr makeTagList(const MBER_ARRAY* const tags)
	{
		if (!tags || tags->numElements <= 0 || !tags->elements) {
			return TagListPtr();
		}
		TagListPtr results = new TagList();
		for (int i = 0; i < tags->numElements; ++i) {
			if (tags->elements[i]) {
				results->push_back(reinterpret_cast<char*>(tags->elements[i]));
			}
		}
		return results;
	}

	typedef MberPtr<Mber::EntityID> EntityIDPtr;
	EntityIDPtr makeEntityID(const char* const id)
	{
		if (!id || std::string(id).empty()) {
			return EntityIDPtr();
		}
		EntityIDPtr result = new Mber::EntityID();
		result->id = new std::string(id);
		result->name = 0;
		return result;
	}

	void mber_strcpy(char* const dst, const int length, const std::string& src)
	{
		strcpy_s(dst, length, src.c_str());
	}
}

MBER* MberInit(const char* const url)
{
	return new MBER(url);
}

void MberTerm(MBER* mber)
{
	delete mber;
}

void MberStartup()
{
	Poco::Net::HTTPSessionFactory::defaultFactory().registerProtocol("http", new Poco::Net::HTTPSessionInstantiator);
	Poco::Net::HTTPSessionFactory::defaultFactory().registerProtocol("https", new Poco::Net::HTTPSSessionInstantiator);
	Poco::SharedPtr<Poco::Net::PrivateKeyPassphraseHandler> console = new Poco::Net::KeyConsoleHandler(true);
	Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> cert = new Poco::Net::ConsoleCertificateHandler(true);
	Poco::Net::Context::Ptr context = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
	Poco::Net::SSLManager::instance().initializeClient(console, cert, context);
}

void MberShutdown()
{
	Poco::Net::SSLManager::instance().shutdown();
}

// Note: profile memory is owned by caller
bool Profile_Read (Mber::MberSession *session, Mber::Status &status, MBER_PROFILE *profile)
{
	MberPtr<Profile::Read::Response> rsp = session->execute( Profile::Read::Request( *(session->getProfileId()) ) );
	if( rsp->status == Mber::Status_Success ) {
		status = rsp->status;
		// @TODO: Use CopyProfile()
		strcpy_s(profile->profileId, 25, rsp->result->profileId.c_str());
		strcpy_s(profile->accountId, 25, rsp->result->accountId.c_str());
		if (!rsp->result->region.isNull()) {
			profile->region = *rsp->result->region;
		}
		if (!rsp->result->username.isNull()) {
			strcpy_s(profile->username, 256, rsp->result->username->c_str());
		}
		strcpy_s(profile->displayname, 33, rsp->result->displayname.c_str());
		if (!rsp->result->email.isNull()) {
			strcpy_s(profile->email, 256, (*rsp->result->email).c_str());
		}
		if (!rsp->result->unvalidated_email.isNull()) {
			strcpy_s(profile->unvalidated_email, 256, (*rsp->result->unvalidated_email).c_str());
		}
		if (!rsp->result->dateOfBirth.isNull()) {
			profile->dateOfBirth = *rsp->result->dateOfBirth;
		}
		// @TODO: Fix this
		//profile->status = rsp->result->status;
		return true;
	}
	return false;
}

// @TODO: Status is not copied
void CopyProfile (MBER_PROFILE *dst, Mber::Profile &src)
{
	// Required fields
	src.profileId.copy(dst->profileId, src.profileId.length());
	src.accountId.copy(dst->accountId, src.accountId.length());
	if (!src.region.isNull()) {
		dst->region = *src.region;
	}
	if (!src.username.isNull()) {
		src.username->copy(dst->username, src.username->length());
	}
	src.displayname.copy(dst->displayname, src.displayname.length());

	// Optional fields
	if (!src.email.isNull()) {
		src.email->copy(dst->email, src.email->length());
	}
	if (!src.unvalidated_email.isNull()) {
		src.unvalidated_email->copy(dst->unvalidated_email, src.unvalidated_email->length());
	}
	if (!src.dateOfBirth.isNull()) {
		dst->dateOfBirth = *src.dateOfBirth;
	}

	// @TODO: Status??

	/*
	    char profileId[25];							// The id of the profile
        char accountId[25];							// The id of the account the profile belongs to
        Mber::Region region;						// The region the user is coming from
        char username[256];							// The username of the profile
        char displayname[33];						// The display name of the profile

		//optional
        char email[256];							// The email address of the profile
        char unvalidated_email[256];				// The unvalidated email address of the profile
        long dateOfBirth;							// The user's date of birth
	*/
}

bool Free_Profiles (MBER_ARRAY **profiles)
{
	if (*profiles != NULL) {
		for (int n = 0; n < (*profiles)->numElements; ++n) {
			MBER_PROFILE *next = (MBER_PROFILE *)(*profiles)->elements[n];
			free(next);
		}
		free((*profiles)->elements);
		free(*profiles);
		*profiles = NULL;
		return true;
	}
	return false;
}

// profiles is array of Mber::Profile (owned by this)
bool Profile_Search (Mber::MberSession *session, const char *field, const char *name, const double similarity, Mber::Status &status, MBER_ARRAY **profiles)
{
	Mber::Query query;
	query.field = field;
	query.like = new Mber::FuzzyValue;
	query.like->minSimilarity = new double( similarity );
	query.like->value = name;

	MberPtr<ProfileQuery::Create::Response> rsp = session->execute( ProfileQuery::Create::Request( query ) );
	if( rsp->status == Mber::Status_Success ) {
		status = rsp->status;

		// Convert document list into an MBER_ARRAY of MBER_DOCUMENTS
		MBER_ARRAY *profileArray = (MBER_ARRAY *)calloc(1, sizeof(MBER_ARRAY));
		profileArray->numElements = (int)rsp->results->size();
		profileArray->elements = (void **)calloc(profileArray->numElements, sizeof(MBER_PROFILE *));
		int n = 0;
		for (std::list<Mber::Profile>::const_iterator iterator = rsp->results->begin(), end = rsp->results->end(); iterator != end; ++iterator, ++n) {
			Mber::Profile next = *iterator;
			profileArray->elements[n] = calloc(1, sizeof(MBER_PROFILE));
			CopyProfile(reinterpret_cast<MBER_PROFILE *>(profileArray->elements[n]), next);
		}

		*profiles = profileArray;

		return true;
	}
	return false;
}

void CopyDocument (MBER_DOCUMENT *dst, Mber::Document &src)
{
	// Required fields
	src.documentId.copy(dst->documentId, src.documentId.length());

	// Optional fields
	if (!src.name.isNull()) {
		src.name->copy(dst->name, src.name->length());
	}
	if (!src.alias.isNull()) {
		src.alias->copy(dst->alias, src.alias->length());
	}
	if (!src.size.isNull()) {
		dst->size = *src.size;
	}
	if (!src.version.isNull()) {
		dst->version = *src.version;
	}
	if (!src.scope.isNull()) {
		src.scope->copy(dst->scope, src.scope->length());
	}
	if (!src.documentTemplate.isNull()) {
		src.documentTemplate->copy(dst->documentTemplate, src.documentTemplate->length());
	}

	// @TODO: Some optional fields are not returned...
/*      char name[65];	// optional							
        char documentId[25];	// required					
        char *data;			// optional								
        int size;			// optional								
        int version;		// optional								
        char scope[25];		// optional								
        MBER_ARRAY *tags;	// optional								
        MBER_ARRAY *properties;	// optional							
        char documentTemplate[25];	// optional						
        char *content;      // optional		
*/
}

bool Free_Documents (MBER_ARRAY **documents)
{
	if (*documents != NULL) {
		for (int n = 0; n < (*documents)->numElements; ++n) {
			MBER_DOCUMENT *next = (MBER_DOCUMENT *)(*documents)->elements[n];
			free(next);
		}
		free((*documents)->elements);
		free(*documents);
		*documents = NULL;
		return true;
	}
	return false;
}

// tags = array of strings (owned by caller)
// documents = array of Mber::Document (owned by this)
bool Document_Find (Mber::MberSession *session, int &version, Mber::Status &status, MBER_ARRAY *tags, MBER_ARRAY **documents)
{
	if (!session || !tags || !documents) {
		return false;
	}

	TagListPtr tagList = makeTagList(tags);

	Document::List::Request request(NULL, tagList);
	MberPtr<Document::List::Response> rsp = session->execute(request);
	if (rsp.isNull()) {
		return false;
	}

	if (!rsp->results.isNull()) {
		// Convert document list into an MBER_ARRAY of MBER_DOCUMENTS
		MBER_ARRAY *docArray = (MBER_ARRAY *)calloc(1, sizeof(MBER_ARRAY));
		docArray->numElements = (int)rsp->results->size();
		docArray->elements = (void **)calloc(docArray->numElements, sizeof(MBER_DOCUMENT *));
		int n = 0;
		for (std::list<Mber::Document>::const_iterator iterator = rsp->results->begin(), end = rsp->results->end(); iterator != end; ++iterator, ++n) {
			Mber::Document next = *iterator;
			docArray->elements[n] = calloc(1, sizeof(MBER_DOCUMENT));
			CopyDocument(reinterpret_cast<MBER_DOCUMENT *>(docArray->elements[n]), next);
		}

		*documents = docArray;
	}

	status = rsp->status;
	session->setLastError(rsp->errorMessage);
	return true;
}

bool Document_Read (Mber::MberSession* const session, const char* const docId, Mber::Status& status, char* const name, const int name_size, char* const content, const int content_size)
{
	std::vector<char> alias(65, '\0');
	return Document_Read_Aliased(session, docId, status, name, name_size, alias.data(), (int)alias.size(), content, content_size);
}

bool Document_Read_Aliased (Mber::MberSession* const session, const char* const docId, Mber::Status& status, char* const name, const int name_size, char* const alias, const int alias_size, char* const content, const int content_size)
{
	if (!session || !name || !alias || !content) {
		return false;
	}

	EntityIDPtr entityId = makeEntityID(docId);
	if (entityId.isNull()) {
		return false;
	}

	Document::Read::Request request(*entityId, NULL);
	MberPtr<Document::Read::Response> rsp = session->execute(request);
	if (rsp.isNull()) {
		return false;
	}

	if (!rsp->result.isNull()) {
		if (!rsp->result->name.isNull()) {
			mber_strcpy(name, name_size, *rsp->result->name);
		}
		if (!rsp->result->alias.isNull()) {
			mber_strcpy(alias, alias_size, *rsp->result->alias);
		}
		else {
			mber_strcpy(alias, alias_size, "");
		}
		if (!rsp->result->content.isNull()) {
			std::string data = *rsp->result->content;
			if (rsp->result->documentTemplate.isNull()) {
				data = Mber::base64Decode(data);
			}
			mber_strcpy(content, content_size, data);
		}
	}

	status = rsp->status;
	session->setLastError(rsp->errorMessage);
	return true;
}

// tags = array of strings (owned by caller)
bool Document_Create (Mber::MberSession* const session, const char* const name, const char* const content, const MBER_ARRAY* const tags, Mber::Status& status, char* const docId, const int docId_size)
{
	if (!session || !name || !content || !docId) {
		return false;
	}

	return Document_Create_Aliased(session, name, name, content, tags, status, docId, docId_size);
}

bool Document_Create_Aliased (Mber::MberSession* const session, const char* const name, const char* const alias, const char* const content, const MBER_ARRAY* const tags, Mber::Status& status, char* const docId, const int docId_size)
{
	if (!session || !name || !content || !docId) {
		return false;
	}

	TagListPtr tagList = makeTagList(tags);

	Document::Create::Request request(name, CheckedMberPtrString(alias), tagList, NULL, NULL, new std::string(content), NULL, NULL, NULL, NULL, NULL);
	MberPtr<Document::Create::Response> rsp = session->execute(request);
	if (rsp.isNull()) {
		return false;
	}

	if (!rsp->documentId.isNull()) {
		mber_strcpy(docId, docId_size, *rsp->documentId);
	}

	status = rsp->status;
	session->setLastError(rsp->errorMessage);
	return true;
}

// tags = array of strings (owned by caller)
bool Document_Update (Mber::MberSession *session, const char *docId, const char *name, const char *data, MBER_ARRAY *tags, Mber::Status &status)
{
	if (!session || !name || !data) {
		return false;
	}

	return Document_Update_Aliased(session, docId, name, name, data, tags, status);
}

bool Document_Update_Aliased (Mber::MberSession* const session, const char* const docId, const char* const name, const char* const alias, const char* const data, const MBER_ARRAY* const tags, Mber::Status& status)
{
	if (!session) {
		return false;
	}

	TagListPtr tagList = makeTagList(tags);

	EntityIDPtr entityId = makeEntityID(docId);
	if (entityId.isNull()) {
		return false;
	}

	Document::Update::Request request(CheckedMberPtrString(name), CheckedMberPtrString(alias), *entityId, NULL, tagList, NULL, CheckedMberPtrString(data), NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	MberPtr<Document::Update::Response> rsp = session->execute(request);
	if (rsp.isNull()) {
		return false;
	}

	status = rsp->status;
	session->setLastError(rsp->errorMessage);
	return true;
}

bool Document_Delete (Mber::MberSession* const session, const char* const docId, Mber::Status& status)
{
	if (!session || !docId) {
		return false;
	}

	EntityIDPtr entityId = makeEntityID(docId);
	if (entityId.isNull()) {
		return false;
	}

	Document::Delete::Request request(*entityId);
	MberPtr<Document::Delete::Response> rsp = session->execute(request);
	if (rsp.isNull()) {
		return false;
	}

	status = rsp->status;
	session->setLastError(rsp->errorMessage);
	return true;
}

bool Commerce_WalletCredit (Mber::MberSession* const session, const char* const virtualCurrencyId, const char* const profileId, const double amount, Mber::Status& status)
{
	if (!session || !virtualCurrencyId || !profileId) {
		return false;
	}

	EntityIDPtr entityId = makeEntityID(virtualCurrencyId);
	if (entityId.isNull()) {
		return false;
	}

	WalletLot::Create::Request request(*entityId, profileId, amount);
	MberPtr<WalletLot::Create::Response> rsp = session->execute(request);
	if (rsp.isNull()) {
		return false;
	}

	status = rsp->status;
	session->setLastError(rsp->errorMessage);

	return true;
}

bool Commerce_WalletDebit (Mber::MberSession* const session, const char* const virtualCurrencyId, const char* const profileId, const double amount, const char* const reason, Mber::Status& status)
{
	if (!session || !virtualCurrencyId || !profileId) {
		return false;
	}

	EntityIDPtr entityId = makeEntityID(virtualCurrencyId);
	if (entityId.isNull()) {
		return false;
	}

	Mber::EntityPointer recipient;
	recipient.entityId = std::string(profileId);
	recipient.entityType = Mber::EntityType_Profile;
	if (recipient.entityId.empty()) {
	  return false;
	}

	Deduction::Create::Request request(*entityId, amount, CheckedMberPtrString(reason), recipient);
	MberPtr<Deduction::Create::Response> rsp = session->execute(request);
	if (rsp.isNull()) {
		return false;
	}

	status = rsp->status;
	session->setLastError(rsp->errorMessage);

	return true;
}

bool Commerce_WalletBalance (Mber::MberSession* const session, const char* const virtualCurrencyId, const char* const profileId, double& amount, Mber::Status& status)
{
	if (!session || !virtualCurrencyId || !profileId) {
		return false;
	}

	const std::string entityId(profileId);
	if (entityId.empty()) {
		return false;
	}

	Wallet::Read::Request request(entityId, NULL);
	MberPtr<Wallet::Read::Response> rsp = session->execute(request);
	if (rsp.isNull()) {
		return false;
	}

	status = rsp->status;
	session->setLastError(rsp->errorMessage);

	// If we're given an alias, convert it to the currency name.
	const std::string currencyId = virtualCurrencyId;
	const std::string currencyName = (currencyId.find("'") == 0) ? currencyId.substr(1, currencyId.size()) : currencyId;

	if (!rsp->result.isNull() && !rsp->result->funds.isNull()) {
		const std::list<Mber::WalletTotal>& funds = *rsp->result->funds;
		for (std::list<Mber::WalletTotal>::const_iterator itr = funds.begin(); itr != funds.end(); ++itr) {
			if (itr->virtualCurrencyId == currencyId || itr->virtualCurrencyName == currencyName) {
				amount = itr->total;
				break;
			}
		}
	}

	return true;
}

bool DigitalGoodInstance_List(Mber::MberSession* const session, const MBER_ENTITY_POINTER* const entity, const char* const* const definition_ids, const int definition_id_count, MBER_DIGITAL_GOOD_INSTANCE_LIST** results, Mber::Status& status)
{
	if (!session || !entity || !results) {
		return false;
	}

	// Make sure the user's provided a valid entity ID.
	const std::string entityId = EntityPointer_GetId(entity);
	if (entityId.empty()) {
		return false;
	}

	// Make sure the user's provided a valid entity type.
	Mber::EntityType entityType;
	try {
		entityType = Mber::stringToEntityType(EntityPointer_GetType(entity));
	} catch (const std::invalid_argument& e) {
		std::stringstream message;
		message << "The entity type " << e.what() << " is invalid.";
		status = Mber::Status_Failed;
		session->setLastError(message.str());
		return false;
	}

	// Create the list of definition IDs.
	typedef std::list<std::string> DefinitionList;
	typedef MberPtr<DefinitionList> DefinitionListPtr;
	DefinitionListPtr definitionIds;
	if (definition_ids && definition_id_count > 0) {
		DefinitionList list;
		for (int i = 0; i < definition_id_count; ++i) {
			list.push_back(definition_ids[i]);
		}
		definitionIds = DefinitionListPtr(new DefinitionList(list));
	}

	// Create the list of states. This is empty, since we want all the digital goods.
	typedef std::list<Mber::EntitlementState> StateList;
	typedef MberPtr<StateList> StateListPtr;
	StateListPtr states;

	// Create the boolean for expired goods. This is empty, since we want non-expired goods.
	MberPtr<bool> expired;

	// Make the actual request to Mber.
	Mber::digitalGood::Instance::List::Request request(entityId, entityType, definitionIds, states, expired, NULL);
	MberPtr<Mber::digitalGood::Instance::List::Response> rsp = session->execute(request);
	if (rsp.isNull()) {
		return false;
	}

	// Unpack the results into digital good instances.
	if (!rsp->results.isNull() && !rsp->results->empty()) {
		*results = DigitalGoodInstanceList_Init();
		const std::list<Mber::DigitalGoodInstance>& goods = *rsp->results;
		for (std::list<Mber::DigitalGoodInstance>::const_iterator itr = goods.begin(); itr != goods.end(); ++itr) {
			MBER_DIGITAL_GOOD_INSTANCE* instance = DigitalGoodInstance_Init();
			DigitalGoodInstance_SetId(instance, itr->id.c_str());
			DigitalGoodInstance_SetDefinitionId(instance, itr->definitionId.c_str());
			DigitalGoodInstance_SetState(instance, Mber::EntitlementStateToString(itr->state).c_str());
			if (!itr->documentId.isNull()) {
				DigitalGoodInstance_SetDocumentId(instance, itr->documentId->c_str());
			}
			if (!itr->name.isNull()) {
				DigitalGoodInstance_SetName(instance, itr->name->c_str());
			}
			if (!itr->scope.isNull()) {
				DigitalGoodInstance_SetScope(instance, itr->scope->c_str());
			}
			if (!itr->properties.isNull() && !itr->properties->empty()) {
				MBER_PROPERTY_LIST* properties = PropertyList_Init();
				const std::list<Mber::Property>& props = *itr->properties;
				for (std::list<Mber::Property>::const_iterator pitr = props.begin(); pitr != props.end(); ++pitr) {
					MBER_PROPERTY* property = Property_Init();
					Property_SetKey(property, pitr->key.c_str());
					Property_SetValue(property, pitr->value.c_str());
					PropertyList_Push(properties, property);
				}
				DigitalGoodInstance_SetProperties(instance, properties);
			}
			DigitalGoodInstanceList_Push(*results, instance);
		}
	}

	status = rsp->status;
	session->setLastError(rsp->errorMessage);

	return true;
}

bool Session_Login(Mber::MberSession* const session, const char* const grant_type, const char* const client_id, const char* const client_secret, const char* const code, const char* const refresh_token, const char* const username, const char* const password, const char* const redirect_uri, const char* const scope, Mber::Status& status)
{
  EntityIDPtr client = makeEntityID(client_id);
  if (client.isNull()) {
	  return false;
  }

  AccessToken::Create::Request request(
    grant_type,
    *client,
    CheckedMberPtrString(client_secret),
    CheckedMberPtrString(code),
    CheckedMberPtrString(refresh_token),
    CheckedMberPtrString(username),
    CheckedMberPtrString(password),
    CheckedMberPtrString(redirect_uri),
    CheckedMberPtrString(scope)
  );
  status = session->login(request);
  return status == Mber::Status_Success;
}

bool Session_LoginWithClientToken (Mber::MberSession* const session, Mber::MberSession* const client_session, const char* const authorization_token, const char* const client_type, const int ttl, const char* const* const required_entity_ids, const char* const* const required_entity_types, const int required_entity_count, Mber::Status& status)
{
	if (!session || !client_session || !authorization_token || !client_type) {
		return false;
	}

	// Convert the given entity IDs and types to a list of entity pointers.
	typedef std::list<Mber::EntityPointer> EntityPointerList;
	typedef MberPtr<EntityPointerList> MberEntityPointerList;

	if ((required_entity_ids && !required_entity_types) || (required_entity_types && !required_entity_ids)) {
		status = Mber::Status_Failed;
		session->setLastError("Both required_entity_types and required_entity_ids must be provided.");
		return false;
	}

	EntityPointerList entities;
	for (int i = 0; i < required_entity_count; ++i) {
		Mber::EntityPointer entity;
		entity.entityId = required_entity_ids[i];
		try {
			entity.entityType = Mber::stringToEntityType(required_entity_types[i]);
		} catch (const std::invalid_argument& e) {
			std::stringstream message;
			message << "The entity type " << e.what() << " is invalid.";
			status = Mber::Status_Failed;
			session->setLastError(message.str());
			return false;
		}
		entities.push_back(entity);
	}

	MberEntityPointerList entityList;
	if (!entities.empty()) {
		entityList = MberEntityPointerList(new EntityPointerList(entities));
	}

	ClientToken::Create::Request request(authorization_token, client_type, Mber::MberPtr<int>(new int(ttl)), entityList);
	MberPtr<ClientToken::Create::Response> rsp = session->execute(request);
	if (rsp.isNull()) {
		return false;
	}

	status = rsp->status;
	session->setLastError(rsp->errorMessage);

	client_session->setLastError(rsp->errorMessage);
	client_session->setLoggedIn(status == Mber::Status_Success);
	if (!rsp->clientToken.isNull()) {
		client_session->setToken(*rsp->clientToken);
	}
	if (!rsp->profileId.isNull()) {
		client_session->setProfileId(*rsp->profileId);
	}
	if (!rsp->accountId.isNull()) {
		client_session->setAccountId(*rsp->accountId);
	}
	if (!rsp->displayname.isNull()) {
		client_session->setDisplayName(*rsp->displayname);
	}
	if (!rsp->ownerHas.isNull() && (*rsp->ownerHas).size() > 0) {
		const std::list<Mber::EntityPointer>& ownerHas = *rsp->ownerHas;
		MBER_ENTITY_POINTER_LIST* ownedEntities = EntityPointerList_Init();
		for (std::list<Mber::EntityPointer>::const_iterator itr = ownerHas.begin(); itr != ownerHas.end(); ++itr) {
			MBER_ENTITY_POINTER* entity = EntityPointer_Init();
			EntityPointer_SetId(entity, itr->entityId.c_str());
			EntityPointer_SetType(entity, Mber::EntityTypeToString(itr->entityType).c_str());
			if (!itr->name.isNull()) {
				EntityPointer_SetName(entity, (*itr->name).c_str());
			}
			EntityPointerList_Push(ownedEntities, entity);
		}
		client_session->setOwnedEntities(ownedEntities);
	}

	return true;
}

void Session_Create (Mber::MberSession **session, const char *uri)
{
	*session = new Mber::MberSession(uri);
}

void Session_Destroy (Mber::MberSession* session)
{
  delete session;
  session = NULL;
}

const char *Session_GetToken (Mber::MberSession *session)
{
	if (!session) {
		return 0;
	}
	// TODO: Fix this. Returing pointers to std::string is less than ideal.
	const std::string* const token = session->getToken();
	if (!token) {
		return 0;
	}
	return token->c_str();
}

const char* const Session_GetRefreshToken (const Mber::MberSession* const session)
{
  if (!session) {
    return NULL;
  }
  return session->getRefreshToken();
}

bool Session_GetAuthorizationToken (Mber::MberSession* const session, const char* const client_id, char* const authorization_token)
{
  if (!session || !client_id || !authorization_token) {
    return false;
  }

  const char* const refreshToken = Session_GetRefreshToken(session);
  if (!refreshToken) {
    return false;
  }

  EntityIDPtr client = makeEntityID(client_id);
  if (client.isNull()) {
	  return false;
  }

  AuthorizationToken::Create::Request request(*client, NULL, new std::string(refreshToken), NULL, NULL, NULL);
  MberPtr<AuthorizationToken::Create::Response> response = session->execute(request);
  if (response->status != Mber::Status_Success) {
    return false;
  }

  MberPtr<std::string> authToken = response->authorization_code;
  if (authToken.isNull()) {
    return false;
  }

  // +1 to account for the '\0' terminator on the string.
  const size_t length = authToken->length() + 1;
  memcpy(authorization_token, authToken->c_str(), length);
  return true;
}

bool Session_GetClientToken (Mber::MberSession* const session, const char* const authorization_token, const char* const client_type, const int ttl, const char* const* const required_entity_ids, const char* const* const required_entity_types, const int required_entity_count, char* const client_token, const int client_token_size, Mber::Status& status)
{
	if (!session || !authorization_token || !client_type || !client_token || client_token_size <= 0) {
		return false;
	}

	// Convert the given entity IDs and types to a list of entity pointers.
	typedef std::list<Mber::EntityPointer> EntityPointerList;
	typedef MberPtr<EntityPointerList> MberEntityPointerList;

	if ((required_entity_ids && !required_entity_types) || (required_entity_types && !required_entity_ids)) {
		status = Mber::Status_Failed;
		session->setLastError("Both required_entity_types and required_entity_ids must be provided.");
		return false;
	}

	EntityPointerList entities;
	for (int i = 0; i < required_entity_count; ++i) {
		Mber::EntityPointer entity;
		entity.entityId = required_entity_ids[i];
		try {
			entity.entityType = Mber::stringToEntityType(required_entity_types[i]);
		} catch (const std::invalid_argument& e) {
			std::stringstream message;
			message << "The entity type " << e.what() << " is invalid.";
			status = Mber::Status_Failed;
			session->setLastError(message.str());
			return false;
		}
		entities.push_back(entity);
	}

	MberEntityPointerList entityList;
	if (!entities.empty()) {
		entityList = MberEntityPointerList(new EntityPointerList(entities));
	}

	ClientToken::Create::Request request(authorization_token, client_type, Mber::MberPtr<int>(new int(ttl)), entityList);
	MberPtr<ClientToken::Create::Response> rsp = session->execute(request);
	if (rsp.isNull()) {
		return false;
	}

	status = rsp->status;
	session->setLastError(rsp->errorMessage);

	if (!rsp->clientToken.isNull()) {
		mber_strcpy(client_token, client_token_size, *rsp->clientToken);
	}

	return true;
}

const char *Session_GetProfileId (Mber::MberSession *session)
{
	if (!session) {
		return 0;
	}
	// TODO: Fix this. Returing pointers to std::string is less than ideal.
	const std::string* const profile = session->getProfileId();
	if (!profile) {
		return 0;
	}
	return profile->c_str();
}

const char* const Session_GetAccountId(const Mber::MberSession* const session)
{
	if (!session) {
		return 0;
	}
	return session->getAccountId();
}

const char* const Session_GetLastError(const Mber::MberSession* const session)
{
	if (!session) {
		return 0;
	}
	return session->getLastError();
}

const char* const Session_GetDisplayName(const Mber::MberSession* const session)
{
	if (!session) {
		return 0;
	}
	return session->getDisplayName();
}

const MBER_ENTITY_POINTER_LIST* const Session_GetOwnedEntities(const Mber::MberSession* const session)
{
	if (session) {
		return session->getOwnedEntities();
	}
	return 0;
}

int Base64Encode ( const char* buffer, int size, char* out_buffer, int out_size)
{
	if (!buffer || size <= 0 || !out_buffer || out_size <= 0) {
		return 0;
	}
	const std::string encoded = Mber::base64Encode(buffer, size);
	// +1 to account for the terminating '\0' character.
	const int encoded_size = (int)encoded.length() + 1;
	if (encoded_size > out_size) {
		return 0;
	}
	memcpy(out_buffer, encoded.c_str(), encoded_size);
	// -1 to return the length of the string.
	return encoded_size - 1;
};
