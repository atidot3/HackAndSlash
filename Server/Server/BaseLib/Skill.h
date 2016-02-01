#pragma once

#include "SharedType.h"
#include "Vector.h"


// ��ų ���� enumeration
enum eSKILL_CLASS
{
	NTL_SKILL_CLASS_PASSIVE = 0,
	NTL_SKILL_CLASS_ACTIVE,
	NTL_SKILL_CLASS_HTB,

	NTL_SKILL_CLASS_UNKNOWN = 0xFFui8,

	NTL_SKILL_CLASS_FIRST = NTL_SKILL_CLASS_PASSIVE,
	NTL_SKILL_CLASS_LAST = NTL_SKILL_CLASS_HTB
};


// ��ų ����
enum eSKILL_TYPE
{
	NTL_SKILL_TYPE_NONE = 0,
	NTL_SKILL_TYPE_PHYSICAL,
	NTL_SKILL_TYPE_ENERGY,
	NTL_SKILL_TYPE_STATE,

	NTL_SKILL_TYPE_FIRST = NTL_SKILL_TYPE_NONE,
	NTL_SKILL_TYPE_LAST = NTL_SKILL_TYPE_STATE,

	NTL_SKILL_TYPE_COUNT = NTL_SKILL_TYPE_LAST - NTL_SKILL_TYPE_FIRST + 1
};


// ��ų Ÿ��
enum eSKILL_ACTIVE_TYPE
{
	SKILL_ACTIVE_TYPE_DD, // Direct Damage ( LP ���� )
	SKILL_ACTIVE_TYPE_DOT, // Damage Over Time
	SKILL_ACTIVE_TYPE_DH, // Direct Heal
	SKILL_ACTIVE_TYPE_HOT, // Heal Over Time
	SKILL_ACTIVE_TYPE_DB, // Direct Bless ( ������ �̻� ġ��, �ڷ���Ʈ, ... )
	SKILL_ACTIVE_TYPE_BB, // Bless Buff
	SKILL_ACTIVE_TYPE_DC, // Direct Curse ( EP/RP�� ����, ... )
	SKILL_ACTIVE_TYPE_CB, // Curse Buff

	SKILL_ACTIVE_TYPE_UNKNOWN				= 0xFF,

	SKILL_ACTIVE_TYPE_FIRST = SKILL_ACTIVE_TYPE_DD,
	SKILL_ACTIVE_TYPE_LAST = SKILL_ACTIVE_TYPE_CB
};

enum eDBO_SKILL_APPOINT_TARGET
{
	DBO_SKILL_APPOINT_TARGET_SELF = 0,
	DBO_SKILL_APPOINT_TARGET_TARGET,
	DBO_SKILL_APPOINT_TARGET_POINT,

	DBO_SKILL_APPOINT_TARGET_COUNT,

	DBO_SKILL_APPOINT_TARGET_UNKNOWN = 0xFF,

	DBO_SKILL_APPOINT_TARGET_FIRST = DBO_SKILL_APPOINT_TARGET_SELF,
	DBO_SKILL_APPOINT_TARGET_LAST = DBO_SKILL_APPOINT_TARGET_COUNT - 1
};

enum eDBO_SKILL_APPLY_TARGET
{
	DBO_SKILL_APPLY_TARGET_SELF = 0,
	DBO_SKILL_APPLY_TARGET_ENEMY,
	DBO_SKILL_APPLY_TARGET_ALLIANCE,
	DBO_SKILL_APPLY_TARGET_PARTY,
	DBO_SKILL_APPLY_TARGET_MOB_PARTY,
	DBO_SKILL_APPLY_TARGET_ANY,

	DBO_SKILL_APPLY_TARGET_COUNT,

	DBO_SKILL_APPLY_TARGET_UNKNOWN = 0xFF,

	DBO_SKILL_APPLY_TARGET_FIRST = DBO_SKILL_APPLY_TARGET_SELF,
	DBO_SKILL_APPLY_TARGET_LAST = DBO_SKILL_APPLY_TARGET_COUNT - 1
};

enum eDBO_SKILL_APPLY_RANGE
{
	DBO_SKILL_APPLY_RANGE_SINGLE = 0,
	DBO_SKILL_APPLY_RANGE_CIRCLE,
	DBO_SKILL_APPLY_RANGE_RECTANGLE,
	DBO_SKILL_APPLY_RANGE_FORWARD,

	DBO_SKILL_APPLY_RANGE_UNKNOWN = 0xFF,

