#pragma once

#include "SharedDef.h"
#include "SharedType.h"

const DWORD DBO_MAX_MEMBER_IN_GUILD = 100;
const DWORD DBO_MAX_SECOND_MASTER_IN_GUILD = 4;
const DWORD DBO_ZENNY_FOR_NEW_GUILD = 10000;
const DWORD DBO_LEVEL_FOR_NEW_GUILD = 30;
const DWORD DBO_ZENNY_FOR_GUILD_POINT = 1000;
const DWORD DBO_POINT_FOR_GUILD_ZENNY = 5;

// WARNING :
// You can add a new guild function but MUST NOT REMOVE one. These index numbers are synchronized with DB.
// Guild ����� �߰��� ���� ������ �����ؼ��� �� �˴ϴ�. �ε��� ��ȣ���� DB�� ����ȭ�Ǿ� �ֽ��ϴ�.
// by YOSHIKI(2007-04-25)
// itzrnb - DB�� ����� �Ǿ� �����Ƿ� �� ���̳� �߰��� ���Ե� �� �˴ϴ�. �߰��� ����
enum eDBO_GUILD_FUNCTION
{
	DBO_GUILD_FUNCTION_MAX_MEMBER_20 = 0,		// ���� 20��
	DBO_GUILD_FUNCTION_MAX_SECOND_MASTER_1,		// ���� ��� 1��
	DBO_GUILD_FUNCTION_NOTICE_BOARD,			// ���� ���� ����
	DBO_GUILD_FUNCTION_POST,					// ���� ����
	DBO_GUILD_FUNCTION_WAREHOUSE,				// ���� â��

	DBO_GUILD_FUNCTION_MAX_MEMBER_30,			// ���� ��� 30��
	DBO_GUILD_FUNCTION_MAX_SECOND_MASTER_2,		// ���� ��� 2��
	DBO_GUILD_FUNCTION_MAX_MEMBER_40,			// ���� ��� 40��
	DBO_GUILD_FUNCTION_CAN_CHANGE_NAME,			// ���� �̸� ����
	DBO_GUILD_FUNCTION_MAX_MEMBER_50,			// ���� ��� 50��
	DBO_GUILD_FUNCTION_MAX_SECOND_MASTER_3,		// ���� ��� 3��
	DBO_GUILD_FUNCTION_CAN_SET_EMBLEM,			// ���� ���� ����
	DBO_GUILD_FUNCTION_MAX_MEMBER_60,			// ���� ��� 60��
	DBO_GUILD_FUNCTION_MAX_MEMBER_70,			// ���� ��� 70��
	DBO_GUILD_FUNCTION_MAX_SECOND_MASTER_4,		// ���� ��� 4��
	DBO_GUILD_FUNCTION_CAN_HAVE_DOJO,			// ���� ���� ����
	DBO_GUILD_FUNCTION_CAN_USE_DOJO_TELEPORT,	// ���� ���� �ڷ���Ʈ
	
	DBO_GUILD_FUNCTION_MAX_MEMBER_80,			// ���� ��� 80��
	DBO_GUILD_FUNCTION_DOJO_UPGRADE_1,			// ���� ���� ���׷��̵�1
	DBO_GUILD_FUNCTION_CAN_MAKE_DOGI,			// ���� ����
	DBO_GUILD_FUNCTION_CAN_MAKE_DOJO_DOGI,		// ���� ���� ����

	DBO_GUILD_FUNCTION_CAN_CHANGE_EMBLEM,		// ���� ���� ü����
	DBO_GUILD_FUNCTION_DOJO_UPGRADE_2,			// ���� ���� ���׷��̵�2
	DBO_GUILD_FUNCTION_TENKAICHI_SEED,			// ���� õ������ ���� ��ȸ ����

	DBO_GUILD_FUNCTION_MAX_MEMBER_90,			// ���� ��� 90��

	DBO_GUILD_FUNCTION_DOJO_UPGRADE_3,			// ���� ���� ���׷��̵�3
	DBO_GUILD_FUNCTION_DOJO_QUEST_1,			// ���� ���� ����Ʈ1
	DBO_GUILD_FUNCTION_DOJO_MIX_RATE_UP_1,		// ���� ȣ������ �ͽ� ���׷��̵�1

