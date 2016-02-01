//***********************************************************************************
//
//	File		:	NtlRankBattle.h
//
//	Begin		:	2007-05-31
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	
//
//	Desc		:	
//
//***********************************************************************************

#pragma once

#include "SharedType.h"
#include "SharedDef.h"
#include "NtlParty.h"

//-----------------------------------------------------------------------------------
// Enumeration
//-----------------------------------------------------------------------------------

// Room State
enum eRANKBATTLE_ROOMSTATE
{
	RANKBATTLE_ROOMSTATE_NONE,			// �ʱ�
	RANKBATTLE_ROOMSTATE_WAIT,			// ������븦 ��ٸ�
	RANKBATTLE_ROOMSTATE_MATCH_READY,	// ���� �غ���
	RANKBATTLE_ROOMSTATE_WAIT_MATCH_WORLD,	// ������� �����Ǳ⸦ ��ٸ�
	RANKBATTLE_ROOMSTATE_MATCH_RUN,		// ���� ����
	RANKBATTLE_ROOMSTATE_MATCH_END,		// ���� ������ -> ���� �ٽ� WAIT ���·� �����

	RANKBATTLE_ROOMSTATE_COUNT,
	INVALID_RANKBATTLE_ROOMSTATE = INVALID_BYTE,
};


// ��ũ��Ʋ ���
enum eRANKBATTLE_MODE
{
	RANKBATTLE_MODE_INDIVIDUAL, // ������
	RANKBATTLE_MODE_PARTY, // ��Ƽ��

	MAX_RANKBATTLE_MODE,
	INVALID_RANKBATTLE_MODE = INVALID_BYTE
};

enum eRANKBATTLE_TEAM_TYPE
{
	RANKBATTLE_TEAM_NONE		= 0,
	RANKBATTLE_TEAM_OWNER		= 0x01 << 0,
	RANKBATTLE_TEAM_CHALLENGER	= 0x01 << 1,
	RANKBATTLE_TEAM_OTHER		= 0x01 << 2,				// ���� �ƴѰ��, ex.GM

	RANKBATTLE_TEAM_ALL			= RANKBATTLE_TEAM_OWNER | RANKBATTLE_TEAM_CHALLENGER,		// RANKBATTLE_TEAM_OTHER �� ����
};


// ��ũ��Ʋ ���� ���
enum eRANKBATTLE_BATTLESTATE
{
	RANKBATTLE_BATTLESTATE_NONE,			// �ʱ� ����
	RANKBATTLE_BATTLESTATE_WAIT,			// �����ڵ��� ��ٸ�
	RANKBATTLE_BATTLESTATE_DIRECTION,		// ����
	RANKBATTLE_BATTLESTATE_STAGE_READY,		// �������� �غ�
	RANKBATTLE_BATTLESTATE_STAGE_RUN,		// �������� ����
	RANKBATTLE_BATTLESTATE_STAGE_FINISH,	// �������� ����
	RANKBATTLE_BATTLESTATE_MATCH_FINISH,	// ��� ����
	RANKBATTLE_BATTLESTATE_BOSS_DIRECTION,	// BOSS ����
	RANKBATTLE_BATTLESTATE_BOSS_READY,		// BOSS �غ�
	RANKBATTLE_BATTLESTATE_BOSS_RUN,		// BOSS ����
	RANKBATTLE_BATTLESTATE_BOSS_FINISH,		// BOSS ����
	RANKBATTLE_BATTLESTATE_END,				// ����

	MAX_RANKBATTLE_BATTLESTATE,
	INVALID_RANKBATTLE_BATTLESTATE = INVALID_BYTE
};


// Member �� ����
enum eRANKBATTLE_MEMBER_STATE
{
	RANKBATTLE_MEMBER_STATE_NONE,			// �ʱ� ����
	RANKBATTLE_MEMBER_STATE_NORMAL,			// �Ϲ� ����
	RANKBATTLE_MEMBER_STATE_FAINT,			// ����
	RANKBATTLE_MEMBER_STATE_OUTOFAREA,		// ���
	RANKBATTLE_MEMBER_STATE_GIVEUP,			// �������(���� ���� ��)
	RANKBATTLE_MEMBER_STATE_NOAPPLY,		// PC ������ ������ ��� ���� �� ������ �������� �ʴ´�.
};


// Match Result
enum eRANKBATTLE_MATCH_RESULT
{
	RANKBATTLE_MATCH_NONE,				// ���� ��Ȳ : ��� ������� ���� ����.. ������ - ��Ų��.
	RANKBATTLE_MATCH_WIN_OWNER,		// ���� ��
	RANKBATTLE_MATCH_WIN_CHALLENGER,	// ������ ��
	RANKBATTLE_MATCH_DRAW,				// ���

	INVALID_RANKBATTLE_MATCH = INVALID_BYTE,
};



// ������������ RankBattle Score�� Update �Ҷ� ���
enum eRANKBATTLE_QUERY_UPDATE_TYPE
{
	RANKBATTLE_QUERY_UPDATE_NONE,		// �״�� �д�,(������Ʈ ���� �ʴ´�.)
	RANKBATTLE_QUERY_UPDATE_ADD,		// 1 �߰��Ѵ�
	RANKBATTLE_QUERY_UPDATE_INIT,		// 0���� �ʱ�ȭ ��Ų��.
};


//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//	��� ����
//-----------------------------------------------------------------------------------
const DWORD		DBO_RANKBATTLE_MAX_ROOM_COUNT = 100;			// ��ũ��Ʋ �ʴ� ���� �ִ� ����

const DWORD		DBO_RANKBATTLE_MAX_ROOM_COUNT_PER_PAGE = 10;	// ���������� ����� �ִ� ���� ���� (��������)

const DWORD		DBO_RANKBATTLE_USER_WAIT_TIME = 60000;			// ���� ��� 1��

const DWORD		DBO_RANKBATTLE_NAME_LENGTH = 128;				// RankBattle�� �̸�

const BYTE		DBO_RANKBATTLE_PARTY_MEMBER_RESTRICTION = 1;	// ��Ƽ�ο� ����

const DWORD		DBO_RANKBATTLE_ROOM_READY_TIME = 10000;			// ���� ���� �˸� �� ���������� ��� �ð�

const DWORD		DBO_RANKBATTLE_ENDSTAGE_WAIT_TIME = 5000;		// End Stage ���� ��� �ð�

const BYTE		DBO_RANKBATTLE_MAX_RANK_BOARD_RECORD_COUNT = 10;	// Rank �Խ��ǿ� ��µǴ� �ִ� ���ڵ� ī��Ʈ

const BYTE		DBO_RANKBATTLE_MAX_COMPARE_DAY = 7;					// Rank �Խ��ǿ��� ���Ҽ� �ִ� �ִ� �ϼ�

const DWORD		DBO_RANKBATTLE_RANK_REQUEST_TERM = 500;		// 2�ʿ� �ѹ��� Rank list ��û�� �� �� �ִ�.

const BYTE		DBO_RANKBATTLE_RANK_BACKUP_TIME = 6;			// Rank�� Backup�ϴ� �ð� 0~23, * ���� DB�� �����ٰ� ���� ������Ʈ �ؾ� �Ѵ�. *


const WORD		DBO_RANKBATTLE_MAX_ARENA_TYPE = 10;				// �Ʒ��� ������ �ִ� ���� ������,��Ƽ�� ���� 10��

const DWORD		DBO_RANKBATTLE_MATCH_START_TERM = 60;			// ��Ⱑ �����ϴ� �ֱ�

const BYTE		DBO_RANKBATTLE_MAX_MATCHING_LEVEL = 1;			// ��⸦ ������ �� �ִ� �� PC �� Party ���� �ִ� ���� ����

//-----------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------
//	�ڷ� ���� ����
//-----------------------------------------------------------------------------------
#pragma pack(1)

struct sRANKBATTLE_ARENA_INFO
{
	TBLIDX		rankBattleTblidx;
	WORD		wRegisterCount;
};



// ������ �� ����
struct sRANKBATTLE_ROOMLIST_INDIVIDUAL
{
	ROOMID	roomId;
	WCHAR	wszOwnerPc[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];	// ����
	WORD	wWinCounter;
};



// ��Ƽ�� �� ����
struct sRANKBATTLE_ROOMLIST_PARTY
{
	ROOMID	roomId;
	WCHAR	wszOwnerParty[NTL_MAX_SIZE_PARTY_NAME_IN_UNICODE + 1];	// ����
	WORD	wWinCounter;
};


//--------------------------------------------------------------------------------
// �� �� ����

// �� �� ���� ���ۿ� ����ϴ� Member�� ����
struct sRANKBATTLE_ROOMINFO_MEMBER
{
	WCHAR	wszName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];	//
	BYTE	byClass;
	BYTE	byLevel;
};


// �� �� ���� ���ۿ� ����ϴ� ���� �� ����
struct sRANKBATTLE_ROOMINFO_INDIVIDUAL
{
	TBLIDX						rankBattleTblidx;	// RankBattle Tblidx
	ROOMID						roomId;
	WORD						wWinCount;

	sRANKBATTLE_ROOMINFO_MEMBER	sMember;			// Member
};


