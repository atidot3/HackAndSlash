#pragma once
#include "HackAndSlash.h"
#include "Net/UnrealNetwork.h"
#include "Define.generated.h"

// Entire Server Connection Structure
#define NTL_MAX_COUNT_CHARACTER_SERVER					(16)
//#define NTL_MAX_SIZE_SERVER_FARM_NAME					(32)
#define NTL_MAX_SIZE_SERVER_FARM_NAME_UNICODE			(32)
//#define NTL_MAX_SIZE_SERVER_CHANNEL_NAME				(32)
#define NTL_MAX_SIZE_SERVER_CHANNEL_NAME_UNICODE		(32)
#define NTL_MAX_SERVER_CHANNEL_COUNT_IN_SERVER_FARM		(10)

#define NTL_MAX_SIZE_DB_DSN								(32)
#define NTL_MAX_SIZE_DB_ID								(32)
#define NTL_MAX_SIZE_DB_PASSWORD						(32)

// User AccountID and Password
#define NTL_MAX_SIZE_USERID								(12)
#define NTL_MAX_SIZE_USERPW								(12)
#define NTL_MAX_SIZE_USERID_UNICODE						(12)
#define NTL_MAX_SIZE_USERPW_UNICODE						(12)
#define NTL_MAX_SIZE_USERID_MULTIBYTE_BUFFER			(128)
#define NTL_MAX_SIZE_USERPW_MULTIBYTE_BUFFER			(128)
#define NTL_MAX_SIZE_USERCN								(12)

#define NTL_MAX_SIZE_CP_COOKIE							(1024 * 2)
#define DBO_MAX_SIZE_CJI_KOR_UNI_ID						(12)

#define NTL_MAX_SIZE_TOOL_USERNAME_MULTIBYTE_BUFFER		(256)
#define NTL_MAX_SIZE_TOOL_PARTNAME_MULTIBYTE_BUFFER		(512)
#define NTL_MAX_SIZE_TOOL_COMMENT_MULTIBYTE_BUFFER		(2048)
#define NTL_MAX_SIZE_TOOL_COMMENT						(512)
#define NTL_MAX_SIZE_TOOL_COMMENT_UNICODE				(512)
#define NTL_MAX_SIZE_TOOL_PARTNAME						(128)
#define NTL_MAX_SIZE_TOOL_PARTNAME_UNICODE				(128)
#define NTL_MAX_SIZE_TOOL_USERNAME						(60)
#define NTL_MAX_SIZE_TOOL_USERNAME_UNICODE				(60)
#define NTL_MAX_SIZE_TOOL_GM_NAME						(16)
#define NTL_MAX_SIZE_TOOL_GM_NAME_UNICODE				(16)
#define NTL_MAX_SIZE_TOOL_GM_NAME_MULTIBYTE_BUFFER		(128)
#define NTL_MAX_SIZE_TOOL_GROUPNAME						(60)
#define NTL_MAX_SIZE_TOOL_GROUPNAME_UNICODE				(60)
#define NTL_MAX_SIZE_TOOL_GROUPNAME_MULTIBYTE_BUFFER	(256)
#define NTL_MAX_COUNT_TOOL_AUTH							(160)
#define NTL_MAX_COUNT_COMMAND_AUTH						(160)
#define NTL_MAX_COUNT_ETC_AUTH							(160)
#define NTL_MAX_SIZE_TOOL_AUTH							(int)(( NTL_MAX_COUNT_TOOL_AUTH - 1) / 8 + 1)
#define NTL_MAX_SIZE_COMMAND_AUTH						(int)(( NTL_MAX_COUNT_COMMAND_AUTH - 1) / 8 + 1)
#define NTL_MAX_SIZE_ETC_AUTH							(int)(( NTL_MAX_COUNT_ETC_AUTH - 1) / 8 + 1)
#define NTL_MAX_COUNT_TOOL_USER							(100)
#define NTL_MAX_COUNT_GM_GROUP							(20)
#define NTL_MAX_COUNT_ON_PLAY_USER						(1000)

#define NTL_MAX_SIZE_AUTH_KEY							(16)
#define NTL_MAX_LENGTH_OF_IP_ADDRESS					(16)
#define NTL_MAX_LENGTH_OF_IP							(64)
#define NTL_MAX_LENGTH_OF_RECENT_DATE					(20)

//- yoshiki : 256 should be changed back into 120!
#define NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE			(256)
#define NTL_MAX_LENGTH_OF_CHAT_MESSAGE					(256)
#define NTL_MAX_LENGTH_OF_CHAT_MESSAGE_MULTIBYTE_BUFFER	(1024)

