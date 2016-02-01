//***********************************************************************************
//
//	File		:	NtlWorld.h
//
//	Begin		:	2006-11-15
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	
//
//***********************************************************************************

#pragma once

#include "SharedType.h"
#include "NtlTimeQuest.h"


//-----------------------------------------------------------------------------------
//  
//-----------------------------------------------------------------------------------

// ���� ���� �� 
enum eGAMERULE_TYPE
{
	GAMERULE_NORMAL,		// �Ϲ� �ʵ�
	GAMERULE_RANKBATTLE,	// ��ŷ ��Ʋ
	GAMERULE_MUDOSA,		// õ�����Ϲ���ȸ��
	GAMERULE_DOJO,			// ����
	GAMERULE_RAID,			// ���̵�
	GAMERULE_HUNT,			// ��� (����/��Ƽ�� �ν��Ͻ�)
	GAMERULE_TIMEQUEST,		// Ÿ�Ӹӽ� ����Ʈ
	GAMERULE_TUTORIAL,		// Ʃ�丮��
	GAMERULE_MINORMATCH,	// õ�����Ϲ���ȸ ����
	GAMERULE_MAJORMATCH,	// õ�����Ϲ���ȸ ����
	GAMERULE_FINALMATCH,	// õ�����Ϲ���ȸ �ἱ
	GAMERULE_TEINKAICHIBUDOKAI,	// õ�����Ϲ���ȸ
	GAMERULE_TLQ,			// Ÿ�Ӹ��� ����Ʈ

	GAMERULE_TYPE_COUNT,
	INVALID_GAMERULE = 0xFFFFFFFF, // ����
};

// WorldPlay Executer
enum eWORLDPLAY_EXECUTER_TYPE
{
	WORLDPLAY_EXECUTER_TS,
	WORLDPLAY_EXECUTER_WPS,
	WORLDPLAY_EXECUTER_TLQ,
	WORLDPLAY_EXECUTER_STATIC_WORLD,
	WORLDPLAY_EXECUTER_DYNAMIC_WORLD,
	WORLDPLAY_EXECUTER_OBJECTTRIGGER,
	WORLDPLAY_EXECUTER_ITEM_USE_BY_LOCATION,

	WORLDPLAY_EXECUTER_TYPE_COUNT,
	INVALID_WORLDPLAY_EXECUTER_TYPE = 0xff
};


// World Play Share Type
enum eWORLDPLAY_SHARE_TYPE
{
	WORLDPLAY_SHARE_NONE,
	WORLDPLAY_SHARE_INDIVIDUAL,
	WORLDPLAY_SHARE_PARTY,
//	WORLDPLAY_SHARE_ALL,

	WORLDPLAY_SHARE_TYPE_COUNT,
	INVALID_WORLDPLAY_SHARE_TYPE = 0xff,
};


//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// ���� ���� ����
//-----------------------------------------------------------------------------------
const float			NTL_DUMMY_AREA_WIDTH_IN_WORLD = 512.0f;		// in meters

const unsigned int	DBO_MAX_WAYPOINT_COUNT = 255; //
//-----------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------
// ���� ���� �Լ�
//-----------------------------------------------------------------------------------
HOBJECT MakeTriggerObjectHandle(HOBJECT hWorldTriggerObjectOffset, DWORD dwTriggerObjectSequence);

const char * NtlGetGameRuleTypeString(BYTE byRuleType);
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// ���� ���� packet structure
//-----------------------------------------------------------------------------------
#pragma pack(1)


struct sGAME_RULE_INFO
{
	BYTE			byRuleType;	// eGAMERULE_TYPE
	union
	{
		sTIMEQUEST_RULE_INFO	sTimeQuestRuleInfo;
		//sRANKBATTLE_RULE_INFO		sRankBattleRuleInfo;
		//sBUDOKAI_RULE_INFO	sBudokaiRuleInfo;
		//sDOJO_RULE_INFO		sDojoRuleInfo;
	};
};


struct sWORLD_INFO
{
	// World Base Info
	WORLDID			worldID;	// ���� �ν��Ͻ� �ڵ�
	TBLIDX			tblidx;		// ���� ���̺� �ε���

	// World Game Info
	HOBJECT			hTriggerObjectOffset; // Ʈ���� ������Ʈ ���� �ڵ鰪 (Ʈ���� ������Ʈ ���̺��� ������Ʈ�� ������ ���̺� ��ȣ + ���� �ڵ��ȣ�� ������ �� )

	// World Rule Info
	sGAME_RULE_INFO	sRuleInfo;
};

struct sWORLD_ZONE_INFO
{
	ZONEID			zoneId;
	bool			bIsDark;
};

#pragma pack()
//-----------------------------------------------------------------------------------
