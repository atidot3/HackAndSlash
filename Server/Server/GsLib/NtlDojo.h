//***********************************************************************************
//
//	File		:	NtlDojo.h
//
//	Begin		:	2009-01-07
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Chung,DooSup (mailto:john@ntl-inc.com)
//
//	Desc		:	
//
//***********************************************************************************

#pragma once

#include "SharedType.h"
#include "SharedDef.h"
#include "Guild.h"
#include "Vector.h"

#pragma pack(1)

const DWORD DBO_MAX_COUNT_DOJO_IN_WORLD = 7;
const DWORD DBO_MAX_COUNT_DOJO_BANK_HISTORY = 40;
const DWORD DBO_DOJO_SCRAMBLE_REQUEST_FARE = 1000000;		// ���� ��Ż�� ��û�ݾ� (���� ���� �Ҷ�)
const DWORD DBO_DOJO_SCRAMBLE_REJECT_FARE = 1000000;		// ���� ��Ż�� �źαݾ� (���� ���� �Ҷ�)
const DWORD DBO_DOJO_SCRAMBLE_REQUIRED_REPUTATION = 100000;

const DWORD DBO_DOJO_SCRAMBLE_MAX_WAIT_TICK = 10 * 60 * 1000; // �������� ��û�˸� �ִ���ð� 10 ��
const DWORD DBO_DOJO_SCRAMBLE_INIT_WAIT_SEC = 10; // ��Ż�� ������ ������� ���ư��µ� 10��

const DWORD DBO_DOJO_SCRAMBLE_MAX_MEMBER = 30; // ��Ż�� ���� ���� ���� �ִ� �ο�

/*const DWORD	DBO_DOJO_SCRAMBLE_CHANGE_SCRAMBLE_POINT = 1;	// seal ȹ��� ��Ż����
const DWORD	DBO_DOJO_SCRAMBLE_FULL_CHARGED_SCRAMBLE_POINT = 8;		// Ǯ������ ��Ż����
const DWORD	DBO_DOJO_SCRAMBLE_FULL_GOAL_SCRAMBLE_POINT = 100;		// ��Ż����GOAL
const DWORD	DBO_DOJO_SCRAMBLE_FULL_SEAL_POINT = 300;		// ����������Ʈ        
const DWORD	DBO_DOJO_SCRAMBLE_SEC_SEAL_POINT = 2;			// 1�ʴ� ����������Ʈ  */

const DWORD	DBO_DOJO_SCRAMBLE_BROADCAST_TERM = 5 * 1000;	// ��Ż�� ���� ��� �� 
const DWORD DBO_MAX_LEVEL_DOJO_IN_WORLD = 7;

enum eDOJO_STATE
{
	DOJO_STATE_CLOSE,
	DOJO_STATE_OPEN,
	DOJO_STATE_CLEAR,

	MAX_DOJO_STATE,
	INVALID_DOJO_STATE = 0xff,
};

//---------------------------------------------------------------------------------------
struct sDOJO_STATE_INFO
{
	eDOJO_STATE		eState;		// eDOJO_STATE
	DOJOTIME		tmNextStepTime;
	DOJOTIME		tmRemainTime;
};

enum eDBO_DOJO_STATUS
{
	eDBO_DOJO_STATUS_NORMAL = 0,		// ��Ż�� ���� ��� ���� (��Ż�� �̿� ����)
	eDBO_DOJO_STATUS_RECEIVE,			// ��Ż�� ��û ��� ���� (��û �������� BroadCast)
	eDBO_DOJO_STATUS_REJECT_END,		// ��Ż�� �ź� ���� ���� (�źΰ��ɽð� ������� )
	eDBO_DOJO_STATUS_STANDBY,			// ��Ż�� �غ� ���� ������忡 GUI ǥ�� (���ݹ������������� �˸��޼���) 
	eDBO_DOJO_STATUS_INITIAL,			// ��Ż�� ���� �ʱ�ȭ (���峻 ĳ�� �����Ա��� NPC���� ���峻 �̵��Ұ� �������)		
	eDBO_DOJO_STATUS_READY,				// ��Ż�� (���� ���� ���� ĳ���̵��Ұ� ��ų�������� )	
	eDBO_DOJO_STATUS_START,				// ��Ż�� ����~ ( ������ ���� ���� ȹ�� ���� )
	eDBO_DOJO_STATUS_END,				// ��Ż�� �Ϸ� (�������� ���ں���)
};	


