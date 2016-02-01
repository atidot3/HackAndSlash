#pragma once

#include "SharedDef.h"
#include "SharedType.h"
#include "Vector.h"
#include "NtlItem.h"

enum eNTL_INVITATION_RESPONSE
{
	NTL_INVITATION_RESPONSE_ACCEPT = 0,		// ��Ƽ �ʴ뿡 ���ϱ�
	NTL_INVITATION_RESPONSE_DECLINE,		// ��Ƽ �ʴ븦 �����ϱ�
	NTL_INVITATION_RESPONSE_EXPIRE,			// ��Ƽ �ʴ밡 Ÿ�Ӿƿ� �Ǿ����� �˸���

	NTL_INVITATION_RESPONSE_COUNT,

	NTL_INVITATION_RESPONSE_FIRST = NTL_INVITATION_RESPONSE_ACCEPT,
	NTL_INVITATION_RESPONSE_LAST = NTL_INVITATION_RESPONSE_EXPIRE
};

enum eNTL_PARTY_ZENNY_LOOTING
{
	NTL_PARTY_ZENNY_LOOTING_GREEDILY = 0,		// ���ϸ� �ݴ� ����� ��� ������.
	NTL_PARTY_ZENNY_LOOTING_SHARED,				// ���ϸ� ������� �����ϰ� �����ش�.

	NTL_PARTY_ZENNY_LOOTING_COUNT,

	NTL_PARTY_ZENNY_LOOTING_UNKNOWN = 0xFF,

	NTL_PARTY_ZENNY_LOOTING_FIRST = NTL_PARTY_ZENNY_LOOTING_GREEDILY,
	NTL_PARTY_ZENNY_LOOTING_LAST = NTL_PARTY_ZENNY_LOOTING_SHARED
};

enum eNTL_PARTY_ITEM_LOOTING
{
	NTL_PARTY_ITEM_LOOTING_GREEDILY = 0,			// �������� �ݴ� ����� ������ ������.
	NTL_PARTY_ITEM_LOOTING_IN_ORDER,				// �������� ������ ���� ���� ������ ������� �й��Ѵ�.
	NTL_PARTY_ITEM_LOOTING_IN_ORDER_SEPERATELY,		// Normal ����� �й� ������ Excellent ��� �̻��� �й� ������ ���� ����Ѵ�.
	
	NTL_PARTY_ITEM_LOOTING_IN_LEADER,				// ������ ���Ƿ� �й�
	NTL_PARTY_ITEM_LOOTING_BY_ZENNY,				// ���ϸ� ����ϰ� �¶��Ͽ� �й�
	NTL_PARTY_ITEM_LOOTING_DICE,					// �ֻ����� �й�

	NTL_PARTY_ITEM_LOOTING_COUNT,

	NTL_PARTY_ITEM_LOOTING_UNKNOWN = 0xFF,

	NTL_PARTY_ITEM_LOOTING_FIRST = NTL_PARTY_ITEM_LOOTING_GREEDILY,
	NTL_PARTY_ITEM_LOOTING_LAST = NTL_PARTY_ITEM_LOOTING_DICE
};

enum eDBO_PARTY_OPTION
{
	DBO_PARTY_OPTION_CANT_INVITE = 0,
	DBO_PARTY_OPTION_CANT_LEAVE,
	DBO_PARTY_OPTION_CANT_KICK_OUT,
	DBO_PARTY_OPTION_CANT_APPOINT_LEADER
};

enum eDBO_PARTY_OPTION_FLAG
{
	DBO_PARTY_OPTION_FLAG_CANT_INVITE = 1 << DBO_PARTY_OPTION_CANT_INVITE,
	DBO_PARTY_OPTION_FLAG_CANT_LEAVE = 1 << DBO_PARTY_OPTION_CANT_LEAVE,
	DBO_PARTY_OPTION_FLAG_CANT_KICK_OUT = 1 << DBO_PARTY_OPTION_CANT_KICK_OUT,
	DBO_PARTY_OPTION_FLAG_CANT_APPOINT_LEADER = 1 << DBO_PARTY_OPTION_CANT_APPOINT_LEADER
};

//-----------------------------------------------------------------------------------
//	��Ƽ ���� ��� ����
//-----------------------------------------------------------------------------------
// Basic Values
const DWORD NTL_MAX_PARTY_COUNT = 2000;

const DWORD NTL_MAX_MEMBER_IN_PARTY = 5;
const float NTL_VALID_DISTANCE_FOR_EXP_FROM_VICTIM = 100.0f;
const float DBO_VALID_DISTANCE_TO_GET_ZENNY_IN_PARTY = 100.0f;
const float DBO_VALID_DISTANCE_TO_GET_ITEM_IN_PARTY = 100.0f;

// Charm
const DWORD NTL_PARTY_CHARM_INVENTORY_COUNT = 2;
const DWORD NTL_SLOT_COUNT_IN_PARTY_CHARM_INVENTORY = 11;
const DWORD NTL_MAX_PARTY_BUFF = 2;