#define NTL_MAX_COUNT_USER_CHAR_SLOT					(8)
#define NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM				(128)
#define NTL_MAX_COUNT_USER_HAVE_NORMAL_BANK_ITEM		(52)
#define NTL_MAX_COUNT_USER_HAVE_PUBLIC_BANK_ITEM		(16)
#define NTL_MAX_COUNT_USER_HAVE_BANK_ITEM				(NTL_MAX_COUNT_USER_HAVE_NORMAL_BANK_ITEM + NTL_MAX_COUNT_USER_HAVE_PUBLIC_BANK_ITEM)
#define NTL_MAX_COUNT_USER_HAVE_TOTAL_ITEM				(NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM + NTL_MAX_COUNT_USER_HAVE_BANK_ITEM)

//#define NTL_MIN_SIZE_CHAR_NAME						(4)
#define NTL_MIN_SIZE_CHAR_NAME_UNICODE					(2)
#define NTL_MAX_SIZE_CHAR_NAME							(16)
#define NTL_MAX_SIZE_CHAR_NAME_UNICODE					(16)
#define NTL_MAX_SIZE_CHAR_NAME_BUFFER_MULTIBYTE			(128)

#define NTL_MIN_SIZE_PARTY_NAME							(4)
#define NTL_MAX_SIZE_PARTY_NAME							(16)
#define NTL_MAX_SIZE_PARTY_NAME_IN_UNICODE				(16)
#define NTL_MAX_SIZE_PARTY_NAME_MULTIBYTE_BUFFER		(64)

#define NTL_MIN_SIZE_GUILD_NAME							(4)
#define NTL_MAX_SIZE_GUILD_NAME							(32)
#define NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE				(32)
#define NTL_MAX_SIZE_GUILD_NAME_MULTIBYTE_BUFFER		(128)
#define NTL_MAX_LENGTH_OF_GUILD_NOTICE					(256)
#define NTL_MAX_LENGTH_OF_GUILD_NOTICE_UNICODE			(256)
#define NTL_MAX_LENGTH_OF_GUILD_NOTICE_MULTIBYTE_BUFFER	(1024)

#define NTL_MAX_LENGTH_OF_DOJO_NOTICE					(64)
#define NTL_MAX_LENGTH_OF_DOJO_NOTICE_UNICODE			(64)
#define NTL_MAX_LENGTH_OF_DOJO_NOTICE_MULTIBYTE_BUFFER	(256)

#define NTL_MAX_LENGTH_MODEL_NAME						(32)

#define NTL_MAX_LENGTH_REPORT_NAME						(64) // ����Ʈ ���� �� ����ϴ� �̸��� �ִ����(��ų, ������ �� ���)
#define NTL_MAX_LENGTH_REPORT_NAME_UNICODE				(64)
#define NTL_MAX_LENGTH_REPORT_NAME_MUlTIBYTE_BUFFER		(512)

#define NTL_MAX_PRIVATESHOP_NAME_IN_UNICODE				(32)
#define NTL_MAX_PRIVATESHOP_NOTICE_IN_UNICODE			(64)
#define NTL_MAX_COUNT_PRIVATESHOP_ITEM					(66)
#define NTL_MAX_PRIVATESHOP_NAME_MULTIBYTE_BUFFER		(128)
#define NTL_MAX_PRIVATESHOP_NOTICE_MULTIBYTE_BUFFER		(256)

#define NTL_MAX_LENGTH_OF_MAIL_MESSAGE					(128)
#define NTL_MAX_LENGTH_OF_MAIL_MESSAGE_IN_UNICODE		(128)
#define NTL_MAX_LENGTH_OF_MAIL_MESSAGE_MULTIBYTE_BUFFER	(1024)
#define NTL_MAX_LENGTH_OF_MAIL_MESSAGE_IN_MULTIBYTE		(256)

#define NTL_MAX_COUNT_WAR_FOG							(80)
#define NTL_MAX_SIZE_WAR_FOG							(int)(( NTL_MAX_COUNT_WAR_FOG - 1) / 8 + 1)

#define NTL_MAX_COUNT_FRIEND							(100)		// ��ϰ��� ģ����

#define NTL_MIN_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE		(2)
#define NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE		(20)
#define NTL_REPORT_LOG_PARAMATER_MAX					(7)

#define	NTL_MAX_SIZE_FILE_NAME							(256)
#define NTL_MAX_SIZE_LOCALSETTING_FILE					(2048)

#define NTL_MAX_SIZE_MOB_NAME							(60)

#define NTL_MAX_SIZE_WORLD_NAME							(32)
#define NTL_MAX_SIZE_WORLD_NAME_UNICODE					(32)
#define NTL_MAX_SIZE_FULL_WORLD_NAME					(64)

