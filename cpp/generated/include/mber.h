//
// mber.h
//
// This file is generated. Do not edit.
//
// Implementation of the C++ Mber API using the Mber REST interface.
//
// Copyright (c) 2012-2013, FirePub, Inc. All Rights Reserved.
//

#pragma once

#include <stdint.h>
#include <iostream>
#include <list>

extern "C" {
  struct MBER_ENTITY_POINTER_LIST;
}

namespace Mber{
    class MberRefCounter{
        private:
            int count;
        public:
            void AddRef(){ count++; };
            int Release(){ return --count; };
    };
    template<typename T> class MberPtr{
        private:
            T* _ptr;
            MberRefCounter* _ref;
        public:
            MberPtr(){
                _ptr = NULL;
                _ref = new MberRefCounter();
                _ref->AddRef();
            };
            MberPtr(T* ptr){
                _ref = new MberRefCounter();
                _ref->AddRef();
                _ptr = ptr;
            };
            MberPtr(const MberPtr<T>& ptr){
                _ptr = ptr._ptr;
                _ref = ptr._ref;
                _ref->AddRef();
            };
            ~MberPtr(){
                if(_ref->Release() == 0){
                    if( _ptr != NULL ){
                        delete _ptr;
                    }
                    delete _ref;
                }
            };
            T& operator* (){ return *_ptr; };
            const T& operator* () const { return *_ptr; };
            T* operator-> (){ return _ptr; };
            const T* const operator-> () const { return _ptr; };
            bool isNull(){ return _ptr == NULL; };
            bool isNull() const { return _ptr == NULL; };
            MberPtr<T>& operator = (const MberPtr<T>& ptr){
                if(this != &ptr){
                    if(_ref->Release() == 0){
                        if( _ptr != NULL ){
                            delete _ptr;
                        }
                        delete _ref;
                    }
                    
                    _ptr = ptr._ptr;
                    _ref = ptr._ref;
                    _ref->AddRef();
                }
                return *this;
            };
    };

    // Structure declarations
	struct CallingContext;
	struct CustomCountField;
	struct EntityID;
	struct EntityPointer;
	struct ErrorResult;
	struct EventCluster;
	struct EventEnvelope;
	struct Metric;
	struct Permission;
	struct ProcessEvent;
	struct ProcessList;
	struct Property;
	struct Token;
	struct Count;

	struct FuzzyValue;
	struct PrefixValue;
	struct Query;
	struct QueryValue;

	struct ReplicationOperation;
	struct SchemaVersion;

	struct Account;
	struct AnonymousUpgrade;
	struct Application;
	struct ApplicationShardAssignment;
	struct AutomaticRoleAssignment;
	struct Build;
	struct ForgotPassword;
	struct ForgotUsername;
	struct IPFilter;
	struct Login;
	struct PasswordReset;
	struct Persona;
	struct Profile;
	struct ProfileAddress;
	struct ProfileGroup;
	struct ProfileReindex;
	struct Role;
	struct RoleAssignment;
	struct SteamApplication;
	struct SteamSyncEvent;

	struct AchievementDefinition;
	struct AchievementInstance;
	struct AchievementPropertyDefinition;
	struct Campaign;
	struct Definition;
	struct DigitalGoodDefinition;
	struct DigitalGoodInstance;
	struct DigitalGoodPropertyDefinition;
	struct EarnedAchievements;
	struct EntitlementInstance;
	struct EntitlementPropertyDefinition;
	struct Keys;
	struct RedemptionEvent;
	struct Reward;

	struct CDNConfig;
	struct CDNSyncEvent;
	struct DataEvent;
	struct Directory;
	struct Document;
	struct DocumentHistoryConfiguration;
	struct DocumentReindex;
	struct DocumentTemplate;
	struct DocumentVersion;
	struct S3BucketConfig;
	struct TemplateField;

	struct Provider;

	struct EventPointer;
	struct ReconciledEvent;
	struct AvailableEvent;

	struct AdyenCallback;
	struct Affiliate;
	struct BoaCompraCallback;
	struct Catalog;
	struct DeductionRule;
	struct EntityTotal;
	struct Invoice;
	struct InvoiceActualItem;
	struct InvoiceExpectedItem;
	struct InvoicePurchase;
	struct InvoiceStatusSummary;
	struct MerchantReference;
	struct Offer;
	struct OfferItem;
	struct OfferPurchase;
	struct PaymentProvider;
	struct RealCurrency;
	struct RealMoneyInput;
	struct Referral;
	struct ReferralCount;
	struct ReferralEntityTotals;
	struct Store;
	struct VirtualCurrency;
	struct VirtualCurrencyChange;
	struct VirtualPurchase;
	struct Wallet;
	struct WalletLot;
	struct WalletTotal;

	struct Heartbeat;
	struct Lobby;
	struct Server;

	struct DocumentMessage;
	struct EmailConfig;
	struct EmailMessage;
	struct ReplacementProperty;
	struct StringMessage;

	struct Group;



    // Enum definitions

    // enumeration of all of the possible entity types
    enum EntityType{
        EntityType_Account
        ,EntityType_Profile
        ,EntityType_Application
        ,EntityType_Group
        ,EntityType_Tag
        ,EntityType_Document
        ,EntityType_Any
        ,EntityType_Token
        ,EntityType_Entitlement
        ,EntityType_Role
        ,EntityType_Achievement
        ,EntityType_Metrics
        ,EntityType_Offer
        ,EntityType_RealCurrency
        ,EntityType_Store
        ,EntityType_DigitalGood
        ,EntityType_Cart
        ,EntityType_Invoice
        ,EntityType_Server
        ,EntityType_Email
        ,EntityType_Lobby
        ,EntityType_VirtualCurrency
        ,EntityType_WalletLot
        ,EntityType_DocumentTemplate
        ,EntityType_Catalog
        ,EntityType_AchievementInstance
        ,EntityType_DigitalGoodInstance
        ,EntityType_Directory
        ,EntityType_DocumentLink
        ,EntityType_DirectoryLink
        ,EntityType_BuildProject
        ,EntityType_Build
        ,EntityType_ProfileGroup
        ,EntityType_PaymentProvider
        ,EntityType_SteamApplication
        ,EntityType_Affiliate
        ,EntityType_Campaign
        ,EntityType_Persona
        ,EntityType_CDNConfig
    };
    // enumeration of all of the possible event types
    enum EventType{
        EventType_CREATE
        ,EventType_READ
        ,EventType_UPDATE
        ,EventType_DELETE
        ,EventType_DISABLE
        ,EventType_ENABLE
        ,EventType_START
        ,EventType_STOP
        ,EventType_PAUSE
    };
    // Enumeration of all the possible metric value types
    enum MetricType{
        MetricType_String				// A metric value type of String.
        ,MetricType_Int				// A metric value type of Integer.
        ,MetricType_Long				// A metric value type of Long.
        ,MetricType_Boolean				// A metric value type of Boolean.
        ,MetricType_Double				// A metric value type of Double.
        ,MetricType_StringArray				// A metric value type of String Array.
        ,MetricType_CompositeData				// A metric value type of java management CompositeData.
        ,MetricType_TabularData				// A metric value type of java management TabularData.
    };
    // The type of privilege associated with a permission
    enum PermissionType{
        PermissionType_Create
        ,PermissionType_Read
        ,PermissionType_Update
        ,PermissionType_Delete
        ,PermissionType_Assign
        ,PermissionType_History
    };
    // enumeration of all of the possible response statuses
    enum Status{
        Status_Success				// A successful operation
        ,Status_NotAuthorized				// Failed due to insufficient privileges
        ,Status_TransactionAlreadyApplied				// An operation which is already known to have succeeded
        ,Status_DuplicateTransactionId				// A previously used transaction ID was provided with a mismatching hash
        ,Status_Failed				// A failed operation. The response may structure may contain more details.
        ,Status_Duplicate				// An item already exists in the system
        ,Status_NotFound				// A requested object could not be found
        ,Status_WrongEntityVersion				// A valid entity was referenced with a mismatching entity version
        ,Status_NotAllowed				// Some rules of the API were violated outside of authentication and field validation
        ,Status_PasswordReset				// A password reset process needs to be completed
    };
    // Supported Mber token types
    enum TokenType{
        TokenType_Access
        ,TokenType_Refresh
        ,TokenType_Authorization
        ,TokenType_EmailValidation
        ,TokenType_PasswordReset
        ,TokenType_SingleUse				// An access token that is only valid for one API call.
        ,TokenType_ForgotPassword				// A token that can be used to set a new password.
        ,TokenType_Client				// A token that can provide increased permissions when logging in with a specific client application.
    };
    // Supported OAuth2 token types
    enum AccessTokenType{
        AccessTokenType_Bearer
    };
    // Valid account statuses
    enum AccountStatus{
        AccountStatus_Activated				// Indicates the account has been formally recognized by the system
    };
    // Valid application statuses
    enum ApplicationStatus{
        ApplicationStatus_Activated				// Indicates the application has been formally recognized by the system
        ,ApplicationStatus_Disabled				// Indicates the application is currently disabled. It is reserved to be reused in the future, though it is not currently usable.
        ,ApplicationStatus_Deleted				// Indicates the application is currently deleted. It is no longer usable and has released its name for use.
    };
    // OAuth2 error codes
    enum OauthError{
        OauthError_invalid_request				// The request is missing a required parameter, includes an unsupported parameter value (other than grant type), repeats a parameter, includes multiple credentials, utilizes more than one mechanism for authenticating the client, or is otherwise malformed.
        ,OauthError_invalid_client				// Client authentication failed (e.g. unknown client, no client authentication included, or unsupported authentication method).  The authorization server MAY return an HTTP 401 (Unauthorized) status code to indicate which HTTP authentication schemes are supported.  If the client attempted to authenticate via the &#39;Authorization&#39; request header field, the authorization server MUST respond with an HTTP 401 (Unauthorized) status code, and include the &#39;WWW-Authenticate&#39; response header field matching the authentication scheme used by the client.
        ,OauthError_invalid_grant				// The provided authorization grant (e.g. authorization code, resource owner credentials) or refresh token is invalid, expired, revoked, does not match the redirection URI used in the authorization request, or was issued to another client.
        ,OauthError_unauthorized_client				// The authenticated client is not authorized to use this authorization grant type.
        ,OauthError_unsupported_grant_type				// The authorization grant type is not supported by the authorization server.
        ,OauthError_invalid_scope				// The requested scope is invalid, unknown, malformed, or exceeds the scope granted by the resource owner.
    };
    // Role statuses
    enum PermissionFlags{
        PermissionFlags_SelfOnly				// Indicates the permission applies to self
        ,PermissionFlags_AllowPrivate				// Indicates the permission allows private access
    };
    // Types of addresses that profiles can have.
    enum ProfileAddressType{
        ProfileAddressType_Shipping				// Indicates the address is a physical location things can be sent to.
    };
    // Available statuses that can be applied to profile groups.
    enum ProfileGroupStatus{
        ProfileGroupStatus_Active				// Indicates the profile group is a group recognized by the system.
        ,ProfileGroupStatus_Disabled				// Indicates that the profile group is disabled. It will persist in storage, but will not be accessible.
        ,ProfileGroupStatus_System				// Denotes a system level group.
    };
    // Valid profile statuses
    enum ProfileStatus{
        ProfileStatus_Activated				// Indicates the profile has been formally recognized by the system
        ,ProfileStatus_Disabled				// Indicates the profile is currently disabled. It is reserved to be reused in the future, though it is not currently usable.
        ,ProfileStatus_Deleted				// Indicates the profile is currently deleted. It is no longer usable and has released its name for use.
        ,ProfileStatus_EmailValidationPending				// Indicates that an email validation message has been sent.
        ,ProfileStatus_PasswordReset				// Indicates that the profile currently requires the password reset process to be completed.
    };
    // Supported profile regions
    enum Region{
        Region_Global
        ,Region_China
    };
    // Role statuses
    enum RoleStatus{
        RoleStatus_Disabled				// Indicates the role is disabled, and thus does not take effect
    };
    // Supported statuses that can be applied to steam users.
    enum SteamUserStatus{
        SteamUserStatus_Active				// Indicates this is an active steam user.
        ,SteamUserStatus_UnlinkPending				// Indicates this user is still currently in the system, but will be unlinked shortly.
    };
    // Entitlement definition status
    enum DefinitionStatus{
        DefinitionStatus_Enabled				// Indicates the entitlement definition is enabled
        ,DefinitionStatus_SelfGrant				// Indicates the entitlement definition can be self granted
    };
    // Indicator of when entitlement properties may be specified
    enum EntitlementPropertyAvailability{
        EntitlementPropertyAvailability_Unavailable
        ,EntitlementPropertyAvailability_Optional
        ,EntitlementPropertyAvailability_Required
    };
    // Specifies the current state of an entitlement instance
    enum EntitlementState{
        EntitlementState_Granted
        ,EntitlementState_Claimed
        ,EntitlementState_Revoked
    };
    // Entitlement types
    enum EntitlementType{
        EntitlementType_Entitlement				// Indicates this is a basic entitlement
        ,EntitlementType_Achievement				// Indicates this is special kind of entitlement called an achievement
        ,EntitlementType_DigitalGood				// Indicates this is special kind of entitlement called granting digital content to a profile
    };
    // Campaign key formats
    enum KeyFormat{
        KeyFormat_Print				// A key suitable for printing
        ,KeyFormat_URL				// A key encoded in a URL
    };
    // The type or provider of a CDN
    enum CDNType{
        CDNType_Highwinds
    };
    // An enumeration of storage devices for data. This enumeration is for internal use only so that migrations to different storage devices can be handled cleanly.
    enum DataStorageLocation{
        DataStorageLocation_Cassandra				// Stores small files in chunks across the cluster.
        ,DataStorageLocation_S3				// Stores files that can be uploaded and downloaded directly from the client. Can store large files.
        ,DataStorageLocation_CDN				// Indicates that this document is configured to sync with a CDN.
    };
    // An enumeration of various statuses that can be set on a document.
    enum DocumentStatus{
        DocumentStatus_Incomplete				// Indicates that a document was not completely uploaded.
        ,DocumentStatus_Invalid				// Indicates that the document no longer conforms to it&#39;s template and needs to be fixed.
        ,DocumentStatus_NotIndexed				// Indicates that the document no longer indexed.
        ,DocumentStatus_SyncPending				// Indicates that a document sync is in progress.
        ,DocumentStatus_SyncFailed				// Indicates that the last sync has failed.
        ,DocumentStatus_SyncComplete				// Indicates that the last sync has completed.
        ,DocumentStatus_SyncEnabled				// Indicates that this document will be automatically synced to its CDNs on update.
    };
    // Applicable field types for a template field
    enum TemplateFieldType{
        TemplateFieldType_Number				// A number field
        ,TemplateFieldType_String				// A string field
        ,TemplateFieldType_Boolean				// A boolean field
        ,TemplateFieldType_Object				// An arbitrary JSON object
    };
    // The types of aggregation available to metric counts
    enum AppCountType{
        AppCountType_SELFONLY				// Used to denote counts for this application only.
        ,AppCountType_INCLUSIVE				// Used to denote counts for this application and all its children.
    };
    // Filters to limit profile history results
    enum ProfileHistoryFilter{
        ProfileHistoryFilter_Profile				// Only show profile related events
        ,ProfileHistoryFilter_VirtualPurchase				// Only show virtual purchase related events
        ,ProfileHistoryFilter_InvoicePurchase				// Only show invoice purchase related events
        ,ProfileHistoryFilter_PasswordReset				// Only show password reset related events
    };
    // Units of time available for metrics analysis
    enum TimeUnit{
        TimeUnit_SECONDS				// Used for counting metrics by the second.
        ,TimeUnit_MINUTES				// Used for counting metrics by the year.
        ,TimeUnit_HOURS				// Used for counting metrics by the hour.
        ,TimeUnit_DAYS				// Used for counting metrics by the day.
        ,TimeUnit_MONTHS				// Used for counting metrics by the month.
        ,TimeUnit_YEARS				// Used for counting metrics by the year.
    };
    // Status of an affiliate
    enum AffiliateStatus{
        AffiliateStatus_Activated				// An active affiliate
        ,AffiliateStatus_Deleted				// A deleted affiliate. Its referrals will not be counted.
    };
    // Supported ISO 4217 Currency Codes
    enum CurrencyCode{
        CurrencyCode_AED				// United Arab Emirates Dirham
        ,CurrencyCode_AFN				// Afghanistan Afghani
        ,CurrencyCode_ALL				// Albania Lek
        ,CurrencyCode_AMD				// Armenia Dram
        ,CurrencyCode_ANG				// Netherlands Antilles Guilder
        ,CurrencyCode_AOA				// Angola Kwanza
        ,CurrencyCode_ARS				// Argentina Peso
        ,CurrencyCode_AUD				// Australia Dollar
        ,CurrencyCode_AWG				// Aruba Guilder
        ,CurrencyCode_AZN				// Azerbaijan New Manat
        ,CurrencyCode_BAM				// Bosnia and Herzegovina Convertible Marka
        ,CurrencyCode_BBD				// Barbados Dollar
        ,CurrencyCode_BDT				// Bangladesh Taka
        ,CurrencyCode_BGN				// Bulgaria Lev
        ,CurrencyCode_BHD				// Bahrain Dinar
        ,CurrencyCode_BIF				// Burundi Franc
        ,CurrencyCode_BMD				// Bermuda Dollar
        ,CurrencyCode_BND				// Brunei Darussalam Dollar
        ,CurrencyCode_BOB				// Bolivia Boliviano
        ,CurrencyCode_BRL				// Brazil Real
        ,CurrencyCode_BSD				// Bahamas Dollar
        ,CurrencyCode_BTN				// Bhutan Ngultrum
        ,CurrencyCode_BWP				// Botswana Pula
        ,CurrencyCode_BYR				// Belarus Ruble
        ,CurrencyCode_BZD				// Belize Dollar
        ,CurrencyCode_CAD				// Canada Dollar
        ,CurrencyCode_CDF				// Congo/Kinshasa Franc
        ,CurrencyCode_CHF				// Switzerland Franc
        ,CurrencyCode_CLP				// Chile Peso
        ,CurrencyCode_CNY				// China Yuan Renminbi
        ,CurrencyCode_COP				// Colombia Peso
        ,CurrencyCode_CRC				// Costa Rica Colon
        ,CurrencyCode_CUC				// Cuba Convertible Peso
        ,CurrencyCode_CUP				// Cuba Peso
        ,CurrencyCode_CVE				// Cape Verde Escudo
        ,CurrencyCode_CZK				// Czech Republic Koruna
        ,CurrencyCode_DJF				// Djibouti Franc
        ,CurrencyCode_DKK				// Denmark Krone
        ,CurrencyCode_DOP				// Dominican Republic Peso
        ,CurrencyCode_DZD				// Algeria Dinar
        ,CurrencyCode_EGP				// Egypt Pound
        ,CurrencyCode_ERN				// Eritrea Nakfa
        ,CurrencyCode_ETB				// Ethiopia Birr
        ,CurrencyCode_EUR				// Euro Member Countries
        ,CurrencyCode_FJD				// Fiji Dollar
        ,CurrencyCode_FKP				// Falkland Islands (Malvinas) Pound
        ,CurrencyCode_GBP				// United Kingdom Pound
        ,CurrencyCode_GEL				// Georgia Lari
        ,CurrencyCode_GGP				// Guernsey Pound
        ,CurrencyCode_GHS				// Ghana Cedi
        ,CurrencyCode_GIP				// Gibraltar Pound
        ,CurrencyCode_GMD				// Gambia Dalasi
        ,CurrencyCode_GNF				// Guinea Franc
        ,CurrencyCode_GTQ				// Guatemala Quetzal
        ,CurrencyCode_GYD				// Guyana Dollar
        ,CurrencyCode_HKD				// Hong Kong Dollar
        ,CurrencyCode_HNL				// Honduras Lempira
        ,CurrencyCode_HRK				// Croatia Kuna
        ,CurrencyCode_HTG				// Haiti Gourde
        ,CurrencyCode_HUF				// Hungary Forint
        ,CurrencyCode_IDR				// Indonesia Rupiah
        ,CurrencyCode_ILS				// Israel Shekel
        ,CurrencyCode_IMP				// Isle of Man Pound
        ,CurrencyCode_INR				// India Rupee
        ,CurrencyCode_IQD				// Iraq Dinar
        ,CurrencyCode_IRR				// Iran Rial
        ,CurrencyCode_ISK				// Iceland Krona
        ,CurrencyCode_JEP				// Jersey Pound
        ,CurrencyCode_JMD				// Jamaica Dollar
        ,CurrencyCode_JOD				// Jordan Dinar
        ,CurrencyCode_JPY				// Japan Yen
        ,CurrencyCode_KES				// Kenya Shilling
        ,CurrencyCode_KGS				// Kyrgyzstan Som
        ,CurrencyCode_KHR				// Cambodia Riel
        ,CurrencyCode_KMF				// Comoros Franc
        ,CurrencyCode_KPW				// Korea (North) Won
        ,CurrencyCode_KRW				// Korea (South) Won
        ,CurrencyCode_KWD				// Kuwait Dinar
        ,CurrencyCode_KYD				// Cayman Islands Dollar
        ,CurrencyCode_KZT				// Kazakhstan Tenge
        ,CurrencyCode_LAK				// Laos Kip
        ,CurrencyCode_LBP				// Lebanon Pound
        ,CurrencyCode_LKR				// Sri Lanka Rupee
        ,CurrencyCode_LRD				// Liberia Dollar
        ,CurrencyCode_LSL				// Lesotho Loti
        ,CurrencyCode_LTL				// Lithuania Litas
        ,CurrencyCode_LVL				// Latvia Lat
        ,CurrencyCode_LYD				// Libya Dinar
        ,CurrencyCode_MAD				// Morocco Dirham
        ,CurrencyCode_MDL				// Moldova Leu
        ,CurrencyCode_MGA				// Madagascar Ariary
        ,CurrencyCode_MKD				// Macedonia Denar
        ,CurrencyCode_MMK				// Myanmar (Burma) Kyat
        ,CurrencyCode_MNT				// Mongolia Tughrik
        ,CurrencyCode_MOP				// Macau Pataca
        ,CurrencyCode_MRO				// Mauritania Ouguiya
        ,CurrencyCode_MUR				// Mauritius Rupee
        ,CurrencyCode_MVR				// Maldives (Maldive Islands) Rufiyaa
        ,CurrencyCode_MWK				// Malawi Kwacha
        ,CurrencyCode_MXN				// Mexico Peso
        ,CurrencyCode_MYR				// Malaysia Ringgit
        ,CurrencyCode_MZN				// Mozambique Metical
        ,CurrencyCode_NAD				// Namibia Dollar
        ,CurrencyCode_NGN				// Nigeria Naira
        ,CurrencyCode_NIO				// Nicaragua Cordoba
        ,CurrencyCode_NOK				// Norway Krone
        ,CurrencyCode_NPR				// Nepal Rupee
        ,CurrencyCode_NZD				// New Zealand Dollar
        ,CurrencyCode_OMR				// Oman Rial
        ,CurrencyCode_PAB				// Panama Balboa
        ,CurrencyCode_PEN				// Peru Nuevo Sol
        ,CurrencyCode_PGK				// Papua New Guinea Kina
        ,CurrencyCode_PHP				// Philippines Peso
        ,CurrencyCode_PKR				// Pakistan Rupee
        ,CurrencyCode_PLN				// Poland Zloty
        ,CurrencyCode_PYG				// Paraguay Guarani
        ,CurrencyCode_QAR				// Qatar Riyal
        ,CurrencyCode_RON				// Romania New Leu
        ,CurrencyCode_RSD				// Serbia Dinar
        ,CurrencyCode_RUB				// Russia Ruble
        ,CurrencyCode_RWF				// Rwanda Franc
        ,CurrencyCode_SAR				// Saudi Arabia Riyal
        ,CurrencyCode_SBD				// Solomon Islands Dollar
        ,CurrencyCode_SCR				// Seychelles Rupee
        ,CurrencyCode_SDG				// Sudan Pound
        ,CurrencyCode_SEK				// Sweden Krona
        ,CurrencyCode_SGD				// Singapore Dollar
        ,CurrencyCode_SHP				// Saint Helena Pound
        ,CurrencyCode_SLL				// Sierra Leone Leone
        ,CurrencyCode_SOS				// Somalia Shilling
        ,CurrencyCode_SRD				// Suriname Dollar
        ,CurrencyCode_STD				// São Tomé and Príncipe Dobra
        ,CurrencyCode_SVC				// El Salvador Colon
        ,CurrencyCode_SYP				// Syria Pound
        ,CurrencyCode_SZL				// Swaziland Lilangeni
        ,CurrencyCode_THB				// Thailand Baht
        ,CurrencyCode_TJS				// Tajikistan Somoni
        ,CurrencyCode_TMT				// Turkmenistan Manat
        ,CurrencyCode_TND				// Tunisia Dinar
        ,CurrencyCode_TOP				// Tonga Pa&#39;anga
        ,CurrencyCode_TRY				// Turkey Lira
        ,CurrencyCode_TTD				// Trinidad and Tobago Dollar
        ,CurrencyCode_TVD				// Tuvalu Dollar
        ,CurrencyCode_TWD				// Taiwan New Dollar
        ,CurrencyCode_TZS				// Tanzania Shilling
        ,CurrencyCode_UAH				// Ukraine Hryvna
        ,CurrencyCode_UGX				// Uganda Shilling
        ,CurrencyCode_USD				// United States Dollar
        ,CurrencyCode_UYU				// Uruguay Peso
        ,CurrencyCode_UZS				// Uzbekistan Som
        ,CurrencyCode_VEF				// Venezuela Bolivar
        ,CurrencyCode_VND				// Viet Nam Dong
        ,CurrencyCode_VUV				// Vanuatu Vatu
        ,CurrencyCode_WST				// Samoa Tala
        ,CurrencyCode_XAF				// Communauté Financière Africaine (BEAC) CFA Franc BEAC
        ,CurrencyCode_XCD				// East Caribbean Dollar
        ,CurrencyCode_XDR				// International Monetary Fund (IMF) Special Drawing Rights
        ,CurrencyCode_XOF				// Communauté Financière Africaine (BCEAO) Franc
        ,CurrencyCode_XPF				// Comptoirs Français du Pacifique (CFP) Franc
        ,CurrencyCode_YER				// Yemen Rial
        ,CurrencyCode_ZAR				// South Africa Rand
        ,CurrencyCode_ZMW				// Zambia Kwacha
        ,CurrencyCode_ZWD				// Zimbabwe Dollar
    };
    // Indicates how to prioritize the wallet lots when deducting currency
    enum DeductionRulePriority{
        DeductionRulePriority_Most				// Prioritize the property starting with the greatest value
        ,DeductionRulePriority_Least				// Prioritize the property starting with the smallest value
    };
    // Indicates which property
    enum DeductionRuleProperty{
        DeductionRuleProperty_Recent				// Organize the lots by time created
        ,DeductionRuleProperty_Expensive				// Organize the lots by real money value spent to initially acquire them
    };
    // Status of an invoice item
    enum InvoiceItemStatus{
        InvoiceItemStatus_Waiting				// An invoice item which is waiting to be processed
        ,InvoiceItemStatus_Processing				// An invoice item which is currently being processed
        ,InvoiceItemStatus_Failed				// An invoice item which failed to process
        ,InvoiceItemStatus_Completed				// An invoice item which successfully processed
        ,InvoiceItemStatus_Refunded				// An invoice item which has been successfully revoked due to a refund.
    };
    // Retail source of an invoice
    enum InvoiceSource{
        InvoiceSource_OnMber				// An invoice purchased through an mber source.
        ,InvoiceSource_OnSteam				// An invoice purchased through a steam source.
    };
    // Status of an invoice
    enum InvoiceStatus{
        InvoiceStatus_Open				// An invoice which is not yet finalized and may be modified
        ,InvoiceStatus_Collecting				// An invoice which is currently processing inputs
        ,InvoiceStatus_Fulfilling				// An invoice which is currently delivering outputs
        ,InvoiceStatus_Failed				// An invoice which is resolved in a failed state
        ,InvoiceStatus_Completed				// An invoice which is resolved in a successful state
        ,InvoiceStatus_Refunded				// An invoice which is resolved in a refunded state
    };
    // Enumeration of supported RMT providers
    enum RealMoneyTransactionProvider{
        RealMoneyTransactionProvider_AmazonFPS				// Amazon FPS
        ,RealMoneyTransactionProvider_Adyen				// Adyen payment provider
        ,RealMoneyTransactionProvider_Steam				// Steam payment provider
        ,RealMoneyTransactionProvider_BoaCompra				// BoaCompra payment provider
    };
    // Status of a currency
    enum VirtualCurrencyStatus{
        VirtualCurrencyStatus_Deleted				// A deleted currency
        ,VirtualCurrencyStatus_DisableSpending				// A virtual currency which cannot be spent
        ,VirtualCurrencyStatus_DisableEarning				// A virtual currency which cannot be earned
    };
    // Server status
    enum ServerState{
        ServerState_Unknown				// Indicates the server state is currently unknown
        ,ServerState_Online				// Indicates the server is currently online
    };