	DBO_GUILD_FUNCTION_MAX_MEMBER_100,			// ���� ��� 100��
	DBO_GUILD_FUNCTION_DOJO_UPGRADE_4,			// ���� ���� ���׷��̵�4
	DBO_GUILD_FUNCTION_CAN_CHANGE_DOGI,			// ���� ���� ü����
	DBO_GUILD_FUNCTION_CAN_CHANGE_DOJO_DOGI,	// ���� ���� ���� ü����

	DBO_GUILD_FUNCTION_DOJO_UPGRADE_5,			// ���� ���� ���׷��̵�5
	DBO_GUILD_FUNCTION_DOJO_QUEST_2,			// ���� ���� ����Ʈ2
	DBO_GUILD_FUNCTION_DOJO_VEHICLE,			// ���� ���� ����

	DBO_GUILD_FUNCTION_DOJO_UPGRADE_6,			// ���� ���� ���׷��̵�6
	DBO_GUILD_FUNCTION_CAN_HAVE_BOOK,			// ���� ���� ����
	DBO_GUILD_FUNCTION_DOJO_SKILL,				// ���� ��ų

	DBO_GUILD_FUNCTION_DOJO_UPGRADE_7,			// ���� ���� ���׷��̵�7
	DBO_GUILD_FUNCTION_DOJO_MIX_RATE_UP_2,		// ���� ȣ������ �ͽ� ���׷��̵�2

	// ���� ��� �߰��� �̰���

	DBO_GUILD_FUNCTION_COUNT,					// ���� ��� ����
	DBO_GUILD_FUNCTION_INVALID = 0xFFui8
};

struct sDBO_GUILD_MARK
{
	bool IsIntialized()
	{
		if ( INVALID_BYTE == byMarkMain && INVALID_BYTE == byMarkMainColor && INVALID_BYTE == byMarkInLine &&
			INVALID_BYTE == byMarkOutLine && INVALID_BYTE == byMarkOutColor )
		{
			return false;
		}
		else
		{
			return true;
		}

	}
	BYTE					byMarkMain;
	BYTE					byMarkMainColor;
	BYTE					byMarkInLine;
	BYTE					byMarkInColor;
	BYTE					byMarkOutLine;
	BYTE					byMarkOutColor;
	
};

struct sDBO_DOGI_DATA
{
	bool IsIntialized(bool bIsDojo)
	{
		if ( bIsDojo )
		{
			if ( INVALID_BYTE == byDojoColor )
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			if ( INVALID_BYTE == byGuildColor )
			{
				return false;
			}
			else
			{
				return true;
			}
		}

	}
	GUILDID         guildId;
	BYTE			byType;			// ��������
	BYTE		    byGuildColor;	// ��嵵������
	BYTE			byDojoColor;	// ���嵵������

};

struct sDBO_GUILD_DATA
{
	GUILDID			guildId;
	WCHAR			wszName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];

	CHARACTERID		guildMaster;
	CHARACTERID		guildSecondMaster[DBO_MAX_SECOND_MASTER_IN_GUILD];

	DWORD			dwGuildReputation;
	DWORD			dwMaxGuildPointEver;
	DWORD64			qwGuildFunctionFlag;

	time_t			timeToDisband;

	sDBO_GUILD_MARK	sMark;
	WCHAR			awchName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WCHAR			awchNotice[NTL_MAX_LENGTH_OF_GUILD_NOTICE_UNICODE + 1];	
	sDBO_DOGI_DATA  sDogi; 
};

struct sDBO_GUILD_INFO
{
	GUILDID			guildId;
	WCHAR			wszName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];	// ''

	CHARACTERID		guildMaster;	
	CHARACTERID		guildSecondMaster[DBO_MAX_SECOND_MASTER_IN_GUILD];

	DWORD			dwGuildReputation;		// ����
	DWORD			dwMaxGuildPointEver;	// Load �׵��� dwGuildReputation ���� �ְ�
	DWORD64			qwGuildFunctionFlag;	//

	time_t			timeToDisband;

	sDBO_GUILD_MARK	sMark;			// �ʱ� 0xff
	WCHAR			awchName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];	// ''
	WCHAR			awchNotice[NTL_MAX_LENGTH_OF_GUILD_NOTICE_UNICODE + 1];	//''	
	sDBO_DOGI_DATA  sDogi; 
};