#define NTL_MAX_LENGTH_SKILL_NAME_TEXT					(40) // GM �� ��� �α׿��� ����ϴ� ũ��
#define NTL_MAX_LENGTH_ITEM_NAME_TEXT					(32)
#define NTL_MAX_LENGTH_BEFORE_AFTER_STATUS				(128)

// ACCOUNT ID
typedef unsigned int ACCOUNTID;
const ACCOUNTID INVALID_ACCOUNTID = 0xFFFFFFFF;

struct sNTLPACKETHEADER
{
	sNTLPACKETHEADER(WORD wGivenOpCode) :
		wOpCode(wGivenOpCode) {}

	WORD			wOpCode;
};

#define BEGIN_PROTOCOL(opcode)						\
struct s##opcode :									\
	public sNTLPACKETHEADER							\
	{													\
	s##opcode() :									\
		sNTLPACKETHEADER(opcode)					\
		{												\
		}

#define END_PROTOCOL()	};

enum STATUT_PLAYER
{
	OK,
	LOADINGSCREEN
};

struct NtlVector
{
	float x;
	float y;
	float z;
};
enum Difficulty
{
	DIFFICULTY_NONE = 0,
	DIFFICULTY_NORMAL = 1,
	DIFFICULTY_HEROIC = 2,
	DIFFICULTY_10_N = 3,
	DIFFICULTY_25_N = 4,
	DIFFICULTY_10_HC = 5,
	DIFFICULTY_25_HC = 6,
	DIFFICULTY_LFR = 7,
	DIFFICULTY_CHALLENGE = 8,
	DIFFICULTY_40 = 9,
	DIFFICULTY_HC_SCENARIO = 11,
	DIFFICULTY_N_SCENARIO = 12,
	DIFFICULTY_NORMAL_RAID = 14,
	DIFFICULTY_HEROIC_RAID = 15,
	DIFFICULTY_MYTHIC_RAID = 16,
	DIFFICULTY_LFR_NEW = 17,
	DIFFICULTY_EVENT_RAID = 18,
	DIFFICULTY_EVENT_DUNGEON = 19,
	DIFFICULTY_EVENT_SCENARIO = 20,
	DIFFICULTY_MYTHIC = 23,
	DIFFICULTY_TIMEWALKER = 24,

	MAX_DIFFICULTY
};
UENUM(BlueprintType)
enum class DifficultyEnum : uint8
{
	DIFFICULTY_NORMAL	 			UMETA(DisplayName = "Normal"),
	DIFFICULTY_HEROIC	 			UMETA(DisplayName = "Heroic"),
	DIFFICULTY_CHALLENGE		 	UMETA(DisplayName = "Challenge"),
	DIFFICULTY_MYTHIC				UMETA(DisplayName = "Mythic")
};
UENUM(BlueprintType)
enum class LoginResultEnum : uint8
{
	BadPassword	 	UMETA(DisplayName = "BadPassword"),
	BadUsername	 	UMETA(DisplayName = "BadUsername"),
	Banned		 	UMETA(DisplayName = "Banned"),
	OK				UMETA(DisplayName = "OK"),
	Unknow			UMETA(DisplayName = "unknow")
};
USTRUCT(blueprintable)
struct HACKANDSLASH_API FFriend
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite)
	FString					name;
	UPROPERTY(BlueprintReadWrite)
	bool					Online;
	UPROPERTY(BlueprintReadWrite)
	int32					Level;
	UPROPERTY(BlueprintReadWrite)
	int32					Class;
	UPROPERTY(BlueprintReadWrite)
	int32					AccountID;
};
USTRUCT(blueprintable)
struct HACKANDSLASH_API FMaps
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite)
	FString					name;
	UPROPERTY(BlueprintReadWrite)
	int32					id;
};
USTRUCT(blueprintable)
struct HACKANDSLASH_API FSpawnFriendParty
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite)
	FString					name;
	UPROPERTY(BlueprintReadWrite)
	int32					level;
	UPROPERTY(BlueprintReadWrite)
	int32					charID;
	UPROPERTY(BlueprintReadWrite)
	FVector					location;
};
USTRUCT(blueprintable)
struct HACKANDSLASH_API FRefreshFriend
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite)
	FString					name;
	UPROPERTY(BlueprintReadWrite)
	int32					charID;
	UPROPERTY(BlueprintReadWrite)
	bool					leader;
	UPROPERTY(BlueprintReadWrite)
	int32					level;
	UPROPERTY(BlueprintReadWrite)
	int32					life;
	UPROPERTY(BlueprintReadWrite)
	int32					classe;
	UPROPERTY(BlueprintReadWrite)
	bool					disconnected;
};