	DBO_SKILL_APPLY_RANGE_FIRST = DBO_SKILL_APPLY_RANGE_SINGLE,
	DBO_SKILL_APPLY_RANGE_LAST = DBO_SKILL_APPLY_RANGE_FORWARD
};

enum eDBO_SYSTEM_EFFECT_RESULT_TYPE
{
	DBO_SYSTEM_EFFECT_RESULT_TYPE_GENERAL = 0,
	DBO_SYSTEM_EFFECT_RESULT_TYPE_DH_HOT,
	DBO_SYSTEM_EFFECT_RESULT_TYPE_DD_DOT,
	DBO_SYSTEM_EFFECT_RESULT_TYPE_LP_EP_STEAL,

	DBO_SYSTEM_EFFECT_RESULT_TYPE_COUNT,

	DBO_SYSTEM_EFFECT_RESULT_TYPE_UNKNOWN = 0xFFui8,

	DBO_SYSTEM_EFFECT_RESULT_TYPE_FIRST = DBO_SYSTEM_EFFECT_RESULT_TYPE_GENERAL,
	DBO_SYSTEM_EFFECT_RESULT_TYPE_LAST = DBO_SYSTEM_EFFECT_RESULT_TYPE_COUNT - 1
};

// WARNING :
// You can add a new RP bonus type but MUST NOT REMOVE one. These index numbers are synchronized with DB.
// RP ���ʽ� Ÿ���� �߰��� ���� ������ �����ؼ��� �� �˴ϴ�. �ε��� ��ȣ���� DB�� ����ȭ�Ǿ� �ֽ��ϴ�.
// by YOSHIKI(2007-11-26)
enum eDBO_RP_BONUS_TYPE
{
	DBO_RP_BONUS_TYPE_KNOCKDOWN = 0,
	DBO_RP_BONUS_TYPE_RESULT_PLUS,
	DBO_RP_BONUS_TYPE_EP_MINUS,					// PERCENT
	DBO_RP_BONUS_TYPE_KEEP_TIME_PLUS,			// ABSOLUTE
	DBO_RP_BONUS_TYPE_CASTING_TIME_MINUS,		// ABSOLUTE
	DBO_RP_BONUS_TYPE_COOL_TIME_MINUS,			// ABSOLUTE
	DBO_RP_BONUS_TYPE_GUARD_CRASH,

	DBO_RP_BONUS_TYPE_COUNT,
	DBO_RP_BONUS_TYPE_INVALID = 0xFFui8,

	DBO_RP_BONUS_TYPE_FIRST = DBO_RP_BONUS_TYPE_KNOCKDOWN,
	DBO_RP_BONUS_TYPE_LAST = DBO_RP_BONUS_TYPE_COUNT - 1,
};

//2009�� 1�� 21�� DBO_BLOCK_MODE_TYPE�� DBO_GUARD_TYPE���� ����. (�¿�)
enum eDBO_GUARD_TYPE
{
	DBO_GUARD_TYPE_DEFENCE = 0,
	DBO_GUARD_TYPE_DAMAGE_SKILL,
	DBO_GUARD_TYPE_CURSE_SKILL,
	DBO_GUARD_TYPE_KNOCKDOWN,
	DBO_GUARD_TYPE_HTB,

	DBO_GUARD_TYPE_COUNT,
	DBO_GUARD_TYPE_INVALID = 0xFFui8,

	DBO_GUARD_TYPE_FIRST = DBO_GUARD_TYPE_DEFENCE,
	DBO_GUARD_TYPE_LAST  = DBO_GUARD_TYPE_COUNT - 1
};

enum eDBO_STUN_TYPE
{
	DBO_STUN_TYPE_GENERAL = 0,
	DBO_STUN_TYPE_FROZEN,
	DBO_STUN_TYPE_TIED,
	DBO_STUN_TYPE_STONE,
	DBO_STUN_TYPE_CANDY,

	DBO_STUN_TYPE_COUNT,
	DBO_STUN_TYPE_INVALID = 0xFFui8,

	DBO_STUN_TYPE_FIRST = DBO_STUN_TYPE_GENERAL,
	DBO_STUN_TYPE_LAST = DBO_STUN_TYPE_COUNT - 1
};