// GMTool�� ����Ÿ [4/22/2008 SGpro]
struct sDBO_GMTOOL_GUILD_DATA
	: public sDBO_GUILD_DATA
{
	SERVERFARMID	serverfarmID;
	WCHAR			wszMasterName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	DWORD			dwZenny;	
};

// GMTool�� Search ����Ÿ [7/1/2008 SGpro]
struct sDBO_GMTOOL_GUILD_SEARCH_DATA
{
	GUILDID			guildId;
	SERVERFARMID	serverfarmID;
	WCHAR			wszName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];
	DWORD			dwGuildReputation;
	DWORD			dwMaxGuildPointEver;
	WCHAR			wszMasterName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	CHARACTERID		guildMaster;	
};

struct sDBO_GUILD_MEMBER_DATA
{
	ACCOUNTID		accountId;
	CHARACTERID		charId;
	WCHAR			wszMemberName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE			byRace;
	BYTE			byClass;
	BYTE			byLevel;
	DWORD			dwReputation;
};

struct sDBO_GUILD_MEMBER_INFO
{
	sDBO_GUILD_MEMBER_INFO() :
			charId(INVALID_CHARACTERID),
			byRace(INVALID_BYTE),
			byClass(INVALID_BYTE),
			byLevel(INVALID_BYTE),
			dwReputation(INVALID_DWORD),
			bIsOnline(false)
	{
		::ZeroMemory(wszMemberName, sizeof(wszMemberName));
	}

	sDBO_GUILD_MEMBER_INFO(sDBO_GUILD_MEMBER_DATA* pGuildMemberData) :
			charId(pGuildMemberData->charId),
			byRace(pGuildMemberData->byRace),
			byClass(pGuildMemberData->byClass),
			byLevel(pGuildMemberData->byLevel),
			dwReputation(pGuildMemberData->dwReputation)
	{
		::CopyMemory(wszMemberName, pGuildMemberData->wszMemberName, NTL_MAX_SIZE_CHAR_NAME_UNICODE * sizeof(WCHAR));
		wszMemberName[NTL_MAX_SIZE_CHAR_NAME_UNICODE] = L'\0';
	};

	CHARACTERID		charId;
	WCHAR			wszMemberName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE			byRace;
	BYTE			byClass;
	BYTE			byLevel;
	DWORD			dwReputation;
	bool			bIsOnline;
};

// GMTool�� ����Ÿ [4/22/2008 SGpro]
struct sDBO_GMTOOL_GUILD_MEMBER_DATA
	: public sDBO_GUILD_MEMBER_DATA
{
	SERVERFARMID serverfarmID;
	GUILDID guildID;
	WCHAR wszAccountName[NTL_MAX_SIZE_USERID_UNICODE + 1];
};

struct sDBO_GUILD_FUNCTION_INFO
{
	eDBO_GUILD_FUNCTION		function;			
	eDBO_GUILD_FUNCTION		prerequisite;
	BYTE					byPassive;
	DWORD					dwRequiredPoint;
	DWORD					dwRequiredZenny;
	BYTE					byRequiredRock;
};

enum eDBO_GUILD_SEARCH_TYPE
{	
	DBO_GUILD_SEARCH_TYPE_GUILDNAME = 0,
	DBO_GUILD_SEARCH_TYPE_LEADERNAME,
	DBO_GUILD_SEARCH_TYPE_ALL,
};

struct sDBO_GUILD_CAHNGE_INFO
{
	WCHAR			wszName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];	// ''

	DWORD			dwGuildReputation;		// ����
	DWORD			dwMaxGuildPointEver;	// Load �׵��� dwGuildReputation ���� �ְ�

	DWORD64			qwGuildFunctionFlag;	// Replace

	sDBO_GUILD_MARK	sMark;					// �ʱ� 0xff

	WCHAR			awchName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];	// ''
	WCHAR			awchNotice[NTL_MAX_LENGTH_OF_GUILD_NOTICE_UNICODE + 1];	//''	
	sDBO_DOGI_DATA  sDogi; 
};

