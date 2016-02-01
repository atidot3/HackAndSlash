//***********************************************************************************
//
//	File		:	NtlWorld.cpp
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

#include "stdafx.h"
#include "NtlWorld.h"

#include <crtdbg.h>


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
const char * s_game_rule_string[ GAMERULE_TYPE_COUNT ] = 
{
	"GAMERULE_NORMAL",
	"GAMERULE_RANKBATTLE",
	"GAMERULE_BUDOKAI",
	"GAMERULE_DOJO",
	"GAMERULE_RAID",
	"GAMERULE_HUNT",
	"GAMERULE_TIMEQUEST",
	"GAMERULE_TUTORIAL",
	"GAMERULE_MINORMATCH",
	"GAMERULE_MAJORMATCH",
	"GAMERULE_FINALMATCH",
	"GAMERULE_TEINKAICHIBUDOKAI",
	"GAMERULE_TLQ",
};


//-----------------------------------------------------------------------------------
// ���ӷ� Ÿ�� �Լ� ���� : 
//-----------------------------------------------------------------------------------
const char * NtlGetGameRuleTypeString(BYTE byRuleType)
{
	if( byRuleType >= GAMERULE_TYPE_COUNT )
	{
		return "UNDEFINED_GAME_RULE";
	}

	return s_game_rule_string[ byRuleType ];
}


//-----------------------------------------------------------------------------------
// Ʈ���� ������Ʈ �ڵ鰪 ���� �Լ�
//-----------------------------------------------------------------------------------
HOBJECT MakeTriggerObjectHandle(HOBJECT hWorldTriggerObjectOffset, DWORD dwTriggerObjectSequence)
{
	return hWorldTriggerObjectOffset + dwTriggerObjectSequence;
}