enum eDBO_SKILL_PASSIVE_EFFECT
{
	DBO_SKILL_PASSIVE_EFFECT_CASTING_TIME_DOWN = 0,
	DBO_SKILL_PASSIVE_EFFECT_COOL_TIME_DOWN,
	DBO_SKILL_PASSIVE_EFFECT_SYSTEM_EFFECT_VALUE_UP,
	DBO_SKILL_PASSIVE_EFFECT_KEEP_TIME_UP,
	DBO_SKILL_PASSIVE_EFFECT_REQUIRED_EP_DOWN,
	DBO_SKILL_PASSIVE_EFFECT_APPLY_RANGE_TYPE,
	DBO_SKILL_PASSIVE_EFFECT_APPLY_AREA_SIZE_UP,
	DBO_SKILL_PASSIVE_EFFECT_USE_RANGE_MAX_UP,

	DBO_SKILL_PASSIVE_EFFECT_COUNT,

	DBO_SKILL_PASSIVE_EFFECT_INVALID = 0xFFui8,

	DBO_SKILL_PASSIVE_EFFECT_FIRST = DBO_SKILL_PASSIVE_EFFECT_CASTING_TIME_DOWN,
	DBO_SKILL_PASSIVE_EFFECT_LAST = DBO_SKILL_PASSIVE_EFFECT_COUNT - 1,
};

//-----------------------------------------------------------------------------------
// ��ų ����Ʈ �ڵ� ����
//-----------------------------------------------------------------------------------
#ifdef DEF_SYSTEM_EFFECT_CODE
	#undef DEF_SYSTEM_EFFECT_CODE
#endif
#define DEF_SYSTEM_EFFECT_CODE(c, can_cast_when_being_interrupted) c,

enum eSYSTEM_EFFECT_CODE
{
	#include "SystemEffect.h"

	MAX_SYSTEM_EFFECT_CODE,

	INVALID_SYSTEM_EFFECT_CODE = 0xFFFFFFFF
};
//-----------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------
// ��ų ���� ����
//-----------------------------------------------------------------------------------
const unsigned int NTL_MAX_PC_HAVE_SKILL = 120;

const unsigned int NTL_MAX_NPC_HAVE_SKILL = 7;

const unsigned int NTL_MAX_BLESS_BUFF_CHARACTER_HAS = 8;

const unsigned int NTL_MAX_CURSE_BUFF_CHARACTER_HAS = 8;

const unsigned int DBO_MAX_BUFF_CHARACTER_HAS = NTL_MAX_BLESS_BUFF_CHARACTER_HAS + NTL_MAX_CURSE_BUFF_CHARACTER_HAS;

const unsigned int NTL_MAX_EFFECT_IN_SKILL = 2;

const int NTL_SYSTEM_EFFECT_1 = 0;

const int NTL_SYSTEM_EFFECT_2 = 1;

const unsigned int NTL_EFFECT_APPLY_INTERVAL = 2 * 1000;		// in millisecs.

const unsigned int NTL_MAX_NUMBER_OF_SKILL_TARGET = 8;

const BYTE INVALID_BUFF_GROUP = 0xFF;

const float DBO_BACKSTAB_DAMAGE_BONUS_IN_PERCENT = 50.0f;		// in percent

const unsigned int DBO_MAX_RP_BONUS_COUNT_PER_SKILL = 6;

const float DBO_DEFAULT_BLOCK_MODE_SUCCESS_RATE = 70.0f;		// in percent

const float DBO_MAX_BLOCK_MODE_SUCCESS_RATE = 70.0f;		// in percent

const float DBO_MAX_CRITICAL_BLOCK_SUCCESS_RATE = 100.0f;		// in percent

const float DBO_CONFUSE_SCAN_DISTANCE_PC = 20.0f;				// in meters.

const float DBO_MAX_TERROR_MOVEMENT_DISTANCE = 30.0f;			// in meters.

const float DBO_SYSTEM_EFFECT_PULL_DISTANCE = 1.0f;				// in meters.

const DWORD DBO_MIN_POWER_LEVEL_WHEN_HIDING_KI = 1;

const float DBO_KEEPING_EFFECT_VALID_DISTANCE_BUFFER = 10.0f;		// in meters.

