//***********************************************************************************
//
//	File		:	NtlMatch.h
//
//	Begin		:	2008-05-06
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	
//
//	Desc		:	
//
//***********************************************************************************

#pragma once

#include "SharedDef.h"
#include "SharedType.h"
#include "NtlParty.h"


//---------------------------------------------------------------------------------------

#define	NTL_MAX_MINORMATCH_TEAM_COUNT	32


// �ִ� ���� �������� ī��Ʈ
#define NTL_MAX_MATCH_EXTENDED_STAGE_COUNT		3

// �ִ� �������� ī��Ʈ
#define NTL_MAX_MATCH_STAGE_COUNT				(5 + NTL_MAX_MATCH_EXTENDED_STAGE_COUNT)

// õ�����Ϲ���ȸ ���� �ִ� ������ ī��Ʈ ���� : NTL_MAX_MATCH_EXTENDED_STAGE_COUNT ���� ū ���ڰ� �� �� ����.
#define DBO_MAX_MAJORMATCH_EXTENDED_STAGE_COUNT	1


// õ�����Ϲ���ȸ������ ��� ������ �ִ� ������ ����
#define	MAX_BUDOKAI_MATCH_REWARD_ITEM_COUNT		3

//---------------------------------------------------------------------------------------

// Match Type
enum eMATCHWORLD_TYPE
{
	MATCHWORLD_TYPE_MINOR_MATCH,			// ���� : eBUDOKAI_MINORMATCH_STATE
	MATCHWORLD_TYPE_MAJOR_MATCH,			// ���� : eBUDOKAI_MAJORMATCH_STATE
	MATCHWORLD_TYPE_FINAL_MATCH,			// �ἱ : eBUDOKAI_FINALMATCH_STATE

	MAX_MATCHWORLD_TYPE,
	INVALID_MATCHWORLD_TYPE = 0xff
};



// Member �� ����
enum eMATCH_MEMBER_STATE
{
	MATCH_MEMBER_STATE_NONE,			// �ʱ� ����
	MATCH_MEMBER_STATE_NORMAL,			// �Ϲ� ����
	MATCH_MEMBER_STATE_FAINT,			// ����
	MATCH_MEMBER_STATE_OUTOFAREA,		// ���
	MATCH_MEMBER_STATE_GIVEUP,			// �������(���� ���� ��)
	MATCH_MEMBER_STATE_NOAPPLY,			// PC ������ ������ ��� ���� �� ������ �������� �ʴ´�.
	MATCH_MEMBER_STATE_TELEPORTING,		// �ڷ���Ʈ ���̴�. ����� ���ο��� ���η� �ڷ���Ʈ �Ѱ��
	MATCH_MEMBER_STATE_BE_LATE,			// ��� ���� ������ ���, ����, ���� ������ ����
	MATCH_MEMBER_STATE_RESCUE,			// ��Ȱ����(�ڷ���Ʈ)
};


enum eMATCH_TEAM_TYPE
{
	MATCH_TEAM_TYPE_TEAM1,
	MATCH_TEAM_TYPE_TEAM2,

	MAX_MATCH_TEAM_TYPE_COUNT,
	INVALID_MATCH_TEAM_TYPE = 0xffff
};


//
enum eMATCH_RESULT
{
	MATCH_RESULT_SUCCESS,

	//	MATCH_RESULT_TYPE_ALL_LEAVED,		// �ƹ��� ����
	//	MATCH_RESULT_TYPE_STAY_ALONE,		// ȥ�� ����

	MATCH_RESULT_DRAW,						// ���
	MATCH_RESULT_WIN,						// ���ڰ� ����

	MATCH_RESULT_TIMEOVER,					// �ð��� ����

	MATCH_RESULT_DOJO_RECOMMENDER,			// ���� ��õ��
	MATCH_RESULT_UNEARNED_WIN,				// ������

	INVALID_MATCH_RESULT = 0xff,
};


// ���� : ��Ʋ�ξ�
enum eBUDOKAI_MINORMATCH_STATE
{
	BUDOKAI_MINORMATCH_STATE_NONE,			// �ʱ� ����
	BUDOKAI_MINORMATCH_STATE_WAIT_MINORMATCH,	// ������ ��� �ð�
	BUDOKAI_MINORMATCH_STATE_WAIT,			// �����ڵ��� ��ٸ�
	BUDOKAI_MINORMATCH_STATE_DIRECTION,		// ����
	BUDOKAI_MINORMATCH_STATE_MATCH_READY,	// ��� �غ�
	BUDOKAI_MINORMATCH_STATE_STAGE_READY,	// �������� �غ�
	BUDOKAI_MINORMATCH_STATE_STAGE_RUN,		// �������� ����
	BUDOKAI_MINORMATCH_STATE_STAGE_SELECTION,	// ������ ��÷
	BUDOKAI_MINORMATCH_STATE_STAGE_FINISH,	// �������� ����
	BUDOKAI_MINORMATCH_STATE_MATCH_FINISH,	// ��� ����
	BUDOKAI_MINORMATCH_STATE_END,			// ����

	MAX_BUDOKAI_MINORMATCH_STATE,
	INVALID_BUDOKAI_MINORMATCH_STATE = INVALID_BYTE
};



