//***********************************************************************************
//
//	File		:	NtlObject.h
//
//	Begin		:	2006-04-07
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	
//
//***********************************************************************************

#pragma once

#include "Character.h"
#include "Quest.h"


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
enum eOBJTYPE
{
	OBJTYPE_PC, // PC
	OBJTYPE_NPC, // NPC
	OBJTYPE_MOB, // MOB
	OBJTYPE_SUMMON_PET, // ��ų�� ��ȯ�� pet
	OBJTYPE_ITEM_PET, // ���������� ��ȯ�� pet
	OBJTYPE_DROPMONEY, // ���� ������ ��
	OBJTYPE_DROPITEM, // ���� ������ ������
	OBJTYPE_TOBJECT, // Ʈ���� ������Ʈ
	OBJTYPE_DYNAMIC,	// ���� ���� ������Ʈ
	OBJTYPE_ITEM,	// ITEM TYPE�� �ʵ忡 �������� �ʴ´�. ( ĳ���͸� ������ �ִ� )
	
	MAX_OBJTYPE,
	MAX_SPAWNOBJTYPE = OBJTYPE_DYNAMIC,	// �ʵ忡 �����Ǵ� ������Ʈ Ÿ���� MAX
	INVALID_OBJTYPE = 0xFF,

	OBJTYPE_FIRST = OBJTYPE_PC,
	OBJTYPE_LAST = MAX_OBJTYPE - 1,
};


// Object�� ������ source
enum eDBO_OBJECT_SOURCE
{
	DBO_OBJECT_SOURCE_SKILL = 0,		// ��ų�� ���� ���� object
	DBO_OBJECT_SOURCE_ITEM,				// �����ۿ� ���� ���� object

	DBO_OBJECT_SOURCE_UNKNOWN = 0xFF,

	DBO_OBJECT_SOURCE_FIRST = DBO_OBJECT_SOURCE_SKILL,
	DBO_OBJECT_SOURCE_LAST = DBO_OBJECT_SOURCE_ITEM
};


// Trigger object�� ���
enum eDBO_TRIGGER_OBJECT_FUNC
{
	eDBO_TRIGGER_OBJECT_FUNC_SELECTION				= 0x1,
	eDBO_TRIGGER_OBJECT_FUNC_PORTAL					= 0x2,
	eDBO_TRIGGER_OBJECT_FUNC_BIND					= 0x4,
	eDBO_TRIGGER_OBJECT_FUNC_SCOUTER				= 0x8,
	eDBO_TRIGGER_OBJECT_FUNC_RANK_BATTLE			= 0x10,
	eDBO_TRIGGER_OBJECT_FUNC_NORMAL_DRAGONBALL		= 0x20,
	eDBO_TRIGGER_OBJECT_FUNC_RAID_DRAGONBALL		= 0x40,
	eDBO_TRIGGER_OBJECT_FUNC_MAIL_BOX				= 0x80,
	eDBO_TRIGGER_OBJECT_FUNC_TIME_MACHINE			= 0x100,
	eDBO_TRIGGER_OBJECT_FUNC_NAMEKAN_SIGN			= 0x200,
	eDBO_TRIGGER_OBJECT_FUNC_PARTY_INSTANCE_DUNGEON = 0x400,
	eDBO_TRIGGER_OBJECT_FUNC_TIME_LEAP_QUEST		= 0x800,
	eDBO_TRIGGER_OBJECT_FUNC_HOIPOIMIX				= 0x1000,
	eDBO_TRIGGER_OBJECT_FUNC_DOJO_WAREHOUSE			= 0x2000,
	eDBO_TRIGGER_OBJECT_FUNC_DOJO_SEAL				= 0x4000,
};

// Dynamic Object�� state
enum eDYNAMIC_OBJECT_STATE
{
	eDYNAMIC_OBJECT_STATE_SPAWN,
	eDYNAMIC_OBJECT_STATE_IDLE,
	eDYNAMIC_OBJECT_STATE_DESPAWN,

	eDYNAMIC_OBJECT_STATE_NUMS,
	eDYNAMIC_OBJECT_STATE_INVALID = 0xFF
};

// Dynamic object function
enum eDYNAMIC_OBJECT_FUNCTION
{
	eDYNAMIC_OBJECT_FUNCTION_HOIPOIMIX = 0x1,

	eDYNAMIC_OBJECT_FUNCTION_NUMS,
	eDYNAMIC_OBJECT_FUNCTION_INVALID = 0xFF
};

// Dynamic Object�� ���
enum eDBO_DYNAMIC_OBJECT_TYPE
{
	eDBO_DYNAMIC_OBJECT_TYPE_HOIPOI_MIX_MACHINE		= 1,		// ȣ������ �ͽ� ��Ż �ӽ�
	eDBO_DYNAMIC_OBJECT_TYPE_CAPSULE_HOUSE,						// ȣ������ �ͽ� ĳ�� �ӽ�

	eDBO_DYNAMIC_OBJECT_TYPE_NONE = 0xFF,
};