const float DBO_STRIKE_RUSH_MOVEMENT_SPEED = 60.0f;					// in m/s
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// HTB ���� ����
//-----------------------------------------------------------------------------------
const DWORD			NTL_HTB_MAX_PC_HAVE_HTB_SKILL				= 30; // PC�� ������ HTB ��ų�� �ִ� ����
const DWORD			NTL_HTB_MAX_SKILL_COUNT_IN_SET				= 10; // �� ���� HTB skill set�� ���Ե� �� �ִ� ��ų�� �ִ� ����
const BYTE			DBO_HTB_PREREQUISITE_RP_BALL				= 1;		// HTB�� ���� ���� �ʿ��� �ּ� RP ����
//-----------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
const char *		NtlGetSystemEffectString(DWORD dwSystemEffectCode);
const bool			NtlCanCastWhenBeingInterrupted(eSYSTEM_EFFECT_CODE eSystemEffectCode);
bool				Dbo_IsForBlessBuff(BYTE byActiveEffectType);
bool				Dbo_IsForCurseBuff(BYTE byActiveEffectType);
bool				Dbo_IsHarmfulEffectType(BYTE byActiveEffectType);
//-----------------------------------------------------------------------------------



// ��ų ���� packet structure
#pragma pack(1)


struct sSKILL_DATA
{	// ĳ������ ��ų ���� ����
	BYTE				bySlot;
	TBLIDX				skillId;
	int					nRemainSec;
	int					nExp;
	BYTE				byRpBonusType;
	bool				bIsRpBonusAuto;
};

struct sBUFF_DATA
{
	TBLIDX				sourceTblidx;
	BYTE				bySourceType;		// eDBO_OBJECT_SOURCE
	DWORD				dwInitialDuration;
	DWORD				dwTimeRemaining;		// in Millisecs.
	int					nArgument1;
	int					nArgument2;
	float				fEffectValue1;
	float				fEffectValue2;
	BYTE				byBuffGroup;		//
};


struct sPET_BUFF_DATA
{
	BYTE				byAvatarType;		// eDBO_AVATAR_TYPE
	BYTE				bySourceType;		// eDBO_OBJECT_SOURCE
	TBLIDX				sourceTblidx;
	DWORD				dwInitialDuration;
	DWORD				dwTimeRemaining;		// in Millisecs.
	int					nArgument1;
	int					nArgument2;
	float				fEffectValue1;
	float				fEffectValue2;
};


// HTB ��ų ����Ÿ ( DB �ε��� )
struct sHTB_SKILL_DATA
{
	TBLIDX			skillId; // HTB Skill ID
	int				nSkillTime; // Remaining time(in millisecs.)
};


// ��ų ����
struct sSKILL_INFO
{
	TBLIDX			tblidx; // ��ų tblidx
	DWORD			dwTimeRemaining;		// in millisecs.
	int				nExp;
	BYTE			bySlotId;
	BYTE			byRpBonusType;			// eDBO_RP_BONUS_TYPE
	bool			bIsRpBonusAuto;
};


// �� ��ų ����
struct sSKILL_INFO_PET
{
	TBLIDX			tblidx; // ��ų tblidx
	BYTE			bySlotIndex;
};


struct sBUFF_INFO
{
	TBLIDX			sourceTblidx;
	BYTE			bySourceType;			// eDBO_OBJECT_SOURCE
	DWORD			dwInitialDuration;
	DWORD			dwTimeRemaining;		// in millisecs.
	float			afEffectValue[NTL_MAX_EFFECT_IN_SKILL];
};


// HTB ��ų ����Ÿ ( Ŭ���̾�Ʈ ���޿� )
struct sHTB_SKILL_INFO
{
	TBLIDX			skillId; // HTB Skill ID
	BYTE			bySlotId;
	DWORD			dwTimeRemaining; // millisecs
};

// System Effect ���
struct sDBO_SYSTEM_EFFECT_RESULT
{
	eDBO_SYSTEM_EFFECT_RESULT_TYPE		eResultType;

	union
	{
		// �Ϲ����� ���
		float							fResultValue;

		// DH/HOT
		struct
		{
			float						DH_HOT_fHealAmount;
		};

		// DD/DOT
		struct
		{
			float						DD_DOT_fDamage;
			float						DD_DOT_fAbsorbedDamage;
			float						DD_DOT_fReflectedDamage;
		};

		// ACTIVE_LP_STEAL, ACTIVE_EP_STEAL, ACTIVE_LP_STEAL_OVER_TIME, ACTIVE_EP_STEAL_OVER_TIME
		struct
		{
			float						LP_EP_STEAL_fLpDamage;
			float						LP_EP_STEAL_fEpDamage;
			float						LP_EP_STEAL_fAbsorbedDamage;
			float						LP_EP_STEAL_fReflectedDamage;
			float						LP_EP_STEAL_fLpGained;
			float						LP_EP_STEAL_fEpGained;
		};
	};
};