// �� �� ���� ���ۿ� ����ϴ� ��Ƽ �� ����
struct sRANKBATTLE_ROOMINFO_PARTY
{
	TBLIDX						rankBattleTblidx;	// RankBattle Tblidx
	ROOMID						roomId;
	WORD						wWinCount;
	WCHAR						wszPartyName[NTL_MAX_SIZE_PARTY_NAME_IN_UNICODE + 1];

	BYTE						byMemberCount;		// Room�� MemberCount
	sRANKBATTLE_ROOMINFO_MEMBER	asMember[NTL_MAX_MEMBER_IN_PARTY];		// Member
};


// 
union uRANKBATTLE_ROOMINFO
{
	sRANKBATTLE_ROOMINFO_INDIVIDUAL	sIndividual;
	sRANKBATTLE_ROOMINFO_PARTY		sParty;
};


//-------------------------------------------------------------------------------


// Ŭ���̾�Ʈ�� �� ����Ʈ�� ������ �� ���
union uRANKBATTLE_ROOMINFO_LIST
{
	// �迭�� ũ�� : ���� ���۵Ǵ� �����ʹ� byRoomCount ��ŭ�� ���۵ȴ�.
	sRANKBATTLE_ROOMLIST_INDIVIDUAL	asIndividualRoom[DBO_RANKBATTLE_MAX_ROOM_COUNT_PER_PAGE];	// byRoomMode == RANKBATTLE_MODE_INDIVIDUAL
	sRANKBATTLE_ROOMLIST_PARTY		asPartyRoom[DBO_RANKBATTLE_MAX_ROOM_COUNT_PER_PAGE];	// byRoomMode == RANKBATTLE_MODE_PARTY
};

struct sRANKBATTLE_SCORE_INFO
{
	WORD						wMaxStraightWin;	// �ִ� ���� ī��Ʈ
	WORD						wStraightWin;		// ���� ī��Ʈ
	WORD						wMaxStraightKOWin;	// �ִ� KO ���� ī��Ʈ
	WORD						wStraightKOWin;		// KO ���� ī��Ʈ
	DWORD						dwWin;				// �¸� ī��Ʈ
	DWORD						dwDraw;				// ���º� ī��Ʈ
	DWORD						dwLose;				// �й� ī��Ʈ
	float						fPoint;				// Point
};


// 
struct sRANKBATTLE_MEMBER_RESULT
{
	HOBJECT	hPc;
	WORD	wResultCode;
};

// RankBattle �� �����ϴ� PC ���� ����
struct sRANKBATTLE_MATCH_MEMBER_INFO
{
	HOBJECT hPc;
	BYTE	byTeam;		// eRANKBATTLE_TEAM_TYPE
	BYTE	byState;	// eRANKBATTLE_MEMBER_STATE
};



// Score : [Battle Score - ����� ���, Stage Score - �ش� Stage�� ���] � ���ȴ�.
struct sRANKBATTLE_SCORE
{
	BYTE	byOwner;
	BYTE	byChallenger;
};



// Point : BattlePoint
struct sRANKBATTLE_POINT
{
	float					fOwner;
	float					fChallenger;
};


// ��� ���
struct sRANKBATTLE_MATCH_FINISH_INFO
{
	struct sWINER_RECORD
	{
		WORD				wStraightKOWinCount;	// KO ���� ī��Ʈ
		WORD				wStraightWinCount;		// ���� ī��Ʈ
	};

	struct sTEAM_MATCH_FINISH_INFO
	{
		BYTE			byScore;		// score

		float			fPoint;			// ȹ�� ����Ʈ
		float			fBonusPoint;	// ���ʽ� ����Ʈ

		WORD			wWinCount;
		WORD			wDrawCount;
		WORD			wLoseCount;
	};

	//------------------------------------------------------------------------

	BYTE					byMatchWinner;			// eRANKBATTLE_MATCH_RESULT : Winner
	sWINER_RECORD			sWinerRecord;

	sTEAM_MATCH_FINISH_INFO	sOwnerInfo;
	sTEAM_MATCH_FINISH_INFO	sChallengerInfo;
};


// 
struct sRANKBATTLE_RANK_DATA
{
	WCHAR				wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE];
	BYTE				byLevel;
	BYTE				byClass;
	WCHAR				wszGuildName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE];
	int					nPoint;
	WORD				wStraightWinCount;
	DWORD				adwCompareRank[DBO_RANKBATTLE_MAX_COMPARE_DAY];
};

struct sRANKBATTLE_RANK_INFO
{
	WORD				wCharName;				// WCHAR [NTL_MAX_SIZE_CHAR_NAME_UNICODE]
	BYTE				byLevel;
	BYTE				byClass;
	WORD				wGuildName;				// WCHAR [NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE]
	int					nPoint;
	WORD				wStraightWinCount;
	DWORD				dwCompareRank;
};


#pragma pack()
//-------------------------------------------------------------------------------------