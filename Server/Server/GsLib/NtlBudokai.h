//***********************************************************************************
//
//	File		:	NtlBudokai.h
//
//	Begin		:	2008-04-22
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Ju-hyung Lee
//
//	Desc		:	õ�����Ϲ���ȸ
//
//***********************************************************************************

#pragma once

#include "NtlParty.h"

// õ�����Ϲ���ȸ�� �����ֱ⸦ �˾Ƴ���.
BUDOKAITIME CalcBudokaiNextStartTime( BUDOKAITIME tmDefaultTime, BYTE byOpenTerm, BYTE byOpenDayOfWeek, BYTE byOpenHour, BYTE byOpenMinute );


// õ�����Ϲ���ȸ Ÿ��
enum eBUDOKAI_TYPE
{
	BUDOKAI_TYPE_JUNIOR,	// �ҳ��
	BUDOKAI_TYPE_ADULT,		// ���κ�

	INVALID_BUDOKAI_TYPE = 0xff
};


// õ�����Ϲ���ȸ ��� Ÿ��
enum eBUDOKAI_MATCH_TYPE
{
	BUDOKAI_MATCH_TYPE_INDIVIDIAUL,
	BUDOKAI_MATCH_TYPE_TEAM,

	MAX_BUDOKAI_MATCH_TYPE,
	INVALID_BUDOKAI_MATCH_TYPE = 0xff,
};


// ������ ���� Ÿ��
enum eBUDOKAI_NOTICE_TYPE
{
	BUDOKAI_NOTICE_SYSTEM,					// �������� ���̺� �ε����� ����
	BUDOKAI_NOTICE_GM,						// �������� ��Ʈ���� ����
	BUDOKAI_NOTICE_ONLY_CLIENT,				// Ŭ���̾�Ʈ���� ��ü ó��

	INVALID_BUDOKAI_NOTICE_TYPE = 0xff,
};


//
enum eBUDOKAI_STATE
{
	// �ҳ��
	BUDOKAI_STATE_JUNIOR_CLOSE,
	BUDOKAI_STATE_JUNIOR_OPEN_NOTICE,
	BUDOKAI_STATE_JUNIOR_DOJO_RECOMMEND,
	BUDOKAI_STATE_JUNIOR_OPEN,
	BUDOKAI_STATE_JUNIOR_CLEAR,

	// ���κ�
	BUDOKAI_STATE_CLOSE,
	BUDOKAI_STATE_OPEN_NOTICE,		// ���� ����
	BUDOKAI_STATE_DOJO_RECOMMEND,	// ���� ��õ
	BUDOKAI_STATE_OPEN,
	BUDOKAI_STATE_CLEAR,

	MAX_BUDOKAI_STATE,
	BUDOKAI_STATE_JUNIOR_FIRST = BUDOKAI_STATE_JUNIOR_CLOSE,
	BUDOKAI_STATE_JUNIOR_LAST = BUDOKAI_STATE_JUNIOR_CLEAR,
	BUDOKAI_STATE_ADULT_FIRST = BUDOKAI_STATE_CLOSE,
	BUDOKAI_STATE_ADULT_LAST = BUDOKAI_STATE_CLEAR,
	BUDOKAI_STATE_FIRST = BUDOKAI_STATE_JUNIOR_CLOSE,
	BUDOKAI_STATE_LAST = BUDOKAI_STATE_CLEAR,
	INVALID_BUDOKAI_STATE = 0xff,
};

// eBUDOKAI_STATE �� ����Ǿ�� �� ��� ���� �Լ��� �����ؾ� �Ѵ�.
eBUDOKAI_TYPE GetBudokaiType( BYTE byState );	// eBUDOKAI_STATE

// is open
bool IsBudokaiOpen( BYTE byState );