struct sDOJO_MATCHSTATE_INFO
{
	eDBO_DOJO_STATUS	eState;		// eDBO_DOJO_STATUS
	DOJOTIME			tmNextStepTime;
	DOJOTIME			tmRemainTime;
};

struct sDBO_DOJO_DATA	
{
public:
	sDBO_DOJO_DATA()
	{
		guildId = INVALID_GUILDID;
		byLevel = 0;
		dojoTblidx = INVALID_TBLIDX;		
		byPeaceStatus = 0;	
		dwPeacePoint = 0;	
		memset( wszName,0x00, sizeof(wszName) );
		challengeGuildId = INVALID_GUILDID;		
		memset( wszSeedCharName,0x00, sizeof(wszSeedCharName) );
		memset( wchLeaderName,0x00, sizeof(wchLeaderName) );
		memset( wchNotice,0x00, sizeof(wchNotice) );
	}
	GUILDID			guildId;
	BYTE			byLevel;											// ���� ����
	TBLIDX			dojoTblidx;											// �ش� �������̺� �ε���
	BYTE			byPeaceStatus;										// ġ�Ȼ��� eDBO_DOJO_PEACE_TYPE
	DWORD			dwPeacePoint;										// ġ������Ʈ
	WCHAR			wszName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];	// ����
	GUILDID			challengeGuildId;									//	�������id
	WCHAR			wszSeedCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];		// �õ����ĳ����

	WCHAR			wchLeaderName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];	// ''	������
	WCHAR			wchNotice[NTL_MAX_LENGTH_OF_DOJO_NOTICE_UNICODE + 1];	//'' ����	
};
struct sDOJO_SCRAMBLE_POINT
{
	TBLIDX				dojoTblidx;
	BYTE				byDefCount;		// ��� �ο�
	BYTE				byAttCount;		// ���� �ο�	
	BYTE				byDefSealCount;	// ����� ����ȹ�氹��
	BYTE				byAttSealCount; // ���ݱ�� ����ȹ�氹��
	DWORD				dwDefPoint;	// Goal 100
	DWORD				dwAttPoint;	// Goal 100
	DWORD				dwDefCharge;	// 300 -> 8 Point
	DWORD				dwAttCharge;	// 300 -> 8 Point
	
};
struct sDBO_DOJO_BRIEF
{
	GUILDID			guildId;
	TBLIDX			dojoTblidx;
	BYTE			byLevel;
	sDBO_GUILD_MARK sMark;
};

enum eDBO_DOJO_PEACE_TYPE
{
	eDBO_DOJO_PEACE_TYPE_PANIC = 0,
	eDBO_DOJO_PEACE_TYPE_FEAR,
	eDBO_DOJO_PEACE_TYPE_COMMON,
	eDBO_DOJO_PEACE_TYPE_QUIET,
	eDBO_DOJO_PEACE_TYPE_FESTIVAL,
};	

struct sDBO_DOJO_BANK_HISTORY_DATA
{
	sDBO_TIME		sTime;
	BYTE			byType;			// eDBO_GUILD_ZENNY_UPDATE_TYPE
	DWORD			dwAmount;		
	bool			bIsSave;		//	0: withdraw 1:save
	DWORD			dwBalance;		// �ܾ�
};

struct sDBO_DOJO_BANK_HISTORY_INFO
{
	sDBO_TIME		sTime;
	BYTE			byType;			// eDBO_GUILD_ZENNY_UPDATE_TYPE
	DWORD			dwAmount;		
	bool			bIsSave;		//	0: withdraw 1:save
};

struct sDBO_DOJO_NPC_INFO
{
	TBLIDX				dojoTblidx;										// �����ε���
	WCHAR				wszName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];// �����̸�
	BYTE				byLevel;
	DWORD				dwGuildReputation;		// ����
	DWORD				dwMaxGuildPointEver;	// Load �׵��� dwGuildReputation ���� �ְ�
	BYTE				byPeaceStatus;	
	WCHAR				wszSeedCharName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];		// �õ����ĳ����
	WCHAR				wchLeaderName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];		// ���� ĳ����
	WCHAR				wchNotice[NTL_MAX_LENGTH_OF_DOJO_NOTICE_UNICODE + 1];
	WCHAR				wszChallengeName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];
	WCHAR				wszChallengeLeaderName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];			// ����������
};

struct sDBO_DOJO_TELEPORT_DATA
{
	BYTE								byTeleportType; 
	WORD								wWaitTime;
	WORLDID								destWorldId;
	TBLIDX								destWorldTblidx;
	CNtlVector							vDestDefLoc;
	CNtlVector							vDestAttLoc;
	SERVERCHANNELID						destServerChannelId;
	SERVERINDEX							destServerIndex;
};


//--------------------------
// ��� Condition

enum eDOJO_PROGRESS_MESSAGE
{
	DOJO_PROGRESS_MESSAGE_NORMAL,			// ��Ż�� ��û�� ����		
	DOJO_PROGRESS_MESSAGE_RECEIVE,			// ��Ż�� ��û ����
	DOJO_PROGRESS_MESSAGE_REJECT_END,		// ��Ż�� �ź� ���� 
	DOJO_PROGRESS_MESSAGE_STANDBY,			// ��Ż�� �غ� ���� ������忡 GUI ǥ�� (���ݹ������������� �˸��޼���) 
	DOJO_PROGRESS_MESSAGE_INITIAL,			// ��Ż�� ���� �ʱ�ȭ (���峻 ĳ�� �����Ա��� NPC���� ���峻 �̵��Ұ� �������)		
	DOJO_PROGRESS_MESSAGE_READY,			// ��Ż�� (���� ���� ���� ĳ���̵��Ұ� ��ų�������� )	
	DOJO_PROGRESS_MESSAGE_START,			// ��Ż�� ����~ ( ������ ���� ���� ȹ�� ���� )
	DOJO_PROGRESS_MESSAGE_END,				// ��Ż�� �Ϸ� (�������� ���ں���)

	INVALID_DOJO_PROGRESS_MESSAGE = 0xff,
};


enum eDBO_DOJO_REPEAT_TYPE
{
	eDBO_DOJO_REPEAT_TYPE_TIME = 0,
	eDBO_DOJO_REPEAT_TYPE_DAY,
	eDBO_DOJO_REPEAT_TYPE_WEEK,
};	

enum eDBO_DOJO_WEEK_BITFLAG
{
	eDBO_DOJO_WEEK_BITFLAG_MON = 0x01 << 0,
	eDBO_DOJO_WEEK_BITFLAG_TUE = 0x01 << 1,
	eDBO_DOJO_WEEK_BITFLAG_WED = 0x01 << 2,
	eDBO_DOJO_WEEK_BITFLAG_THU = 0x01 << 3,
	eDBO_DOJO_WEEK_BITFLAG_FRI = 0x01 << 4,
	eDBO_DOJO_WEEK_BITFLAG_SAT = 0x01 << 5,
	eDBO_DOJO_WEEK_BITFLAG_SUN = 0x01 << 6,
};

enum eDBO_DOJO_PC_TYPE
{
	eDBO_DOJO_PC_TYPE_OWNNER = 0,
	eDBO_DOJO_PC_TYPE_CHALLENGER,

	eDBO_DOJO_PC_TYPE_NONE = 0xff,
};	

enum eDBO_DOJO_REWARD_TYPE
{
	eDBO_DOJO_REWARD_TYPE_PERFECT_DEF = 0,		// ��� �ִ� ����Ʈ ȹ��
	eDBO_DOJO_REWARD_TYPE_WIN_DEF,				// ��� ����
	eDBO_DOJO_REWARD_TYPE_SAME_DEF,				// ��� ��������
	
	eDBO_DOJO_REWARD_TYPE_PERFECT_ATT,			// ���� �ִ� ����Ʈ ȹ��
	eDBO_DOJO_REWARD_TYPE_WIN_ATT,				// ���� ����

	eDBO_DOJO_REWARD_TYPE_NONE = 0xff,
};	

enum eDBO_DOJO_COMMAND_TYPE
{
	eDBO_DOJO_COMMAND_TYPE_CLEAR = 0,
	eDBO_DOJO_COMMAND_TYPE_START,
	eDBO_DOJO_COMMAND_TYPE_NEXT,
	eDBO_DOJO_COMMAND_TYPE_RESPONSE,

};	
#pragma pack()