    // Struct definitions

    // the calling context for all system packets
    struct CallingContext{
        std::string correlationId;				// an id to correlate multiple requests across
        std::string transactionId;				// the id specific to this request transaction
    };
    // Event wrapper to push custom event data into the application&#39;s metrics
    struct CustomCountField{
        std::string name;				// The name of the custom count field
        long count;				// The value of the custom count field
        Mber::MberPtr<uint64_t > time;				// The timestamp that the custom count field should be applied to.
    };
    // Entity ID which encapsulates either a uuid or unique name
    struct EntityID{
        Mber::MberPtr<std::string > id;				// The uuid identifier of the entity
        Mber::MberPtr<std::string > name;				// The unique name identifier of the entity
    };
    // Representation of an entity pointer
    struct EntityPointer{
        std::string entityId;				// The unique identifier of the entity
        Mber::EntityType entityType;				// The type of the entity
        Mber::MberPtr<std::string > name;				// The optional name of the entity. Not required when used as an input to an api. May be returned in the api results.
    };
    // An optional structure returned on requests that do not have a Success status
    struct ErrorResult{
        std::string message;				// An optional error message indicating why the status of the response was not Success.
        Mber::MberPtr<std::list<std::string> > fields;				// An optional list of fields that were involved in producing the error result.
    };
    // A structure to aggregate multiple events of a type into a single event.
    struct EventCluster{
        std::string eventName;				// The name of the event that is aggregated in this structure.
        Mber::MberPtr<std::string > applicationId;				// The application of the aggregated events.
        std::list<Mber::Count> totals;				// The total number of events captured by this cluster.
        Mber::MberPtr<std::list<Mber::EventEnvelope> > events;				// The variant and count fields for the type of event aggregated over time.
        Mber::MberPtr<std::list<Mber::CustomCountField> > counts;				// The variant and count fields for the type of event aggregated over time.
    };
    // the envelope for all events
    struct EventEnvelope{
        Mber::CallingContext callingContext;				// the calling context the event was issued under
        std::string eventId;				// the Id of this event
        Mber::EventType eventType;				// the type of this event
        uint64_t created;				// the timestamp when the event was created
        std::string decoderClass;				// the class of the decoder that can deserialize the payload
        std::string payload;				// the binary event payload
        Mber::MberPtr<std::string > version;				// the mber version this event was created in
        Mber::MberPtr<std::list<Mber::Property> > properties;				// any arbitrary optional properties for the event that need to be known to deserialize it properly
    };
    // The structure for jmx and system metrics
    struct Metric{
        std::string name;				// The name of the metric from the originating system.
        std::string objectName;				// The name of the object the metric belongs to.
        Mber::MetricType metricType;				// The type of the underlying metric
        Mber::MberPtr<std::string > metricValue;				// The value of the metric in binary format.
        std::string metricEventName;				// The unique name of the metric in the mber metric sytem.
        long metricCount;				// The count of this metric. If possible, this will be metricValue converted into a Long value, otherwise it will be 0.
    };
    // Structural representation of an atomic permission
    struct Permission{
        Mber::EntityType entityType;
        std::list<Mber::PermissionType> permissions;
        Mber::MberPtr<bool > selfOnly;
        Mber::MberPtr<bool > allowPrivate;
    };
    // A process event
    struct ProcessEvent{
        std::string name;				// The name of the process
        std::string group;				// The group the process belongs to
        Mber::MberPtr<std::list<Mber::Property> > properties;				// The custom configuration for the process
        Mber::MberPtr<bool > infinite;				// Whether the process should be scheduled to run forever.
    };
    // An event emitted when a server&#39;s configured processes change.
    struct ProcessList{
        Mber::MberPtr<std::list<std::string> > processesAdded;				// The processes added to the server
        Mber::MberPtr<std::list<std::string> > processesRemoved;				// The processes removed from the server
        Mber::MberPtr<std::string > serverId;				// The unique mber identifier of the server that the process list changed within
    };
    // Representation of key value property pair
    struct Property{
        std::string key;
        std::string value;
    };
    // Representation of any Mber token
    struct Token{
        std::string id;
        Mber::TokenType tokenType;
        uint64_t expires;
        Mber::MberPtr<std::string > clientRedirectUri;
        Mber::MberPtr<std::string > accountId;
        Mber::MberPtr<std::string > profileId;
        Mber::MberPtr<std::list<Mber::Permission> > permissions;
        int shard;				// Shard to use when creating data with this token
        int masterShard;				// The application master shard to use when creating data with this token
        Mber::MberPtr<std::string > email;				// Email address optionally bound to the token
        Mber::MberPtr<std::string > displayname;				// The display name of the profile
        Mber::MberPtr<std::string > clientType;				// Required to qualify the client token.  Only one token of the given type is allowed at any time.
        Mber::MberPtr<std::string > clientProfile;				// An optional profile id that may modify the token permissions based on the token type
        std::string userSource;				// An optional type to identify the source of the user. Defaults to mber.
        Mber::MberPtr<std::string > grantType;				// authorization_code, password, refresh_token
        Mber::MberPtr<std::list<std::string> > createdFrom;				// The ids of the tokens used in the creation of this token
        Mber::MberPtr<std::string > refreshToken;				// The refresh token id paired with this token
        Mber::MberPtr<uint64_t > created;				// The timestamp of this token&#39;s creation
        Mber::MberPtr<std::string > steamId;				// The corresponding steam account id for this user.
        Mber::MberPtr<std::string > ip;				// The IP address the request to create the token came from.
        Mber::EntityID applicationId;
    };
    // Representation of a metric count
    struct Count{
        uint64_t time;
        long count;
    };
    // Fuzzy match value
    struct FuzzyValue{
        std::string value;				// The query value to match
        Mber::MberPtr<double > minSimilarity;				// The minimum similarity threshold to match the query value between 0 (inclusive) and 1 (exclusive). A fuzzy match is found if the Levenshtein distance is less than length(term) * minSimilarity
    };
    // Prefix match value
    struct PrefixValue{
        std::string value;				// The query value to match
    };
    // Search Query
    struct Query{
        std::string field;				// Name of the field in question
        Mber::MberPtr<double > from;				// From value
        Mber::MberPtr<double > to;				// To value
        Mber::MberPtr<std::list<Mber::QueryValue> > in;				// Expected value is somewhere in the set
        Mber::MberPtr<std::list<Mber::Query> > thisAnd;				// This query and all inner query must match
        Mber::MberPtr<std::list<Mber::Query> > thisOr;				// This query or any inner query must match
        Mber::MberPtr<Mber::PrefixValue > prefix;				// Expected value has the given value as a prefix
        Mber::MberPtr<Mber::FuzzyValue > like;				// Expected value is similar to the given value
    };
    // Search Query value
    struct QueryValue{
        Mber::MberPtr<std::string > stringValue;				// String value
        Mber::MberPtr<bool > booleanValue;				// Boolean value
        Mber::MberPtr<double > numberValue;				// Double value
    };
    // Contains all the model operation information required to replicate a SQL query on another server
    struct ReplicationOperation{
        std::string id;				// A unique id for this replication event.
        std::string applicationId;				// The application this replication operation applies to.
        int masterShardId;				// The shard the original sql statement was executed against
        std::string schema;				// The schema the sql statement should be executed against
        std::string sql;				// The sql statement to execute
    };
    // Holds schema version information
    struct SchemaVersion{
        std::string name;				// The name of the schema
        std::string version;				// The version of the schema
        std::string comment;				// Additional information about this schema version entry
        uint64_t created;				// The time this schema version was created
        uint64_t updated;				// The last time this schema version was updated
        int shard;				// The shard id of the schema
    };
    // Representation of an account
    struct Account{
        std::string accountId;				// The id of the account
        std::string masterProfileId;				// The id of the master profile on the account
        std::list<Mber::AccountStatus> status;				// Set of statuses set on the account
        Mber::MberPtr<std::string > email;				// The email address of the account to create
        Mber::MberPtr<std::string > password;				// The password for the account
        Mber::MberPtr<uint64_t > dateOfBirth;				// The user&#39;s date of birth
        Mber::MberPtr<Mber::Region > region;				// The region the user is coming from
        Mber::MberPtr<std::string > username;				// The username of the profile
        Mber::MberPtr<std::string > displayname;				// The display name of the profile
        Mber::MberPtr<std::string > sourceApplication;				// The application from which the request is originating
        Mber::MberPtr<std::string > sourceReferredUrl;				// The referrence url from which the request is originating
        Mber::MberPtr<bool > forcePasswordReset;				// If specified as true, the account will be required to change password upon logging in. This is preferred when creating an account on behalf of another user.
        Mber::MberPtr<long > steamId;				// The corresponding steam account id for this user.
        Mber::MberPtr<Mber::EntityPointer > referrer;				// The account or affiliate which referred this new account
    };
    // An indication of an upgrade of an anonymous account.
    struct AnonymousUpgrade{
        std::string profileId;				// The id of the profile being upgraded.
        std::string displayName;				// The current display name of the profile being upgraded.
        std::string email;				// The current email address of the profile being upgraded. Also the email address the anon-uprade email will be sent to.
        std::string readToken;				// The token with profile read permissions for this user.
        std::string updateToken;				// The token with profile update permissions for this user.
        std::string applicationContext;				// The application in which the anonymous user upgrade email template lives
    };
    // Representation of an application
    struct Application{
        std::string applicationId;				// The id of the application
        std::string name;				// The name of the application
        Mber::MberPtr<std::string > alias;				// The optional alias of the application. The alias must be unique within Mber.
        Mber::MberPtr<std::string > parent;				// The parent application for this application
        Mber::MberPtr<std::string > redirectUri;				// The redirect uri of the application
        Mber::MberPtr<std::string > version;				// The application version, as defined by the application creator
        Mber::MberPtr<std::string > creator;				// The creator of the application
        Mber::MberPtr<std::list<Mber::Application> > applications;				// The child applications of this application
        Mber::MberPtr<Mber::ApplicationStatus > status;				// The status of the application
        int maxPersonas;				// The maximum number of personas a profile can have in this application
        bool uniquePersonas;				// Controls whether persona names have to be unique within this application
    };
    // Describes the assignment of a profile to a shard within an application
    struct ApplicationShardAssignment{
        std::string profileId;				// The id of the profile which has been assigned to a shard
        std::string applicationId;				// The id of the application the shard was assigned within
        int shard;				// The assigned shard
        Mber::MberPtr<int > processedCount;				// A count of the number of times we have tried to process this shard assignment
    };
    // Representation of an mber Role assignment trigger
    struct AutomaticRoleAssignment{
        Mber::EntityType entityType;				// The entity type that will trigger a role assignment on creation
        std::string role;				// The id of the role to assign in context of the created entity
    };
    // Representation of build version
    struct Build{
        std::string number;				// The build number of mber
        std::string commit;				// The last git commit of this version of Mber
        Mber::MberPtr<std::list<Mber::SchemaVersion> > schemas;				// Data about the schemas this instance of mber is connected to
    };
    // An indication of a request for a user&#39;s forgotten password.
    struct ForgotPassword{
        std::string username;				// The user name used to look up corresponding profiles.
        std::string displayname;				// The displayname in the found profile.
        std::string email;				// The email used to look up corresponding profiles.
        std::string tokenId;				// The ID of the token that can be redeemed to reset the password.
        std::string profileId;				// The ID of the profile for the user name and email provided.
        Mber::EntityID applicationId;				// The application ID to use to look up the forgotten password email template.
    };
    // An indication of a request for a user&#39;s forgotten username.
    struct ForgotUsername{
        std::string email;				// The email address used to look up corresponding profiles.
        std::string username;				// The username found for the email provided.
        std::string profileId;				// The id of the profile for the email provided.
        std::string displayname;				// The displayname of the profile for the email provided.
        std::string applicationId;				// The application id to use to look up the Forgot Username email template.
    };
    // A representation of an IP address filter
    struct IPFilter{
        std::list<std::string> ipAddresses;				// A set of IP addresses
        Mber::EntityID role;				// The role to which this filter applies
    };
    // Representation of an attempt to login to mber
    struct Login{
        Mber::Status status;				// the status of the login attempt
        Mber::MberPtr<Mber::Token > token;
        Mber::MberPtr<std::string > requested_scope;
        Mber::MberPtr<std::string > applicationId;
        Mber::MberPtr<std::string > username;
        Mber::MberPtr<std::string > redirect_uri;
        Mber::MberPtr<std::string > userSource;
    };
    // Indication of a password reset process
    struct PasswordReset{
        std::string profileId;				// The id of the profile which is undergoing a password reset
        std::string tokenId;				// The password reset token generated for this instance
        std::string applicationContext;				// The application context in which the reset is occurring. This will determine how messaging is performed.
    };
    // A persona tied to a profile on an application in Mber
    struct Persona{
        std::string personaId;				// The ID of the persona
        std::string profileId;				// The ID of the profile this persona belongs to
        std::string applicationId;				// The ID of the application the persona is under
        std::string displayname;				// The visible name of the persona
    };
    // Representation of a profile
    struct Profile{
        std::string profileId;				// The id of the profile
        std::string accountId;				// The id of the account the profile belongs to
        Mber::MberPtr<Mber::Region > region;				// The region the user is coming from
        Mber::MberPtr<std::string > username;				// The username of the profile
        std::string displayname;				// The display name of the profile
        Mber::MberPtr<std::string > email;				// The email address of the profile
        Mber::MberPtr<std::string > unvalidated_email;				// The unvalidated email address of the profile
        Mber::MberPtr<uint64_t > dateOfBirth;				// The user&#39;s date of birth
        Mber::MberPtr<std::list<Mber::ProfileStatus> > status;				// Set of statuses set on the profile
        Mber::MberPtr<std::string > sourceApplication;				// The application from which the request is originating
        Mber::MberPtr<std::string > sourceReferredUrl;				// The referrence url from which the request is originating
        Mber::MberPtr<std::string > steamId;				// The corresponding steam account id for this user.
        Mber::MberPtr<Mber::EntityPointer > referrer;				// The account or affiliate which referred this new account
    };
    // Representation of the address associated with a profile
    struct ProfileAddress{
        std::string profileId;				// The ID of the profile
        Mber::ProfileAddressType addressType;				// The type of address e.g. billing, shipping, etc.
        Mber::MberPtr<std::string > houseNumberOrName;				// The house number (or name)
        Mber::MberPtr<std::string > street;				// The street name
        Mber::MberPtr<std::string > city;				// The city
        Mber::MberPtr<std::string > postalCode;				// The postal/zip code
        Mber::MberPtr<std::string > stateOrProvince;				// The state or province
        Mber::MberPtr<std::string > country;				// The country in ISO 3166-1 alpha-2 format
    };
    // A group of profiles
    struct ProfileGroup{
        std::string id;				// The unique identifier of the group.
        std::string name;				// The creator-defined name of the group.
        Mber::MberPtr<std::string > alias;				// The optional alias of the group.
        std::string applicationId;				// The application this group of profiles is defined in.
        Mber::MberPtr<std::list<Mber::EntityPointer> > members;				// The profiles currently included in this group.
        std::list<Mber::ProfileGroupStatus> status;				// A set of statuses that are currently applied to this group.
        Mber::MberPtr<uint64_t > size;				// The total number of profiles in this profile group.
    };
    // Event triggered by ProfileReindexing API to start the ProfileReindexing process
    struct ProfileReindex{
        std::string applicationId;				// The application to index profiles in
        Mber::MberPtr<bool > deleteIndex;				// Delete the index before reindexing profiles
    };
    // Representation of an mber Role
    struct Role{
        std::string id;				// The id of the role
        Mber::EntityPointer parent;				// The id of the parent object
        std::string name;				// The name of the role
        bool active;				// If true, the role takes effect.
        bool automatic;				// Flag indicating if this role automatically applies to any user of the parent
        bool cascading;				// Flag indicating if this role automatically applies to any user of a child object
        Mber::MberPtr<std::list<Mber::Permission> > permissions;				// Set of permissions that this role grants
        Mber::MberPtr<std::list<Mber::AutomaticRoleAssignment> > automaticAssignments;				// Roles that become automatically granted in the context of a created object
        bool negative;				// Flag indicating if this role negates its defined permissions
    };
    // Representation of an mber Role Assignment
    struct RoleAssignment{
        std::string roleId;				// The role id which has been assigned
        Mber::EntityPointer context;				// The context of the assignment
        Mber::EntityPointer recipient;				// The entity which has been assigned a role
    };
    // A representation of a Steam application
    struct SteamApplication{
        std::string id;				// The unique Mber identifier of the application
        int steamApplicationId;				// The unique Steam identifier of the application
        std::string name;				// Name of the Steam application.
        std::string applicationId;				// Application identifier in which the steam app is defined
        std::string webAPIKey;				// The web api key that will be used for this application
        Mber::MberPtr<int > packageId;				// The steam identifier of the corresponding package for this application.
    };
    // Triggers synchronization of Steam data with Mber data.
    struct SteamSyncEvent{
        Mber::MberPtr<std::string > profileId;				// The id of the profile to synchronize
        Mber::MberPtr<std::string > applicationId;				// The id of the application to synchronize
        Mber::MberPtr<long > steamId;				// The corresponding steam account id for this profile.
        Mber::MberPtr<long > previousSteamId;				// The previous steam id linked to the profile specified. This field will be set if the profile has been unlinked from the steam account.
    };
    // Definition of an achievement
    struct AchievementDefinition{
        std::string definitionId;
        std::string name;
        std::list<Mber::DefinitionStatus> status;
        std::string scope;
        Mber::MberPtr<std::list<Mber::AchievementPropertyDefinition> > properties;
        Mber::MberPtr<std::list<std::string> > categories;
    };
    // Instance of an achievement
    struct AchievementInstance{
        std::string id;
        std::string definitionId;
        Mber::MberPtr<std::string > name;
        Mber::MberPtr<std::string > scope;
        Mber::MberPtr<std::list<Mber::Property> > properties;
        Mber::MberPtr<std::list<std::string> > categories;				// The list of categories this achievement instance falls under.
    };
    // Definition of an achievement property
    struct AchievementPropertyDefinition{
        std::string name;				// The key of the achievement property
        Mber::EntitlementPropertyAvailability onEarn;				// One of Unavailable, Optional, Required denoting if the property needs to be set when earned.
        Mber::MberPtr<std::string > defaultValue;				// The optional default value of the property.
    };
    // Definition of a campaign
    struct Campaign{
        Mber::EntityID campaignId;
        Mber::EntityID applicationId;
        std::string name;
        Mber::EntityID digitalGood;
        Mber::MberPtr<std::string > description;
        Mber::MberPtr<std::string > url;
        Mber::MberPtr<Mber::EntityID > invalidWords;
    };
    // Definition of an entitlement
    struct Definition{
        std::string definitionId;
        std::string name;
        std::list<Mber::DefinitionStatus> status;
        std::string scope;
        bool autoClaim;
        Mber::MberPtr<std::list<Mber::EntitlementPropertyDefinition> > properties;
        Mber::MberPtr<bool > truncated;
        Mber::MberPtr<std::list<Mber::DefinitionStatus> > setStatuses;				// A set of statuses which must be included on the definition in order to be returned
        Mber::MberPtr<std::list<Mber::DefinitionStatus> > unsetStatuses;				// A set of statuses which must *not* be included on the definition in order to be returned
        Mber::MberPtr<std::list<std::string> > redeemableFor;				// List of digital good definitions this good is redeemable for
        Mber::MberPtr<uint64_t > ttl;				// The time in seconds an entitlement created from this definition exists for
        Mber::MberPtr<uint64_t > selfGrantCount;				// The maximum number of times this digital good can be self granted
        Mber::MberPtr<bool > emailOnGrant;				// If true, an email will be sent to the owner when an instance of this digital good is granted.
        Mber::MberPtr<bool > emailOnClaim;				// If true, an email will be sent to the owner when an instance of this digital good is claimed.
        Mber::MberPtr<std::list<Mber::Reward> > redemptionRewards;				// List of reward entities to be rewarded to the owner when claimed by another user.
        Mber::MberPtr<std::list<std::string> > categories;				// List of categories the entitlement falls under.
    };
    // Definition of a digital good
    struct DigitalGoodDefinition{
        std::string definitionId;
        std::string name;
        std::list<Mber::DefinitionStatus> status;
        std::string scope;
        Mber::MberPtr<std::string > documentId;				// The id of the document associated with this digital good, if there is one.
        bool autoClaim;
        Mber::MberPtr<std::list<Mber::DigitalGoodPropertyDefinition> > properties;
        Mber::MberPtr<std::list<Mber::EntityPointer> > redeemableFor;				// List of digital good definitions this good is redeemable for
        Mber::MberPtr<uint64_t > ttl;				// The time in seconds a digital good created from this definition exists for
        Mber::MberPtr<uint64_t > selfGrantCount;				// The maximum number of times this digital good can be self granted
        Mber::MberPtr<bool > emailOnGrant;				// If true, an email will be sent to the owner when an instance of this digital good is granted.
        Mber::MberPtr<bool > emailOnClaim;				// If true, an email will be sent to the owner when an instance of this digital good is claimed.
        Mber::MberPtr<std::list<Mber::Reward> > redemptionRewards;				// List of reward entities to be rewarded to the owner when claimed by another user.
        Mber::MberPtr<std::list<std::string> > categories;				// List of categories the digital good definition falls under.
    };
    // Instance of a digital good
    struct DigitalGoodInstance{
        std::string id;
        std::string definitionId;
        Mber::EntitlementState state;
        Mber::MberPtr<std::string > documentId;				// The id of the document associated with this digital good, if there is one.
        Mber::MberPtr<std::string > name;
        Mber::MberPtr<std::string > scope;
        Mber::MberPtr<std::list<Mber::Property> > properties;
        Mber::MberPtr<Mber::EntityPointer > grantedBy;				// The entity that granted this digital good
        Mber::MberPtr<Mber::EntityPointer > claimedBy;				// The entity that claimed this digital good, if it&#39;s been claimed
        Mber::MberPtr<Mber::EntityPointer > revokedBy;				// The entity that revoked this digital good, if it&#39;s been revoked
        Mber::MberPtr<std::string > redeemedFrom;				// The instance from which this digital good was redeemed
        Mber::MberPtr<uint64_t > expiresOn;				// The time this digital good expires if its definition has a TTL
        Mber::MberPtr<bool > selfGranted;				// True if this digital good was self granted. False otherwise.
        Mber::MberPtr<Mber::EntityPointer > entity;				// The entity that the digital good belongs to.
        Mber::MberPtr<bool > emailOnGrant;				// If true, an email will be sent to the owner when an instance of this digital good is granted.
        Mber::MberPtr<bool > emailOnClaim;				// If true, an email will be sent to the owner when an instance of this digital good is claimed.
        Mber::MberPtr<std::list<std::string> > categories;				// The categories this digital good falls under.
    };
    // Definition of a digital good property
    struct DigitalGoodPropertyDefinition{
        std::string name;				// The key of the digital good property
        Mber::EntitlementPropertyAvailability onGrant;				// One of Unavailable, Optional, Required denoting if the property needs to be set when granting.
        Mber::EntitlementPropertyAvailability onClaim;				// One of Unavailable, Optional, Required denoting if the property needs to be set when claiming..
        Mber::MberPtr<std::string > defaultValue;				// The optional default value of the property.
    };
    // The pairing of a named entity with the achievements it has earned.
    struct EarnedAchievements{
        Mber::EntityPointer entity;				// The entity that has earned the achievements
        std::list<Mber::AchievementInstance> achievements;				// The set of achievements that this entity has earned.
    };
    // Instance of an entitlement
    struct EntitlementInstance{
        std::string id;
        std::string definitionId;
        Mber::MberPtr<std::string > name;
        Mber::MberPtr<std::string > scope;
        Mber::EntityPointer entity;				// The entity that the entitlement belongs to
        Mber::EntitlementState state;
        Mber::MberPtr<std::list<Mber::Property> > properties;
        Mber::MberPtr<Mber::EntityPointer > grantedBy;				// The entity that granted this entitlement
        Mber::MberPtr<Mber::EntityPointer > claimedBy;				// The entity that claimed this entitlement, if it&#39;s been claimed
        Mber::MberPtr<Mber::EntityPointer > revokedBy;				// The entity that revoked this entitlement, if it&#39;s been revoked
        Mber::MberPtr<std::string > redeemedFrom;				// The instance from which this digital good was redeemed
        Mber::MberPtr<uint64_t > expiresOn;				// The time this entitlement expires if its definition has a TTL
        Mber::MberPtr<bool > selfGranted;				// True if this entitlement was self granted. False otherwise.
        Mber::MberPtr<std::list<std::string> > categories;				// The categories this entitlement falls under.
    };
    // Definition of an entitlement property
    struct EntitlementPropertyDefinition{
        std::string name;				// The key of the entitlement property
        Mber::EntitlementPropertyAvailability onGrant;				// One of Unavailable, Optional, Required denoting if the property needs to be set when granting.
        Mber::EntitlementPropertyAvailability onClaim;				// One of Unavailable, Optional, Required denoting if the property needs to be set when claiming..
        Mber::MberPtr<std::string > defaultValue;				// The optional default value of the property.
    };
    // Traces changes to campaigns regarding key generation
    struct Keys{
        Mber::EntityID campaignId;
        Mber::EntityID applicationId;
        int numberOfKeys;
        Mber::EntityID outputDocument;
        Mber::KeyFormat keyFormat;
    };
    // A representation of a redemption event
    struct RedemptionEvent{
        std::string instanceId;				// The instance redeemed
        std::string definitionId;				// The definition id of the redeemed instance
        std::string scope;				// The scope of the instance and definition
        Mber::EntityPointer claimedBy;				// The profile redeeming this instance
        Mber::EntityPointer owner;				// The owner of the instance
        std::list<Mber::Reward> redemptionRewards;				// The list of digital goods or virtual currency the owner of the instance is entitled to
        Mber::EntityPointer grantedBy;				// The granter of this particular instance
    };
    // A representation of some reward entity and amount
    struct Reward{
        Mber::EntityPointer item;				// The item to be rewarded
        double amount;				// The amount of the given entity to reward
    };
    // A CDN configuration
    struct CDNConfig{
        std::string applicationId;				// The application this CDN is configured for
        std::string id;				// The unique id of this CDN configuration
        Mber::CDNType cdnType;				// The type or provider of the CDN
        std::string name;				// The human readable name for this CDN configuration
        Mber::MberPtr<std::string > defaultPath;				// The default path or container that a resource will be synced to; relative to base container where applicable
        Mber::MberPtr<std::string > username;				// The username used for authenticating CDN requests
        Mber::MberPtr<std::string > account;				// The customer/tenant account name. Used for authentication and URI construction
        Mber::MberPtr<std::string > cdnHost;				// The host, if any, where the cached files reside. Used for cache invalidation/purging.
        Mber::MberPtr<std::string > baseContainer;				// The base container for all object paths. This will be excluded from absolute URLs when purging the CDN cache for a given object.
    };
    // Occurs when data is synced with a CDN.
    struct CDNSyncEvent{
        std::string applicationId;				// The application of the entity
        Mber::EntityPointer entity;				// The entity to be synced
        Mber::MberPtr<int > version;				// The version at which this entity was synced
        Mber::MberPtr<Mber::CDNConfig > cdnConfig;				// The CDN configuration to delete from
    };
    // Occurs when data is stored, modified, or deleted.
    struct DataEvent{
        std::string applicationId;				// The unique identifier of the document
        long oldSize;				// The previous size of the data
        long newSize;				// The new size of the data
        long sizeChange;				// newSize minus oldSize - used to track the total data size in the system
    };
    // Representation of a directory
    struct Directory{
        std::string name;				// Name of the directory.
        Mber::MberPtr<std::string > alias;				// Optional alias for the directory.
        std::string directoryId;				// The unique identifier of the directory
        Mber::MberPtr<std::string > parentId;				// The unique identifier of the parent of this directory
        std::string applicationId;				// The unique identifier of the application this directory belongs to
        Mber::MberPtr<bool > isLink;				// True if this directory object represents a link to the actual directory under a different parent.  Not included or false otherwise.
        Mber::MberPtr<std::list<Mber::Directory> > directories;				// The child directories in the directory.
        Mber::MberPtr<std::list<Mber::Document> > documents;				// The documents in the directory.
    };
    // Representation of a document
    struct Document{
        Mber::MberPtr<std::string > name;				// Name of the document being stored.
        Mber::MberPtr<std::string > alias;				// The optional alias of the document. Must be unique within the parent directory.
        std::string documentId;				// The unique identifier of the document
        Mber::MberPtr<int > version;				// The current version of the document.
        Mber::MberPtr<std::string > scope;				// Application associated with the document
        Mber::MberPtr<std::list<std::string> > tags;				// Initial set of tags (eg: Article ) to apply to the data for querying purposes. Each tag can be up to 64 characters in length.
        Mber::MberPtr<std::list<Mber::Property> > properties;				// An arbitrary set of properties that can be applied to a document
        Mber::MberPtr<std::string > documentTemplate;				// Document template to create data with
        Mber::MberPtr<std::string > content;				// JSON content to store and validate against the template
        Mber::MberPtr<std::string > directoryId;				// The unique identifier of the directory of this document
        Mber::MberPtr<bool > isLink;				// True if this document object represents a link to the actual document under a different parent directory.  Not included or false otherwise.
        Mber::MberPtr<uint64_t > size;				// The size of the data stored.
        Mber::MberPtr<bool > canDownload;				// True if this document object can be downloaded by the client through an exernal URL and false otherwise.
        Mber::MberPtr<bool > canEdit;				// True if this document object can be edited in the Mber portal and false otherwise.
        Mber::MberPtr<std::list<Mber::DocumentStatus> > status;				// Represents the current state of the document.
        Mber::MberPtr<int > maxVersionsToKeep;				// The maximum number of versions that will be kept for this document.
        Mber::MberPtr<int > maxTimeToKeep;				// The maxiumum amount of time (in seconds) before old versions of this document will expire.
        Mber::MberPtr<bool > keepAllVersions;				// A flag indicating whether or not all versions of this document are kept.
    };
    // An event to track the change in document history configuration for an application.
    struct DocumentHistoryConfiguration{
        std::string applicationId;				// The application for which the document history configuration has changed.
        Mber::MberPtr<int > maxVersionsToKeep;				// The maximum number of versions to keep for documents in the application.
        Mber::MberPtr<int > maxTimeToKeep;				// The maximum amount of time (in seconds) to keep versions of documents in the application.
        bool keepAllVersions;				// A flag indicating whether or not to keep all versions of documents in the application.
    };
    // Occurs when the DocumentReindex process is started or stopped.
    struct DocumentReindex{
        Mber::EntityID applicationId;				// The ID of the application to index documents in
        Mber::MberPtr<std::string > templateId;				// The ID of the document template to index documents in
        Mber::MberPtr<bool > deleteIndex;				// Flag to determine if the index should be deleted
    };
    // Representation of a document template
    struct DocumentTemplate{
        std::string documentTemplateId;				// ID of the template
        std::string name;				// Name of the template
        Mber::MberPtr<std::string > templateId;				// The defined template
        Mber::MberPtr<std::string > application;				// Referenced entity. If type is a Object, then this may point to a template
        Mber::MberPtr<uint64_t > size;				// The size of the template data
        Mber::MberPtr<int > version;				// The current version of the template.
        Mber::MberPtr<int > maxVersionsToKeep;				// The maximum number of versions that will be kept for this template.
        Mber::MberPtr<int > maxTimeToKeep;				// The maxiumum amount of time (in seconds) before old versions of this template will expire.
    };
    // A structure describing document version data.
    struct DocumentVersion{
        std::string documentId;				// The unique identifier of the document.
        int version;				// The version of the document.
        Mber::MberPtr<uint64_t > created;				// The time this version was created.
    };
    // Representation of a S3 bucket configuration
    struct S3BucketConfig{
        std::string bucketConfigId;				// The unique id of the bucket configuration
        std::string applicationId;				// The application this bucket belongs to
        std::string name;				// The name of the S3 bucket
        std::string accessKey;				// An AWS access key ID
        int urlTtl;				// Used for signing URLs, the time when the signature expires, specified as the number of seconds since the epoch.
    };
    // Representation of a document field
    struct TemplateField{
        Mber::TemplateFieldType fieldType;				// The type of the field
        Mber::MberPtr<std::string > reference;				// Referenced entity. If type is Object, then this may point to a template
        Mber::MberPtr<std::string > templateId;				// If type is Object, then this may be an inline template
        Mber::MberPtr<bool > optional;				// Flag indicating if this field is optional
        Mber::MberPtr<bool > list;				// Flag indicating if this field is a list of the defined type
    };
    // Representation of an OpenId provider that is registered with Mber
    struct Provider{
        std::string name;				// The name of the OpenId provider
        std::string domain;				// The domain of the OpenId provider as registered with Mber
        std::string identity;				// The identity to send to Mber to initiate communication with the OpenId provider. 
    };
    // A pointer to the row and column of a raw event stored in the metrics system
    struct EventPointer{
        std::string name;				// The name of the event in the metrics system.
        int typeId;				// The type of the event stored.
        std::string id;				// The id of the event.
        uint64_t created;				// The timestamp the event was created.
        Mber::MberPtr<std::string > applicationId;				// The application scope in which the event was created.
    };
    // A structure representing a reconciled metric.
    struct ReconciledEvent{
        std::string name;				// The name of the event
        Mber::EventType eventType;				// The type of the event
        std::string applicationId;				// The application in which the event occurred.
        Mber::AppCountType scope;				// The scope in which the event was queried.
        Mber::MberPtr<uint64_t > lastReconciled;				// The time at which this event was last reconciled in its application and scope
    };
    // Representation of a metric available for use in other queries
    struct AvailableEvent{
        std::string eventName;				// The name of the event in the metrics system.
        Mber::MberPtr<std::list<Mber::EventType> > types;				// The event types for the given metric name in the metrics system.
    };
    // Holds all of the information supplied by Adyen when calling back into Mber
    struct AdyenCallback{
        Mber::MberPtr<std::string > applicationId;				// The id of the store
        Mber::MberPtr<std::string > invoiceId;				// This was passed to us as the merchantReference field.  We supplied the invoice id when calling adyen and they return it to us so we can tie the response to the invoice
        Mber::MberPtr<std::string > providerId;				// The id of the payment provider used.
        Mber::MberPtr<std::string > merchantReference;				// This reference assigned by Mber to the original payment.
        Mber::MberPtr<bool > live;				// boolean (true/false) indicating if the notification originated from the LIVE or TEST payment systems.
        Mber::MberPtr<std::string > eventCode;				// The event type of the notification.
        Mber::MberPtr<std::string > pspReference;				// The reference we assigned to the payment or modification
        Mber::MberPtr<std::string > originalReference;				// If this is a notification for a modification request this will be the pspReference that was originally assigned to the authorisation. For a payment it will be blank.
        Mber::MberPtr<std::string > merchantAccountCode;				// The merchant account the payment or modification was processed with.
        Mber::MberPtr<std::string > eventDate;				// The time the event was generated.
        Mber::MberPtr<bool > success;				// Whether or not the event succeeded (boolean true/false).
        Mber::MberPtr<std::string > paymentMethod;				// The payment method used (only for AUTHORISATION). e.g. visa, mc, ideal, elv, wallie, etc...
        Mber::MberPtr<std::string > operations;				// The modification operations supported by this payment as a list of strings (only for AUTHORISATION). The operations will tell you whether you need to capture the payment (if you don&#39;t have auto-capture set up), whether you can cancel the payment (before capture) or if you can refund the payment (after it has been captured).
        Mber::MberPtr<std::string > reason;				// Text field with information depending on whether the result is successful or not. For AUTHORISATION events with the success field set to true and a payment method of visa, mc or amex this field contains the authorisation code, last 4 digits of the card, and the expiry date in the following format: 6 digit Authorisation Code:Last 4 digits:Expiry Date (e.g. 874574:1935:11/2012). When the success field is set to false it gives a reason as to why it was refused. For REPORT_AVAILABLE it contains the URL where the report can be downloaded from.
        Mber::MberPtr<long > value;				// The amount (if relevant) associated with the payment or modification.
        Mber::MberPtr<Mber::CurrencyCode > currency;				// The currencyCode that the value is in (if relevant).
    };
    // Representation of an affiliate
    struct Affiliate{
        std::string affiliateId;				// The id of the affiliate
        std::string name;				// Human readable name for the affiliate
        std::string applicationId;				// The application this affiliate is scoped to
        Mber::MberPtr<std::string > profileId;				// The Mber profile associated with this affiliate
        Mber::MberPtr<std::list<Mber::AffiliateStatus> > status;				// The status of the affiliate
    };
    // Holds all of the information supplied by BoaCompra when calling back into Mber
    struct BoaCompraCallback{
        Mber::MberPtr<std::string > storeId;				// Virtual Store identification on BoaCompra.com
        Mber::MberPtr<std::string > transactionId;				// Order identification on BoaCompra.com
        Mber::MberPtr<std::string > invoiceId;				// This comes back as the order_id from BoaCompra
        Mber::MberPtr<std::string > providerId;				// This is looked up from the invoice ID
        Mber::MberPtr<long > amount;				// Order total without any separators; the last two digits correspond to the decimal part of the value
        Mber::MberPtr<Mber::CurrencyCode > currencyCode;				// Order country ISO code
        Mber::MberPtr<std::string > paymentId;				// Identification of the payment method used
        Mber::MberPtr<std::string > countryPayment;				// Country ISO Code (2 characters) from which the payments methods must be displayed without showing the country selection page to the final user.
        Mber::MberPtr<std::string > testMode;				// Parameter used to indicate that a transaction will be in test mode. Can be used the value “1” to test integration and “0” to production environment.
    };
    // Holds the set of items available for offers in the application
    struct Catalog{
        std::string applicationId;				// The id of the store
        Mber::MberPtr<std::list<Mber::EntityPointer> > addItems;				// The items added to the catalog
        Mber::MberPtr<std::list<Mber::EntityPointer> > removeItems;				// The items removed from the catalog
    };
    // An automatic deduction rule for virtual currency
    struct DeductionRule{
        Mber::DeductionRulePriority priority;				// The prioritization mechanism of the rule
        Mber::DeductionRuleProperty property;				// The property to use when determining how to apply deductions
    };
    // Representation of a total of some entity
    struct EntityTotal{
        double total;
        Mber::EntityPointer entity;				// The named entity
    };
    // Representation of an invoice
    struct Invoice{
        std::string invoiceId;				// The id of the invoice
        std::string applicationId;				// The application the invoice pertains to
        std::string profileId;				// Owner of the invoice
        Mber::InvoiceStatus status;				// Status of the invoice
        Mber::MberPtr<std::string > storeId;				// Store in which the invoice is defined
        Mber::MberPtr<std::list<Mber::PaymentProvider> > paymentProviders;				// Available payment providers for the invoice
        Mber::MberPtr<std::list<Mber::Offer> > offers;				// Offers associated with the invoice
        Mber::MberPtr<std::list<Mber::InvoiceExpectedItem> > expectedInputs;				// Expected inputs to the invoice
        Mber::MberPtr<std::list<Mber::InvoiceExpectedItem> > expectedOutputs;				// Expected outputs to the invoice
        Mber::MberPtr<double > realMoneyTotal;				// Total cost as a real money transaction for this invoice
        Mber::MberPtr<uint64_t > createdTime;				// The time the invoice was initially created
        Mber::MberPtr<uint64_t > updatedTime;				// The time the invoice was last updated
    };
    // Representation of an invoice actual item
    struct InvoiceActualItem{
        std::string itemId;				// Id of the actual item
        Mber::InvoiceItemStatus status;				// The status of this actual item
        Mber::MberPtr<Mber::EntityPointer > owner;				// The entity that owns the actual item. Older invoices won&#39;t have this, which means the item&#39;s owned by the profile on the invoice.
    };
    // Representation of an invoice expected item
    struct InvoiceExpectedItem{
        Mber::EntityPointer item;				// Pointer to the expected object
        double amount;				// The amount associated with the expected object
        Mber::InvoiceItemStatus status;				// The status of this item
        Mber::MberPtr<std::list<Mber::InvoiceActualItem> > actualItems;				// Actual items for this expectation
        Mber::MberPtr<Mber::EntityPointer > associatedInput;				// For a reward output, this is the input whose granter will be given the reward
    };
    // Representation of a purchase within Mber
    struct InvoicePurchase{
        Mber::MberPtr<Mber::CurrencyCode > currencyCode;				// The currency used in the purchase
        Mber::MberPtr<Mber::RealMoneyInput > realMoneyInput;				// A real money used for the purchase, identifying the payment provider used.
        Mber::MberPtr<Mber::RealMoneyTransactionProvider > providerType;				// The type of provider used.
        std::string applicationId;				// The application the currency was spent in
        std::string invoiceId;				// The id of the invoice the purchase is tied to
        std::string profileId;				// The profile that made the purchase
        std::string storeId;				// Store in which the invoice is defined
        Mber::MberPtr<std::list<Mber::Offer> > offers;				// Offers associated with the invoice
        Mber::MberPtr<std::list<Mber::InvoiceExpectedItem> > expectedInputs;				// Expected inputs to the invoice
        Mber::MberPtr<std::list<Mber::InvoiceExpectedItem> > expectedOutputs;				// Expected outputs to the invoice
        Mber::MberPtr<Mber::InvoiceSource > invoiceSource;				// The retail source of the invoice
    };
    // Representation of a change in the status of an invoice
    struct InvoiceStatusSummary{
        std::string invoiceId;				// The id of the invoice
        std::string applicationId;				// The application the invoice pertains to
        std::string profileId;				// Owner of the invoice
        Mber::InvoiceStatus status;				// Status of the invoice
        Mber::MberPtr<std::string > storeId;				// Store in which the invoice is defined
    };
    // The reference for an invoice in the Adyen system
    struct MerchantReference{
        std::string applicationId;				// The id of the application the invoice belongs to.
        std::string invoiceId;				// The id of the invoice that corresponds to the transaction in Adyen.
        std::string providerId;				// The id of the payment provider used.
    };
    // Representation of an offer
    struct Offer{
        std::string offerId;				// The id of the offer
        std::string application;				// The application to build the offer in
        std::string name;				// Human readable name for the offer
        Mber::MberPtr<int > stock;				// The number of remaining times this offer can be consumed; Infinite if unspecified
        Mber::MberPtr<std::list<Mber::OfferItem> > inputs;				// The items provided to consume this offer
        Mber::MberPtr<std::list<Mber::OfferItem> > outputs;				// The items distributed upon consumption of this offer
        Mber::MberPtr<std::list<std::string> > categories;				// The categories this offer belongs to.
        Mber::MberPtr<std::list<Mber::OfferItem> > rewards;				// The items distributed upon consumption of this offer entities other than the recipient of the outputs.
    };
    // Representation of an offer item
    struct OfferItem{
        Mber::EntityPointer item;				// Pointer to the required object
        double amount;				// The amount associated with the object
        Mber::MberPtr<Mber::EntityPointer > associatedInput;				// For a reward output, this is the input whose granter will be given the reward
    };
    // Representation of an offer that has been purchased
    struct OfferPurchase{
        std::string offerId;				// The id of the offer
        std::string application;				// The application the offer belongs in
        std::string name;				// Human readable name for the offer
        Mber::MberPtr<std::list<Mber::OfferItem> > inputs;				// The items provided to consume this offer
        Mber::MberPtr<std::list<Mber::OfferItem> > outputs;				// The items distributed upon consumption of this offer
        std::string invoiceId;				// The id of the invoice the offer purchase is tied to
    };
    // Description of an endpoint for executing a real money transaction
    struct PaymentProvider{
        Mber::RealMoneyTransactionProvider provider;				// The provider
        std::string providerUrl;				// The url to execute the payment
        Mber::MberPtr<std::string > merchantId;				// The id for the merchant account to use in the Payment Provider&#39;s system
        Mber::MberPtr<std::string > applicationId;				// The id for the application this payment provider is configured for
        Mber::MberPtr<std::string > providerId;				// The id of this payment provider
        bool isActive;				// True if this payment provider is active and false otherwise.
        Mber::MberPtr<std::string > paymentPageId;				// The optional id for the payment page to use in the Payment Provider&#39;s system
        Mber::MberPtr<std::string > paymentPageUri;				// The optional URI for the payment page to use in the Payment Provider&#39;s system
        Mber::MberPtr<std::string > notificationUri;				// The optional URI that the payment provider should use to contact Mber.
        Mber::MberPtr<bool > testMode;				// The optional flag to indicate this provider is in test mode
    };
    // Representation of real currency
    struct RealCurrency{
        std::string currencyId;				// Id of the currency
        Mber::CurrencyCode name;				// ISO 4217 Currency Code
        std::string decsription;				// Description of the currency
    };
    // Representation of an offer item
    struct RealMoneyInput{
        std::string provider;				// The real money provider
        Mber::MberPtr<std::string > providerToken;				// The token from the provider.  Required for some but not all provider types.
        double amount;				// The amount associated with the token
    };
    // Representation of a referral
    struct Referral{
        Mber::EntityPointer referrerId;				// The id of the referrer
        std::string profileId;				// The Mber profile created as a result of the referral
        std::string applicationId;				// The application under the referral took place
    };
    // Representation of a referral count
    struct ReferralCount{
        long count;
        Mber::EntityPointer referrer;				// The referring entity
    };
    // Representation of entity totals by referrer and entity
    struct ReferralEntityTotals{
        Mber::EntityPointer referrer;				// The referring entity
        std::list<Mber::EntityTotal> totals;				// The entity totals
    };
    // Representation of a store
    struct Store{
        std::string storeId;				// The id of the store
        std::string application;				// The application the store is defined in
        std::string name;				// Human readable name for the store
        Mber::MberPtr<std::list<Mber::Offer> > offers;				// The offers available in the store
    };
    // Representation of a virtual currency
    struct VirtualCurrency{
        std::string virtualCurrencyId;				// The id of the currency
        std::string application;				// The application of the currency
        std::string name;				// Human readable name for the currency
        bool disabledSpending;				// Flag indicating if spending is disabled
        bool disabledEarning;				// Flag indicating if earning is disabled
        Mber::DeductionRule deductionRule;				// Rule to use for deducting currency
        Mber::MberPtr<int > walletTtl;				// The time to live, in hours, for an individual wallet lot. If unspecified, wallet lots will not expire
    };
    // Representation of a fluctuation in the amount of a virtual currency in the system.
    struct VirtualCurrencyChange{
        std::string virtualCurrencyId;				// The unique identifier of the virtual currency that has changed.
        std::string virtualCurrencyName;				// The name of the virtual currency that has changed. This is also the name of the event in the metric system.
        double currencyAmount;				// The amount of currency that has changed.
        std::string applicationId;				// The application the currency fluctuation took place in.
    };
    // Representation of a purchase using virtual currency within Mber
    struct VirtualPurchase{
        Mber::EntityPointer virtualCurrency;				// The virtual currency used for the purchase
        Mber::MberPtr<std::string > reason;				// An optional string describing what was purchased
        std::string applicationId;				// The application the currency was spent in
        double total;				// Total cost in virtual currency for this purchase
        std::list<Mber::WalletLot> walletLots;				// The wallet lots that were involved in the purchase
        Mber::MberPtr<std::string > invoiceId;				// The id of the invoice
        Mber::MberPtr<double > remainingBalance;				// The remaining balance in the wallet for this virtual currency after this purchase
        Mber::EntityPointer purchaser;				// The entity that made the purchase
    };
    // Representation of a profile&#39;s virtual funds
    struct Wallet{
        std::string profileId;				// The profile belonging to the holder of the wallet
        std::string applicationId;				// The application this wallet pertains to
        Mber::MberPtr<std::list<Mber::WalletTotal> > funds;				// The available funds
        Mber::EntityPointer owner;				// The holder of the wallet
    };
    // Representation of an individual pool of virtual currency funds
    struct WalletLot{
        std::string lotId;				// The id of the lot
        std::string virtualCurrencyId;				// The currency
        std::string profileId;				// The holder of the lot
        Mber::EntityPointer origin;				// The origin of the lot
        double amount;				// The amount in the lot (rounded to 2 decimal places)
        uint64_t timeCreated;				// The time the lot was created
        Mber::MberPtr<double > amountChange;				// An amount to change the lot by; may be positive for a deposit or negative for a deduction
    };
    // A currency total within a wallet
    struct WalletTotal{
        std::string virtualCurrencyId;				// The virtual currency
        std::string virtualCurrencyName;				// The name of the currency
        double total;				// The available funds
    };
    // Definition of a heartbeat
    struct Heartbeat{
        std::string serverId;				// Id of the server the heartbeat belongs to
        Mber::MberPtr<std::string > status;				// The optional, arbitrary status set by the server on it&#39;s heartbeat
        uint64_t time;				// The time at which this heartbeat occured
        Mber::MberPtr<uint64_t > currentUsers;				// The number of users currently on the server
        Mber::MberPtr<uint64_t > userCapacity;				// The maximum number of users that can be on the server
        Mber::MberPtr<double > utilization;				// The percent the server is utilized. Servers can supply their own calculation.
    };
    // Definition of a lobby instance
    struct Lobby{
        std::string lobbyId;				// Lobby identifier
        std::string serverId;				// Server the lobby is registered on
        std::string name;				// Human readable name of the lobby
        Mber::MberPtr<std::list<std::string> > profiles;				// Participants in the lobby
        Mber::MberPtr<std::list<std::string> > addProfiles;				// Profiles to add to the lobby
        Mber::MberPtr<std::list<std::string> > removeProfiles;				// Profiles to remove from the lobby
    };
    // Definition of a server
    struct Server{
        std::string serverId;				// Server identifier
        std::string applicationId;				// Application identifier in which the server is defined
        std::string name;				// Human readable name of the server
        std::string host;				// Server host
        Mber::MberPtr<int > port;				// Server port
        Mber::ServerState state;				// Current state of the server
        Mber::MberPtr<int > heartbeatInterval;				// The number of seconds this server can go without a heartbeat before reporting it is offline
        Mber::MberPtr<long > lastHeartbeat;				// The number of seconds elapsed since the last heartbeat
        Mber::MberPtr<std::string > status;				// An optional, arbitrary status set by the server on it&#39;s heartbeat
        std::string serverType;				// The arbitrary type of the server
        Mber::MberPtr<uint64_t > currentUsers;				// The number of users currently on the server
        Mber::MberPtr<uint64_t > userCapacity;				// The maximum number of users that can be on the server
        Mber::MberPtr<double > utilization;				// The percent the server is utilized. Servers can supply their own calculation.
    };
    // An Mber document based message.
    struct DocumentMessage{
        std::list<std::string> documentIds;				// An ordered list of document ids from which to construct this message.
        std::list<Mber::ReplacementProperty> properties;				// List of variable - value pairs to replace in the document based message and subject.
        Mber::MberPtr<std::string > subject;				// The optional string subject of the message. If not included a subject property will be searched for on the documents.
    };
    // The email configuration settings for an application
    struct EmailConfig{
        std::string applicationId;				// The id of the application the email configuration settings correspond to.
        std::string host;				// The host name or ip address of smtp server for this application
        Mber::MberPtr<int > port;				// The smpt server port. If useSsl is enabled this should be the ssl port of the smtp server
        bool useSsl;				// If true, SSL encryption will be used.
        bool useTls;				// If true, TLS encryption will be used.
        Mber::MberPtr<std::string > userName;				// The user name for the smtp server.
        Mber::MberPtr<std::string > password;				// The password for the smtp server.
        std::string senderEmail;				// The from email address for outgoing messages.
        Mber::MberPtr<std::string > senderName;				// The optional name that outgoing email messages will be from
    };
    // An email message to be sent.
    struct EmailMessage{
        std::string applicationId;				// The id of the application sending the email.
        std::list<Mber::EntityPointer> to;				// List of profile identifiers to send the email message to.
        std::list<Mber::EntityPointer> cc;				// List of profile identifiers to carbon copy the email message to.
        std::list<Mber::EntityPointer> bcc;				// List of profile identifiers to blind carbon copy the email message to.
        Mber::MberPtr<Mber::DocumentMessage > documentMessage;				// The message represented by documents stored in mber. If not supplied, StringBody must be supplied.
        Mber::MberPtr<Mber::StringMessage > stringMessage;				// The raw message body and subject. If not supplied, DocumentBody must be supplied.
        Mber::MberPtr<bool > sendToUnvalidatedEmails;				// If true, the message will be sent to unvalidated email addresses.  If false, it will only be sent to validated email addresses.
    };
    // Representation of variable - value pair to be used in replacing fields in a document.
    struct ReplacementProperty{
        std::string variable;				// The strict variable or regex expression to replace.
        std::string value;				// The value to replace the variable with
        Mber::MberPtr<bool > useRegex;				// True to do a regex replacement of the variable and false otherwise.  False by default.
    };
    // A raw string message.
    struct StringMessage{
        Mber::MberPtr<std::string > subject;				// The string subject of the message
        std::string body;				// The string body of the message
    };
    // Representation of a group
    struct Group{
        std::string groupId;				// The unique identifier of the group
        std::string name;				// The human readable name of the group
        std::string parentId;				// Entity id of the parent in which the group is defined
        Mber::EntityType parentType;				// Entity type of the parent in which the group is defined
        Mber::EntityType groupType;				// Type of entities included in the group
        Mber::MberPtr<std::list<std::string> > members;				// Members currently in the group
        Mber::MberPtr<std::list<std::string> > addMembers;				// Members to add to the group
        Mber::MberPtr<std::list<std::string> > removeMembers;				// Members to remove from the group
    };