const DWORD DBO_MAX_TIME_PARTY_CHARM_DICE = 30000;		//30sec 
const DWORD DBO_MAX_TIME_PARTY_DICE_ITEM = 30000;		//30sec 
const BYTE	DBO_PARTY_INVEN_DEFAULT_ITEM_RANK = ITEM_RANK_SUPERIOR;
// Contribution Point
//const DWORD NTL_PARTY_MAX_CONTRIBUTION_POINT = 200;

// Party Inventory
const DWORD NTL_PARTY_INVENTORY_SLOT_COUNT = 16;

// Party Option
const DWORD DBO_PARTY_OPTION_FLAG_DEFAULT = 0;
const DWORD DBO_PARTY_OPTION_FLAG_TMQ =
			DBO_PARTY_OPTION_FLAG_CANT_INVITE |
			DBO_PARTY_OPTION_FLAG_CANT_LEAVE |
			DBO_PARTY_OPTION_FLAG_CANT_KICK_OUT |
			DBO_PARTY_OPTION_FLAG_CANT_APPOINT_LEADER;
const DWORD DBO_PARTY_OPTION_FLAG_RANK_BATTLE =
			DBO_PARTY_OPTION_FLAG_CANT_INVITE |
			DBO_PARTY_OPTION_FLAG_CANT_LEAVE |
			DBO_PARTY_OPTION_FLAG_CANT_KICK_OUT |
			DBO_PARTY_OPTION_FLAG_CANT_APPOINT_LEADER;

const DWORD DBO_PARTY_OPTION_FLAG_BUDOKAI = 
			DBO_PARTY_OPTION_FLAG_CANT_INVITE |
			DBO_PARTY_OPTION_FLAG_CANT_LEAVE |
			DBO_PARTY_OPTION_FLAG_CANT_KICK_OUT |
			DBO_PARTY_OPTION_FLAG_CANT_APPOINT_LEADER;
			

const DWORD NTL_MAX_SHARETARGET_COUNT = 5;// ����Ÿ�� ���� �ִ� ����[3/28/2008 SGpro]
//-----------------------------------------------------------------------------------


#pragma pack(1)

struct sPARTY_MEMBER_INFO
{
	HOBJECT hHandle;
	WCHAR awchMemberName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE byRace;
	BYTE byClass;
	BYTE byLevel;
	WORD wCurLP;
	WORD wMaxLP;
	WORD wCurEP;
	WORD wMaxEP;
	DWORD dwZenny;
	TBLIDX worldTblidx;
	WORLDID worldId;
	sVECTOR3 vCurLoc;
};

struct sVICTIM_ITEM_DATA
{
	CHARACTERID charId;
	BYTE byPlace;
	BYTE byPos;
	HOBJECT hItem;
	ITEMID itemId;
};

struct sDBO_PARTY_VICTIM_ITEM_INFO
{
	BYTE bySlotIndex;
	TBLIDX itemTblidx;
};

struct sDBO_ZENNY_DATA
{
	CHARACTERID		memberCharId;
	DWORD			dwZenny;
};

struct sINVEST_ZENNY_INFO
{
	HOBJECT hMember;
	DWORD dwZenny;
};

struct sPARTY_INVENTORY_ITEM_INFO
{
	TBLIDX tblidx;
	// bNeedToIdentify�� true�� ���� byStackCount, byRank, byGrade, option�� �ǹ̰� ���� ���̴�.
	// byStackCount, byRank, byGrade and option's values are meaningless if bNeedToIdentify is true.
	// by YOSHIKI(2006-10-31)
	BYTE byStackCount;
	BYTE byRank;
	BYTE byGrade;
	bool bNeedToIdentify;
	BYTE byBattleAttribute;
	TBLIDX			aOptionTblidx[NTL_MAX_OPTION_IN_ITEM];
};

struct sDBO_PARTY_INVENTORY_SLOT_INFO
{
	BYTE							bySlotIndex;
	sPARTY_INVENTORY_ITEM_INFO		itemInfo;
};

struct sDBO_VICTIM_INFO
{
	HOBJECT							hMember;
	DWORD							dwZenny;
};

struct sDBO_VICTIM_DATA
{
	CHARACTERID						charId;
	DWORD							dwZenny;
};

struct sZENNY_INFO
{
	CHARACTERID charId;
	DWORD dwZenny; //ȹ���� �� ����( dwOrgZenny + dwBonusZenny )
	DWORD dwOrgZenny; //���� ȹ���� ����
	DWORD dwBonusZenny; //�߰� ȹ�� ����
};

// ����Ÿ�� ����Ÿ [3/28/2008 SGpro]
struct sSHARETARGET_INFO
{
	HOBJECT hTarget;

public:
	sSHARETARGET_INFO()
		: hTarget( INVALID_HOBJECT )
	{
	}
};

#pragma pack()