//
enum eBUDOKAI_MATCHSTATE
{
	BUDOKAI_MATCHSTATE_REGISTER,				// ��� �Ⱓ
	BUDOKAI_MATCHSTATE_WAIT_MINOR_MATCH,		// ������ ���
	BUDOKAI_MATCHSTATE_MINOR_MATCH,				// ������ 
	BUDOKAI_MATCHSTATE_WAIT_MAJORMATCH_32,
	BUDOKAI_MATCHSTATE_MAJORMATCH_32,
	BUDOKAI_MATCHSTATE_WAIT_MAJORMATCH_16,
	BUDOKAI_MATCHSTATE_MAJORMATCH_16,
	BUDOKAI_MATCHSTATE_WAIT_MAJORMATCH_08,
	BUDOKAI_MATCHSTATE_MAJORMATCH_08,
	BUDOKAI_MATCHSTATE_WAIT_SEMIFINAL_MATCH,	// �ذ�� ���
	BUDOKAI_MATCHSTATE_SEMIFINAL_MATCH,			// �ذ��
	BUDOKAI_MATCHSTATE_WAIT_FINAL_MATCH,		// ��� ��� : ������� ����
	BUDOKAI_MATCHSTATE_FINAL_MATCH,				// ���
	BUDOKAI_MATCHSTATE_MATCH_END,				// ��. �����ð�

	MAX_BUDOKAI_MATCHSTATE,
	INVALID_BUDOKAI_MATCHSTATE = 0xff,
};


// player �� ���� ����
enum eBUDOKAI_JOIN_STATE
{
	BUDOKAI_JOIN_STATE_PLAY = 0,		// ������ - DB�� ���߾��� �ʱⰪ�̹Ƿ� ����Ǿ�� �ȵȴ�.
	BUDOKAI_JOIN_STATE_DROPOUT,			// Ż���� - DB�� ���߾��� ���̹Ƿ� ����Ǿ�� �ȵȴ�.

	INVALID_BUDOKAI_JOIN_STATE = 0xff,	// ���� ����
};


// player �� ���� ���
enum eBUDOKAI_JOIN_RESULT
{
	BUDOKAI_JOIN_RESULT_REGISTER = 0,	// ����� - DB�� ���߾��� �ʱⰪ�̹Ƿ� ����Ǿ�� �ȵȴ�.
	BUDOKAI_JOIN_RESULT_MINORMATCH,		// �������� - DB�� ���߾��� ���̹Ƿ� ����Ǿ�� �ȵȴ�.
	BUDOKAI_JOIN_RESULT_ENTER_32,
	BUDOKAI_JOIN_RESULT_ENTER_16,
	BUDOKAI_JOIN_RESULT_ENTER_8,
	BUDOKAI_JOIN_RESULT_ENTER_4,
	BUDOKAI_JOIN_RESULT_ENTER_2,
	BUDOKAI_JOIN_RESULT_WINNER,

	INVALID_BUDOKAI_JOIN_RESULT = 0xff
};


enum eBUDOKAI_MATCH_DEPTH
{
	BUDOKAI_MATCH_DEPTH_2 = 0,	// 1	2^0
	BUDOKAI_MATCH_DEPTH_4,		// 2	2^1
	BUDOKAI_MATCH_DEPTH_8,		// 4	2^2
	BUDOKAI_MATCH_DEPTH_16,		// 8	2^3
	BUDOKAI_MATCH_DEPTH_32,		// 16	2^4

	BUDOKAI_MATCH_DEPTH_COUNT,
	MAX_BUDOKAI_MATCH_DEPTH_INDIVIDUAL = BUDOKAI_MATCH_DEPTH_32,
	MAX_BUDOKAI_MATCH_DEPTH_TEAM = BUDOKAI_MATCH_DEPTH_16,
	INVALID_BUDOKAI_MATCH_DEPTH = 0xff,
};


//--------------------------
// ��� Condition

enum eBUDOKAI_PROGRESS_MESSAGE
{
	BUDOKAI_PROGRESS_MESSAGE_START = 0,					// õ�����Ϲ���ȸ�� ���۵˴ϴ�. �ҽ���....

	// ����
	BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_ENTERING,		// ���� ���� �����մϴ�. ������ ������....
	BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_BEFORE_1MIN,	// �� ���� ������ ���۵˴ϴ�. ������ ��...
	BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_WINNER,			// OOO���� ... 32�� ������ Ȯ�� �Ǽ̽�....
	BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_LOSER,			// OOO���� ... ��Ÿ���Ե� 32���� ������...
	BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_ALL_FINISHED,	// ������ ��� ����Ǿ����ϴ�. ���� ��....

	// ����
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_32_BEFORE_10SEC,		// 10�� �� 32�� ��������� �ڵ� �����մϴ�.
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_32_WINNER,			// OOO���� 32��.... �����մϴ�. 16��������.
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_32_LOSER,			// OOO���� 32��.... ��Ÿ���Ե�, 16���� ��..
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_32_ALL_FINISHED,		// 32���� ��� ����.... 16�� �����ڰ� ��...