// SKILL ��� ��
struct sSKILL_RESULT
{
	HOBJECT			hTarget;
	BYTE			byAttackResult;		// eBATTLE_ATTACK_RESULT
	sDBO_SYSTEM_EFFECT_RESULT		effectResult1;
	sDBO_SYSTEM_EFFECT_RESULT		effectResult2;
	BYTE							byBlockedAction;		// eDBO_GUARD_TYPE
	sVECTOR3		vShift;
};


// HTB ��ų ��� ��
struct sHTBSKILL_RESULT
{
	BYTE			byStep; // ���� HTB ����
	sSKILL_RESULT	sSkillResult;
};


// Bot�� ��ų ����Ÿ [2/11/2008 SGpro]
struct sSKILL_DATA_BOT
{	// ĳ������ ��ų ���� ����
	BYTE				bySlot;
	TBLIDX				skillId;
	int					nRemainSec;
};

// ��ų ���� [2/11/2008 SGpro]
struct sSKILL_INFO_BOT
{
	TBLIDX			tblidx; // ��ų tblidx
	DWORD			dwTimeRemaining; // in millisecs.
	BYTE			bySlotId;
};

// ��ų AI ���� ���� [2/15/2008 SGpro]
enum eSKILLPRIORITY
{	
	 SKILLPRIORITY_CALL = 0x00ui8		// ������ [2/15/2008 SGpro]
	,SKILLPRIORITY_START				// ������ [2/15/2008 SGpro]
	,SKILLPRIORITY_FAINTING				// ������ [2/15/2008 SGpro]
	,SKILLPRIORITY_LP					// table�� lp���� �ڽſ� lp�� �۰�, cool time�� �ǰ�, table�� time���� �����̰� �Ǿ��ٸ� ��ų �ߵ� [10/29/2008 SGpro]
	,SKILLPRIORITY_GIVE					// table�� lp���� ��Ƽ���� lp�� �۰� , cool time�� �ǰ�, table�� time���� �����̰� �Ǿ��ٸ� ��ų �ߵ� [10/29/2008 SGpro]
	,SKILLPRIORITY_TIME					// table�� time�� cool time�� ���ǿ� �մ��ϸ� ��ų �ߵ� [10/29/2008 SGpro]
	,SKILLPRIORITY_RINGRANGE			// ������ ������ ���� ������ ��ų�� �ߵ��� [8/12/2008 SGpro]
	,SKILLPRIORITY_ONLYLP				// table�� lp ���� �ڽſ� lp�� ���� cool time�� �Ǹ� ��ų�ߵ�, �� �ѹ��� �ߵ�( �������� á�ٰ� �ٽ� �پ��� �ٽ� �� �ߵ� ) [10/29/2008 SGpro]
};

struct sDBO_UPDATED_SKILL_DATA
{
	BYTE			bySkillPassiveEffect;		// eDBO_SKILL_PASSIVE_EFFECT
	union
	{
		// DBO_SKILL_PASSIVE_EFFECT_CASTING_TIME_DOWN
		float		fCasting_Time;

		// DBO_SKILL_PASSIVE_EFFECT_COOL_TIME_DOWN
		WORD		wCool_Time;

		// DBO_SKILL_PASSIVE_EFFECT_SYSTEM_EFFECT_VALUE_UP
		float		fSkill_Effect_Value[NTL_MAX_EFFECT_IN_SKILL];

		// DBO_SKILL_PASSIVE_EFFECT_KEEP_TIME_UP
		WORD		wKeep_Time;

		// DBO_SKILL_PASSIVE_EFFECT_REQUIRED_EP_DOWN
		WORD		wRequire_EP;

		// DBO_SKILL_PASSIVE_EFFECT_APPLY_RANGE_TYPE
		BYTE		byApply_Range;

		// DBO_SKILL_PASSIVE_EFFECT_APPLY_AREA_SIZE_UP
		struct
		{
			BYTE	byApply_Area_Size_1;
			BYTE	byApply_Area_Size_2;
		};

		// DBO_SKILL_PASSIVE_EFFECT_USE_RANGE_MAX_UP
		BYTE		byUse_Range_Max;
	};
};

DWORD Dbo_GetLevelUpGainSP( BYTE byLevel, BYTE byLevelDiff=1 );
DWORD Dbo_GetLevelSP( BYTE byLevel );

#pragma pack()