#pragma once
#include "HackAndSlash.h"
#include "Net/UnrealNetwork.h"
#include "Define.generated.h"

#define NTL_MAX_SIZE_AUTH_KEY							(16)
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