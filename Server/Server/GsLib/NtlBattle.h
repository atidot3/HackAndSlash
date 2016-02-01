//***********************************************************************************
//
//	File		:	NtlBattle.h
//
//	Begin		:	2006-04-24
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	
//
//***********************************************************************************

#pragma once

#include "NtlBitFlag.h"

// ������ Ÿ��
enum eDBO_DAMAGE_TYPE
{
	DBO_DAMAGE_TYPE_PHYSICAL,
	DBO_DAMAGE_TYPE_ENERGY,

	DBO_DAMAGE_TYPE_COUNT,

	DBO_DAMAGE_TYPE_INVALID = 0xFFui8,

	DBO_DAMAGE_TYPE_FIRST = DBO_DAMAGE_TYPE_PHYSICAL,
	DBO_DAMAGE_TYPE_LAST = DBO_DAMAGE_TYPE_ENERGY
};

// ���� Ÿ��
enum eBATTLE_ATTACK_TYPE
{
	BATTLE_ATTACK_TYPE_PHYSICAL,
	BATTLE_ATTACK_TYPE_ENERGY,

	BATTLE_ATTACK_TYPE_COUNT,

	BATTLE_ATTACK_TYPE_INVALID = 0xFFui8
};


// ���� ���
enum eBATTLE_ATTACK_RESULT
{
	BATTLE_ATTACK_RESULT_HIT, // �Ϲ� ����
	BATTLE_ATTACK_RESULT_CRITICAL_HIT, // ũ��ƼĮ ����
	BATTLE_ATTACK_RESULT_DODGE, // ȸ��
	BATTLE_ATTACK_RESULT_RESISTED, // ����
	BATTLE_ATTACK_RESULT_BLOCK, // ���
	BATTLE_ATTACK_RESULT_REFLECTED_DAMAGE, // Ÿ�����κ��� �ݻ�Ǿ� ���� ����
	BATTLE_ATTACK_RESULT_KNOCKDOWN, // �˴ٿ�
	BATTLE_ATTACK_RESULT_SLIDING, // �����̵�

	BATTLE_ATTACK_RESULT_COUNT,

	BATTLE_ATTACK_RESULT_FIRST = BATTLE_ATTACK_RESULT_HIT,
	BATTLE_ATTACK_RESULT_LAST = BATTLE_ATTACK_RESULT_SLIDING
};


// ���� �Ӽ� ( ��/��/��/��/�� )
enum eBATTLE_ATTRIBUTE
{
	BATTLE_ATTRIBUTE_NONE, // ���Ӽ�
	BATTLE_ATTRIBUTE_HONEST, // ����
	BATTLE_ATTRIBUTE_STRANGE, // ����
	BATTLE_ATTRIBUTE_WILD, // ����
	BATTLE_ATTRIBUTE_ELEGANCE, // ���
	BATTLE_ATTRIBUTE_FUNNY, // ���

	BATTLE_ATTRIBUTE_COUNT,
	BATTLE_ATTRIBUTE_UNKNOWN	= 0xFF,

	BATTLE_ATTRIBUTE_FIRST = BATTLE_ATTRIBUTE_NONE,
	BATTLE_ATTRIBUTE_LAST = BATTLE_ATTRIBUTE_FUNNY
};


// ĳ���� �������� reason
enum eFAINT_REASON
{
	FAINT_REASON_HIT, // �¾Ƽ� 
	FAINT_REASON_SKILL, // ��ų��
	FAINT_REASON_BUFF, // ������
	FAINT_REASON_KNOCKDOWN, // �˴ٿ�����
	FAINT_REASON_SLIDING, // �˴ٿ�����
	FAINT_REASON_COMMAND, // ��ɾ��
	FAINT_REASON_HTB, // HTB�� ���� ���
	FAINT_REASON_REMOVE, // ���ŷ� ���� ��� ( TMQ ��� ��� )
	FAINT_REASON_SELF_FAINTING, // ���� ��ų � ���� �ǽ�

	FAINT_REASON_COUNT,

	FAINT_REASON_UNKNOWN = 0xFF
};


// HTB ���� ����
enum eHTB_SKILL_TYPE
{
	HTB_SKILL_NONE,
	HTB_SKILL_DASH,			// htb�� ó�� ������ �� client�� target�� dash �̵����� ������ �����Ѵ�.(�ڿ������� ������ ���Ͽ�)
	HTB_SKILL_HOMING_UP,	// attacker�� target�� ���� �ö󰣴�.
	HTB_SKILL_HOMING_DOWN,	// attacket�� �������� �ٽ� �����´�.
	HTB_SKILL_JUMPING_UP,	// ���� 12m ���̷� ������ �ö󰣴�
	HTB_SKILL_JUMPING_DOWN,	// ���� 12m ���̿��� ������ �����´�

	HTB_SKILL_TYPE_UNKNOWN	= 0xFF,

	HTB_SKILL_TYPE_FIRST = HTB_SKILL_NONE,
	HTB_SKILL_TYPE_TYPE_LAST  = HTB_SKILL_JUMPING_DOWN
};


// ������Ʋ ���
enum eFREEBATTLE_RESULT
{
	FREEBATTLE_RESULT_WIN, // �����߿� �Ѹ��� HP�� 0�� �Ǿ� �¸���
	FREEBATTLE_RESULT_LOSE, // �����߿� �Ѹ��� ���������� ��� �¸���
	FREEBATTLE_RESULT_DRAW, // �ð��� ����Ǿ� ���ºΰ� ��

	FREEBATTLE_RESULT_COUNT
};


// ���� �׼� ����
enum eATTACK_ACTION
{
	ATTACK_ACTION_HTB,
	ATTACK_ACTION_PUSH,
	ATTACK_ACTION_KNOCKDOWN,
	ATTACK_ACTION_ACTIVE_PULL,

	MAX_ATTACK_ACTION,
	INVALID_ATTACK_ACTION,
};

// ���� �׼� �÷���
enum eATTACK_ACTION_FLAG
{
	ATTACK_ACTION_FLAG_HTB			= MAKE_BIT_FLAG( ATTACK_ACTION_HTB ),
	ATTACK_ACTION_FLAG_PUSH			= MAKE_BIT_FLAG( ATTACK_ACTION_PUSH ),
	ATTACK_ACTION_FLAG_KNOCKDOWN	= MAKE_BIT_FLAG( ATTACK_ACTION_KNOCKDOWN ),
	ATTACK_ACTION_FLAG_ACTIVE_PULL	= MAKE_BIT_FLAG( ATTACK_ACTION_ACTIVE_PULL ),
};

enum eDBO_AGGRO_CHANGE_TYPE
{
	DBO_AGGRO_CHANGE_TYPE_INCREASE,
	DBO_AGGRO_CHANGE_TYPE_DECREASE,
	DBO_AGGRO_CHANGE_TYPE_HIGHEST,
	DBO_AGGRO_CHANGE_TYPE_LOWEST,

	DBO_AGGRO_CHANGE_TYPE_PERCENT,
	DBO_AGGRO_CHANGE_TYPE_HIGHEST_PERCENT,
	DBO_AGGRO_CHANGE_TYPE_LOWEST_PERCENT,

	DBO_AGGRO_CHANGE_TYPE_COUNT,

	DBO_AGGRO_CHANGE_TYPE_FIRST = DBO_AGGRO_CHANGE_TYPE_INCREASE,
	DBO_AGGRO_CHANGE_TYPE_LAST = DBO_AGGRO_CHANGE_TYPE_COUNT - 1,
};

//-----------------------------------------------------------------------------------
// ���� ���� ��� ���� : [4/25/2006 zeroera] : �����ʿ� : lua�� �ű� ��
//-----------------------------------------------------------------------------------
const float			NTL_BATTLE_PUSH_DISTANCE					= 1.0f; // PUSH �Ÿ�
const float			NTL_BATTLE_KNOCKDOWN_DISTANCE				= 5.6f;	// KNOCKDOWN �Ÿ�.
const float			NTL_BATTLE_SLIDING_DISTANCE					= 4.0f; // SLIDING �Ÿ�

const int			NTL_BATTLE_CHAIN_ATTACK_START				= 1; // chain attack start id 

const int			NTL_BATTLE_MAX_CHAIN_ATTACK_COUNT			= 6; // �ִ� ü�� ���� ��

const float			NTL_BATTLE_BLOCK_DAMAGE_REDUCE_RATE			= 0.3f;
const float			DBO_BATTLE_OFFENCE_CHANGE_RATE_BY_BLOCK			= 0.3f;
const float			NTL_BATTLE_CRITICAL_DAMAGE_INCREASE_RATE	= 1.5f;
const float			DBO_BATTLE_OFFENCE_BONUS_RATE_BY_CRITICAL		= 50.0f;		// in percent