// Dynamic object substate
enum eDYNAMIC_OBJECT_SUBSTATE
{
	eDYNAMIC_OBJECT_SUBSTATE_ALL_SHOW,
	eDYNAMIC_OBJECT_SUBSTATE_ONLY_SPAWN_AVATAR_SHOW,
	eDYNAMIC_OBJECT_SUBSTATE_ENEMY_HIDE,

	eDYNAMIC_OBJECT_SUBSTATE_NUMS,
	eDYNAMIC_OBJECT_SUBSTATE_INVALID = 0xFF
};

// Dynamic object substate
enum eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE
{
	eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_NORMAL	= 1,
	eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_RENTAL,
	eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_NETP,
	eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_CASH,

	eDYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_NONE = 0xFF,
};


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
const unsigned int MAX_PC = 3000;	// ��ü PC ��

const unsigned int MAX_NPC = 3000;	// ��ü NPC ��

const unsigned int MAX_MOB = 60000;	// ��ü MOB ��

const unsigned int MAX_SUMMON_PET = MAX_PC;	// ��ü Summon Pet ��

const unsigned int MAX_ITEM_PET = MAX_PC;	// ��ü Item Pet ��

const unsigned int MAX_DROP_ITEM = 3000;	// ��ü DROP �Ǵ� ITEM ��

const unsigned int MAX_DROP_MONEY = 3000;	// ��ü DROP �Ǵ� MONEY ��

const unsigned int MAX_PC_HAVE_ITEM = 200;	// PC�� ������ �ִ� ITEM ��

const unsigned int MAX_TRIGGER_OBJECT = 20000; // ��ü ���� Ʈ���� ������Ʈ ��

const unsigned int MAX_DYNAMIC_OBJECT = MAX_PC; // ��ü ���� ������Ʈ �� PC �� �Ѱ��� ���

const unsigned int MAX_BOT = MAX_NPC + MAX_MOB + MAX_SUMMON_PET + MAX_ITEM_PET;		// BOT �� ( ���� ���� ó���� )

const unsigned int MAX_ITEM = MAX_PC * MAX_PC_HAVE_ITEM;	// ��ü ������ ��

const unsigned int MAX_GAME_OBJECT = MAX_PC + MAX_BOT + MAX_ITEM + MAX_DROP_ITEM + MAX_DROP_MONEY + MAX_TRIGGER_OBJECT + MAX_DYNAMIC_OBJECT; // ��ü ������Ʈ ��

const float		   DBO_MAX_DISTANCE_OF_DYNAMIC_OBJECT = 20.0f;		// DYNAMIC OBJECT ��ġ ��� �ִ� �Ÿ�

const unsigned int DYNAMIC_OBJECT_CHECK_TERM = 1000;	// ���̳��Ϳ�����Ʈ�� ���ΰ� �Ÿ� �̰� üũ ��  seconds

const unsigned int DYNAMIC_OBJECT_DESPAWN_TERM = 1000;

const unsigned int DYNAMIC_OBJECT_SPAWN_TERM = 1000;
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
const char * NtlGetObjectTypeString(eOBJTYPE eObjType);
#pragma pack(1)
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef BYTE DYNAMIC_OBJECT_STATE;

struct sDYNAMIC_OBJECT_BRIEF
{
	BYTE		byObjectType;	// eDBO_DYNAMIC_OBJECT_TYPE
	TBLIDX		idObjectTblidx;	// �ش��ϴ� tblidx(dynamic object�� �ƴ� hoipoi, capsule house���� tblidx)
	HOBJECT		hOwner;
};


struct sDYNAMIC_OBJECT_STATE
{
	BYTE		byState; // Main State
	sVECTOR3	vCurLoc;
};
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#pragma pack(push, 1)



struct sOBJECT_INFO
{
	BYTE					objType;

	union
	{
		struct // pc
		{
			sPC_BRIEF		pcBrief;
			sCHARSTATE		pcState;
		};
		struct // npc
		{
			sNPC_BRIEF		npcBrief;
			sCHARSTATE		npcState;
		};
		struct // mob
		{
			sMOB_BRIEF		mobBrief;
			sCHARSTATE		mobState;
		};
		struct // summon pet
		{
			sSUMMON_PET_BRIEF		summonPetBrief;
			sCHARSTATE				summonPetState;
		};
		struct // item pet
		{
			sITEM_PET_BRIEF			itemPetBrief;
			sCHARSTATE				itemPetState;
		};
		struct // item
		{
			sITEM_BRIEF		itemBrief;
			sITEM_STATE		itemState;
		};
		struct // money
		{
			sMONEY_BRIEF	moneyBrief;
			sMONEY_STATE	moneyState;
		};
		struct // trigger object
		{
			sTOBJECT_BRIEF	tobjectBrief;
			sTOBJECT_STATE	tobjectState;
		};
		struct // dynamic object
		{
			sDYNAMIC_OBJECT_BRIEF	dynamicObjBrief;
			sDYNAMIC_OBJECT_STATE	dynamicObjState;
		};
	};
};


#pragma pack()