	BUDOKAI_PROGRESS_MESSAGE_DEPTH_16_BEFORE_10SEC,		// 10�� �� 16�� ��������� �ڵ� �����մϴ�.
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_16_WINNER,			// OOO���� 16��.... �����մϴ�. 16��������.
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_16_LOSER,			// OOO���� 16��.... ��Ÿ���Ե�, 16���� ��..
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_16_ALL_FINISHED,		// 16���� ��� ����.... 8�� �����ڰ� ��...

	BUDOKAI_PROGRESS_MESSAGE_DEPTH_08_BEFORE_10SEC,		// 10�� �� 8�� ��������� �ڵ� �����մϴ�.
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_08_WINNER,			// OOO���� 8��.... �����մϴ�. 8��������.
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_08_LOSER,			// OOO���� 8��.... ��Ÿ���Ե�, 8���� ��..
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_08_ALL_FINISHED,		// 8���� ��� ����... �ذ�� �����ڰ� ��...

	//
	BUDOKAI_PROGRESS_MESSAGE_SEMI_FINAL_BEFORE_10SEC,
	BUDOkAI_PROGRESS_MESSAGE_SEMI_FINAL_RUNNING,
	BUDOkAI_PROGRESS_MESSAGE_FINAL_WAIT_LOSER,

	BUDOkAI_PROGRESS_MESSAGE_END,

	INVALID_BUDOKAI_PROGRESS_MESSAGE = 0xff,
};


//------------------------------------------------------------------------------------
// define

//-----------------------------------------------
// [8/4/2008 SGpro]
#define INVALID_MUDOSAPOINT INVALID_DWORD 

#define MAX_MUDOSA_POINT				(500000)

#define BUDOKAI_SERVER_INDEX			0


#define BUDOKAI_MAX_NOTICE_LENGTH		255


// Game <-> Query ���̿��� �� ��Ŷ�� �� �� �ִ� �ִ� ����
#define BUDOKAI_MAX_INDIVIDUAL_DB_DATA_PACKET_COUNT	20
#define BUDOKAI_MAX_TEAM_DB_DATA_PACKET_COUNT		(int)(BUDOKAI_MAX_INDIVIDUAL_DB_DATA_PACKET_COUNT / NTL_MAX_MEMBER_IN_PARTY)


// �������� ����
#define	BUDOKAI_MAX_TOURNAMENT_INDIVIDUAL_ENTRY_PACKET_COUNT	(NTL_MAX_MEMBER_IN_PARTY * 4)
#define	BUDOKAI_MAX_TOURNAMENT_TEAM_ENTRY_PACKET_COUNT			4



//-----------------------------------------------
// Rule define

// �ִ� ������ ��û �ο� �� �� �ο�
#define BUDOKAI_MAX_INDIVIDUAL_REGISTER_COUNT		10000
#define BUDOKAI_MAX_TEAM_REGISTER_COUNT				2000

// �ּ�, �ִ� �� �ο�
#define BUDOKAI_MIN_TEAM_MEMBER_COUNT	1
#define BUDOKAI_MAX_TEAM_MEMBER_COUNT	NTL_MAX_MEMBER_IN_PARTY;

// ������ ����, ���� ??��
#define	BUDOKAI_MAX_INDIVIDUAL_MATCH_COUNT			32
#define	BUDOKAI_MAX_TEAM_MATCH_COUNT				16

#if BUDOKAI_MAX_INDIVIDUAL_MATCH_COUNT > BUDOKAI_MAX_TEAM_MATCH_COUNT
#define BUDOKAI_MAX_MATCH_COUNT		BUDOKAI_MAX_INDIVIDUAL_MATCH_COUNT
#else
#define BUDOKAI_MAX_MATCH_COUNT		BUDOKAI_MAX_TEAM_MATCH_COUNT
#endif


// ���� ���� �ο� �� ��
#define BUDOKAI_MINOR_MATCH_INDIVIDUAL_COUNT		15
#define BUDOKAI_MINOR_MATCH_TEAM_COUNT				5

#if BUDOKAI_MINOR_MATCH_INDIVIDUAL_COUNT > BUDOKAI_MINOR_MATCH_TEAM_COUNT
#define BUDOKAI_MAX_MINORMATCH_TEAM_COUNT		BUDOKAI_MINOR_MATCH_INDIVIDUAL_COUNT
#else
#define BUDOKAI_MAX_MINORMATCH_TEAM_COUNT		BUDOKAI_MINOR_MATCH_TEAM_COUNT
#endif


// �� ���� ���� �ο�
#define BUDOKAI_MINOR_MATCH_MAX_INDIVIDUAL_COUNT	(BUDOKAI_MINOR_MATCH_INDIVIDUAL_COUNT * BUDOKAI_MAX_INDIVIDUAL_MATCH_COUNT)
#define BUDOKAI_MINOR_MATCH_MAX_TEAM_COUNT			(BUDOKAI_MINOR_MATCH_TEAM_COUNT * BUDOKAI_MAX_TEAM_MATCH_COUNT)
#define BUDOKAI_MINOR_MATCH_MAX_TEAM_MEMBER_COUNT	(BUDOKAI_MINOR_MATCH_MAX_TEAM_COUNT * NTL_MAX_MEMBER_IN_PARTY)


// ������ ���� ���� �ο� : ������ ��� QG_BUDOKAI_INDIVIDUAL_LIST_RES ��Ŷ�� ũ�Ⱑ �Ѿ�� �ʴ��� üũ�Ѵ�.
#define BUDOKAI_MAJOR_MATCH_PLAYER_NUMBER			(BUDOKAI_MAX_INDIVIDUAL_MATCH_COUNT)


// ���� ���� ���� �ο� : ������ ��� QG_BUDOKAI_TEAM_LIST_RES ��Ŷ�� ũ�Ⱑ �Ѿ�� �ʴ��� üũ�Ѵ�.
#define BUDOKAI_MAJOR_MATCH_TEAM_NUMBER				(BUDOKAI_MAX_TEAM_MATCH_COUNT)


// ������ �ڵ� ��Ȱ �ð�(��)
#define BUDOKAI_MINORMATCH_RESCUE_TIME				10

// ������ STAGE SELECTION state �ð�
#define BUDOKAI_MINORMATCH_SELECTION_STATE_TIME		20

// Stage Selection ���� ������ Random Number�� ũ��
#define BUDOKAI_MINORMATCH_SELECTION_NUMBER			100


//-----------------------------------------------
// Mudosa

// ������ ���� �ִ� ����
#define BUDOKAI_MAX_MUDOSA_INFO_COUNT				5

// ������ �ִ� ���� �ο�
#define BUDOKAI_MAX_MUDOSA_PLAYER_COUNT				200

// ������ �ִ� �̸� ���� : DBO_MAX_LENGTH_WORLD_NAME_IN_UNICODE/
#define BUDOKAI_MAX_MUDOSA_NAME_IN_UNICODE			32




// �ִ� ��ʸ�Ʈ ������ ���� Ƚ��
#define BUDOKAI_MAX_TOURNAMENT_INDIVIDUAL_MATCH_COUNT	(BUDOKAI_MAJOR_MATCH_PLAYER_NUMBER - 1)

// �ִ� ��ʸ�Ʈ �� ���� Ƚ��
#define BUDOKAI_MAX_TOURNAMENT_TEAM_MATCH_COUNT			(BUDOKAI_MAJOR_MATCH_TEAM_NUMBER - 1)


// FinalMatch Max Team Count
#define BUDOKAI_MAX_FINALMATCH_TEAM_COUNT			4



// DB ���� ����
// ��ʸ�Ʈ ������ ��� �ִ� ���ڵ� ī��Ʈ
#define BUDOKAI_MAX_TOURNAMENT_INDIVIDUAL_MATCH_RECORD_COUNT	(BUDOKAI_MAJOR_MATCH_PLAYER_NUMBER * 2)
// ��ʸ�Ʈ ���� ��� �ִ� ���ڵ� ī��Ʈ
#define BUDOKAI_MAX_TOURNAMENT_TEAM_MATCH_RECORD_COUNT			(BUDOKAI_MAJOR_MATCH_TEAM_NUMBER * 2)



//------------------------------------------------------------------------------------
// history ����

// ������ �Ի��� ī��Ʈ : �ἱ 4��
#define	BUDOKAI_MAX_SEASON_HISTORY_INDIVIAUL_WINNER_COUNT		(4)
// ���� �Ի��� ī��Ʈ : �ἱ 4���� 20��
#define	BUDOKAI_MAX_SEASON_HISTORY_TEAM_WINNER_COUNT			(NTL_MAX_MEMBER_IN_PARTY * 4)

// ������ �� ���� �Ի��� ī��Ʈ
#define	BUDOKAI_MAX_SEASON_HISTORY_WINNER_PLAYER_COUNT			(BUDOKAI_MAX_SEASON_HISTORY_INDIVIAUL_WINNER_COUNT + BUDOKAI_MAX_SEASON_HISTORY_TEAM_WINNER_COUNT)


// join state�� ������ ����Ŷ�� ������ �ִ� �ִ� ����
const BYTE BUDOkAI_MAX_PLAYER_JOIN_STATE_DATA_COUNT = 100;


//------------------------------------------------------------------------------------


#pragma pack(1)


// ���� ���� : DB �����
struct sBUDOKAI_STATE_DATA
{
	BYTE		byState;		// eBUDOKAI_STATE or eBUDOKAI_MATCHSTATE
	BUDOKAITIME	tmNextStepTime;
};

#define sBUDOKAI_MATCHSTATE_DATA sBUDOKAI_STATE_DATA	


struct sBUDOKAI_UPDATEDB_INITIALIZE
{
	WORD						wSeasonCount;				// ��ȸ�� õ������ ����ȸ ����?
	BUDOKAITIME					tmDefaultOpenTime;			// �⺻ ���۽ð�

	bool						bRankPointInitialized;

	sBUDOKAI_STATE_DATA			sStateData;
	sBUDOKAI_MATCHSTATE_DATA	sIndividualStateData;
	sBUDOKAI_MATCHSTATE_DATA	sTeamStateData;
};

//-----------------------------------------------------------------------------------


// ���� ���� : ���
struct sBUDOKAI_STATE_INFO
{
	eBUDOKAI_STATE	eState;		// eBUDOKAI_STATE
	BUDOKAITIME		tmNextStepTime;
//	BUDOKAITIME		tmRemainTime;
};


//
struct sBUDOKAI_MATCHSTATE_INFO
{
	eBUDOKAI_MATCHSTATE	eState;		// eBUDOKAI_MATCHSTATE
	BUDOKAITIME			tmNextStepTime;
//	BUDOKAITIME			tmRemainTime;
};


//---------------------------------------------------------------------------------------

// õ�����Ϲ���ȸ�� ��û�� player�� ���� ��������
struct sBUDOKAI_PLAYER_DATA
{
//	sBUDOKAI_PLAYER_DATA() : charId(INVALID_CHARACTERID), byClass(INVALID_BYTE), byLevel(INVALID_BYTE), fPoint(0)
//	{
//		memset( wszName, 0x00, sizeof(wszName));
//	}

	CHARACTERID	charId;
	BYTE		byClass;
	BYTE		byLevel;
	float		fPoint;
	WCHAR		wszName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
};



//---------------------------------------------------------------------------------------
// ���� ������ ����Ʈ

//
struct sBUDOKAI_REGISTER_DATA
{
	JOINID			wJoinId;
	WORD			wRanking;
	BYTE			byMinorMatch_MatchIndex;
	float			fPoint;
};

// DB�� ���� Data : ������ ��� QG_BUDOKAI_INDIVIDUAL_LIST_DATA ��Ŷ�� ũ�Ⱑ �Ѿ�� �ʴ��� Ȯ���Ѵ�.
struct sBUDOKAI_REGISTER_INDIVIDUAL_DATA : public sBUDOKAI_REGISTER_DATA
{
	CHARACTERID		charId;
	bool			bDojoRecommender;
};

// DB�� ���� Data : ������ ��� QG_BUDOKAI_TEAM_LIST_RES ��Ŷ�� ũ�Ⱑ �Ѿ�� �ʴ��� üũ�Ѵ�.
struct sBUDOKAI_REGISTER_TEAM_DATA : public sBUDOKAI_REGISTER_DATA
{
	WCHAR					wszTeamName[NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
	CHARACTERID				aMembers[NTL_MAX_MEMBER_IN_PARTY];
};


//---------------------------------------------------------------------------------------
// ���� ������ ����Ʈ

struct sBUDOKAI_TOURNAMENT_ENTRY_DATA
{
	JOINID			wJoinId;
	BYTE			byMinorMatch_MatchIndex;
};


struct sBUDOKAI_TOURNAMENT_INDIVIDUAL_ENTRY_DATA : public sBUDOKAI_TOURNAMENT_ENTRY_DATA
{
	CHARACTERID		charId;
	WCHAR			wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE			byClass;
	BYTE			byLevel;
	float			fRankPoint;
	bool			bDojoRecommender;
	WORD			wRankBattleWinCount;
	WORD			wRankBattleDrawCount;
	WORD			wRankBattleLoseCount;
	WCHAR			wszGuildName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];
};