    // Conversion functions
    EntityType stringToEntityType(const std::string& val);
    std::string EntityTypeToString(Mber::EntityType val);
    EventType stringToEventType(const std::string& val);
    std::string EventTypeToString(Mber::EventType val);
    MetricType stringToMetricType(const std::string& val);
    std::string MetricTypeToString(Mber::MetricType val);
    PermissionType stringToPermissionType(const std::string& val);
    std::string PermissionTypeToString(Mber::PermissionType val);
    Status stringToStatus(const std::string& val);
    std::string StatusToString(Mber::Status val);
    TokenType stringToTokenType(const std::string& val);
    std::string TokenTypeToString(Mber::TokenType val);
    AccessTokenType stringToAccessTokenType(const std::string& val);
    std::string AccessTokenTypeToString(Mber::AccessTokenType val);
    AccountStatus stringToAccountStatus(const std::string& val);
    std::string AccountStatusToString(Mber::AccountStatus val);
    ApplicationStatus stringToApplicationStatus(const std::string& val);
    std::string ApplicationStatusToString(Mber::ApplicationStatus val);
    OauthError stringToOauthError(const std::string& val);
    std::string OauthErrorToString(Mber::OauthError val);
    PermissionFlags stringToPermissionFlags(const std::string& val);
    std::string PermissionFlagsToString(Mber::PermissionFlags val);
    ProfileAddressType stringToProfileAddressType(const std::string& val);
    std::string ProfileAddressTypeToString(Mber::ProfileAddressType val);
    ProfileGroupStatus stringToProfileGroupStatus(const std::string& val);
    std::string ProfileGroupStatusToString(Mber::ProfileGroupStatus val);
    ProfileStatus stringToProfileStatus(const std::string& val);
    std::string ProfileStatusToString(Mber::ProfileStatus val);
    Region stringToRegion(const std::string& val);
    std::string RegionToString(Mber::Region val);
    RoleStatus stringToRoleStatus(const std::string& val);
    std::string RoleStatusToString(Mber::RoleStatus val);
    SteamUserStatus stringToSteamUserStatus(const std::string& val);
    std::string SteamUserStatusToString(Mber::SteamUserStatus val);
    DefinitionStatus stringToDefinitionStatus(const std::string& val);
    std::string DefinitionStatusToString(Mber::DefinitionStatus val);
    EntitlementPropertyAvailability stringToEntitlementPropertyAvailability(const std::string& val);
    std::string EntitlementPropertyAvailabilityToString(Mber::EntitlementPropertyAvailability val);
    EntitlementState stringToEntitlementState(const std::string& val);
    std::string EntitlementStateToString(Mber::EntitlementState val);
    EntitlementType stringToEntitlementType(const std::string& val);
    std::string EntitlementTypeToString(Mber::EntitlementType val);
    KeyFormat stringToKeyFormat(const std::string& val);
    std::string KeyFormatToString(Mber::KeyFormat val);
    CDNType stringToCDNType(const std::string& val);
    std::string CDNTypeToString(Mber::CDNType val);
    DataStorageLocation stringToDataStorageLocation(const std::string& val);
    std::string DataStorageLocationToString(Mber::DataStorageLocation val);
    DocumentStatus stringToDocumentStatus(const std::string& val);
    std::string DocumentStatusToString(Mber::DocumentStatus val);
    TemplateFieldType stringToTemplateFieldType(const std::string& val);
    std::string TemplateFieldTypeToString(Mber::TemplateFieldType val);
    AppCountType stringToAppCountType(const std::string& val);
    std::string AppCountTypeToString(Mber::AppCountType val);
    ProfileHistoryFilter stringToProfileHistoryFilter(const std::string& val);
    std::string ProfileHistoryFilterToString(Mber::ProfileHistoryFilter val);
    TimeUnit stringToTimeUnit(const std::string& val);
    std::string TimeUnitToString(Mber::TimeUnit val);
    AffiliateStatus stringToAffiliateStatus(const std::string& val);
    std::string AffiliateStatusToString(Mber::AffiliateStatus val);
    CurrencyCode stringToCurrencyCode(const std::string& val);
    std::string CurrencyCodeToString(Mber::CurrencyCode val);
    DeductionRulePriority stringToDeductionRulePriority(const std::string& val);
    std::string DeductionRulePriorityToString(Mber::DeductionRulePriority val);
    DeductionRuleProperty stringToDeductionRuleProperty(const std::string& val);
    std::string DeductionRulePropertyToString(Mber::DeductionRuleProperty val);
    InvoiceItemStatus stringToInvoiceItemStatus(const std::string& val);
    std::string InvoiceItemStatusToString(Mber::InvoiceItemStatus val);
    InvoiceSource stringToInvoiceSource(const std::string& val);
    std::string InvoiceSourceToString(Mber::InvoiceSource val);
    InvoiceStatus stringToInvoiceStatus(const std::string& val);
    std::string InvoiceStatusToString(Mber::InvoiceStatus val);
    RealMoneyTransactionProvider stringToRealMoneyTransactionProvider(const std::string& val);
    std::string RealMoneyTransactionProviderToString(Mber::RealMoneyTransactionProvider val);
    VirtualCurrencyStatus stringToVirtualCurrencyStatus(const std::string& val);
    std::string VirtualCurrencyStatusToString(Mber::VirtualCurrencyStatus val);
    ServerState stringToServerState(const std::string& val);
    std::string ServerStateToString(Mber::ServerState val);
    