// ����
enum eBUDOKAI_MAJORMATCH_STATE
{
	BUDOKAI_MAJORMATCH_STATE_NONE,			// �ʱ� ����
	BUDOKAI_MAJORMATCH_STATE_WAIT,			// �����ڵ��� ��ٸ�
	BUDOKAI_MAJORMATCH_STATE_DIRECTION,		// ����
	BUDOKAI_MAJORMATCH_STATE_MATCH_READY,	// ��� �غ�
	BUDOKAI_MAJORMATCH_STATE_STAGE_READY,	// �������� �غ�
	BUDOKAI_MAJORMATCH_STATE_STAGE_RUN,		// �������� ����
	BUDOKAI_MAJORMATCH_STATE_STAGE_FINISH,	// �������� ����
	BUDOKAI_MAJORMATCH_STATE_MATCH_FINISH,	// ��� ����
	BUDOKAI_MAJORMATCH_STATE_END,			// ����

	MAX_BUDOKAI_MAJORMATCH_STATE,
	INVALID_BUDOKAI_MAJORMATCH_STATE = INVALID_BYTE
};



// �ἱ
enum eBUDOKAI_FINALMATCH_STATE
{
	BUDOKAI_FINALMATCH_STATE_NONE,			// �ʱ� ����
	BUDOKAI_FINALMATCH_STATE_WAIT,			// �����ڵ��� ��ٸ�
	BUDOKAI_FINALMATCH_STATE_DIRECTION,		// ����
	BUDOKAI_FINALMATCH_STATE_MATCH_READY,	// ���ο� ��� �غ�
	BUDOKAI_FINALMATCH_STATE_STAGE_READY,	// �������� �غ�
	BUDOKAI_FINALMATCH_STATE_STAGE_RUN,		// �������� ����
	BUDOKAI_FINALMATCH_STATE_STAGE_FINISH,	// �������� ����
	BUDOKAI_FINALMATCH_STATE_MATCH_FINISH,	// ��� ����
	BUDOKAI_FINALMATCH_STATE_FINALDIRECTION,// ����� ����
	BUDOKAI_FINALMATCH_STATE_AWARDING,		// �û�
	BUDOKAI_FINALMATCH_STATE_END,			// ����

	MAX_BUDOKAI_FINALMATCH_STATE,
	INVALID_BUDOKAI_FINALMATCH_STATE = INVALID_BYTE
};



//---------------------------------------------------------------------------------------
// Final Match

enum eFINALMATCH_TYPE
{
	FINALMATCH_TYPE_SEMIFINAL_1 = 0,
	FINALMATCH_TYPE_SEMIFINAL_2,
	FINALMATCH_TYPE_FINAL,

	FINALMATCH_TYPE_COUNT,
	INVALID_FINALMATCH_TYPE = 0xFF,
};

enum eFINALMATCH_RESULT
{
	FINALMATCH_RESULT_WINNER,			// ���
	FINALMATCH_RESULT_SEMIWINNER,		// �ؿ��
	FINALMATCH_RESULT_MATCH1_LOSER,		// �ذ�� 1��� �й�
	FINALMATCH_RESULT_MATCH2_LOSER,		// �ذ�� 2��� �й�

	MAX_FINALMATCH_RESULT,
};


//---------------------------------------------------------------------------------------
#pragma pack(1)


struct sMATCH_SCORE
{
	BYTE	byTeam1;
	BYTE	byTeam2;
};


//
struct sMATCH_MEMBER_STATE_INFO
{
	HOBJECT		handle;				// pc handle
	BYTE		byState;			// eMATCH_MEMBER_STATE
	BYTE		byLevel;
	BYTE		byClass;			// ePC_CLASS
	WORD		wGuildName;			// WCHAR		wszGuildName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];
	WORD		wWinCount;			// RankBattle ��� Win
	WORD		wDrawCount;			// RankBattle ��� Draw
	WORD		wLoseCount;			// RankBattle ��� Lose
	WORD		wCharName;			// WCHAR		wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
};


// MinorMatch TeamInfo
struct sMATCH_MINORMATCH_TEAM_INFO
{
	TEAMTYPE					wTeamType;
	WCHAR						wszTeamName[NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
	bool						bDojoRecommender;
	BYTE						byMemberCount;
	sMATCH_MEMBER_STATE_INFO	aMembers[NTL_MAX_MEMBER_IN_PARTY];
};

// MinorMatch TeamInfo Variable Data
struct sMATCH_MINORMATCH_TEAM_INFO_VAR
{
	TEAMTYPE	wTeamType;
	WORD		wTeamName_var;		//	WCHAR [NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
	bool		bDojoRecommender;	// ���� ��õ
	BYTE		byMemberCount;
	WORD		wMembers_var;		// sMATCH_MEMBER_STATE_INFO [NTL_MAX_MEMBER_IN_PARTY];
};

typedef	sMATCH_MINORMATCH_TEAM_INFO			sMATCH_MAJORMATCH_TEAM_INFO;
typedef sMATCH_MINORMATCH_TEAM_INFO_VAR		sMATCH_MAJORMATCH_TEAM_INFO_VAR;

typedef	sMATCH_MINORMATCH_TEAM_INFO			sMATCH_FINALMATCH_TEAM_INFO;
typedef sMATCH_MINORMATCH_TEAM_INFO_VAR		sMATCH_FINALMATCH_TEAM_INFO_VAR;


// MinorMatch Team score
struct sMATCH_MINORMATCH_TEAM_SCORE
{
	TEAMTYPE	teamType;
	BYTE		byScore;
};

#pragma pack()
