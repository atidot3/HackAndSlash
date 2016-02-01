//***********************************************************************************
//
//	File		:	NtlPartyDungeon.h
//
//	Begin		:	2008-07-22
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Chung, Doo-Sup (mailto:john@ntl-inc.com)
//
//	Desc		:	
//
//***********************************************************************************
#pragma once

#include "SharedType.h"

enum ePARTY_DUNGEON_STATE
{
	PARTY_DUNGEON_STATE_NORMAL,		// normal
	PARTY_DUNGEON_STATE_HARD,		// hard
	PARTY_DUNGEON_STATE_SUPER,		// super
	PARTY_DUNGEON_STATE_HERO,		// hero

	PARTY_DUNGEON_STATE_FIRST = PARTY_DUNGEON_STATE_NORMAL,
	PARTY_DUNGEON_STATE_LAST = PARTY_DUNGEON_STATE_HERO,
};



const DWORD NTL_MIN_MEMBER_IN_DUNGEON = 1;
const DWORD NTL_MIN_DUNGEON_CHECK_TIME = 1 * 1000;
const DWORD NTL_MIN_DUNGEON_PARTYOUT_TIME = 30 * 1000;


//-----------------------------------------------------------------------------
// TLQ Define

// TLQ Rule State Type
enum eTLQ_STATE_TYPE
{
	TLQ_STATE_WAIT,				// TLQ ���� �� �÷��̾� ���� ���
	TLQ_STATE_PREPARE,			// �÷��̾� ������ WPS ����
	TLQ_STATE_RUN,				// �÷��� ����
	TLQ_STATE_FAIL,				// ����
	TLQ_STATE_END,				// ���� ����

	TLQ_STATE_COUNT,
};

//-----------------------------------------------------------------------------