    // Request + Response classes
    template<class T> class MberRequest{
    public:
        virtual MberPtr<T> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 ) = 0;
    };
    
    class MberResponse{
    public:
        Status result;
        std::string errorMessage;
    };

    // Service for dealing with account data
    namespace account{ 
        // An Mber account
        namespace Account{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > accountId;
                    Mber::MberPtr<std::string > masterProfileId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_username;					// The name used to authenticate
                    std::string m_password;					// The password for the account
                    Mber::Region m_region;					// The region the user is coming from
                    Mber::MberPtr<uint64_t > m_dateOfBirth;					// The user&#39;s date of birth
                    Mber::MberPtr<std::string > m_displayname;					// The visible name of the user
                    Mber::MberPtr<std::string > m_email;					// The email address of the account to create
                    Mber::EntityID m_sourceApplication;					// The application from which the request is originating
                    Mber::MberPtr<std::string > m_sourceReferredUrl;					// The referrence url from which the request is originating
                    Mber::MberPtr<bool > m_forcePasswordReset;					// If specified as true, the account will be required to change password upon logging in. This is preferred when creating an account on behalf of another user.
                    Mber::MberPtr<std::string > m_referringAccount;					// The account which referred this new account
                    Mber::MberPtr<Mber::EntityPointer > m_referrer;					// The account or affiliate which referred this new account
                public:
                    Request::Request( std::string username,std::string password,Mber::Region region,Mber::MberPtr<uint64_t > dateOfBirth,Mber::MberPtr<std::string > displayname,Mber::MberPtr<std::string > email,Mber::EntityID sourceApplication,Mber::MberPtr<std::string > sourceReferredUrl,Mber::MberPtr<bool > forcePasswordReset,Mber::MberPtr<std::string > referringAccount,Mber::MberPtr<Mber::EntityPointer > referrer );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Account > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_accountId;					// The account identifier to lookup
                public:
                    Request::Request( std::string accountId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // An Mber profile
        namespace Profile{ 
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Profile > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The profile identifier to lookup
                public:
                    Request::Request( std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The profile identifier to update
                    Mber::MberPtr<std::string > m_username;					// The name used to authenticate
                    Mber::MberPtr<std::string > m_password;					// The password for the account
                    Mber::MberPtr<Mber::Region > m_region;					// The region the user is coming from
                    Mber::MberPtr<uint64_t > m_dateOfBirth;					// The user&#39;s date of birth
                    Mber::MberPtr<std::string > m_displayname;					// The visible name of the user
                    Mber::MberPtr<std::string > m_email;					// The email address of the account to create
                    Mber::MberPtr<std::string > m_steamId;					// The user&#39;s Steam id. Will only update if the token has private data permissions.
                    Mber::MberPtr<bool > m_preserveCurrentSteamId;					// A flag to determine whether to save the user&#39;s current steam id, if none is provided. If false, and no steam id is provided, the current steam account will be unlinked.
                public:
                    Request::Request( std::string profileId,Mber::MberPtr<std::string > username,Mber::MberPtr<std::string > password,Mber::MberPtr<Mber::Region > region,Mber::MberPtr<uint64_t > dateOfBirth,Mber::MberPtr<std::string > displayname,Mber::MberPtr<std::string > email,Mber::MberPtr<std::string > steamId,Mber::MberPtr<bool > preserveCurrentSteamId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Deletes or disables the profile.  User&#39;s are not allowed to perform this action on their own profile.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The profile identifier to update
                public:
                    Request::Request( std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Search for a profile by some identifying details
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Profile> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::string > m_displayName;					// The display name to resolve
                    Mber::MberPtr<std::string > m_userName;					// The user name to resolve
                    Mber::MberPtr<std::string > m_email;					// The email to resolve
                public:
                    Request::Request( Mber::MberPtr<std::string > displayName,Mber::MberPtr<std::string > userName,Mber::MberPtr<std::string > email );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // API for enabling and disabling profiles.
        namespace ProfileEnable{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The id of the profile to enable.
                public:
                    Request::Request( std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The id of the profile to disable.
                public:
                    Request::Request( std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // For querying against profiles in the system
        namespace ProfileQuery{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Profile> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::Query m_query;					// The structured search query to use
                public:
                    Request::Request( Mber::Query query );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // For configuring the address of a profile
        namespace ProfileAddress{ 
            // List addresses for the specified profile
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::ProfileAddress> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The ID of the profile to get an address for
                public:
                    Request::Request( std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Update the address for the specified profile
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The ID of the profile to update
                    Mber::ProfileAddressType m_addressType;					// The type of address e.g. billing, shipping, etc.
                    Mber::MberPtr<std::string > m_houseNumberOrName;					// The house number (or name)
                    Mber::MberPtr<std::string > m_street;					// The street name
                    Mber::MberPtr<std::string > m_city;					// The city
                    Mber::MberPtr<std::string > m_postalCode;					// The postal/zip code
                    Mber::MberPtr<std::string > m_stateOrProvince;					// The state or province
                    Mber::MberPtr<std::string > m_country;					// The country in ISO 3166-1 alpha-2 format
                public:
                    Request::Request( std::string profileId,Mber::ProfileAddressType addressType,Mber::MberPtr<std::string > houseNumberOrName,Mber::MberPtr<std::string > street,Mber::MberPtr<std::string > city,Mber::MberPtr<std::string > postalCode,Mber::MberPtr<std::string > stateOrProvince,Mber::MberPtr<std::string > country );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete an address for the specified profile
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The ID of the profile to update
                    Mber::ProfileAddressType m_addressType;					// The type of address e.g. billing, shipping, etc.
                public:
                    Request::Request( std::string profileId,Mber::ProfileAddressType addressType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // An Mber persona
        namespace Persona{ 
            // Create a new persona on a profile
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > personaId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The ID of the profile to create the persona on
                    std::string m_displayname;					// The visible name of the persona
                public:
                    Request::Request( std::string profileId,std::string displayname );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Read a persona on a profile
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Persona > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_personaId;					// The ID of the persona to read
                public:
                    Request::Request( std::string personaId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // List personas owned by a given profile
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Persona> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                    bool truncated;
                    long totalPages;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The ID of the profile to list personas on
                    Mber::MberPtr<uint64_t > m_page;					// The page in the results to return. Pages start at 1.
                    Mber::MberPtr<uint64_t > m_maxResults;					// Can be used to specify the maximum number of results to return.  Will be limited to the global maximum number of results by default and may never return more than this.
                public:
                    Request::Request( std::string profileId,Mber::MberPtr<uint64_t > page,Mber::MberPtr<uint64_t > maxResults );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Update a persona on a profile
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_personaId;					// The ID of the persona to update
                    Mber::MberPtr<std::string > m_displayname;					// The visible name of the persona
                public:
                    Request::Request( std::string personaId,Mber::MberPtr<std::string > displayname );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete a persona from a profile
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_personaId;					// The ID of the persona to delete
                public:
                    Request::Request( std::string personaId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // For querying against personas in the system
        namespace PersonaQuery{ 
            // Look for a persona in the system
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Persona> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::Query m_query;					// The structured search query to use
                public:
                    Request::Request( Mber::Query query );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // The Mber region
        namespace SystemRegion{ 
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Region> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                public:
                    Request::Request(  );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Allows users to reset their password if they&#39;ve forgotten it
        namespace ForgotPassword{ 
            // Sends a forgot password email to the specified user
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_username;					// The username of the account whose password is forgotten
                    std::string m_email;					// The email address of the account whose password is forgotten
                    Mber::MberPtr<Mber::EntityID > m_applicationId;					// The application in which the forgot password is being requested. This determines how messaging is performed. Defaults to the root application
                public:
                    Request::Request( std::string username,std::string email,Mber::MberPtr<Mber::EntityID > applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Sets a user&#39;s password with a token
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_tokenId;					// The token to redeem to set the password
                    std::string m_password;					// The new password to set
                public:
                    Request::Request( std::string tokenId,std::string password );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Manages the forced password reset process
        namespace PasswordReset{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The profile identifier to invoke a password reset on
                    Mber::MberPtr<std::string > m_applicationContext;					// The application context in which the reset is occurring. This will determine how messaging is performed. If unspecified, defaults to the token application
                public:
                    Request::Request( std::string profileId,Mber::MberPtr<std::string > applicationContext );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The profile identifier to undo a password reset on
                public:
                    Request::Request( std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > scope;
                    Mber::MberPtr<std::string > access_token;
                    Mber::MberPtr<Mber::AccessTokenType > token_type;
                    Mber::MberPtr<int > expires_in;
                    Mber::MberPtr<std::string > refresh_token;
                    Mber::MberPtr<Mber::OauthError > error;
                    Mber::MberPtr<std::string > accountId;
                    Mber::MberPtr<std::string > profileId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_tokenId;					// The password reset token to use when setting the password
                    std::string m_password;					// The new password to use
                public:
                    Request::Request( std::string tokenId,std::string password );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // API entry-point to control the profile Reindexing process
        namespace ProfileReindexing{ 
            // Sends event to the ProfileReindexing process
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EventType m_eventType;					// The type of event to send to the ProfileReindexing process
                    Mber::EntityID m_applicationId;					// The id of the application to index profiles in.
                    Mber::MberPtr<bool > m_deleteIndex;					// Flag to determine if the index should be deleted.
                public:
                    Request::Request( Mber::EventType eventType,Mber::EntityID applicationId,Mber::MberPtr<bool > deleteIndex );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // For querying again profile entities in the system. Currently includes profiles and groups of profiles.
        namespace ProfileEntityQuery{ 
            // Executes a query across indexes for profiles and profile groups.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::EntityPointer> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::Query m_query;					// The query to execute
                public:
                    Request::Request( Mber::Query query );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Operations for upgrading anonymous users.
        namespace AnonymousUserUpgrade{ 
            // Creates a single-use token for the specified user with profile update permissions. An email is then sent to that user with some url that will allow them to upgrade their profile only once.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_email;					// The email address tied to the account to upgrade
                    Mber::MberPtr<Mber::EntityID > m_applicationId;					// The application context in which the Anonymous Upgrade email template is located. Will default to Mber if not provided.
                public:
                    Request::Request( std::string email,Mber::MberPtr<Mber::EntityID > applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Operations for the retrieval of lost identities.
        namespace ForgotUsername{ 
            // Creates an email that will be send to a user with all their profile ids.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_email;					// The email address tied to the account to retrieve.
                    Mber::MberPtr<Mber::EntityID > m_applicationId;					// The application context in which the Forgot Username email template is located. Will default to Mber if not provided.
                public:
                    Request::Request( std::string email,Mber::MberPtr<Mber::EntityID > applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Boot a profile from a given client
        namespace BootProfile{ 
            // Boots the profile from the given client
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The ID of the profile to boot
                    Mber::MberPtr<std::string > m_clientType;					// The client to boot the profile from
                    Mber::MberPtr<bool > m_includeChildApps;					// Boot the profile from child applications as well
                public:
                    Request::Request( std::string profileId,Mber::MberPtr<std::string > clientType,Mber::MberPtr<bool > includeChildApps );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Ban a profile from a given client
        namespace BanProfile{ 
            // Bans the profile from the given client
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The ID of the profile to ban
                    Mber::MberPtr<std::string > m_clientType;					// The client to ban the profile from
                    Mber::MberPtr<bool > m_includeChildApps;					// Ban the profile from child applications as well
                public:
                    Request::Request( std::string profileId,Mber::MberPtr<std::string > clientType,Mber::MberPtr<bool > includeChildApps );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Removes the ban of the profile from the given client
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The ID of the profile to remove the ban from
                    Mber::MberPtr<std::string > m_clientType;					// The client to remove the banned profile from
                    Mber::MberPtr<bool > m_includeChildApps;					// Remove the ban on the profile from child applications as well
                public:
                    Request::Request( std::string profileId,Mber::MberPtr<std::string > clientType,Mber::MberPtr<bool > includeChildApps );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Read and manipulate tokens associated with the given profile
        namespace ProfileToken{ 
            // Fetch details on the given token
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Token > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_tokenId;					// The token to be fetched
                    Mber::TokenType m_tokenType;					// The type of token
                public:
                    Request::Request( std::string tokenId,Mber::TokenType tokenType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Fetch all tokens of the given token types owned by the given profile
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Token> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_profileId;					// The profile whose tokens to look for
                    Mber::MberPtr<std::list<Mber::TokenType> > m_tokenTypes;					// The types of tokens to list
                public:
                    Request::Request( Mber::EntityID profileId,Mber::MberPtr<std::list<Mber::TokenType> > tokenTypes );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete the given profile token
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_tokenId;					// The token to be deleted
                public:
                    Request::Request( std::string tokenId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for dealing with applications
    namespace application{ 
        // An Mber application
        namespace Application{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > applicationId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// The name of the application
                    Mber::MberPtr<std::string > m_alias;					// The optional alias of the application. The alias must be unique within Mber.
                    Mber::EntityID m_parent;					// The parent application for this application
                    Mber::MberPtr<std::string > m_redirectUri;					// The redirect uri of the application
                    Mber::MberPtr<std::string > m_version;					// The application version, as defined by the application creator
                    Mber::MberPtr<uint64_t > m_maxPersonas;					// The maximum number of personas a profile can have in this application
                    Mber::MberPtr<bool > m_uniquePersonas;					// Controls whether persona names have to be unique within this application. Defaults to true.
                public:
                    Request::Request( std::string name,Mber::MberPtr<std::string > alias,Mber::EntityID parent,Mber::MberPtr<std::string > redirectUri,Mber::MberPtr<std::string > version,Mber::MberPtr<uint64_t > maxPersonas,Mber::MberPtr<bool > uniquePersonas );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_applicationId;					// The id of the application created
                    Mber::MberPtr<std::string > m_name;					// The name of the application
                    Mber::MberPtr<std::string > m_alias;					// The optional alias of the application. The alias must be unique within Mber.
                    Mber::MberPtr<std::string > m_redirectUri;					// The redirect uri of the application
                    Mber::MberPtr<std::string > m_version;					// The application version, as defined by the application creator
                    Mber::MberPtr<uint64_t > m_maxPersonas;					// The maximum number of personas a profile can have in this application
                    Mber::MberPtr<bool > m_uniquePersonas;					// Controls whether persona names have to be unique within this application. Defaults to true.
                public:
                    Request::Request( Mber::EntityID applicationId,Mber::MberPtr<std::string > name,Mber::MberPtr<std::string > alias,Mber::MberPtr<std::string > redirectUri,Mber::MberPtr<std::string > version,Mber::MberPtr<uint64_t > maxPersonas,Mber::MberPtr<bool > uniquePersonas );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Application> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<Mber::ApplicationStatus > m_status;					// The status of the applications to list.  If not provided only Activated applications will be returned.
                public:
                    Request::Request( Mber::MberPtr<Mber::ApplicationStatus > status );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Can be used to delete an application. Deleting will free the namespace for new applications and cannot be undone.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_applicationId;					// The id of the application to delete
                public:
                    Request::Request( Mber::EntityID applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Application > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_applicationId;					// The id of the application to read
                public:
                    Request::Request( Mber::EntityID applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Allows applications to be enabled and disabled.
        namespace State{ 
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_parent;					// The id of the parent application
                    Mber::EntityID m_applicationId;					// The id of the application
                    Mber::ApplicationStatus m_status;					// The new status of the application.  Should be Disabled or Activated.  Applications cannot be deleted through this API
                public:
                    Request::Request( Mber::EntityID parent,Mber::EntityID applicationId,Mber::ApplicationStatus status );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service exposing an OAuth2 complient interface
    namespace oauth{ 
        // An Mber authorization token which may be exchanged for an access token; note that this is a mechanism for use by our own clients in order to provide an authorization code to clients for the standardized access token endpoint
        namespace AuthorizationToken{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > authorization_code;
                    Mber::MberPtr<std::string > scope;
                    Mber::MberPtr<std::string > accountId;
                    Mber::MberPtr<std::string > profileId;
                    Mber::MberPtr<std::string > applicationId;
                    Mber::MberPtr<std::string > redirect_uri;
                    Mber::MberPtr<std::string > passwordResetToken;
                    Mber::MberPtr<std::string > displayname;
                    Mber::MberPtr<std::string > steamId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_client_id;					// The mber application to authenticate against
                    Mber::MberPtr<std::string > m_redirect_uri;					// validate against client redirect_uris; if not provided, use default uri for client
                    Mber::MberPtr<std::string > m_refresh_token;					// Used if attempting to create an authorization based on a refresh token
                    Mber::MberPtr<std::string > m_username;					// Used if attempting to create an authorization based on username/password
                    Mber::MberPtr<std::string > m_password;					// Used if attempting to create an authorization based on username/password
                    Mber::MberPtr<std::string > m_scope;					// space delimited case sensitive strings; requested
                public:
                    Request::Request( Mber::EntityID client_id,Mber::MberPtr<std::string > redirect_uri,Mber::MberPtr<std::string > refresh_token,Mber::MberPtr<std::string > username,Mber::MberPtr<std::string > password,Mber::MberPtr<std::string > scope );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // An Mber Access token; note that this API must strictly adhere to the standard described in the OAuth2 spec, as this is the endpoint through which 3rd party clients may directly interact
        namespace AccessToken{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > scope;
                    Mber::MberPtr<std::string > access_token;
                    Mber::MberPtr<Mber::AccessTokenType > token_type;
                    Mber::MberPtr<int > expires_in;
                    Mber::MberPtr<std::string > refresh_token;
                    Mber::MberPtr<Mber::OauthError > error;
                    Mber::MberPtr<std::string > accountId;
                    Mber::MberPtr<std::string > profileId;
                    Mber::MberPtr<std::string > applicationId;
                    Mber::MberPtr<std::string > passwordResetToken;
                    Mber::MberPtr<std::string > displayname;
                    Mber::MberPtr<std::string > steamId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_grant_type;					// authorization_code, password, client_credentials [must be confidential client], refresh_token
                    Mber::EntityID m_client_id;					// The mber application to authenticate against
                    Mber::MberPtr<std::string > m_client_secret;					// validate against client credentials
                    Mber::MberPtr<std::string > m_code;					// required if type=auth_code
                    Mber::MberPtr<std::string > m_refresh_token;					// required if type=refresh_token; validated against client
                    Mber::MberPtr<std::string > m_username;					// required if grant_type=password
                    Mber::MberPtr<std::string > m_password;					// required if grant_type=password
                    Mber::MberPtr<std::string > m_redirect_uri;					// required if grant_type=authorization_code; Validated against redirect_uri used for auth code
                    Mber::MberPtr<std::string > m_scope;					// space delimited case sensitive strings; requested
                public:
                    Request::Request( std::string grant_type,Mber::EntityID client_id,Mber::MberPtr<std::string > client_secret,Mber::MberPtr<std::string > code,Mber::MberPtr<std::string > refresh_token,Mber::MberPtr<std::string > username,Mber::MberPtr<std::string > password,Mber::MberPtr<std::string > redirect_uri,Mber::MberPtr<std::string > scope );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Returns an Mber access token to be used on behalf the user in the client application. The user&#39;s authorization token is combined with the clients access token to enhance the privileges of the user in the context of the client.  There may only be one such client token for a user at any time.
        namespace ClientToken{ 
            // Creates a user client token with the combined permissions of the user and client application.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > clientToken;
                    Mber::MberPtr<std::string > scope;
                    Mber::MberPtr<std::string > accountId;
                    Mber::MberPtr<std::string > profileId;
                    Mber::MberPtr<std::string > applicationId;
                    Mber::MberPtr<std::string > displayname;
                    Mber::MberPtr<std::list<Mber::EntityPointer> > ownerHas;
                    Mber::MberPtr<int > expiresIn;
                    Mber::MberPtr<std::string > steamId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_authorization_token;					// Used if attempting to create an client token based on a authorization token
                    std::string m_clientType;					// Required to qualify the client token.  Only one token of the given type is allowed at any time.
                    Mber::MberPtr<int > m_ttl;					// The desired lifetime in seconds of the client token.  The token will continue to live as long as it is used within this TTL, so the TTL should be short.
                    Mber::MberPtr<std::list<Mber::EntityPointer> > m_mustHaveOne;					// A list of required entities that the owner of the authorization token must have in order to obtain the client token.  Possible entity pointer types are currently supported limited to ProfileGroups and digital goods.
                public:
                    Request::Request( std::string authorization_token,std::string clientType,Mber::MberPtr<int > ttl,Mber::MberPtr<std::list<Mber::EntityPointer> > mustHaveOne );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // A service for managing groups of profiles
    namespace profileGroups{ 
        // Operations for managing groups of profiles.
        namespace ProfileGroups{ 
            // Creates a new group of profiles
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > profileGroupId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// The name of the profile group, must be unique within the owner&#39;s groups.
                    Mber::MberPtr<std::string > m_alias;					// The optional alias of the profile group, must be unique within the application.
                    Mber::MberPtr<std::list<Mber::EntityPointer> > m_members;					// The members that should be included in this group on creation.
                public:
                    Request::Request( std::string name,Mber::MberPtr<std::string > alias,Mber::MberPtr<std::list<Mber::EntityPointer> > members );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Get the details of the specified group.
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ProfileGroup > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_groupId;					// The identifier of the group to get details for.
                public:
                    Request::Request( Mber::EntityID groupId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Lists all the profile groups defined in the current application.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::ProfileGroup> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                public:
                    Request::Request(  );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Updates the specified profile group with the information provided.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_groupId;					// The group to be updated
                    Mber::MberPtr<std::string > m_name;					// The name of the group
                    Mber::MberPtr<std::string > m_alias;					// The alias of the group. If one is not provided, any current alias will be overwritten.
                    Mber::MberPtr<std::list<Mber::EntityPointer> > m_membersToAdd;					// The profile(s) to be added to the group.
                    Mber::MberPtr<std::list<Mber::EntityPointer> > m_membersToRemove;					// The profile(s) to be removed from the group.
                    Mber::MberPtr<Mber::ProfileGroupStatus > m_status;					// A new status to apply to the group.
                public:
                    Request::Request( Mber::EntityID groupId,Mber::MberPtr<std::string > name,Mber::MberPtr<std::string > alias,Mber::MberPtr<std::list<Mber::EntityPointer> > membersToAdd,Mber::MberPtr<std::list<Mber::EntityPointer> > membersToRemove,Mber::MberPtr<Mber::ProfileGroupStatus > status );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Permanently delete a profile group from the system.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_groupId;					// The id of the profile group to delete.
                public:
                    Request::Request( Mber::EntityID groupId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Operations for displaying relationships between profiles and profile groups.
        namespace ProfileGroupsMembership{ 
            // Lists the groups a given profile belongs to.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::EntityPointer> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The id of the profile to list groups it belongs to.
                public:
                    Request::Request( std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Operations for querying against ProfileGroups.
        namespace ProfileGroupQuery{ 
            // Creates an executes a query for profile groups.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::ProfileGroup> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::Query m_query;					// The structured query to execute
                public:
                    Request::Request( Mber::Query query );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for dealing with roles
    namespace role{ 
        // An Mber application
        namespace Role{ 
            // Create a new role
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > roleId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// The name of the role
                    Mber::EntityPointer m_parent;					// The parent entity for this role
                    bool m_automatic;					// If true, this role is automatically applied
                    bool m_cascading;					// If true, this role applies to children
                    Mber::MberPtr<std::list<Mber::Permission> > m_permissions;					// Permissions granted by this role
                    Mber::MberPtr<std::list<Mber::AutomaticRoleAssignment> > m_automaticAssignments;					// Roles that become automatically granted in the context of a created object
                    Mber::MberPtr<bool > m_negative;					// Flag indicating if this role negates its defined permissions
                public:
                    Request::Request( std::string name,Mber::EntityPointer parent,bool automatic,bool cascading,Mber::MberPtr<std::list<Mber::Permission> > permissions,Mber::MberPtr<std::list<Mber::AutomaticRoleAssignment> > automaticAssignments,Mber::MberPtr<bool > negative );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Look up the details of an existing role
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Role > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_roleId;					// The id of the role
                public:
                    Request::Request( Mber::EntityID roleId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Look up all roles defined in some context
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Role> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_parentId;					// The parent of the role
                    Mber::EntityType m_parentType;					// The type of the parent
                public:
                    Request::Request( std::string parentId,Mber::EntityType parentType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_roleId;					// The id of the role
                    std::string m_name;					// The name of the role
                    bool m_active;					// If true, the role takes effect.
                    bool m_automatic;					// If true, this role is automatically applied
                    bool m_cascading;					// If true, this role applied to children
                    Mber::MberPtr<std::list<Mber::Permission> > m_permissions;					// Permissions granted by this role
                    Mber::MberPtr<std::list<Mber::AutomaticRoleAssignment> > m_automaticAssignments;					// Roles that become automatically granted in the context of a created object
                    Mber::MberPtr<bool > m_negative;					// Flag indicating if this role negates its defined permissions
                public:
                    Request::Request( Mber::EntityID roleId,std::string name,bool active,bool automatic,bool cascading,Mber::MberPtr<std::list<Mber::Permission> > permissions,Mber::MberPtr<std::list<Mber::AutomaticRoleAssignment> > automaticAssignments,Mber::MberPtr<bool > negative );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete a role permanently from the system
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_roleId;					// The id of the role
                public:
                    Request::Request( Mber::EntityID roleId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Allows for assigning and unassigning roles to a profile within some context
        namespace RoleAssignment{ 
            // Assign a role to a profile where the permissions apply by the given context
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_roleId;					// The id of the role to assign
                    Mber::MberPtr<std::string > m_profileId;					// The profile to receive the role
                    Mber::EntityPointer m_context;					// The context in which the permissions of the role apply
                    Mber::EntityPointer m_recipient;					// The entity to receive the role
                public:
                    Request::Request( Mber::EntityID roleId,Mber::MberPtr<std::string > profileId,Mber::EntityPointer context,Mber::EntityPointer recipient );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Unassign a role from a profile in some context
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_roleId;					// The id of the role to unassign
                    Mber::MberPtr<std::string > m_profileId;					// The target profile to remove the role from
                    Mber::EntityPointer m_context;					// The context in which to unassign the role
                    Mber::EntityPointer m_recipient;					// The target entity to remove the role from
                public:
                    Request::Request( Mber::EntityID roleId,Mber::MberPtr<std::string > profileId,Mber::EntityPointer context,Mber::EntityPointer recipient );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Lookup profiles assigned to the role
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::EntityPointer> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_roleId;					// The id of the role to find profiles for
                public:
                    Request::Request( Mber::EntityID roleId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Service for dealing with relationships between profiles and roles.
        namespace ProfileRoles{ 
            // Lists all roles assigned to a given profile
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Role> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::string > m_profileId;					// The id of the profile to query roles for.
                    std::string m_entityId;					// The entity to query roles for.
                    Mber::MberPtr<Mber::EntityType > m_entityType;					// The type of entity to query roles for.
                public:
                    Request::Request( Mber::MberPtr<std::string > profileId,std::string entityId,Mber::MberPtr<Mber::EntityType > entityType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // A list of IP addresses against which a role will be applied
        namespace IPFilter{ 
            // Create an IP address role filter
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::list<std::string> m_ipAddresses;					// A list of IP addresses
                    Mber::EntityID m_role;					// The role to which this filter applies
                public:
                    Request::Request( std::list<std::string> ipAddresses,Mber::EntityID role );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Update an existing IP filter
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_role;					// The role to which this filter is applied
                    Mber::MberPtr<std::list<std::string> > m_ipsToAdd;					// The IP addresses to add to the given filter
                    Mber::MberPtr<std::list<std::string> > m_ipsToRemove;					// The IP addresses to remove from the given filter
                public:
                    Request::Request( Mber::EntityID role,Mber::MberPtr<std::list<std::string> > ipsToAdd,Mber::MberPtr<std::list<std::string> > ipsToRemove );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Get the details for a role&#39;s IP filter
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::IPFilter > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_role;					// The role to which this IP filter applies
                public:
                    Request::Request( Mber::EntityID role );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // List the IP filters that apply to the given IP addresses
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Role> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_ipAddress;					// The IP address whose filters will be fetched
                    std::string m_parentId;					// The parent of the role
                    Mber::EntityType m_parentType;					// The type of the parent
                public:
                    Request::Request( std::string ipAddress,std::string parentId,Mber::EntityType parentType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete the IP filter associated with the given role
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_role;					// The role to which this IP filter applies
                public:
                    Request::Request( Mber::EntityID role );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for configuring Steam applications.
    namespace steam{ 
        // A Steam application
        namespace SteamApplication{ 
            // Creates a new Steam application configuration
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > id;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    int m_steamApplicationId;					// The unique Steam identifier of the application
                    std::string m_name;					// Name of the Steam application.
                    std::string m_webAPIKey;					// The web api key that will be used for this application
                public:
                    Request::Request( int steamApplicationId,std::string name,std::string webAPIKey );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Get the details of the given Steam application.
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::SteamApplication > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_id;					// The identifier of the Steam application.
                public:
                    Request::Request( std::string id );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Get a list of Steam applications tied to the given Mber application.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::SteamApplication> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                public:
                    Request::Request(  );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Force synchronization a profile with Steam
        namespace SyncProfile{ 
            // Sync the profile with Steam. If an application is given, only that application will be synced. Otherwise, all applications will be synced.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_profileId;					// The profile to sync with Steam
                    Mber::MberPtr<Mber::EntityID > m_applicationId;					// The application to sync with Steam
                public:
                    Request::Request( Mber::EntityID profileId,Mber::MberPtr<Mber::EntityID > applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Force synchronization of all profiles in an application with Steam
        namespace SyncApplication{ 
            // Sync all the profiles in an application with Steam
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_applicationId;					// The application whose profiles you want to sync with Steam
                public:
                    Request::Request( Mber::EntityID applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Link an Mber profile with a Steam profile using a Steam AuthSessionTicket. Calls the following Steam API: https://api.steampowered.com/ISteamUserAuth/AuthenticateUserTicket/v0001/
        namespace LinkProfile{ 
            // Link the given Mber profile with the Steam profile defined in the AuthSessionTicket
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_profileId;					// The Mber profile to link with Steam Profile
                    int m_steamApplicationId;					// The unique Steam identifier of the application this ticket belongs to
                    std::string m_authSessionTicket;					// The Steam AuthSessionTicket that can be used to identify a Steam user
                public:
                    Request::Request( Mber::EntityID profileId,int steamApplicationId,std::string authSessionTicket );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for reading the current version of mber
    namespace version{ 
        // Returns the current mber build identifiers
        namespace Build{ 
            // Must have read permission to the mber application to exercise this api.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Build> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                public:
                    Request::Request(  );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for dealing with achievements
    namespace achievement{ 
        // An achievement Definition
        namespace Definition{ 
            // Creates an Achievement Definition in the application associated with the access_token.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > definitionId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// The name of the achievement definition
                    Mber::MberPtr<std::list<Mber::AchievementPropertyDefinition> > m_properties;					// List of property definitions
                    Mber::MberPtr<std::list<std::string> > m_categories;					// List of categories the achievement definition falls under.
                public:
                    Request::Request( std::string name,Mber::MberPtr<std::list<Mber::AchievementPropertyDefinition> > properties,Mber::MberPtr<std::list<std::string> > categories );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Updates an Achievement Definition in the application associated with the access_token.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_definitionId;					// The id of the definition to update
                    std::string m_name;					// The name of the achievement definition
                    Mber::MberPtr<std::list<std::string> > m_categoriesToAdd;					// Additional categories to add to this digital good definition.
                    Mber::MberPtr<std::list<std::string> > m_categoriesToRemove;					// Categories to be removed from this digital good defintion.
                public:
                    Request::Request( Mber::EntityID definitionId,std::string name,Mber::MberPtr<std::list<std::string> > categoriesToAdd,Mber::MberPtr<std::list<std::string> > categoriesToRemove );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Reads an Achievement Definition in the application associated with the access_token.
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::AchievementDefinition > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_definitionId;					// The definition id
                public:
                    Request::Request( Mber::EntityID definitionId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Disables an Achievement Definition in the application associated with the access_token. Disabled definitions can no longer be earned.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_definitionId;					// The definition id
                public:
                    Request::Request( Mber::EntityID definitionId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Lists all Achievement Definitions defined in the application associated with the access_token.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<bool > truncated;
                    Mber::MberPtr<std::list<Mber::AchievementDefinition> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::list<Mber::DefinitionStatus> > m_setStatuses;					// A set of statuses which must be included on the definition in order to be returned
                    Mber::MberPtr<std::list<Mber::DefinitionStatus> > m_unsetStatuses;					// A set of statuses which must *not* be included on the definition in order to be returned
                    Mber::MberPtr<std::list<std::string> > m_categories;					// The list of categories to filter definitions by.
                public:
                    Request::Request( Mber::MberPtr<std::list<Mber::DefinitionStatus> > setStatuses,Mber::MberPtr<std::list<Mber::DefinitionStatus> > unsetStatuses,Mber::MberPtr<std::list<std::string> > categories );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // An earned achievement instance
        namespace Earn{ 
            // Creates an earned Achievement for the given entity.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > achievementInstanceId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_definitionId;					// The id of the definition to create an instance for
                    Mber::EntityPointer m_entity;					// The entity that earned the achievement
                    Mber::MberPtr<std::list<Mber::Property> > m_properties;					// List of properties to set
                public:
                    Request::Request( Mber::EntityID definitionId,Mber::EntityPointer entity,Mber::MberPtr<std::list<Mber::Property> > properties );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Returns a set of profiles that have earned the given achievement definition.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::EarnedAchievements> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_definitionId;					// The id of the definition to create an instance for
                public:
                    Request::Request( Mber::EntityID definitionId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Operations on achievement instances
        namespace Instance{ 
            // Revokes an achievement instance from the entity that earned it
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_achievementInstanceId;					// The instance to revoke
                    Mber::EntityID m_definitionId;					// The achievement definition of the achievement to revoke
                    Mber::EntityPointer m_entity;					// The entity that earned the achievement
                public:
                    Request::Request( std::string achievementInstanceId,Mber::EntityID definitionId,Mber::EntityPointer entity );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Lists the achievement instances earned by an entity
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::AchievementInstance> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_entityId;					// The entity to find achievements on.
                    Mber::EntityType m_entityType;					// The type of the entity that earned the achievement.
                public:
                    Request::Request( std::string entityId,Mber::EntityType entityType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for dealing with campaigns
    namespace campaign{ 
        // Manipulates campaigns in the application associated with the access token
        namespace Campaign{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > campaignId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// The name of the campaign
                    Mber::EntityID m_digitalGood;					// The digital good definition to generate keys for
                    Mber::MberPtr<std::string > m_description;					// A description of this campaign
                    Mber::MberPtr<std::string > m_url;					// The URL where keys can be redeemed
                    Mber::MberPtr<Mber::EntityID > m_invalidWords;					// An Mber document listing words (separated by new lines) that won&#39;t appear in printed keys
                public:
                    Request::Request( std::string name,Mber::EntityID digitalGood,Mber::MberPtr<std::string > description,Mber::MberPtr<std::string > url,Mber::MberPtr<Mber::EntityID > invalidWords );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Campaign > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_campaignId;					// The ID of the campaign to read
                public:
                    Request::Request( Mber::EntityID campaignId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Campaign> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                    bool truncated;
                    long totalPages;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<uint64_t > m_page;					// The page in the results to return. Pages start at 1.
                    Mber::MberPtr<uint64_t > m_maxResults;					// Can be used to specify the maximum number of results to return.  Will be limited to the global maximum number of results by default and may never return more than this.
                public:
                    Request::Request( Mber::MberPtr<uint64_t > page,Mber::MberPtr<uint64_t > maxResults );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_campaignId;					// The ID of the campaign to update
                    Mber::MberPtr<std::string > m_name;					// The name of the campaign
                    Mber::MberPtr<Mber::EntityID > m_digitalGood;					// The digital good definition to generate keys for
                    Mber::MberPtr<std::string > m_description;					// A description of this campaign
                    Mber::MberPtr<std::string > m_url;					// The URL where keys can be redeemed
                    Mber::MberPtr<Mber::EntityID > m_invalidWords;					// An Mber document listing words (separated by new lines) that won&#39;t appear in printed keys
                public:
                    Request::Request( Mber::EntityID campaignId,Mber::MberPtr<std::string > name,Mber::MberPtr<Mber::EntityID > digitalGood,Mber::MberPtr<std::string > description,Mber::MberPtr<std::string > url,Mber::MberPtr<Mber::EntityID > invalidWords );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_campaignId;					// The ID of the campaign to delete
                public:
                    Request::Request( Mber::EntityID campaignId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Manipulates keys associated with a campaign
        namespace Keys{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > documentId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_campaignId;					// The ID of the campaign to generate keys for
                    uint64_t m_numberOfKeys;					// The number of keys to generate
                    std::string m_outputDocumentName;					// The name of the document to put created keys in
                    Mber::MberPtr<Mber::EntityID > m_outputDirectory;					// The directory to put created keys in
                    Mber::MberPtr<Mber::KeyFormat > m_keyFormat;					// The format the keys will show up in
                public:
                    Request::Request( Mber::EntityID campaignId,uint64_t numberOfKeys,std::string outputDocumentName,Mber::MberPtr<Mber::EntityID > outputDirectory,Mber::MberPtr<Mber::KeyFormat > keyFormat );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for dealing with digital goods
    namespace digitalGood{ 
        // Creates a Digital Good definition in the application associated with the access_token.
        namespace Definition{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > definitionId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// The name of the digital good definition
                    Mber::MberPtr<std::string > m_documentId;					// The id of the document associated with this digital good, if there is one.
                    bool m_autoClaim;					// Flag indicating if the digital good is automatically claimed upon being granted
                    Mber::MberPtr<std::list<Mber::DigitalGoodPropertyDefinition> > m_properties;					// List of property definitions
                    Mber::MberPtr<std::list<Mber::EntityID> > m_redeemableFor;					// List of digital good definitions this good is redeemable for
                    Mber::MberPtr<uint64_t > m_ttl;					// The time in seconds a digital good created from this definition exists for
                    Mber::MberPtr<bool > m_selfGrant;					// Flags this digital good as one users can grant to themselves
                    Mber::MberPtr<uint64_t > m_selfGrantCount;					// The maximum number of times this digital good can be self granted
                    Mber::MberPtr<bool > m_emailOnGrant;					// If true, an email will be sent to the owner when an instance of this digital good is granted.
                    Mber::MberPtr<bool > m_emailOnClaim;					// If true, an email will be sent to the owner when an instance of this digital good is claimed.
                    Mber::MberPtr<std::list<Mber::Reward> > m_redemptionRewards;					// List of reward entities to be rewarded to the owner when claimed by another user.
                    Mber::MberPtr<std::list<std::string> > m_categories;					// List of categories the digital good definition falls under.
                public:
                    Request::Request( std::string name,Mber::MberPtr<std::string > documentId,bool autoClaim,Mber::MberPtr<std::list<Mber::DigitalGoodPropertyDefinition> > properties,Mber::MberPtr<std::list<Mber::EntityID> > redeemableFor,Mber::MberPtr<uint64_t > ttl,Mber::MberPtr<bool > selfGrant,Mber::MberPtr<uint64_t > selfGrantCount,Mber::MberPtr<bool > emailOnGrant,Mber::MberPtr<bool > emailOnClaim,Mber::MberPtr<std::list<Mber::Reward> > redemptionRewards,Mber::MberPtr<std::list<std::string> > categories );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Updates an existing digital good definition in the application associated with the access_token.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_definitionId;					// The id of the definition to update
                    std::string m_name;					// The name of the digital good definition
                    bool m_autoClaim;					// Flag indicating if the digital good is automatically claimed upon being granted
                    Mber::MberPtr<std::list<Mber::EntityID> > m_redeemableFor;					// List of digital good definitions this good is redeemable for
                    Mber::MberPtr<uint64_t > m_ttl;					// The time in seconds a digital good created from this definition exists for
                    Mber::MberPtr<bool > m_selfGrant;					// Flags this digital good as one users can grant to themselves
                    Mber::MberPtr<uint64_t > m_selfGrantCount;					// The maximum number of times this digital good can be self granted
                    Mber::MberPtr<bool > m_emailOnGrant;					// If true, an email will be sent to the owner when an instance of this digital good is granted.
                    Mber::MberPtr<bool > m_emailOnClaim;					// If true, an email will be sent to the owner when an instance of this digital good is claimed.
                    Mber::MberPtr<std::list<Mber::Reward> > m_redemptionRewards;					// List of reward entities to be rewarded to the owner when claimed by another user.
                    Mber::MberPtr<std::list<std::string> > m_categoriesToAdd;					// Additional categories to add to this digital good definition.
                    Mber::MberPtr<std::list<std::string> > m_categoriesToRemove;					// Categories to be removed from this digital good defintion.
                public:
                    Request::Request( Mber::EntityID definitionId,std::string name,bool autoClaim,Mber::MberPtr<std::list<Mber::EntityID> > redeemableFor,Mber::MberPtr<uint64_t > ttl,Mber::MberPtr<bool > selfGrant,Mber::MberPtr<uint64_t > selfGrantCount,Mber::MberPtr<bool > emailOnGrant,Mber::MberPtr<bool > emailOnClaim,Mber::MberPtr<std::list<Mber::Reward> > redemptionRewards,Mber::MberPtr<std::list<std::string> > categoriesToAdd,Mber::MberPtr<std::list<std::string> > categoriesToRemove );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Returns an existing Digital Good definition in the application associated with the access_token.
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::DigitalGoodDefinition > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_definitionId;					// The definition id
                public:
                    Request::Request( Mber::EntityID definitionId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Deletes an existing Digital Good definition in the application associated with the access_token.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_definitionId;					// The definition id
                public:
                    Request::Request( Mber::EntityID definitionId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Lists all DigitalGood definitions defined in the application associated with the access_token.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<bool > truncated;
                    Mber::MberPtr<std::list<Mber::DigitalGoodDefinition> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::list<Mber::DefinitionStatus> > m_setStatuses;					// A set of statuses which must be included on the definition in order to be returned
                    Mber::MberPtr<std::list<Mber::DefinitionStatus> > m_unsetStatuses;					// A set of statuses which must *not* be included on the definition in order to be returned
                    Mber::MberPtr<std::list<std::string> > m_categories;					// The categories by which to filter digital good definitions.
                public:
                    Request::Request( Mber::MberPtr<std::list<Mber::DefinitionStatus> > setStatuses,Mber::MberPtr<std::list<Mber::DefinitionStatus> > unsetStatuses,Mber::MberPtr<std::list<std::string> > categories );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // A granted digital good instance
        namespace Granted{ 
            // Grants a Digital Good instance to the given entity.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > instanceId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_definitionId;					// The id of the definition to create an instance for
                    Mber::EntityPointer m_entity;					// The entity to grant the digital good to
                    Mber::MberPtr<std::list<Mber::Property> > m_properties;					// List of properties to set
                public:
                    Request::Request( Mber::EntityID definitionId,Mber::EntityPointer entity,Mber::MberPtr<std::list<Mber::Property> > properties );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // A claimed digital good
        namespace Claimed{ 
            // Claims a granted Digital Good instance.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityPointer m_entity;					// The entity to grant the digital good to
                    std::string m_instanceId;					// The id of the digital good to claim
                    Mber::MberPtr<std::list<Mber::Property> > m_properties;					// List of properties to set
                public:
                    Request::Request( Mber::EntityPointer entity,std::string instanceId,Mber::MberPtr<std::list<Mber::Property> > properties );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Operations on Digital Good instances
        namespace Instance{ 
            // Revokes a Digital Good instance from the entity that claimed it
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_digitalGoodInstanceId;					// The instance to revoke
                    Mber::EntityID m_definitionId;					// The definition id of the Digital Good to revoke
                    Mber::EntityPointer m_entity;					// The entity that earned the achievement
                public:
                    Request::Request( std::string digitalGoodInstanceId,Mber::EntityID definitionId,Mber::EntityPointer entity );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Lists the Digital Good instances claimed by an entity
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::DigitalGoodInstance> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_entityId;					// The entity to find achievements on.
                    Mber::EntityType m_entityType;					// The type of the entity that earned the achievement.
                    Mber::MberPtr<std::list<std::string> > m_definitionIds;					// Only return digital goods with these definition IDs
                    Mber::MberPtr<std::list<Mber::EntitlementState> > m_states;					// Only return digital goods with these states
                    Mber::MberPtr<bool > m_includeExpired;					// Include digital goods that are expired
                    Mber::MberPtr<std::list<std::string> > m_categories;					// The categories by which to filter digital good instances.
                public:
                    Request::Request( std::string entityId,Mber::EntityType entityType,Mber::MberPtr<std::list<std::string> > definitionIds,Mber::MberPtr<std::list<Mber::EntitlementState> > states,Mber::MberPtr<bool > includeExpired,Mber::MberPtr<std::list<std::string> > categories );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // A redeemed digital good
        namespace Redeemed{ 
            // Claims a granted Digital Good instance and redeems it for its configured goods.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_instanceId;					// The id of the digital good to redeem
                    Mber::EntityID m_definitionId;					// The definition id of the Digital Good to revoke
                public:
                    Request::Request( std::string instanceId,Mber::EntityID definitionId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for managing entitlements including Achievements and DigitalGoods.
    namespace entitlement{ 
        // APIs around entitlement categories.
        namespace Category{ 
            // Returns all the available entitlement categories in the system.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<std::string> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                    bool truncated;
                    long totalPages;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<uint64_t > m_page;					// The page in the results to return. Pages start at 1.
                    Mber::MberPtr<uint64_t > m_maxResults;					// Can be used to specify the maximum number of results to return.  Will be limited to the global maximum number of results by default and may never return more than this.
                public:
                    Request::Request( Mber::MberPtr<uint64_t > page,Mber::MberPtr<uint64_t > maxResults );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for dealing with user data
    namespace data{ 
        // A user data object
        namespace Document{ 
            // Must either provide a &#39;template&#39; and &#39;content&#39; or provide the deprecated form of &#39;scope&#39; and &#39;data&#39;
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > documentId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// Name of the document being stored.
                    Mber::MberPtr<std::string > m_alias;					// The optional alias of the document. Must be unique within the parent directory.
                    Mber::MberPtr<std::list<std::string> > m_tags;					// Initial set of tags (eg: Article ) to apply to the data for querying purposes.
                    Mber::MberPtr<std::list<Mber::Property> > m_properties;
                    Mber::MberPtr<Mber::EntityID > m_documentTemplate;					// Document template to create data with
                    Mber::MberPtr<std::string > m_content;					// JSON content to store and validate against the template
                    Mber::MberPtr<Mber::EntityID > m_directoryId;					// The unique identifier of the directory for the document. If not supplied the root directory for the application will be used
                    Mber::MberPtr<bool > m_validateAgainstTemplate;					// Flag to control whether document template validation happens
                    Mber::MberPtr<uint64_t > m_maxVersionsToKeep;					// The maximum number of versions to preserve.
                    Mber::MberPtr<bool > m_keepAllVersions;					// If true, all versions of this document will be preserved.
                    Mber::MberPtr<uint64_t > m_maxTimeToKeep;					// The maximum amount of time to preserve versions of this document.
                public:
                    Request::Request( std::string name,Mber::MberPtr<std::string > alias,Mber::MberPtr<std::list<std::string> > tags,Mber::MberPtr<std::list<Mber::Property> > properties,Mber::MberPtr<Mber::EntityID > documentTemplate,Mber::MberPtr<std::string > content,Mber::MberPtr<Mber::EntityID > directoryId,Mber::MberPtr<bool > validateAgainstTemplate,Mber::MberPtr<uint64_t > maxVersionsToKeep,Mber::MberPtr<bool > keepAllVersions,Mber::MberPtr<uint64_t > maxTimeToKeep );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Document > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_documentId;					// The unique identifier of the document
                    Mber::MberPtr<uint64_t > m_version;					// The optional version of the document to read. Defaults to the most recent version.
                public:
                    Request::Request( Mber::EntityID documentId,Mber::MberPtr<uint64_t > version );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::string > m_name;					// Name of the document being stored.
                    Mber::MberPtr<std::string > m_alias;					// The optional alias of the document. Must be unique within the parent directory.
                    Mber::EntityID m_documentId;					// The unique identifier of the document
                    Mber::MberPtr<int > m_version;					// The current version of the document that is attempting to update.  Include to make sure the document wasn&#39;t edited before this update.
                    Mber::MberPtr<std::list<std::string> > m_tags;					// Set of tags to apply to the data for querying purposes.
                    Mber::MberPtr<std::list<Mber::Property> > m_properties;
                    Mber::MberPtr<std::string > m_content;					// JSON content to store and validate against the template
                    Mber::MberPtr<Mber::EntityID > m_directoryId;					// The unique identifier of the directory for the document. If not supplied the directory will not be updated.
                    Mber::MberPtr<std::list<std::string> > m_tagsToAdd;					// The set of tags to add to the document
                    Mber::MberPtr<std::list<std::string> > m_tagsToRemove;					// The set of tags to remove from the document
                    Mber::MberPtr<bool > m_validateAgainstTemplate;					// Flag to control whether document template validation happens
                    Mber::MberPtr<uint64_t > m_maxVersionsToKeep;					// The maximum number of versions of this document to keep.
                    Mber::MberPtr<uint64_t > m_maxTimeToKeep;					// The maximum amount of time to keep old versions of this document.
                    Mber::MberPtr<bool > m_keepAllVersions;					// If true, all future versions of this document will be preserved.
                    Mber::MberPtr<int > m_restoreVersion;					// A previous version of the document to restore.
                public:
                    Request::Request( Mber::MberPtr<std::string > name,Mber::MberPtr<std::string > alias,Mber::EntityID documentId,Mber::MberPtr<int > version,Mber::MberPtr<std::list<std::string> > tags,Mber::MberPtr<std::list<Mber::Property> > properties,Mber::MberPtr<std::string > content,Mber::MberPtr<Mber::EntityID > directoryId,Mber::MberPtr<std::list<std::string> > tagsToAdd,Mber::MberPtr<std::list<std::string> > tagsToRemove,Mber::MberPtr<bool > validateAgainstTemplate,Mber::MberPtr<uint64_t > maxVersionsToKeep,Mber::MberPtr<uint64_t > maxTimeToKeep,Mber::MberPtr<bool > keepAllVersions,Mber::MberPtr<int > restoreVersion );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_documentId;					// The unique identifier of the document
                public:
                    Request::Request( Mber::EntityID documentId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Lists documents in the system by name and id.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Document> > results;
                    Mber::MberPtr<bool > truncated;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<bool > m_expandTags;					// Flag indicating whether or not to return results that take into account tagged tags
                    Mber::MberPtr<std::list<std::string> > m_tags;					// Set of tags that must be present on the document
                public:
                    Request::Request( Mber::MberPtr<bool > expandTags,Mber::MberPtr<std::list<std::string> > tags );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // A schema describing a document
        namespace DocumentTemplate{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > documentTemplateId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// The name of the template
                    std::string m_templateId;					// The template object
                    Mber::MberPtr<uint64_t > m_maxVersionsToKeep;					// The maximum number of versions to preserve.
                    Mber::MberPtr<uint64_t > m_maxTimeToKeep;					// The maximum amount of time to preserve versions of this document.
                    Mber::MberPtr<bool > m_keepAllVersions;					// If true, all versions of this document template will be preserved.
                public:
                    Request::Request( std::string name,std::string templateId,Mber::MberPtr<uint64_t > maxVersionsToKeep,Mber::MberPtr<uint64_t > maxTimeToKeep,Mber::MberPtr<bool > keepAllVersions );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::DocumentTemplate > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_documentTemplateId;					// The unique identifier of the document created
                public:
                    Request::Request( Mber::EntityID documentTemplateId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::DocumentTemplate> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                public:
                    Request::Request(  );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_documentTemplateId;					// The unique identifier of the document created
                    std::string m_name;					// The name of the template
                    Mber::MberPtr<std::string > m_templateId;					// The template
                    Mber::MberPtr<int > m_version;					// The current version of the document template that is being updated. Include to make sure the template wasn&#39;t edited before this update.
                    Mber::MberPtr<uint64_t > m_maxVersionsToKeep;					// The maximum number of versions to preserve.
                    Mber::MberPtr<uint64_t > m_maxTimeToKeep;					// The maximum amount of time to preserve versions of this document.
                    Mber::MberPtr<bool > m_keepAllVersions;					// If true, all future versions of this document will be preserved.
                public:
                    Request::Request( Mber::EntityID documentTemplateId,std::string name,Mber::MberPtr<std::string > templateId,Mber::MberPtr<int > version,Mber::MberPtr<uint64_t > maxVersionsToKeep,Mber::MberPtr<uint64_t > maxTimeToKeep,Mber::MberPtr<bool > keepAllVersions );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_documentTemplateId;					// The unique identifier of the document created
                public:
                    Request::Request( Mber::EntityID documentTemplateId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // A group of documents or other directories
        namespace Directory{ 
            // Creates a new directory. Directories must have a name and may have any number of documents or other directories. Directories may also have an optional alias that is unique within the application.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > directoryId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// Name of the directory being created.
                    Mber::MberPtr<std::string > m_alias;					// An optional alias for this directory that is unique with the scope of the application.
                    Mber::MberPtr<Mber::EntityID > m_parent;					// The directory to create this directory in. To create a directory in the root of the application, use the application id as the parent.
                    Mber::MberPtr<std::list<Mber::EntityPointer> > m_children;					// Documents or other directories to move into this directory.  Moving a document into this directory will remove it from the other directory.  This action will not be allowed if any one of the supplied pointers is not a Document or Directory.
                public:
                    Request::Request( std::string name,Mber::MberPtr<std::string > alias,Mber::MberPtr<Mber::EntityID > parent,Mber::MberPtr<std::list<Mber::EntityPointer> > children );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Returns the contents of a given directory.
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Directory > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_directoryId;					// The unique identifier of the directory
                public:
                    Request::Request( Mber::EntityID directoryId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Updates an existing directory. The name, parent, and/or children may be changed.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::string > m_name;					// Name of the document being stored.
                    Mber::MberPtr<std::string > m_alias;					// An optional alias for this directory that is unique with the scope of the application.
                    Mber::EntityID m_directoryId;					// The unique identifier of the directory
                    Mber::MberPtr<Mber::EntityID > m_parent;					// An optional directory to move this directory into. The directory parent must be in the same application as the token being used. If not supplied, the directory will be created in the top level of the file system for the application in token.
                    Mber::MberPtr<std::list<Mber::EntityPointer> > m_children;					// Documents or other directories to move into this directory.  Moving a document into this directory will remove it from the other directory.  This action will not be allowed if any one of the supplied pointers is not a Document or Directory.
                public:
                    Request::Request( Mber::MberPtr<std::string > name,Mber::MberPtr<std::string > alias,Mber::EntityID directoryId,Mber::MberPtr<Mber::EntityID > parent,Mber::MberPtr<std::list<Mber::EntityPointer> > children );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Deletes a given directory and all the documents and directories in that directory. NOTE: you cannot delete the root directory for an application.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_directoryId;					// The unique identifier of the directory to delete
                public:
                    Request::Request( Mber::EntityID directoryId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Lists the contents of the root directory for the application in the token.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Directory> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                public:
                    Request::Request(  );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // A structured document query
        namespace DocumentQuery{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Document> > results;
                    Mber::MberPtr<bool > truncated;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::list<Mber::EntityID> > m_documentTemplateId;					// The templates to search for
                    Mber::Query m_query;					// The structured query to execute
                    Mber::MberPtr<Mber::EntityID > m_applicationId;					// The application to search within. If provided, templates will be ignored and all templates will be searched
                public:
                    Request::Request( Mber::MberPtr<std::list<Mber::EntityID> > documentTemplateId,Mber::Query query,Mber::MberPtr<Mber::EntityID > applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Uploads a file into the Mber file system.  Files uploaded into Mber can be downloaded, but cannot be editied, based on a template, or searched on by content.
        namespace Upload{ 
            // Initiates an upload with Mber, verifying permissions and file metadata information and returns a URL to be used for the client side upload.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > documentId;
                    Mber::MberPtr<std::string > url;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// Name of the document being uploaded.
                    Mber::MberPtr<std::string > m_alias;					// The optional alias name for a document being uploaded.
                    long m_size;					// The size of the data to store - maximum is 5GB.
                    Mber::MberPtr<std::string > m_contentType;					// The http content type of the document.  Defaults to application/octet-stream if not provided.
                    Mber::MberPtr<std::list<std::string> > m_tags;					// Initial set of tags (eg: Article ) to apply to the data for querying purposes.
                    Mber::MberPtr<Mber::EntityID > m_directoryId;					// The unique identifier of the directory for the document. If not supplied the root directory for the application will be used
                public:
                    Request::Request( std::string name,Mber::MberPtr<std::string > alias,long size,Mber::MberPtr<std::string > contentType,Mber::MberPtr<std::list<std::string> > tags,Mber::MberPtr<Mber::EntityID > directoryId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Overwrites an uploaded file within Mber, verifying permissions and file metadata information and returns a url to be used for the client side upload.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > url;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_documentId;					// The unique identifier of the document being updated.
                    Mber::MberPtr<std::string > m_name;					// Name of the document being uploaded.
                    Mber::MberPtr<std::string > m_alias;					// The optional alias name for a document being uploaded.
                    Mber::MberPtr<long > m_size;					// The size of the data to store - maximum is 5GB. Required if filename is changed.
                    Mber::MberPtr<std::string > m_contentType;					// The http content type of the document.  Defaults to application/octet-stream if not provided.
                    Mber::MberPtr<std::list<std::string> > m_tags;					// Initial set of tags (eg: Article ) to apply to the data for querying purposes.
                    Mber::MberPtr<Mber::EntityID > m_directoryId;					// The unique identifier of the directory for the document. If not supplied the root directory for the application will be used
                public:
                    Request::Request( Mber::EntityID documentId,Mber::MberPtr<std::string > name,Mber::MberPtr<std::string > alias,Mber::MberPtr<long > size,Mber::MberPtr<std::string > contentType,Mber::MberPtr<std::list<std::string> > tags,Mber::MberPtr<Mber::EntityID > directoryId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Downloads an existing file from Mber.  Returns a URL for the client side download
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_documentId;					// The unique identifier of the document being read.
                    Mber::MberPtr<std::string > m_contentType;					// The http content type of the document being read.  Unlike CREATE and UPDATE, if a content-type is not provided, there should be no content-type header added when using the returned URL. If it is provided, then a matching content-type header must be in the GET request to the returned url.
                public:
                    Request::Request( Mber::EntityID documentId,Mber::MberPtr<std::string > contentType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // API entry-point to control the document re-indexing process
        namespace DocumentReindexing{ 
            // Sends events to the DocumentReindexing process
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EventType m_eventType;					// The type of event to send to the DocumentReindexing process
                    Mber::EntityID m_applicationId;					// The ID of the application to index documents in
                    Mber::MberPtr<std::string > m_templateId;					// The ID of the document template to index documents in
                    Mber::MberPtr<bool > m_deleteIndex;					// Flag to determine if the index should be deleted
                public:
                    Request::Request( Mber::EventType eventType,Mber::EntityID applicationId,Mber::MberPtr<std::string > templateId,Mber::MberPtr<bool > deleteIndex );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // An AWS S3 bucket configuration
        namespace S3BucketConfig{ 
            // Configure an AWS S3 bucket for a given application
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > bucketConfigId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_applicationId;					// The application this bucket belongs to
                    std::string m_name;					// The name of the S3 bucket
                    std::string m_accessKey;					// An AWS access key ID
                    std::string m_secretKey;					// An AWS secret key
                    int m_urlTtl;					// Used for signing URLs, the time when the signature expires, specified as the number of seconds since the epoch.
                public:
                    Request::Request( std::string applicationId,std::string name,std::string accessKey,std::string secretKey,int urlTtl );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Update a S3 bucket configuration
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_applicationId;					// The application this bucket belongs to
                    Mber::MberPtr<std::string > m_name;					// The name of the S3 bucket
                    Mber::MberPtr<std::string > m_accessKey;					// An AWS access key ID
                    Mber::MberPtr<std::string > m_secretKey;					// An AWS secret key
                    Mber::MberPtr<int > m_urlTtl;					// Used for signing URLs, the time when the signature expires, specified as the number of seconds since the epoch.
                public:
                    Request::Request( std::string applicationId,Mber::MberPtr<std::string > name,Mber::MberPtr<std::string > accessKey,Mber::MberPtr<std::string > secretKey,Mber::MberPtr<int > urlTtl );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Fetch details of an S3 bucket configuration
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::S3BucketConfig > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_applicationId;					// The application this bucket belongs to
                public:
                    Request::Request( std::string applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete the S3 bucket configuration for the given application
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_applicationId;					// The application this bucket belongs to
                public:
                    Request::Request( std::string applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Operations to manage document history configuration.
        namespace DocumentHistoryConfiguration{ 
            // Updates the document history configuration for an entity.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_applicationId;					// The application for which to read document history configuration.
                    Mber::MberPtr<uint64_t > m_maxVersionsToKeep;					// The maximum number of versions to keep for the entity.
                    Mber::MberPtr<uint64_t > m_maxTimeToKeep;					// The amount of time (in seconds) to keep versions for the entity.
                    Mber::MberPtr<bool > m_keepAllVersions;					// If true, all future versions of this document will be preserved.
                public:
                    Request::Request( std::string applicationId,Mber::MberPtr<uint64_t > maxVersionsToKeep,Mber::MberPtr<uint64_t > maxTimeToKeep,Mber::MberPtr<bool > keepAllVersions );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Gets the document history configuraiton for an entity.
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::DocumentHistoryConfiguration > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_applicationId;					// The application for which to read document history configuration.
                public:
                    Request::Request( std::string applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Deletes the document history configuration for an entity.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_applicationId;					// The application for which to read document history configuration.
                public:
                    Request::Request( std::string applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Operations to manage document history configuration.
        namespace ApplicationDocumentRestore{ 
            // Rolls back documents in the given entity: application, directory, etc.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_applicationId;					// The id of the application in which to roll back documents.
                    Mber::MberPtr<bool > m_cascading;					// Indicates whether the rollback should apply to documents in nested scopes.
                    Mber::MberPtr<uint64_t > m_rollbackTime;					// The point in time in which to rollback the documents to.
                    Mber::MberPtr<bool > m_earliestVersion;					// A flag indicating whether or not to roll documents back to the earliest version stored.
                public:
                    Request::Request( std::string applicationId,Mber::MberPtr<bool > cascading,Mber::MberPtr<uint64_t > rollbackTime,Mber::MberPtr<bool > earliestVersion );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Lists all the versions in the system for a given document.
        namespace DocumentVersion{ 
            // Lists all the versions for the given document in the system.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::DocumentVersion> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_documentId;					// The id of the document to list versions for.
                    Mber::MberPtr<uint64_t > m_maxResults;					// The maximum number of results to return.
                    Mber::MberPtr<bool > m_descending;					// The order in which to return results. If true, the latest versions will be returned first.
                public:
                    Request::Request( std::string documentId,Mber::MberPtr<uint64_t > maxResults,Mber::MberPtr<bool > descending );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // A CDN configuration
        namespace CDNConfig{ 
            // Add a new CDN configuration
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::CDNType m_cdnType;					// The type or provider of the CDN
                    std::string m_name;					// The human readable name for this CDN configuration
                    Mber::MberPtr<std::string > m_defaultPath;					// The default path or container that a resource will be synced to
                    Mber::MberPtr<std::string > m_username;					// The username used for authenticating CDN requests
                    Mber::MberPtr<std::string > m_password;					// The password used for authenticating CDN requests
                    Mber::MberPtr<std::string > m_storageUsername;					// The username used for authenticating storage requests (if different from CDN requests).
                    Mber::MberPtr<std::string > m_storagePassword;					// The password used for authenticating storage requests (if different from CDN requests).
                    Mber::MberPtr<std::string > m_apiKey;					// The API key used for authenticating CDN requests
                    Mber::MberPtr<std::string > m_account;					// The CDN customer/tenant account name
                    Mber::MberPtr<std::string > m_cdnHost;					// The host, if any, where the cached files reside. Used for cache invalidation/purging.
                    Mber::MberPtr<std::string > m_baseContainer;					// The base container for all object paths. This will be excluded from absolute URLs when purging the CDN cache for a given object.
                public:
                    Request::Request( Mber::CDNType cdnType,std::string name,Mber::MberPtr<std::string > defaultPath,Mber::MberPtr<std::string > username,Mber::MberPtr<std::string > password,Mber::MberPtr<std::string > storageUsername,Mber::MberPtr<std::string > storagePassword,Mber::MberPtr<std::string > apiKey,Mber::MberPtr<std::string > account,Mber::MberPtr<std::string > cdnHost,Mber::MberPtr<std::string > baseContainer );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Read the details of a given CDN configuration
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::CDNConfig > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_id;					// The unique id of the CDN configuration
                public:
                    Request::Request( Mber::EntityID id );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Update an existing CDN configuration
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_id;					// The unique id of the CDN configuration
                    Mber::MberPtr<Mber::CDNType > m_cdnType;					// The type or provider of the CDN
                    Mber::MberPtr<std::string > m_name;					// The human readable name for this CDN configuration
                    Mber::MberPtr<std::string > m_defaultPath;					// The default path or container that a resource will be synced to
                    Mber::MberPtr<std::string > m_username;					// The username used for authenticating CDN requests
                    Mber::MberPtr<std::string > m_password;					// The password used for authenticating CDN requests
                    Mber::MberPtr<std::string > m_storageUsername;					// The username used for authenticating storage requests (if different from CDN requests).
                    Mber::MberPtr<std::string > m_storagePassword;					// The password used for authenticating storage requests (if different from CDN requests).
                    Mber::MberPtr<std::string > m_apiKey;					// The API key used for authenticating CDN requests
                    Mber::MberPtr<std::string > m_account;					// The CDN customer/tenant account name
                    Mber::MberPtr<std::string > m_cdnHost;					// The host, if any, where the cached files reside. Used for cache invalidation/purging.
                    Mber::MberPtr<std::string > m_baseContainer;					// The base container for all object paths. This will be excluded from absolute URLs when purging the CDN cache for a given object.
                public:
                    Request::Request( Mber::EntityID id,Mber::MberPtr<Mber::CDNType > cdnType,Mber::MberPtr<std::string > name,Mber::MberPtr<std::string > defaultPath,Mber::MberPtr<std::string > username,Mber::MberPtr<std::string > password,Mber::MberPtr<std::string > storageUsername,Mber::MberPtr<std::string > storagePassword,Mber::MberPtr<std::string > apiKey,Mber::MberPtr<std::string > account,Mber::MberPtr<std::string > cdnHost,Mber::MberPtr<std::string > baseContainer );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // List CDN configurations by application
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::CDNConfig> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                public:
                    Request::Request(  );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete the given CDN configuration
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_id;					// The unique id of the CDN configuration
                public:
                    Request::Request( Mber::EntityID id );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Sync a document or directory using the given CDN configuration
        namespace CDNSync{ 
            // Sync a document or directory using the given CDN configuration
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityPointer m_entity;					// The entity to sync
                    Mber::MberPtr<Mber::EntityID > m_cdnConfigId;					// The id of the CDN configuration
                    Mber::MberPtr<std::string > m_resourcePath;					// Optional CDN path with which to sync
                public:
                    Request::Request( Mber::EntityPointer entity,Mber::MberPtr<Mber::EntityID > cdnConfigId,Mber::MberPtr<std::string > resourcePath );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Remove CDN configuration on a document or directory. This will trigger CDN storage and cache deletion.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_entityId;					// The entity whose CDN configuration to delete
                    Mber::EntityType m_entityType;					// The type of the entity
                    Mber::MberPtr<Mber::EntityID > m_cdnConfigId;					// The id of the CDN configuration
                public:
                    Request::Request( std::string entityId,Mber::EntityType entityType,Mber::MberPtr<Mber::EntityID > cdnConfigId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // List all CDN sync configurations for the given entity
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::CDNConfig> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_entityId;					// The id of the entity whose CDN sync configurations will be fetched
                    Mber::EntityType m_entityType;					// The type fo the entity whose CDN sync configurations will be fetched.
                public:
                    Request::Request( std::string entityId,Mber::EntityType entityType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Operations to manage document history configuration.
        namespace DirectoryDocumentRestore{ 
            // Rolls back documents in the given directory.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_directoryId;					// The id of the directory in which to roll back documents.
                    Mber::MberPtr<bool > m_cascading;					// Indicates whether the rollback should apply to documents in nested directories.
                    Mber::MberPtr<uint64_t > m_rollbackTime;					// The point in time in which to rollback the documents to.
                    Mber::MberPtr<bool > m_earliestVersion;					// A flag indicating whether or not to roll documents back to the earliest version stored.
                public:
                    Request::Request( std::string directoryId,Mber::MberPtr<bool > cascading,Mber::MberPtr<uint64_t > rollbackTime,Mber::MberPtr<bool > earliestVersion );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service exposing an OpenID 2.0 Consumer complient interface
    namespace openId{ 
        // Creates an OpenId authentication request that can be used to validate the supplied OpenID identity with the appropriate OpenID provider
        namespace AuthRequest{ 
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > providerUrl;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_identity;					// The unique OpenID identity for the OP
                    std::string m_return_to;					// The URL the OpenID provider should respond to.
                public:
                    Request::Request( std::string identity,std::string return_to );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // The end-point for Relying Parties to sign in with a user validated by another OpenID Provider
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > authorization_code;
                    Mber::MberPtr<std::string > scope;
                    Mber::MberPtr<std::string > redirect_uri;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_AuthRequestId;					// The id of the originating auth request in the relying party process that was passed back in the providerUrl.
                    std::string m_return_to;					// The URL the OpenID provider responded to, including the query string if any
                    std::string m_client_id;					// The mber application to authenticate against
                    Mber::MberPtr<std::string > m_redirect_uri;					// validate against client redirect_uris; if not provided, use default uri for client
                    std::list<Mber::Property> m_properties;					// The OpenID properties supplied from the OpenID Provider after authenticating a user
                    Mber::MberPtr<std::string > m_scope;					// space delimited case sensitive strings; requested
                public:
                    Request::Request( std::string AuthRequestId,std::string return_to,std::string client_id,Mber::MberPtr<std::string > redirect_uri,std::list<Mber::Property> properties,Mber::MberPtr<std::string > scope );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // The MBer OpenID provider end-point
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > mode;
                    Mber::MberPtr<std::string > responseText;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::list<Mber::Property> m_properties;					// The OpenID parameters sent to Mber to validate a user
                public:
                    Request::Request( std::list<Mber::Property> properties );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Handles management of open id providers in the system
        namespace OpenIdProvider{ 
            // Updates the openid provider information for the given application.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_applicationId;					// The id of the application to set a provider on
                    std::string m_domain;					// The domain to associated with the application
                    std::string m_identity;					// The identity to send to Mber to initiate communication with the OpenId provider.
                public:
                    Request::Request( Mber::EntityID applicationId,std::string domain,std::string identity );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Deletes the openid provider information for the given application.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_applicationId;					// The id of the application to set a provider on
                public:
                    Request::Request( Mber::EntityID applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Returns the openid provider information for the given application.
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Provider > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_applicationId;					// The id of the application to set a provider on
                public:
                    Request::Request( Mber::EntityID applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Lists the available OpenId providers for this instance of Mber
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Provider> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                public:
                    Request::Request(  );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // The metrics service
    namespace Metrics{ 
        // Returns historical metrics for a given entity.  The total number of events that can be returned from this service is limited to 300.
        namespace History{ 
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::EventEnvelope> > results;
                    Mber::MberPtr<bool > truncated;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_entityId;					// The id of the entity to obtain historical events for.
                    Mber::EntityType m_entityType;					// The type of the entity.
                    uint64_t m_startDate;					// The start date for the query.
                    Mber::MberPtr<uint64_t > m_endDate;					// The end date for the query. If not supplied the end date is now.
                    Mber::MberPtr<bool > m_descending;					// If true, the results are returned from the end date to the start date, otherwise they are returned from the start date to the end date. True by default unless otherwise supplied.
                    Mber::MberPtr<int > m_maxResults;					// Set to the maximum number of results to be returned.  The minimum of this setting and the system level maximum results will be returned.
                    Mber::MberPtr<bool > m_includeChildApplications;					// If true, the scope of the search for events for this entity will include child applications of the application specified by the applicationId parameter. If false, the scope will only include the application specified by the applicationId parameter.
                    Mber::MberPtr<int > m_version;					// The metric schema version to use. Version 1 is the original metric schema, version 2 is the new metric schema. Will default to version 1.
                public:
                    Request::Request( std::string entityId,Mber::EntityType entityType,uint64_t startDate,Mber::MberPtr<uint64_t > endDate,Mber::MberPtr<bool > descending,Mber::MberPtr<int > maxResults,Mber::MberPtr<bool > includeChildApplications,Mber::MberPtr<int > version );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // API for getting historical events on a profile.
        namespace ProfileHistory{ 
            // Get historical events on a profile.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::EventEnvelope> > results;
                    Mber::MberPtr<bool > truncated;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The profile to get history on.
                    uint64_t m_startDate;					// Get historical events from here until now.
                    Mber::MberPtr<std::list<Mber::ProfileHistoryFilter> > m_filterBy;					// Only include events that match these types in the results.
                    Mber::MberPtr<int > m_version;					// The metric schema version to use. Version 1 is the original metric schema, version 2 is the new metric schema. Will default to version 1.
                public:
                    Request::Request( std::string profileId,uint64_t startDate,Mber::MberPtr<std::list<Mber::ProfileHistoryFilter> > filterBy,Mber::MberPtr<int > version );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Returns time series metrics for a given event name and type (CRUD operation).  The total number of event counts that can be returned from this service is limited to 300.
        namespace OverTime{ 
            // Retrieves raw metrics over time by their type. Must have permission to the mber metrics application or the entity in question.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::EventEnvelope> > results;
                    Mber::MberPtr<bool > truncated;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_eventName;					// The name of the event to obtain time series data for.
                    Mber::EventType m_eventType;					// The type of the event.
                    uint64_t m_startDate;					// The start date for the query.
                    Mber::MberPtr<uint64_t > m_endDate;					// The end date for the query. If not supplied the end date is now.
                    Mber::MberPtr<bool > m_descending;					// If true, the results are returned from the end date to the start date, otherwise they are returned from the start date to the end date. True by default unless otherwise supplied.
                    Mber::MberPtr<int > m_maxResults;					// Set to the maximum number of results to be returned.  The minimum of this setting and the system level maximum results will be returned.
                    Mber::MberPtr<bool > m_includeChildApplications;					// If true, the scope of the search for events for this entity will include child applications of the application specified by the access token&#39;s applicationId parameter. If false, the scope will only include the application specified by the access token&#39;s applicationId parameter.
                    Mber::MberPtr<int > m_version;					// The metric schema version to use. Version 1 is the original metric schema, version 2 is the new metric schema. Will default to version 1.
                public:
                    Request::Request( std::string eventName,Mber::EventType eventType,uint64_t startDate,Mber::MberPtr<uint64_t > endDate,Mber::MberPtr<bool > descending,Mber::MberPtr<int > maxResults,Mber::MberPtr<bool > includeChildApplications,Mber::MberPtr<int > version );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Returns counts of time series metrics for a given event name and type (CRUD operation).  The total number of event counts that can be returned from this service is limited to 300.
        namespace CountOverTime{ 
            // Retrieves raw metrics over time by their type. Must have permission to the mber metrics application or the entity in question. If format is supplied then table will be returned instead of counts.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Count> > results;
                    Mber::MberPtr<bool > truncated;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_eventName;					// The name of the event to obtain time series data for.
                    Mber::EventType m_eventType;					// The type of the event.
                    Mber::TimeUnit m_timeUnit;					// The unit of time the metrics should be counted at.  Only SECONDS, MINUTES, and HOURS is supported.
                    uint64_t m_startDate;					// The start date for the query.
                    Mber::MberPtr<uint64_t > m_endDate;					// The end date for the query. If not supplied the end date is now.
                    Mber::MberPtr<bool > m_descending;					// If true, the results are returned from the end date to the start date, otherwise they are returned from the start date to the end date. True by default unless otherwise supplied.
                    Mber::MberPtr<bool > m_includeChildApplications;					// If true, the scope of the search for events for this entity will include child applications of the application specified by the access token&#39;s applicationId parameter. If false, the scope will only include the application specified by the access token&#39;s applicationId parameter.
                    Mber::MberPtr<int > m_version;					// The metric schema version to use. Version 1 is the original metric schema, version 2 is the new metric schema. Will default to version 1.
                public:
                    Request::Request( std::string eventName,Mber::EventType eventType,Mber::TimeUnit timeUnit,uint64_t startDate,Mber::MberPtr<uint64_t > endDate,Mber::MberPtr<bool > descending,Mber::MberPtr<bool > includeChildApplications,Mber::MberPtr<int > version );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Returns the sum of time series metric values for a given event name and type (CRUD operation).
        namespace SumOverTime{ 
            // Retrieves the sum of metric counts over time by their type. Must have permission to the mber metrics application or the entity in question. Sums will be rounded to the day of start and end dates.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<long > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_eventName;					// The name of the event to obtain time series data for.
                    Mber::EventType m_eventType;					// The type of the event.
                    Mber::MberPtr<uint64_t > m_startDate;					// The start date for the query.
                    Mber::MberPtr<uint64_t > m_endDate;					// The end date for the query. If not supplied the end date is now.
                    Mber::MberPtr<bool > m_includeChildApplications;					// If true, the scope of the search for events for this entity will include child applications of the application specified by the applicationId parameter. If false, the scope will only include the application specified by the applicationId parameter.
                    Mber::MberPtr<int > m_version;					// The metric schema version to use. Version 1 is the original metric schema, version 2 is the new metric schema. Will default to version 1.
                public:
                    Request::Request( std::string eventName,Mber::EventType eventType,Mber::MberPtr<uint64_t > startDate,Mber::MberPtr<uint64_t > endDate,Mber::MberPtr<bool > includeChildApplications,Mber::MberPtr<int > version );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Returns a list of event names and types of events that can be used in queries in the metrics system for the given entity id.
        namespace AvailableEvents{ 
            // Retrieves events and the types of those events in the metrics system for the given entity id. Must have permission to the mber metrics application or the entity in question.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::AvailableEvent> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<int > m_version;					// The metric schema version to use. Version 1 is the original metric schema, version 2 is the new metric schema. Will default to version 1.
                public:
                    Request::Request( Mber::MberPtr<int > version );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Returns a running total of the event specified in the range specified. Each summation will include counts over the time unit provided.
        namespace RollingSumOverTime{ 
            // Returns a running total of counts for an event over a period of time. Each new value added is the count from the last value to the the end of the time unit specified.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Count> > results;
                    Mber::MberPtr<bool > truncated;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_eventName;					// The name of the event to gather the running total for.
                    Mber::EventType m_eventType;					// The type of event to gather the running total for.
                    Mber::MberPtr<uint64_t > m_startDate;					// The date at which to begin summation of events.
                    Mber::MberPtr<uint64_t > m_endDate;					// The date at which to end summation of events.
                    Mber::TimeUnit m_timeUnit;					// The unit of time over which to sum events.
                    Mber::MberPtr<bool > m_descending;					// If true, the results are returned from the end date to the start date, otherwise they are returned from the start date to the end date. False by default unless otherwise supplied.
                    Mber::MberPtr<bool > m_includeChildApplications;					// If true, the scope of the search for events for this entity will include child applications of the application specified by the applicationId parameter. If false, the scope will only include the application specified by the applicationId parameter.
                    Mber::MberPtr<int > m_version;					// The metric schema version to use. Version 1 is the original metric schema, version 2 is the new metric schema. Will default to version 1.
                public:
                    Request::Request( std::string eventName,Mber::EventType eventType,Mber::MberPtr<uint64_t > startDate,Mber::MberPtr<uint64_t > endDate,Mber::TimeUnit timeUnit,Mber::MberPtr<bool > descending,Mber::MberPtr<bool > includeChildApplications,Mber::MberPtr<int > version );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for handling requests from adyen
    namespace adyen{ 
        // The REST end point for Adyen notification callbacks
        namespace Notification{ 
            // callbacks are made to a POST endpoint
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > accepted;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::string > m_basicAuthUserName;					// Basic authentication username
                    Mber::MberPtr<std::string > m_basicAuthPassword;					// Basic authentication password
                    Mber::MberPtr<bool > m_live;					// boolean (true/false) indicating if the notification originated from the LIVE or TEST payment systems.
                    Mber::MberPtr<std::string > m_eventCode;					// The event type of the notification.
                    Mber::MberPtr<std::string > m_pspReference;					// The reference we assigned to the payment or modification
                    Mber::MberPtr<std::string > m_originalReference;					// If this is a notification for a modification request this will be the pspReference that was originally assigned to the authorisation. For a payment it will be blank.
                    Mber::MberPtr<std::string > m_merchantReference;					// This reference you assigned to the original payment.
                    Mber::MberPtr<std::string > m_merchantAccountCode;					// The merchant account the payment or modification was processed with.
                    Mber::MberPtr<std::string > m_eventDate;					// The time the event was generated.
                    Mber::MberPtr<bool > m_success;					// Whether or not the event succeeded (boolean true/false).
                    Mber::MberPtr<std::string > m_paymentMethod;					// The payment method used (only for AUTHORISATION). e.g. visa, mc, ideal, elv, wallie, etc...
                    Mber::MberPtr<std::string > m_operations;					// The modification operations supported by this payment as a list of strings (only for AUTHORISATION). The operations will tell you whether you need to capture the payment (if you don&#39;t have auto-capture set up), whether you can cancel the payment (before capture) or if you can refund the payment (after it has been captured).
                    Mber::MberPtr<std::string > m_reason;					// Text field with information depending on whether the result is successful or not. For AUTHORISATION events with the success field set to true and a payment method of visa, mc or amex this field contains the authorisation code, last 4 digits of the card, and the expiry date in the following format: 6 digit Authorisation Code:Last 4 digits:Expiry Date (e.g. 874574:1935:11/2012). When the success field is set to false it gives a reason as to why it was refused. For REPORT_AVAILABLE it contains the URL where the report can be downloaded from.
                    Mber::MberPtr<long > m_value;					// The amount (if relevant) associated with the payment or modification.
                    Mber::MberPtr<Mber::CurrencyCode > m_currency;					// The currencyCode that the value is in (if relevant).
                public:
                    Request::Request( Mber::MberPtr<std::string > basicAuthUserName,Mber::MberPtr<std::string > basicAuthPassword,Mber::MberPtr<bool > live,Mber::MberPtr<std::string > eventCode,Mber::MberPtr<std::string > pspReference,Mber::MberPtr<std::string > originalReference,Mber::MberPtr<std::string > merchantReference,Mber::MberPtr<std::string > merchantAccountCode,Mber::MberPtr<std::string > eventDate,Mber::MberPtr<bool > success,Mber::MberPtr<std::string > paymentMethod,Mber::MberPtr<std::string > operations,Mber::MberPtr<std::string > reason,Mber::MberPtr<long > value,Mber::MberPtr<Mber::CurrencyCode > currency );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for handling requests from BoaCompra
    namespace boaCompra{ 
        // The REST end point for BoaCompra notification callbacks
        namespace Notification{ 
            // Callbacks from BoaCompra are POSTed to this end point
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::string > m_store_id;					// Virtual Store identification on BoaCompra.com
                    Mber::MberPtr<std::string > m_transaction_id;					// Order identification on BoaCompra.com
                    Mber::MberPtr<std::string > m_order_id;					// Order identification on the Virtual Store
                    Mber::MberPtr<long > m_amount;					// Order total without any separators; the last two digits correspond to the decimal part of the value
                    Mber::MberPtr<Mber::CurrencyCode > m_currency_code;					// Order country ISO code
                    Mber::MberPtr<std::string > m_payment_id;					// Identification of the payment method used
                    Mber::MberPtr<std::string > m_country_payment;					// Country ISO Code (2 characters) from which the payments methods must be displayed without showing the country selection page to the final user.
                    Mber::MberPtr<std::string > m_test_mode;					// Parameter used to indicate that a transaction will be in test mode. Can be used the value “1” to test integration and “0” to production environment.
                public:
                    Request::Request( Mber::MberPtr<std::string > store_id,Mber::MberPtr<std::string > transaction_id,Mber::MberPtr<std::string > order_id,Mber::MberPtr<long > amount,Mber::MberPtr<Mber::CurrencyCode > currency_code,Mber::MberPtr<std::string > payment_id,Mber::MberPtr<std::string > country_payment,Mber::MberPtr<std::string > test_mode );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for dealing with commerce
    namespace commerce{ 
        // An Mber store offer
        namespace Offer{ 
            // Create a new offer in the target application
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > offerId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// Human readable name for the offer
                    Mber::MberPtr<uint64_t > m_stock;					// The number of remaining times this offer can be consumed; Infinite if unspecified
                    Mber::MberPtr<std::list<Mber::OfferItem> > m_inputs;					// The items provided to consume this offer
                    Mber::MberPtr<std::list<Mber::OfferItem> > m_outputs;					// The items distributed upon consumption of this offer
                    Mber::MberPtr<std::list<std::string> > m_categories;					// A collection of arbitrary strings denoting the categories this offer falls into.
                    Mber::MberPtr<std::list<Mber::OfferItem> > m_rewards;					// Items distributed on consumption of this offer to a recipient other than the owner of this offer.
                public:
                    Request::Request( std::string name,Mber::MberPtr<uint64_t > stock,Mber::MberPtr<std::list<Mber::OfferItem> > inputs,Mber::MberPtr<std::list<Mber::OfferItem> > outputs,Mber::MberPtr<std::list<std::string> > categories,Mber::MberPtr<std::list<Mber::OfferItem> > rewards );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Find all offers in the target application
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Offer> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::list<std::string> > m_categories;					// The categories to list offers from.
                public:
                    Request::Request( Mber::MberPtr<std::list<std::string> > categories );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Get the details of a specific offer
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Offer > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_offerId;					// The id of the offer to read
                    Mber::MberPtr<Mber::EntityID > m_application;					// The application to find the offer in. If not supplied an access token must be supplied with the request to denote the application.
                public:
                    Request::Request( Mber::EntityID offerId,Mber::MberPtr<Mber::EntityID > application );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete an existing offer
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_offerId;					// The offer to delete
                public:
                    Request::Request( Mber::EntityID offerId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Change the configuration of an existing offer
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_offerId;					// The offer to update
                    std::string m_name;					// Human readable name for the offer
                    Mber::MberPtr<uint64_t > m_stock;					// The number of remaining times this offer can be consumed; Infinite if unspecified
                    Mber::MberPtr<std::list<Mber::OfferItem> > m_inputs;					// The items provided to consume this offer. Any existing inputs will be deleted and replaced with the provided inputs. If any existing input is not provided, it will be removed. To preserve an existing input, include it in the request along with any new inputs. To remove an input, simply exclude it from the request.
                    Mber::MberPtr<std::list<Mber::OfferItem> > m_outputs;					// The items distributed upon consumption of this offer. Any existing outputs will be deleted and replaced with the provided outputs. If any existing output is not provided, it will be removed. To preserve an existing output, include it in the request along with any new outputs. To remove an output, simply exclude it from the request.
                    Mber::MberPtr<std::list<std::string> > m_categories;					// A collection of arbitrary strings denoting the categories this offer falls into. Any existing categories will be deleted and replaced with the provided categories. If an existing category is not provided, they will be removed. To preserve existing categories, provide them in the request along with any new categories. To remove a category, simply exlude it from the request.
                    Mber::MberPtr<std::list<Mber::OfferItem> > m_rewards;					// Items distributed on consumption of this offer to a recipient other than the recipient of the offer outputs.
                public:
                    Request::Request( Mber::EntityID offerId,std::string name,Mber::MberPtr<uint64_t > stock,Mber::MberPtr<std::list<Mber::OfferItem> > inputs,Mber::MberPtr<std::list<Mber::OfferItem> > outputs,Mber::MberPtr<std::list<std::string> > categories,Mber::MberPtr<std::list<Mber::OfferItem> > rewards );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // An Mber store
        namespace Store{ 
            // Create a new store in the target application
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > storeId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// Human readable name for the store
                    Mber::MberPtr<std::list<Mber::EntityID> > m_offers;					// The offers to make available in the store
                public:
                    Request::Request( std::string name,Mber::MberPtr<std::list<Mber::EntityID> > offers );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Find all stores in the target application
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Store> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<Mber::EntityID > m_application;					// The application to find stores in
                public:
                    Request::Request( Mber::MberPtr<Mber::EntityID > application );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Get the details of a specific store
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Store > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_storeId;					// The id of the store to read
                    Mber::MberPtr<Mber::EntityID > m_application;					// The application to find stores in
                    Mber::MberPtr<std::list<std::string> > m_categories;					// The categories to include offers from
                public:
                    Request::Request( Mber::EntityID storeId,Mber::MberPtr<Mber::EntityID > application,Mber::MberPtr<std::list<std::string> > categories );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete an existing store
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_storeId;					// The store to delete
                public:
                    Request::Request( Mber::EntityID storeId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Change the configuration of an existing store
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_storeId;					// The store to update
                    Mber::MberPtr<std::string > m_name;					// Human readable name for the store
                    Mber::MberPtr<std::list<Mber::EntityID> > m_addOffers;					// The offers to make available in the store
                    Mber::MberPtr<std::list<Mber::EntityID> > m_removeOffers;					// The offers to remove from the store
                public:
                    Request::Request( Mber::EntityID storeId,Mber::MberPtr<std::string > name,Mber::MberPtr<std::list<Mber::EntityID> > addOffers,Mber::MberPtr<std::list<Mber::EntityID> > removeOffers );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // A cart for a store
        namespace Cart{ 
            // Read the current state of a cart for a store
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Invoice > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_storeId;					// The store to get the cart contents in
                    Mber::MberPtr<std::string > m_paymentRedirectUri;					// The uri to redirect to after payment
                public:
                    Request::Request( Mber::EntityID storeId,Mber::MberPtr<std::string > paymentRedirectUri );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Set the current state of a cart for a store
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Invoice > invoice;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_storeId;					// The store to set the cart contents in
                    Mber::MberPtr<std::list<Mber::EntityID> > m_offers;					// The offers to include in the cart
                    Mber::MberPtr<std::string > m_paymentRedirectUri;					// The uri to redirect to after payment
                public:
                    Request::Request( Mber::EntityID storeId,Mber::MberPtr<std::list<Mber::EntityID> > offers,Mber::MberPtr<std::string > paymentRedirectUri );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Handles checkout process for an invoice
        namespace Checkout{ 
            // Conduct checkout with the given inputs
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_storeId;					// The store to checkout the cart from
                    Mber::MberPtr<Mber::RealMoneyInput > m_realMoneyInput;					// The real money input, if available
                public:
                    Request::Request( Mber::EntityID storeId,Mber::MberPtr<Mber::RealMoneyInput > realMoneyInput );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // For handling of profile bound invoices
        namespace ProfileInvoice{ 
            // Lookup invoices associated with the profile
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Invoice> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The profile to find invoices on
                    Mber::MberPtr<Mber::InvoiceStatus > m_status;					// Filter by invoice status
                    Mber::MberPtr<Mber::EntityID > m_applicationId;					// Filter by application bound to the invoice
                    Mber::MberPtr<Mber::EntityID > m_storeId;					// Filter by store bound to the invoice
                    Mber::MberPtr<uint64_t > m_minUpdatedTime;					// Filter by earliest updated time
                    Mber::MberPtr<uint64_t > m_maxUpdatedTime;					// Filter by latest updated time
                public:
                    Request::Request( std::string profileId,Mber::MberPtr<Mber::InvoiceStatus > status,Mber::MberPtr<Mber::EntityID > applicationId,Mber::MberPtr<Mber::EntityID > storeId,Mber::MberPtr<uint64_t > minUpdatedTime,Mber::MberPtr<uint64_t > maxUpdatedTime );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // For handling of invoices in an application
        namespace ApplicationInvoice{ 
            // Lookup invoices associated with the application
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Invoice> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<Mber::InvoiceStatus > m_status;					// Filter by invoice status
                    Mber::MberPtr<std::string > m_profileId;					// Filter by profile bound to the invoice
                    Mber::MberPtr<Mber::EntityID > m_storeId;					// Filter by store bound to the invoice
                    Mber::MberPtr<uint64_t > m_minUpdatedTime;					// Filter by earliest updated time
                    Mber::MberPtr<uint64_t > m_maxUpdatedTime;					// Filter by latest updated time
                public:
                    Request::Request( Mber::MberPtr<Mber::InvoiceStatus > status,Mber::MberPtr<std::string > profileId,Mber::MberPtr<Mber::EntityID > storeId,Mber::MberPtr<uint64_t > minUpdatedTime,Mber::MberPtr<uint64_t > maxUpdatedTime );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // The preferred currency for a profile
        namespace ProfileCurrency{ 
            // Get the preferred currency for the target profile
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::CurrencyCode > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The profile to look up the preferred currency for
                    Mber::EntityID m_applicationId;					// The application to look up the preferred currency in
                public:
                    Request::Request( std::string profileId,Mber::EntityID applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // An Mber virtual currency
        namespace VirtualCurrency{ 
            // Create a new virtual currency in the target application
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > virtualCurrencyId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// Human readable name for the currency
                    Mber::DeductionRule m_deductionRule;					// Rule to use when automatically deducting currency
                    Mber::MberPtr<int > m_walletTtl;					// The time to live, in hours, for an individual wallet lot. If unspecified, wallet lots will not expire
                public:
                    Request::Request( std::string name,Mber::DeductionRule deductionRule,Mber::MberPtr<int > walletTtl );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Find all currencies in the target application
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::VirtualCurrency> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<bool > m_disabledSpending;					// Flag indicating if spending is disabled
                    Mber::MberPtr<bool > m_disabledEarning;					// Flag indicating if earning is disabled
                public:
                    Request::Request( Mber::MberPtr<bool > disabledSpending,Mber::MberPtr<bool > disabledEarning );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Get the details of a specific currency
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::VirtualCurrency > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_virtualCurrencyId;					// The id of the currency to read
                public:
                    Request::Request( Mber::EntityID virtualCurrencyId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Change the configuration of an existing currency
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_virtualCurrencyId;					// The currency to update
                    std::string m_name;					// Human readable name for the currency
                    bool m_disabledSpending;					// Flag indicating if spending is disabled
                    bool m_disabledEarning;					// Flag indicating if earning is disabled
                    Mber::DeductionRule m_deductionRule;					// Rule to use when automatically deducting currency
                    Mber::MberPtr<int > m_walletTtl;					// The time to live, in hours, for an individual wallet lot. If unspecified, wallet lots will not expire
                public:
                    Request::Request( Mber::EntityID virtualCurrencyId,std::string name,bool disabledSpending,bool disabledEarning,Mber::DeductionRule deductionRule,Mber::MberPtr<int > walletTtl );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete a currency
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_virtualCurrencyId;					// The id of the currency to delete
                public:
                    Request::Request( Mber::EntityID virtualCurrencyId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // An individual pool of funds within a profile wallet
        namespace WalletLot{ 
            // Create a new lot for a user
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > lotId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_virtualCurrencyId;					// The currency to assign
                    std::string m_profileId;					// The recipient of the currency
                    double m_amount;					// The amount to assign
                public:
                    Request::Request( Mber::EntityID virtualCurrencyId,std::string profileId,double amount );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Read a lot for a user
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::WalletLot > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_virtualCurrencyId;					// The currency to assign
                    std::string m_lotId;					// The lot
                    std::string m_profileId;					// The recipient of the currency
                public:
                    Request::Request( Mber::EntityID virtualCurrencyId,std::string lotId,std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Updates a wallet lot
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_virtualCurrencyId;					// The currency to assign
                    std::string m_lotId;					// The lot
                    double m_amountChange;					// An amount to change the lot by; may be positive for a deposit or negative for a deduction
                    std::string m_profileId;					// The recipient of the currency
                public:
                    Request::Request( Mber::EntityID virtualCurrencyId,std::string lotId,double amountChange,std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // List lots for a user
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::WalletLot> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_virtualCurrencyId;					// Currency to read lots for
                    std::string m_profileId;					// Profile to lookup lots on
                public:
                    Request::Request( Mber::EntityID virtualCurrencyId,std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Summarized contents of a profile&#39;s currency
        namespace Wallet{ 
            // Get the currency totals within an application
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Wallet > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_entityId;					// The ID of the entity that owns the currency
                    Mber::MberPtr<Mber::EntityType > m_entityType;					// The type of the entity that owns the currency
                public:
                    Request::Request( std::string entityId,Mber::MberPtr<Mber::EntityType > entityType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Perform currency deductions according to a currency&#39;s specified rules
        namespace Deduction{ 
            // Create a deduction over wallet lots by following a given currency&#39;s rules
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_virtualCurrencyId;					// The currency to deduct
                    double m_amount;					// The amount to deduct
                    Mber::MberPtr<std::string > m_reason;					// An optional string that can be supplied to note the reason for the deduction
                    Mber::EntityPointer m_recipient;					// The recipient of the deduction
                public:
                    Request::Request( Mber::EntityID virtualCurrencyId,double amount,Mber::MberPtr<std::string > reason,Mber::EntityPointer recipient );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Manages the catalog of available items within offers
        namespace Catalog{ 
            // Requests the catalog of items for the application
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::EntityPointer> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<Mber::EntityType > m_entityType;					// Optional entity type to filter by
                public:
                    Request::Request( Mber::MberPtr<Mber::EntityType > entityType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Updates the current state of the catalog to add or remove items
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::list<Mber::EntityPointer> > m_addItems;					// Items to include in the catalog
                    Mber::MberPtr<std::list<Mber::EntityPointer> > m_removeItems;					// Items to exclude from the catalog
                public:
                    Request::Request( Mber::MberPtr<std::list<Mber::EntityPointer> > addItems,Mber::MberPtr<std::list<Mber::EntityPointer> > removeItems );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Assigns payment providers to applications.
        namespace PaymentProvider{ 
            // Adds a payment provider to the target application and marks it as active.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > providerId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::RealMoneyTransactionProvider m_provider;					// The real money transaction provider to associate with this application
                    Mber::MberPtr<std::string > m_merchantId;					// The id in the providers system that is associated with the target application in Mber.
                    Mber::MberPtr<std::string > m_paymentPageId;					// The optional id for the payment page to use in the Payment Provider&#39;s system
                    Mber::MberPtr<std::string > m_merchantSecret;					// The password or key to use for access to the Payment Provider&#39;s system
                    Mber::MberPtr<std::string > m_paymentPageUri;					// The optional URI for the payment page to use in the Payment Provider&#39;s system
                    Mber::MberPtr<std::string > m_notificationUri;					// The optional URI that the payment provider should use to contact Mber.
                    Mber::MberPtr<bool > m_testMode;					// The optional flag to indicate this provider is in test mode
                public:
                    Request::Request( Mber::RealMoneyTransactionProvider provider,Mber::MberPtr<std::string > merchantId,Mber::MberPtr<std::string > paymentPageId,Mber::MberPtr<std::string > merchantSecret,Mber::MberPtr<std::string > paymentPageUri,Mber::MberPtr<std::string > notificationUri,Mber::MberPtr<bool > testMode );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Returns the details of a specific payment provider regardless of it&#39;s status.  Can be used to read deleted provider information.
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::PaymentProvider > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_providerId;					// The id of the configured payment provider. The payment provider is tracked at time of purchase on the invoice.
                public:
                    Request::Request( std::string providerId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Lists the active payment providers configured for the target application.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::PaymentProvider> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<bool > m_activeOnly;					// Set to true to return only active providers or false to return active and deactivated providers.
                public:
                    Request::Request( Mber::MberPtr<bool > activeOnly );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Removes a payment provider from an application making it inactive. Once deactivated you must create a new provider, you cannot reactivate an old provider.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_providerId;					// The id of the configured payment provider to delete.
                public:
                    Request::Request( std::string providerId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Allows a user to grant a Steam Application Offer to another user.
        namespace SteamOfferGrant{ 
            // Grants a steam application offer directly to a user.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_steamApplication;					// The Steam unique identifier of the application.
                    std::string m_profileId;					// The id of the profile to be granted the steam offer.
                public:
                    Request::Request( Mber::EntityID steamApplication,std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Removes a steam application offer directly from a user.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_steamApplication;					// The Steam unique identifier of the application.
                    std::string m_profileId;					// The id of the profile from which to remove the steam offer.
                public:
                    Request::Request( Mber::EntityID steamApplication,std::string profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // A third party affiliate
        namespace Affiliate{ 
            // Adds an affiliate
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > affiliateId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// The human readable name for this affiliate
                    Mber::MberPtr<std::string > m_profileId;					// An optional profileId associated with this affiliate
                public:
                    Request::Request( std::string name,Mber::MberPtr<std::string > profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Read an affiliate&#39;s details
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Affiliate > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_affiliateId;					// The affiliate&#39;s unique identifier
                public:
                    Request::Request( Mber::EntityID affiliateId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Update an affiliate&#39;s details
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Affiliate > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_affiliateId;					// The affiliate&#39;s unique identifier
                    Mber::MberPtr<std::string > m_name;					// Human readable name for the affiliate
                    Mber::MberPtr<std::string > m_profileId;					// The Mber profile associated with this affiliate
                public:
                    Request::Request( Mber::EntityID affiliateId,Mber::MberPtr<std::string > name,Mber::MberPtr<std::string > profileId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete an affiliate
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_affiliateId;					// The affiliate&#39;s unique identifier
                public:
                    Request::Request( Mber::EntityID affiliateId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // List all affiliates for a given application
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Affiliate> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                public:
                    Request::Request(  );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Count total referrals by referrer and application.
        namespace ReferralCount{ 
            // Get count of referred accounts by referrer
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::ReferralCount> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<bool > m_convertedOnly;					// Only count referrals that resulted in a converted/paying profile
                public:
                    Request::Request( Mber::MberPtr<bool > convertedOnly );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Referral purchase totals by referrer and input
        namespace ReferralPurchaseTotals{ 
            // Get the purchase totals by referrer and input
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::ReferralEntityTotals> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityType m_inputType;					// The entity type of the purchase input by which to filter
                public:
                    Request::Request( Mber::EntityType inputType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for managing servers, games, etc.
    namespace serverManagement{ 
        // A server heartbeat
        namespace Heartbeat{ 
            // Updates the latest heartbeat on a server
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_serverId;					// The server to heartbeat
                    Mber::MberPtr<std::string > m_status;					// The status of the server
                    Mber::MberPtr<uint64_t > m_currentUsers;					// The number of users currently on the server
                    Mber::MberPtr<uint64_t > m_userCapacity;					// The maximum number of users that can be on the server
                    Mber::MberPtr<double > m_utilization;					// The percent the server is utilized. A number between 0 and 1 allowing servers to supply their own calculation.
                public:
                    Request::Request( Mber::EntityID serverId,Mber::MberPtr<std::string > status,Mber::MberPtr<uint64_t > currentUsers,Mber::MberPtr<uint64_t > userCapacity,Mber::MberPtr<double > utilization );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // A server managed by a registered application
        namespace Server{ 
            // Registers a new server
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > serverId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// Human readable name for the server
                    std::string m_host;					// Server host
                    Mber::MberPtr<int > m_port;					// Server port
                    Mber::MberPtr<int > m_heartbeatInterval;					// The number of seconds this server can go without a heartbeat before reporting it is offline
                    std::string m_serverType;					// The arbitrary type of the server
                    Mber::MberPtr<uint64_t > m_userCapacity;					// The maximum number of users that can be on the server
                public:
                    Request::Request( std::string name,std::string host,Mber::MberPtr<int > port,Mber::MberPtr<int > heartbeatInterval,std::string serverType,Mber::MberPtr<uint64_t > userCapacity );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Read an existing server
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Server > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_serverId;					// The server to fetch
                public:
                    Request::Request( Mber::EntityID serverId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Updates an existing server
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_serverId;					// The server to update
                    std::string m_name;					// Human readable name for the server
                    std::string m_host;					// Server host
                    Mber::MberPtr<int > m_port;					// Server port
                    Mber::MberPtr<int > m_heartbeatInterval;					// The number of seconds this server can go without a heartbeat before reporting it is offline
                    Mber::MberPtr<std::string > m_serverType;					// The arbitrary type of the server
                    Mber::MberPtr<std::string > m_status;					// The status of the server
                    Mber::MberPtr<uint64_t > m_currentUsers;					// The number of users currently on the server
                    Mber::MberPtr<uint64_t > m_userCapacity;					// The maximum number of users that can be on the server
                    Mber::MberPtr<double > m_utilization;					// The percent the server is utilized. A number between 0 and 1 allowing servers to supply their own calculation.
                public:
                    Request::Request( Mber::EntityID serverId,std::string name,std::string host,Mber::MberPtr<int > port,Mber::MberPtr<int > heartbeatInterval,Mber::MberPtr<std::string > serverType,Mber::MberPtr<std::string > status,Mber::MberPtr<uint64_t > currentUsers,Mber::MberPtr<uint64_t > userCapacity,Mber::MberPtr<double > utilization );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Delete an existing server
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_serverId;					// The server to fetch
                public:
                    Request::Request( Mber::EntityID serverId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Get servers defined in the application that meet optional filter parameters.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Server> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                    bool truncated;
                    long totalPages;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::MberPtr<std::list<std::string> > m_serverType;					// Optional type(s) of server to filter by
                    Mber::MberPtr<std::list<std::string> > m_status;					// Optional status(es) of a server to filter by
                    Mber::MberPtr<Mber::ServerState > m_state;					// Optional state of a server to filter by
                    Mber::MberPtr<uint64_t > m_minUsers;					// If provided, only servers with this many users or more will be returned.
                    Mber::MberPtr<uint64_t > m_maxUsers;					// If provided, only servers with this many users or fewer will be returned.
                    Mber::MberPtr<uint64_t > m_minCapacity;					// If provided, only servers with a capacity greater than or equal to this number will be returned.
                    Mber::MberPtr<uint64_t > m_maxCapacity;					// If provided, only servers with a capacity less than or equal to this number will be returned.
                    Mber::MberPtr<double > m_minUtilization;					// If provided, only servers with this level of utilization or higher will be returned.
                    Mber::MberPtr<double > m_maxUtilization;					// If provided, only servers with this level of utilization or lower will be returned.
                    Mber::MberPtr<uint64_t > m_page;					// The page in the results to return. Pages start at 1.
                    Mber::MberPtr<uint64_t > m_maxResults;					// Can be used to specify the maximum number of results to return.  Will be limited to the global maximum number of results by default and may never return more than this.
                public:
                    Request::Request( Mber::MberPtr<std::list<std::string> > serverType,Mber::MberPtr<std::list<std::string> > status,Mber::MberPtr<Mber::ServerState > state,Mber::MberPtr<uint64_t > minUsers,Mber::MberPtr<uint64_t > maxUsers,Mber::MberPtr<uint64_t > minCapacity,Mber::MberPtr<uint64_t > maxCapacity,Mber::MberPtr<double > minUtilization,Mber::MberPtr<double > maxUtilization,Mber::MberPtr<uint64_t > page,Mber::MberPtr<uint64_t > maxResults );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Handles active lobby tracking
        namespace Lobby{ 
            // Register a new active lobby
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > lobbyId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_serverId;					// The server to register the lobby on
                    std::string m_name;					// Human readable name of the lobby
                    Mber::MberPtr<std::list<std::string> > m_profiles;					// Initial participants in the lobby
                public:
                    Request::Request( std::string serverId,std::string name,Mber::MberPtr<std::list<std::string> > profiles );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Reads an active lobby
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Lobby > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_lobbyId;					// The lobby to read
                public:
                    Request::Request( std::string lobbyId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Updates an existing active lobby
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_lobbyId;					// The server to register the lobby on
                    std::string m_name;					// Human readable name of the lobby
                    Mber::MberPtr<std::list<std::string> > m_addProfiles;					// Profiles to add to the lobby
                    Mber::MberPtr<std::list<std::string> > m_removeProfiles;					// Profiles to remove from the lobby
                public:
                    Request::Request( std::string lobbyId,std::string name,Mber::MberPtr<std::list<std::string> > addProfiles,Mber::MberPtr<std::list<std::string> > removeProfiles );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Deletes an active lobby
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_lobbyId;					// The lobby to delete
                public:
                    Request::Request( std::string lobbyId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Find lobbies
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Lobby> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_serverId;					// The server to find lobbies on
                public:
                    Request::Request( std::string serverId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Operations for managing mber processes on a node or set of nodes.
        namespace MberProcess{ 
            // Lists the mber processes running on a node or set of nodes.
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<std::string> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                public:
                    Request::Request(  );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Updates the mber process on a node or set of nodes.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_processName;					// The name of the process to update
                    Mber::MberPtr<Mber::EntityID > m_applicationId;					// The scope of the application to update. Should be the application alias.
                    Mber::EventType m_action;					// The type of action to update the process with.
                    Mber::MberPtr<std::list<Mber::Property> > m_properties;					// Configuration for the process to use.
                public:
                    Request::Request( std::string processName,Mber::MberPtr<Mber::EntityID > applicationId,Mber::EventType action,Mber::MberPtr<std::list<Mber::Property> > properties );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // The messaging service
    namespace messaging{ 
        // Provides a mechanism to send email messages to profiles in the system.
        namespace Email{ 
            // Sends the appropriate email message to the given profile.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::list<Mber::EntityPointer> m_to;					// List of profile identifiers to send the email message to.
                    std::list<Mber::EntityPointer> m_cc;					// List of profile identifiers to carbon copy the email message to.
                    std::list<Mber::EntityPointer> m_bcc;					// List of profile identifiers to blind carbon copy the email message to.
                    Mber::MberPtr<Mber::DocumentMessage > m_documentMessage;					// The message represented by documents stored in mber. If not supplied, StringBody must be supplied.
                    Mber::MberPtr<Mber::StringMessage > m_stringMessage;					// The raw message body and subject. If not supplied, DocumentBody must be supplied.
                public:
                    Request::Request( std::list<Mber::EntityPointer> to,std::list<Mber::EntityPointer> cc,std::list<Mber::EntityPointer> bcc,Mber::MberPtr<Mber::DocumentMessage > documentMessage,Mber::MberPtr<Mber::StringMessage > stringMessage );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Provides a mechanism to send an email validation message to profiles in the system.
        namespace EmailValidation{ 
            // Sends the appropriate email validation message to the given profile.
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_profileId;					// The profile to send the email message to.
                    Mber::MberPtr<Mber::EntityID > m_applicationId;					// The optional application context through which to send the email validation message.
                public:
                    Request::Request( std::string profileId,Mber::MberPtr<Mber::EntityID > applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Accepts the validation token and marks the email on the account as valid.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_token;					// The email validation token.
                public:
                    Request::Request( std::string token );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
        // Functions to configure smtp servers for applications in the system.
        namespace EmailConfiguration{ 
            // Configures email settings for an application within mber.
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_host;					// The host name or ip address of smtp server for this application
                    Mber::MberPtr<int > m_port;					// The smpt server port. If useSsl is enabled this should be the ssl port of the smtp server
                    Mber::MberPtr<bool > m_useSsl;					// If true, SSL encryption will be used.  False by default.
                    Mber::MberPtr<bool > m_useTls;					// If true, TLS encryption will be used.  False by default.
                    Mber::MberPtr<std::string > m_userName;					// The user name for the smtp server.
                    Mber::MberPtr<std::string > m_password;					// The password for the smtp server.
                    std::string m_senderEmail;					// The from email address for outgoing messages.
                    Mber::MberPtr<std::string > m_senderName;					// The optional name that outgoing email messages will be from
                public:
                    Request::Request( std::string host,Mber::MberPtr<int > port,Mber::MberPtr<bool > useSsl,Mber::MberPtr<bool > useTls,Mber::MberPtr<std::string > userName,Mber::MberPtr<std::string > password,std::string senderEmail,Mber::MberPtr<std::string > senderName );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Deletes the email configuration settings for an application within mber.
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_applicationId;					// The id of the application the email configuration settings correspond to.
                public:
                    Request::Request( Mber::EntityID applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Returns the email configuration settings for an application within mber.
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::EmailConfig > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    Mber::EntityID m_applicationId;					// The id of the application the email configuration settings correspond to.
                public:
                    Request::Request( Mber::EntityID applicationId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };

    // Service for managing groups in mber
    namespace groups{ 
        // An mber group
        namespace Group{ 
            // Creates a group of entities
            namespace Create{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::string > groupId;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_name;					// Human readable name of the group
                    std::string m_parentId;					// Entity id of the parent in which the group is defined
                    Mber::EntityType m_parentType;					// Entity type of the parent in which the group is defined
                    Mber::EntityType m_groupType;					// Type of entities to be included in the group
                public:
                    Request::Request( std::string name,std::string parentId,Mber::EntityType parentType,Mber::EntityType groupType );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Get the full contents of a specific group
            namespace Read{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::Group > result;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_groupId;					// The unique identifier of the group created
                public:
                    Request::Request( std::string groupId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Find groups by parent
            namespace List{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<std::list<Mber::Group> > results;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_parentId;					// The parent to find groups within
                    Mber::EntityType m_parentType;					// The parent type to find groups within
                    Mber::MberPtr<Mber::EntityType > m_groupType;					// The group type to filter by
                    Mber::MberPtr<std::string > m_name;					// The name to filter by
                public:
                    Request::Request( std::string parentId,Mber::EntityType parentType,Mber::MberPtr<Mber::EntityType > groupType,Mber::MberPtr<std::string > name );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Updates an existing group
            namespace Update{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_groupId;					// The unique identifier of the group
                    Mber::MberPtr<std::string > m_name;					// Human readable name of the group
                    Mber::MberPtr<std::list<std::string> > m_addMembers;					// Members to add to the group
                    Mber::MberPtr<std::list<std::string> > m_removeMembers;					// Members to remove from the group
                public:
                    Request::Request( std::string groupId,Mber::MberPtr<std::string > name,Mber::MberPtr<std::list<std::string> > addMembers,Mber::MberPtr<std::list<std::string> > removeMembers );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
            // Deletes a group
            namespace Delete{
                class Response : public Mber::MberResponse{
                public:
                    virtual ~Response();
                
                    Mber::Status status;
                    Mber::MberPtr<Mber::ErrorResult > errorResult;
                };
                class Request : public Mber::MberRequest<Response>{
                    std::string m_groupId;					// The unique identifier of the group
                public:
                    Request::Request( std::string groupId );
                    virtual MberPtr<Response> execute( std::string uri, std::string* token = 0, std::string* transactionId = 0, std::string* correlationId = 0 );
                };
            };
        };
    };


    // Utility functions
    std::string generateTransactionId();
    std::string base64Encode( const char* buffer, int size );
    std::string base64Decode( std::string buffer );
    
    // Session class
    class MberSession{
        private:
			std::string m_uri;
            std::string m_token;
            std::string m_refreshToken;
            std::string m_profileId;
            std::string m_accountId;
            std::string m_lastError;
            std::string m_displayName;
            MBER_ENTITY_POINTER_LIST* m_ownedEntities;
            bool m_loggedIn;

        public:

			MberSession( void );
			explicit MberSession( const char* const uri );
			~MberSession();
			      void setOwnedEntities(MBER_ENTITY_POINTER_LIST* entities);
			      const MBER_ENTITY_POINTER_LIST* const getOwnedEntities() const;
			      void setToken(const std::string& token);
            std::string* getToken();
            const char* const getRefreshToken() const;
            const char* const getURI() const;
            const char* const getLastError() const;
            void setLoggedIn(bool flag);
            void setProfileId(const std::string& id);
            std::string* getProfileId();
            void setAccountId(const std::string& id);
            const char* const getAccountId() const;
            void setLastError(const std::string& error);
            void setDisplayName(const std::string& name);
            const char* const getDisplayName() const;
            Mber::Status login( Mber::oauth::AccessToken::Create::Request req );
            template <class T> Mber::MberPtr<T> execute( Mber::MberRequest<T> &req ){
                if( m_loggedIn ){
                    return req.execute(m_uri, new std::string(m_token), NULL, NULL);
                } else {
                    return req.execute(m_uri, NULL, NULL, NULL);
                }
            };
    };
};

#ifdef MBER_DLL
#define MBER_DLL_EXPORT(return_type) __declspec(dllexport) return_type __cdecl
#else
#define MBER_DLL_EXPORT(return_type) __declspec(dllimport) return_type __cdecl
#endif

#define MBER_VERSION "0.1.x"

extern "C" {

  struct MBER;
  struct MBER_ENTITY_POINTER;
  struct MBER_PROPERTY;
  struct MBER_PROPERTY_LIST;
  struct MBER_DIGITAL_GOOD_INSTANCE;
  struct MBER_DIGITAL_GOOD_INSTANCE_LIST;

  typedef struct tag_MBER_ARRAY {
    int numElements;
    void** elements;
  } MBER_ARRAY;

  typedef struct tag_MBER_PROFILE {
    char profileId[25];            // The id of the profile
    char accountId[25];            // The id of the account the profile belongs to
    Mber::Region region;           // The region the user is coming from
    char username[256];            // The username of the profile
    char displayname[33];          // The display name of the profile
    char email[256];               // The email address of the profile
    char unvalidated_email[256];   // The unvalidated email address of the profile
    uint64_t dateOfBirth;          // The user's date of birth
    MBER_ARRAY *status;            // Set of statuses set on the profile
  } MBER_PROFILE;

  typedef struct tag_MBER_DOCUMENT {
    char name[65];                 // Name of the document being stored.
    char alias[65];                // Alias of the document.
    char documentId[25];           // The unique identifier of the document
    char *data;                    // The value of the data to store, up to 1MB in size.
    uint64_t size;                 // The size of the data stored.
    int version;                   // The current version of the document.
    char scope[25];                // Application associated with the document
    MBER_ARRAY *tags;              // Initial set of tags (eg: Article ) to apply to the data for querying purposes. Each tag can be up to 64 characters in length.
    MBER_ARRAY *properties;        // An arbitrary set of properties that can be applied to a document
    char documentTemplate[25];     // Document template to create data with
    char *content;                 // JSON content to store and validate against the template
  } MBER_DOCUMENT;

  MBER_DLL_EXPORT(MBER_PROPERTY*) Property_Init();
  MBER_DLL_EXPORT(void) Property_Free(MBER_PROPERTY* property);
  MBER_DLL_EXPORT(void) Property_SetKey(MBER_PROPERTY* const property, const char* const key);
  MBER_DLL_EXPORT(void) Property_SetValue(MBER_PROPERTY* const property, const char* const value);
  MBER_DLL_EXPORT(const char* const) Property_GetKey(const MBER_PROPERTY* const property);
  MBER_DLL_EXPORT(const char* const) Property_GetValue(const MBER_PROPERTY* const property);

  MBER_DLL_EXPORT(MBER_PROPERTY_LIST*) PropertyList_Init();
  MBER_DLL_EXPORT(void) PropertyList_Free(MBER_PROPERTY_LIST* list);
  MBER_DLL_EXPORT(void) PropertyList_FreeAll(MBER_PROPERTY_LIST* list);
  MBER_DLL_EXPORT(unsigned int) PropertyList_Length(const MBER_PROPERTY_LIST* const list);
  MBER_DLL_EXPORT(void) PropertyList_Pop(MBER_PROPERTY_LIST* const list);
  MBER_DLL_EXPORT(void) PropertyList_Push(MBER_PROPERTY_LIST* const list, MBER_PROPERTY* property);
  MBER_DLL_EXPORT(MBER_PROPERTY*) PropertyList_At(const MBER_PROPERTY_LIST* const list, const unsigned int index);

  MBER_DLL_EXPORT(MBER_DIGITAL_GOOD_INSTANCE*) DigitalGoodInstance_Init();
  MBER_DLL_EXPORT(void) DigitalGoodInstance_Free(MBER_DIGITAL_GOOD_INSTANCE* instance);
  MBER_DLL_EXPORT(void) DigitalGoodInstance_SetId(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const id);
  MBER_DLL_EXPORT(void) DigitalGoodInstance_SetDefinitionId(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const id);
  MBER_DLL_EXPORT(void) DigitalGoodInstance_SetState(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const state);
  MBER_DLL_EXPORT(void) DigitalGoodInstance_SetDocumentId(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const id);
  MBER_DLL_EXPORT(void) DigitalGoodInstance_SetName(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const name);
  MBER_DLL_EXPORT(void) DigitalGoodInstance_SetScope(MBER_DIGITAL_GOOD_INSTANCE* const instance, const char* const scope);
  MBER_DLL_EXPORT(void) DigitalGoodInstance_SetProperties(MBER_DIGITAL_GOOD_INSTANCE* const instance, MBER_PROPERTY_LIST* properties);
  MBER_DLL_EXPORT(const char* const) DigitalGoodInstance_GetId(const MBER_DIGITAL_GOOD_INSTANCE* const instance);
  MBER_DLL_EXPORT(const char* const) DigitalGoodInstance_GetDefinitionId(const MBER_DIGITAL_GOOD_INSTANCE* const instance);
  MBER_DLL_EXPORT(const char* const) DigitalGoodInstance_GetState(const MBER_DIGITAL_GOOD_INSTANCE* const instance);
  MBER_DLL_EXPORT(const char* const) DigitalGoodInstance_GetDocumentId(const MBER_DIGITAL_GOOD_INSTANCE* const instance);
  MBER_DLL_EXPORT(const char* const) DigitalGoodInstance_GetName(const MBER_DIGITAL_GOOD_INSTANCE* const instance);
  MBER_DLL_EXPORT(const char* const) DigitalGoodInstance_GetScope(const MBER_DIGITAL_GOOD_INSTANCE* const instance);
  MBER_DLL_EXPORT(const MBER_PROPERTY_LIST* const) DigitalGoodInstance_GetProperties(const MBER_DIGITAL_GOOD_INSTANCE* const instance);

  MBER_DLL_EXPORT(MBER_DIGITAL_GOOD_INSTANCE_LIST*) DigitalGoodInstanceList_Init();
  MBER_DLL_EXPORT(void) DigitalGoodInstanceList_Free(MBER_DIGITAL_GOOD_INSTANCE_LIST* list);
  MBER_DLL_EXPORT(void) DigitalGoodInstanceList_FreeAll(MBER_DIGITAL_GOOD_INSTANCE_LIST* list);
  MBER_DLL_EXPORT(unsigned int) DigitalGoodInstanceList_Length(const MBER_DIGITAL_GOOD_INSTANCE_LIST* const list);
  MBER_DLL_EXPORT(void) DigitalGoodInstanceList_Pop(MBER_DIGITAL_GOOD_INSTANCE_LIST* const list);
  MBER_DLL_EXPORT(void) DigitalGoodInstanceList_Push(MBER_DIGITAL_GOOD_INSTANCE_LIST* const list, MBER_DIGITAL_GOOD_INSTANCE* instance);
  MBER_DLL_EXPORT(MBER_DIGITAL_GOOD_INSTANCE*) DigitalGoodInstanceList_At(const MBER_DIGITAL_GOOD_INSTANCE_LIST* const list, const unsigned int index);

  MBER_DLL_EXPORT(MBER_ENTITY_POINTER*) EntityPointer_Init();
  MBER_DLL_EXPORT(void) EntityPointer_Free(MBER_ENTITY_POINTER* entity);
  MBER_DLL_EXPORT(void) EntityPointer_SetId(MBER_ENTITY_POINTER* const entity, const char* const id);
  MBER_DLL_EXPORT(void) EntityPointer_SetType(MBER_ENTITY_POINTER* const entity, const char* const type);
  MBER_DLL_EXPORT(void) EntityPointer_SetName(MBER_ENTITY_POINTER* const entity, const char* const name);
  MBER_DLL_EXPORT(const char* const) EntityPointer_GetId(const MBER_ENTITY_POINTER* const entity);
  MBER_DLL_EXPORT(const char* const) EntityPointer_GetType(const MBER_ENTITY_POINTER* const entity);
  MBER_DLL_EXPORT(const char* const) EntityPointer_GetName(const MBER_ENTITY_POINTER* const entity);

  MBER_DLL_EXPORT(MBER_ENTITY_POINTER_LIST*) EntityPointerList_Init();
  MBER_DLL_EXPORT(void) EntityPointerList_Free(MBER_ENTITY_POINTER_LIST* list);
  MBER_DLL_EXPORT(void) EntityPointerList_FreeAll(MBER_ENTITY_POINTER_LIST* list);
  MBER_DLL_EXPORT(unsigned int) EntityPointerList_Length(const MBER_ENTITY_POINTER_LIST* const list);
  MBER_DLL_EXPORT(void) EntityPointerList_Pop(MBER_ENTITY_POINTER_LIST* const list);
  MBER_DLL_EXPORT(void) EntityPointerList_Push(MBER_ENTITY_POINTER_LIST* const list, MBER_ENTITY_POINTER* entity);
  MBER_DLL_EXPORT(MBER_ENTITY_POINTER*) EntityPointerList_At(const MBER_ENTITY_POINTER_LIST* const list, const unsigned int index);

  MBER_DLL_EXPORT(const MBER_ENTITY_POINTER_LIST* const) Session_GetOwnedEntities(const Mber::MberSession* const session);

  MBER_DLL_EXPORT(bool) DigitalGoodInstance_List(Mber::MberSession* const session, const MBER_ENTITY_POINTER* const entity, const char* const* const definition_ids, const int definition_id_count, MBER_DIGITAL_GOOD_INSTANCE_LIST** results, Mber::Status& status);

  MBER_DLL_EXPORT(bool) Profile_Read (Mber::MberSession *session, Mber::Status &status, MBER_PROFILE *profile);
  MBER_DLL_EXPORT(bool) Profile_Search (Mber::MberSession *session, const char *field, const char *name, const double similarity, Mber::Status &status, MBER_ARRAY **profiles);
  MBER_DLL_EXPORT(bool) Document_Find (Mber::MberSession *session, int &version, Mber::Status &status, MBER_ARRAY *tags, MBER_ARRAY **documents);
  MBER_DLL_EXPORT(bool) Document_Read (Mber::MberSession* const session, const char* const docId, Mber::Status& status, char* const name, const int name_size, char* const content, const int content_size);
  MBER_DLL_EXPORT(bool) Document_Read_Aliased (Mber::MberSession* const session, const char* const docId, Mber::Status& status, char* const name, const int name_size, char* const alias, const int alias_size, char* const content, const int content_size);
  MBER_DLL_EXPORT(bool) Document_Create (Mber::MberSession* const session, const char* const name, const char* const content, const MBER_ARRAY* const tags, Mber::Status& status, char* const docId, const int docId_size);
  MBER_DLL_EXPORT(bool) Document_Create_Aliased (Mber::MberSession* const session, const char* const name, const char* const alias, const char* const content, const MBER_ARRAY* const tags, Mber::Status& status, char* const docId, const int docId_size);
  MBER_DLL_EXPORT(bool) Document_Update (Mber::MberSession *session, const char *docId, const char *name, const char *data, MBER_ARRAY *tags, Mber::Status &status);
  MBER_DLL_EXPORT(bool) Document_Update_Aliased (Mber::MberSession* const session, const char* const docId, const char* const name, const char* const alias, const char* const data, const MBER_ARRAY* const tags, Mber::Status& status);
  MBER_DLL_EXPORT(bool) Document_Delete (Mber::MberSession* const session, const char* const docId, Mber::Status &status);
  MBER_DLL_EXPORT(bool) Commerce_WalletBalance (Mber::MberSession* const session, const char* const virtualCurrencyId, const char* const profileId, double& amount, Mber::Status& status);
  MBER_DLL_EXPORT(bool) Commerce_WalletCredit (Mber::MberSession* const session, const char* const virtualCurrencyId, const char* const profileId, const double amount, Mber::Status& status);
  MBER_DLL_EXPORT(bool) Commerce_WalletDebit (Mber::MberSession* const session, const char* const virtualCurrencyId, const char* const profileId, const double amount, const char* const reason, Mber::Status& status);
  MBER_DLL_EXPORT(bool) Session_Login (Mber::MberSession* const session, const char* const grant_type, const char* const client_id, const char* const client_secret, const char* const code, const char* const refresh_token, const char* const username, const char* const password, const char* const redirect_uri, const char* const scope, Mber::Status& status);
  MBER_DLL_EXPORT(bool) Session_LoginWithClientToken (Mber::MberSession* const session, Mber::MberSession* const client_session, const char* const authorization_token, const char* const client_type, const int ttl, const char* const* const required_entity_ids, const char* const* const required_entity_types, const int required_entity_count, Mber::Status& status);
  MBER_DLL_EXPORT(void) Session_Create (Mber::MberSession **session, const char *uri);
  MBER_DLL_EXPORT(void) Session_Destroy (Mber::MberSession *session);
  MBER_DLL_EXPORT(const char*) Session_GetToken (Mber::MberSession *session);
  MBER_DLL_EXPORT(const char* const) Session_GetRefreshToken (const Mber::MberSession* const session);
  MBER_DLL_EXPORT(bool) Session_GetAuthorizationToken (Mber::MberSession* const session, const char* const client_id, char* const authorization_token);
  MBER_DLL_EXPORT(bool) Session_GetClientToken (Mber::MberSession* const session, const char* const authorization_token, const char* const client_type, const int ttl, const char* const* const required_entity_ids, const char* const* const required_entity_types, const int required_entity_count, char* const client_token, const int client_token_size, Mber::Status& status);
  MBER_DLL_EXPORT(const char*) Session_GetProfileId (Mber::MberSession *session);
  MBER_DLL_EXPORT(const char* const) Session_GetAccountId (const Mber::MberSession* const session);
  MBER_DLL_EXPORT(const char* const) Session_GetLastError (const Mber::MberSession* const session);
  MBER_DLL_EXPORT(const char* const) Session_GetDisplayName (const Mber::MberSession* const session);
  MBER_DLL_EXPORT(int) Base64Encode ( const char* buffer, int size, char* out_buffer, int out_size);
  MBER_DLL_EXPORT(bool) Free_Profiles (MBER_ARRAY **profiles);
  MBER_DLL_EXPORT(bool) Free_Documents (MBER_ARRAY **documents);
  MBER_DLL_EXPORT(void) MberStartup();
  MBER_DLL_EXPORT(void) MberShutdown();
  MBER_DLL_EXPORT(MBER*) MberInit(const char* const url);
  MBER_DLL_EXPORT(void) MberTerm(MBER* mber);
  MBER_DLL_EXPORT(char*) MberJsonGET(const MBER* const mber, const char* const endpoint, const char* const request);
  MBER_DLL_EXPORT(char*) MberJsonPUT(const MBER* const mber, const char* const endpoint, const char* const request);
  MBER_DLL_EXPORT(char*) MberJsonPOST(const MBER* const mber, const char* const endpoint, const char* const request);
  MBER_DLL_EXPORT(char*) MberJsonDELETE(const MBER* const mber, const char* const endpoint, const char* const request);
  MBER_DLL_EXPORT(char*) MberJsonTXNID();
  MBER_DLL_EXPORT(void) MberJsonFREE(char* response);
}