struct sBUDOKAI_TOURNAMENT_TEAM_ENTRY_MEMBER_DATA
{
	CHARACTERID		charId;
	WCHAR			wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE			byClass;
	BYTE			byLevel;
	float			fRankPoint;
};

struct sBUDOKAI_TOURNAMENT_TEAM_ENTRY_DATA : public sBUDOKAI_TOURNAMENT_ENTRY_DATA
{
	WCHAR			wszTeamName[NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
	BYTE			byMemberCount;
	sBUDOKAI_TOURNAMENT_TEAM_ENTRY_MEMBER_DATA	aMembers[NTL_MAX_MEMBER_IN_PARTY];
};


// variable data ----

struct sBUDOKAI_TOURNAMENT_INDIVIDUAL_ENTRY_DATA_VAR : sBUDOKAI_TOURNAMENT_ENTRY_DATA
{
	CHARACTERID		charId;
	WORD			wCharName;				//WCHAR			wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE			byClass;
	BYTE			byLevel;
	float			fRankPoint;
	bool			bDojoRecommender;		// ���� ��õ��
	WORD			wRankBattleWinCount;
	WORD			wRankBattleDrawCount;
	WORD			wRankBattleLoseCount;
	WORD			wGuildName;				//WCHAR			wszGuildName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];
};


struct sBUDOKAI_TOURNAMENT_TEAM_ENTRY_MEMBER_DATA_VAR
{
	CHARACTERID		charId;
	WORD			wCharName;				//WCHAR			wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE			byClass;
	BYTE			byLevel;
	float			fRankPoint;
};

struct sBUDOKAI_TOURNAMENT_TEAM_ENTRY_DATA_VAR : public sBUDOKAI_TOURNAMENT_ENTRY_DATA
{
	WORD			wTeamName;				//WCHAR			wszTeamName[NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
	BYTE			byMemberCount;
	WORD			wMembers;				//sBUDOKAI_TOURNAMENT_TEAM_ENTRY_MEMBER_DATA	aMembers[NTL_MAX_MEMBER_IN_PARTY];
};


//---------------------------------------------------------------------------------------
// Game Server <-> Client



// �� ��û�Ҷ� ��û ���� ���� ��û(��õ ���� ������ ����ϱ� ����)
struct sBUDOKAI_TEAM_POINT_INFO
{
	BYTE		byClass;
	WCHAR		wszName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE		byLevel;
	float		fPoint;
};


//
struct sBUDOKAI_REGISTER_INDIVIDUAL_INFO
{
	bool			bDojoRecommender;	// ������õ������
	JOINID			wJoinId;
	WCHAR			wszCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
};


//
struct sBUDOKAI_REGISTER_TEAM_INFO
{
	JOINID			wJoinId;
	WCHAR			wszTeamName[NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];

	sBUDOKAI_TEAM_POINT_INFO	aMemberInfo[NTL_MAX_MEMBER_IN_PARTY];
};


// ���ӽ� Ŭ���̾�Ʈ���� �����ִ� ���� ����
struct sBUDOKAI_JOIN_INFO
{
	BYTE					byMatchType;		// eBUDOKAI_MATCH_TYPE
	BYTE					byJoinState;		// ���� ����
	BYTE					byJoinResult;		// ���� ���

	union
	{
		sBUDOKAI_REGISTER_INDIVIDUAL_INFO	sIndividualInfo;
		sBUDOKAI_REGISTER_TEAM_INFO			sTeamInfo;
	};
};



//-----------------------
// ���� ������ ����Ʈ


struct sBUDOKAI_TOURNAMENT_ENTRY_TEAM_INFO
{
	JOINID	wJoinId;
	bool	bDojoRecommender;
	WCHAR	wszTeamName[NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
};


struct sBUDOKAI_TOURNAMENT_ENTRY_TEAM_INFO_VAR
{
	JOINID	wJoinId;
	bool	bDojoRecommender;
	WORD	wTeamName;		// WCHAR	wszTeamName[NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
};



//-----------------------

struct sBUDOKAI_TOURNAMENT_MATCH_DATA
{
	BYTE	byDepth;
	BYTE	byMatchNumber;
	BYTE	byMatchResult;		// eMATCH_RESULT
	JOINID	wWinnerTeam;		// Winner Team
	JOINID	wJoinId1;
	JOINID	wJoinId2;
	BYTE	byScore1;
	BYTE	byScore2;
};


//---------------------------------------------------------------------------------------
struct sBUDOKAI_UPDATE_STATE_INFO
{
	BYTE			byState;		// eBUDOKAI_STATE
	BUDOKAITIME		tmNextStepTime;
	BUDOKAITIME		tmRemainTime;
	WORD			wSeasonCount;
};

struct sBUDOKAI_UPDATE_MATCH_STATE_INFO
{
	BYTE			byState;		// eBUDOKAI_MATCHSTATE
	BUDOKAITIME		tmNextStepTime;
	BUDOKAITIME		tmRemainTime;
};


//---------------------------------------------------------------------------------------

struct sBUDOKAI_MUDOSA_INFO
{
	WCHAR			wszMudosaName[BUDOKAI_MAX_MUDOSA_NAME_IN_UNICODE + 1];
	WORD			wCurrentUserCount;
};


// õ�����Ϲ���ȸ ���� ���� ������� ����
struct sBUDOKAI_PREV_SEASON_PLAYER_INFO
{
	BYTE			byMatchType;		// eBUDOKAI_MATCH_TYPE
	CHARACTERID		charId;
	WCHAR			wszName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE			byClass;
	BYTE			byLevel;
	BYTE			byJoinResult;		// eBUDOKAI_JOIN_RESULT
};


//---------------------------------------------------------------------------------------
// õ�����Ϲ���ȸ ������ �Ϲ� ������ �˷��ִ� ������ ������ ����

// ���� ������ �ڷ���Ʈ ����
struct sMINORMATCH_TELEPORT_INDIVIDUAL_DATA
{
	WORLDID		worldId;
	TBLIDX		worldTblidx;
	BYTE		byPlayerCount;
	CHARACTERID	aPlayers[BUDOKAI_MINOR_MATCH_INDIVIDUAL_COUNT];
};


// ���� ���� �ڷ���Ʈ ����
struct sMINORMATCH_TELEPORT_TEAM_MEMBER_LIST
{
	BYTE		byCount;
	CHARACTERID	charId[NTL_MAX_MEMBER_IN_PARTY];
};

struct sMINORMATCH_TELEPORT_TEAM_DATA
{
	WORLDID									worldId;
	TBLIDX									worldTblidx;
	BYTE									byTeamCount;
	sMINORMATCH_TELEPORT_TEAM_MEMBER_LIST	aTeamList[BUDOKAI_MINOR_MATCH_TEAM_COUNT];
};



enum eBUDOKAI_GM_MATCH_PROGRESS_STATE
{
	BUDOKAI_GM_MATCH_PROGRESS_STATE_READY,		// �غ��� default
	BUDOKAI_GM_MATCH_PROGRESS_STATE_RUN,		// ������
	BUDOKAI_GM_MATCH_PROGRESS_STATE_FINISHED,	// �Ϸ�
};


// GM ���� ���
struct sBUDOKAI_GM_MATCH_PROGRESS_STATE
{
	BYTE		byMatchIndex;
	BYTE		byProgressState;		// eBUDOKAI_GM_MATCH_PROGRESS_STATE

	BYTE		byMatchResult;			// eMATCH_RESULT
	TEAMTYPE	winnerTeamType;			// eMATCH_TEAM_TYPE

	// Team1
	WCHAR		wszTeamName1[NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
	BYTE		byScore1;

	// Team2
	WCHAR		wszTeamName2[NTL_MAX_LENGTH_BUDOKAI_TEAM_NAME_IN_UNICODE + 1];
	BYTE		byScore2;
};


// ������ ������ ��÷ ���� ������
struct sMINORMATCH_SELECTION_DATA
{
	TEAMTYPE	teamType;
	BYTE		byNumber;
};


struct sBUDOKAI_JOIN_STATE_DATA
{
	CHARACTERID				charId;
	JOINID					joinId;
	BYTE					byJoinState;	// eBUDOKAI_JOIN_STATE
	BYTE					byJoinResult;	// eBUDOKAI_JOIN_RESULT
};

#pragma pack()