enum eDBO_GUILD_UPDATE_TYPE
{
	DBO_GUILD_UPDATE_TYPE_CANCEL_DEL = 0,
	DBO_GUILD_UPDATE_TYPE_NOTICE,
	DBO_GUILD_UPDATE_TYPE_NAME,
	DBO_GUILD_UPDATE_TYPE_MARK,
	DBO_GUILD_UPDATE_TYPE_REPUTATION,
	DBO_GUILD_UPDATE_TYPE_FUNCTION,
	DBO_GUILD_UPDATE_TYPE_ALL,
};

enum eDBO_GUILD_ZENNY_UPDATE_TYPE
{
	DBO_GUILD_ZENNY_UPDATE_TYPE_LEADER_INCOME = 0,	// ��Ƽ���������� �Ա� -> ����� �� �����ۿ� ����
	DBO_GUILD_ZENNY_UPDATE_TYPE_LEADER_OUTCOME,	// ��Ƽ���������� ���-> ����� �� �����ۿ� ����
	DBO_GUILD_ZENNY_UPDATE_TYPE_VILLAGE_INCOME,		// ��������Ʈ��
	DBO_GUILD_ZENNY_UPDATE_TYPE_BATTLE_OUTCOME,		// ���� ��Ż/������ �ź� ���ݾ� 
	DBO_GUILD_ZENNY_UPDATE_TYPE_BATTLE_INCOME,		// ���� ��Ż/������ ��û�ݾ� ȯ��
};


extern const sDBO_GUILD_FUNCTION_INFO g_aGuildFunctionInfo[DBO_GUILD_FUNCTION_COUNT];

// Checks if a guild has a specified guild function.
// ��� function�� ������ �ִ��� �Ǵ��Ѵ�.
// by YOSHIKI(2007-04-25)
bool Dbo_HasGuildFunction(DWORD64 qwGuildFunctionFlag, eDBO_GUILD_FUNCTION eGuildFunction);

// Retrieves information of a specified guild function.
// ������ ��� function�� ���� ������ ��´�.
// by YOSHIKI(2007-04-25)
const sDBO_GUILD_FUNCTION_INFO* Dbo_GetGuildFunctionInfo(eDBO_GUILD_FUNCTION eGuildFunction);

// Checks if a guild can obtain guild function.
// ��� function�� ȹ���� �� �ִ��� �Ǵ��Ѵ�.
// by YOSHIKI(2007-04-25)
bool Dbo_CanGetGuildFunction(DWORD64 qwGuildFunctionFlag, DWORD dwPoint, DWORD dwZenny, eDBO_GUILD_FUNCTION eGuildFunction, WORD* pwResultCode);

bool Dbo_CanGetDojoFunction(DWORD64 qwGuildFunctionFlag, DWORD dwPoint, DWORD dwZenny, eDBO_GUILD_FUNCTION eGuildFunction, WORD* pwResultCode);


bool Dbo_GetUIGuildFunction(DWORD64 qwGuildFunctionFlag, eDBO_GUILD_FUNCTION eGuildFunction);

bool Dbo_GetUIDojoFunction(DWORD64 qwGuildFunctionFlag, eDBO_GUILD_FUNCTION eGuildFunction);

// Returns how many members a guild can have at most.
// ��尡 �ִ� �� ���� ������ ���� �� �ִ��� �˷��ش�.
// by YOSHIKI(2007-04-26)
DWORD Dbo_GetMaxGuildMemberCount(DWORD64 qwGuildFunctionFlag);

// Returns how many second masters a guild can have at most.
// ��尡 �ִ� �� ���� Second Master�� ���� �� �ִ��� �˷��ش�.
// by YOSHIKI(2007-04-26)
DWORD Dbo_GetMaxGuildSecondMasterCount(DWORD64 qwGuildFunctionFlag);

DWORD Dbo_GetGuildPoint(DWORD dwZenny);

BYTE GetDojoPeaceType( eDBO_GUILD_FUNCTION eGuildFunction );

bool IsGuildFunction( eDBO_GUILD_FUNCTION eGuildFunction );

bool IsDojoFunction( eDBO_GUILD_FUNCTION eGuildFunction );

DWORD Dbo_GetGuildDojoLevel(DWORD64 qwGuildFunctionFlag);

BYTE Dbo_GetDojoLevel( BYTE eGuildFunction );

DWORD64 AddGuildFunction( DWORD64 qwGuildFunctionFlag, BYTE byFunction );

DWORD64 RemoveGuildFunction( DWORD64 qwGuildFunctionFlag, BYTE byFunction );