const float			NTL_BATTLE_HIT_FRONT_SIDE_BONUS_RATE		= 1.0f;
const float			NTL_BATTLE_HIT_BACK_SIDE_BONUS_RATE			= 0.5f;

const DWORD			NTL_BATTLE_ATTACK_DELAY_TIME				= 1000;

const DWORD			NTL_BATTLE_KNOCKDOWN_WAKEUP_TIME			= 4000; // �˴ٿ�� �Ͼ�� Ÿ�� ( NPC / MOB �� )
const DWORD			NTL_BATTLE_KNOCKDOWN_MIN_WAKEUP_TIME		= 2000; // �˴ٿ�� �Ͼ�� Ÿ�� ( PC�� )
const DWORD			NTL_BATTLE_KNOCKDOWN_MAX_WAKEUP_TIME		= 6000; // �˴ٿ�� �Ͼ�� Ÿ�� ( PC�� )
const DWORD			NTL_BATTLE_KNOCKDOWN_WAKEUP_TIME_DIFF		= NTL_BATTLE_KNOCKDOWN_MAX_WAKEUP_TIME - NTL_BATTLE_KNOCKDOWN_MIN_WAKEUP_TIME;
const DWORD			NTL_BATTLE_SLIDING_END_TIME					= 1200; // �����̵� ������ Ÿ��
const DWORD			NTL_BATTLE_HTB_SANDBAG_END_TIME				= 10000; // HTB�� SANDBAG ������ Ÿ��

const int			NTL_BATTLE_MAX_NPC_ATTACK_TYPE				= 2; // NPC �� ���� ���� ( ����� 2���� )

// Free Battle
const float			DBO_FREEBATTLE_CHALLENGE_RANGE				= 10.0f; // ������Ʋ�� ������ �� �ִ� �Ÿ�
const float			DBO_FREEBATTLE_MATCH_INSIDE_RADIUS			= 45.0f; // ������Ʋ�� ���������� ������ ���� ���� ����(������)
const float			DBO_FREEBATTLE_MATCH_OUTSIDE_RADIUS			= 50.0f; // ������Ʋ�� ���������� ������ �ٱ��� ���� ����(������)
const DWORD			DBO_FREEBATTLE_CHALLENGE_RETRY_TIME			= 10; // ������Ʋ�� �絵��(��)
const DWORD			DBO_FREEBATTLE_CHALLENGE_RETRY_MILLITIME	= DBO_FREEBATTLE_CHALLENGE_RETRY_TIME * 1000; // ������Ʋ�� �絵��(�и�������)
const DWORD			DBO_FREEBATTLE_CHALLENGE_WAIT_TIME			= 60; // ������Ʋ�� �絵��(��)
const DWORD			DBO_FREEBATTLE_CHALLENGE_WAIT_MILLITIME		= DBO_FREEBATTLE_CHALLENGE_WAIT_TIME * 1000; // ������Ʋ�� �絵��(�и�������)
const DWORD			DBO_FREEBATTLE_OUTSIDE_ALLOW_TIME			= 10; // ������Ʋ�� ������ �ð�(��)
const DWORD			DBO_FREEBATTLE_OUTSIDE_ALLOW_MILLITIME		= DBO_FREEBATTLE_OUTSIDE_ALLOW_TIME * 1000; // ������Ʋ�� ������ �ð�(�и�������)
const DWORD			DBO_FREEBATTLE_MATCH_TIME					= 3600; // ������Ʋ ��� �ð�(��)
const DWORD			DBO_FREEBATTLE_MATCH_MILLITIME				= DBO_FREEBATTLE_MATCH_TIME * 1000; // ������Ʋ ���ð�(�и����������)

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
const char * NtlGetBattleAttackTypeString(BYTE byAttackType);

const char * NtlGetBattleAttackResultString(BYTE byAttackResult);

const char * DboGetFreeBattleResultString(BYTE byBattleResult);


//-----------------------------------------------------------------------------------
// ���� ���� �Լ� ���� : [4/25/2006 zeroera] : �����ʿ� : lua�� �ű� ��
//-----------------------------------------------------------------------------------
BYTE				NtlGetBattleChainAttackSequence(BYTE byCharLevel); // ������ �ִ� CHAIN ATTACK �� 

float				NtlGetBattleAttributeBonusRate(BYTE bySubjectAtt, BYTE byTargetAtt); // ĳ���� ���� �Ӽ��� ���� ���ʽ� ���ݷ�

float				NtlGetBattleChainAttackBounsRate(BYTE byAttackSequence); // ü�� ���ÿ� ���� ���ʽ� ���ݷ�
