//***********************************************************************************
//
//	File		:	NtlTimeQuest.h
//
//	Begin		:	2007-05-31
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	
//
//***********************************************************************************

#pragma once

#include "NtlParty.h"
#include "NtlTSCoreDefine.h"

#include "NtlBitFlag.h"


//-----------------------------------------------------------------------------------
// Enumeration
//-----------------------------------------------------------------------------------

// Ÿ�Ӹӽ� Ÿ��
enum eTIMEQUEST_TYPE
{
	TIMEQUEST_TYPE_TUTORIAL, // Ʃ�丮�� Ÿ�� ����Ʈ ( ������ �������� �ʴ´� )
	TIMEQUEST_TYPE_PARTY, // ��Ƽ�� Ÿ�� ����Ʈ
	TIMEQUEST_TYPE_GROUP, // �׷��� Ÿ�� ����Ʈ

	MAX_TIMEQUEST_TYPE,
};


// Ÿ�Ӹӽ� ���
enum eTIMEQUEST_MODE
{
	TIMEQUEST_MODE_INDIVIDUAL, // ���ε���� ���
	TIMEQUEST_MODE_PARTY, // ��Ƽ����� ���

	MAX_TIMEQUEST_MODE,
	INVALID_TIMEQUEST_MODE = 0xFF, // ���� ����� �ȵǾ��� ���
};


// Ÿ�Ӹӽ� ���
enum eTIMEQUEST_ROOM_STATE
{
	TIMEQUEST_ROOM_STATE_REGISTRAITION,		// ���
	TIMEQUEST_ROOM_STATE_WAITENTRY,			// ���� ���
	TIMEQUEST_ROOM_STATE_PC_DIRECTION,		// PC ���� ����
	TIMEQUEST_ROOM_STATE_DAYRECORD_REQ,		// Query�� DayRecord�� ��û
	TIMEQUEST_ROOM_STATE_OBJECT_DIRECTION,	// OBJECT ���� ����
	TIMEQUEST_ROOM_STATE_PREPARE_WORLD,		// WorldPool ���� World�� �����Ѵ�.

	MAX_TIMEQUEST_ROOM_STATE,
	INVALID_TIMEQUEST_ROOM_STATE = 0xFF, 
};


// Ÿ�Ӹӽ� ���� ����
enum eTIMEQUEST_GAME_STATE
{
	TIMEQUEST_GAME_STATE_WAIT, // TMQ �����ϰ� �÷��̾� ���� ���
	TIMEQUEST_GAME_STATE_PREPARE, // ��� �÷��̾� ������ ����� üũ �� ���� ���� ����
	TIMEQUEST_GAME_STATE_ARRIVE, // TMQ ���� ���� ( TS������ �̺�Ʈ ���, ���� ��Ÿ���� �ð� �̺�Ʈ ��� )
	TIMEQUEST_GAME_STATE_BEGIN, // ���� ���� ( ��ũ��Ʈ ���� )
	TIMEQUEST_GAME_STATE_STAGE_READY, // �������� �غ� ( ��ũ��Ʈ ���� )
	TIMEQUEST_GAME_STATE_STAGE_START, // �������� ���� ( ��ũ��Ʈ ���� )
	TIMEQUEST_GAME_STATE_STAGE_FINISH, // �������� ���� ( ��ũ��Ʈ ���� )
	TIMEQUEST_GAME_STATE_END, // ���� ��
	TIMEQUEST_GAME_STATE_LEAVE, // TMQ ������ ����
	TIMEQUEST_GAME_STATE_FAIL, // ���� �� ( TMQ ���� )
	TIMEQUEST_GAME_STATE_CLOSE, // TMQ ����

	MAX_TIMEQUEST_GAME_STATE
};


// Ÿ�Ӹӽ� �������� ����
enum eTIMEQUEST_STAGE_STATE
{

	MAX_TIMEQUEST_STAGE_STATE
};


// Ÿ�Ӹӽ� ���̵�
enum eTIMEQUEST_DIFFICULTY
{
	TIMEQUEST_DIFFICULTY_EASY,
	TIMEQUEST_DIFFICULTY_NORMAL,
	TIMEQUEST_DIFFICULTY_HARD,

	MAX_TIMEQUEST_DIFFICULTY,
	FIRST_TIMEQUEST_DIFFICULTY = TIMEQUEST_DIFFICULTY_EASY,
	INVALID_TIMEQUEST_DIFFICULTY = 0xFF,
};


// Ÿ�Ӹӽ� ���̵� �÷���
enum eTIMEQUEST_DIFFICULTY_FLAG
{
	TIMEQUEST_DIFFICULTY_FLAG_EASY		= MAKE_BIT_FLAG( TIMEQUEST_DIFFICULTY_EASY ),
	TIMEQUEST_DIFFICULTY_FLAG_NORMAL	= MAKE_BIT_FLAG( TIMEQUEST_DIFFICULTY_NORMAL ),
	TIMEQUEST_DIFFICULTY_FLAG_HARD		= MAKE_BIT_FLAG( TIMEQUEST_DIFFICULTY_HARD ),
};


// Ÿ�Ӹӽ� ���� �޽��� Ÿ��
enum eTIMEQUEST_PROGRESS_MESSAGE_TYPE
{
	TIMEQUEST_PROGRESS_MESSAGE_TYPE_START,
	TIMEQUEST_PROGRESS_MESSAGE_TYPE_END,
	TIMEQUEST_PROGRESS_MESSAGE_TYPE_CLEAR,
	TIMEQUEST_PROGRESS_MESSAGE_TYPE_FAIL,

	MAX_TIMEQUEST_PROGRESS_MESSAGE_TYPE,
	INVALID_TIMEQUEST_PROGRESS_MESSAGE_TYPE = 0xFF,
};


// Ÿ������Ʈ ������� Ÿ��
enum eTIMEQUEST_INFORMATION_TYPE
{
	TIMEQUEST_INFORMATION_TYPE_SCENARIO,
	TIMEQUEST_INFORMATION_TYPE_STAGE,

	MAX_TIMEQUEST_INFORMATION_TYPE,
	INVALID_TIMEQUEST_INFORMATION_TYPE = 0xFF,
};


//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//	��� ����
//-----------------------------------------------------------------------------------
const DWORD		DBO_TIMEQUEST_MAX_ROOM_COUNT = 10; // Ÿ�Ӹӽ� �ʴ� ���� �ִ� ����

const DWORD		DBO_TIMEQUEST_MAX_MEMBER_COUNT = NTL_MAX_MEMBER_IN_PARTY; // Ÿ�Ӹӽ� �ִ� ��� �ο�

const DWORD		DBO_TIMEQUEST_ROOM_START_REPORT_TIME = 30000; // Ÿ�Ӹӽ� ��� �˸��� �����ִ� �ð�

const DWORD		DBO_TIMEQUEST_ROOM_LEAVE_LIMIT_TIME = 60000; // Ÿ�Ӹӽ� ���뿡�� ������ ���ϴ� �ð�

const DWORD		DBO_TIMEQUEST_MAX_STAGE_NUMBER = 64; // Ÿ�Ӹӽ� ����Ʈ�� �ִ� ��������

const DWORD		DBO_TIMEQUEST_MAX_KILL_COUNT = 3; // Ÿ�Ӹӽ� ����Ʈ�� �ִ� ųī��Ʈ (�Ѿ�� �ڵ� ����)

const DWORD		DBO_TIMEQUEST_ROOM_REFRESH_TIME = 10000; // Ÿ�Ӹӽ� ����Ʈ�� ������ �������� �ð�

const WORD		DBO_TIMEQUEST_COUNPON_CHANGE_POINT = 1000; // ���� 1������ ��ȯ�Ǵ� Ÿ������Ʈ ����Ʈ����

const WORD		DBO_TIMEQUEST_COUNPON_LIMIT_COUNT = 4; // ������ �ִ� �ִ� ���� ����

const WORD		DBO_TIMEQUEST_DEFAULT_DAYRECORD_RANK_COUNT = 5;	// tblidx�� ���̵� ���� ����� rank�� ����

const WORD		DBO_TIMEQUEST_DEFAULT_TOTAL_RANK_COUNT = DBO_TIMEQUEST_DEFAULT_DAYRECORD_RANK_COUNT + 1;	
													// tblidx�� ���̵� ���� ����� rank�� ���� �� BestRecord +
//-----------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#pragma pack( 1 )

// ���ο� ����
struct sTIMEQUEST_ROOM_MEMBER
{
	HOBJECT					handle;
	WCHAR					awchName[ NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1 ]; // ĳ���� �̸�
	BYTE					byClass; // �ش� ĳ���� Ŭ����
};


// �濡 �ִ� �ο� ����
struct sTIMEQUEST_ROOM_MEMBER_INFO
{
	BYTE byMemberCount;
	sTIMEQUEST_ROOM_MEMBER	asRoomMember[ DBO_TIMEQUEST_MAX_MEMBER_COUNT ];
};


// �濡 �ִ� ��Ƽ ����
struct sTIMEQUEST_ROOM_PARTY_INFO
{
	WCHAR					awchName[ NTL_MAX_SIZE_PARTY_NAME_IN_UNICODE + 1 ];
};


// ������
struct sTIMEQUEST_ROOM
{
	ROOMID					roomID; // �� ��ȣ
	TBLIDX					timeQuestTblidx; // �ش� Ÿ�� ����Ʈ ���̺� �ε���
	DWORD					dwRemainSec; // ��߽ð����� ���� �ð� (��)
	BYTE					byStartHour; // ���۽ð� (��)
	BYTE					byStartMin; // ���۽ð� (��)
	BYTE					byRoomMode; // eTIMEQUEST_MODE
	BYTE					byDifficulty; // eTIMEQUEST_DIFFICULTY
	BYTE					byRoomState; // eTIMEQUEST_ROOM_STATE	
};


// Ÿ�Ӹӽ� ����Ʈ ���� ����
struct sTIMEQUEST_STAGE
{
	BYTE					byStageNumber; // �������� ��ȣ
};


// Ÿ�Ӹӽ� ����Ʈ ���� ����
struct sTIMEQUEST_STATE
{
	BYTE					byGameState; // eTIMEQUEST_GAME_STATE
	sTIMEQUEST_STAGE		sTimeQuestStage;
};


// Ÿ������Ʈ ���� ����
struct sTIMEQUEST_RULE_INFO
{
	TBLIDX					timeQuestTblidx; // �ش� Ÿ�� ����Ʈ ���̺� �ε���
	BYTE					byStartHour; // ���۽ð� (��)
	BYTE					byStartMin; // ���۽ð� (��)
	BYTE					byTimeQuestMode; // eTIMEQUEST_MODE
	BYTE					byDifficulty; // eTIMEQUEST_DIFFICULTY
	bool					bCountDown; // ī��Ʈ �ٿ� ����
	DWORD					dwLimitTime; // ���� �ð�
	DWORD					dwBonusTime; // ���ʽ� �ð�
	DWORD					dwDayRecord; // �ش� Ÿ������Ʈ�� DayRecord

	sTIMEQUEST_STATE		sTimeQuestState;
};


// TMQ ���� ����ϴ� �ð� ���� ����
struct sTIMEQUEST_TIME
{
	// ���� ��� �ð��� ���
	void	NextTime(BYTE byTermMinute)
	{
		byHour = byHour + (BYTE)(byTermMinute / 60);
		byMinute += byTermMinute % 60;

		if( 60 <= byMinute)
		{
			byMinute -= 60;
			byHour++;
		}

		if(24 < byHour)
		{
			byHour -= 24;
		}
	}

	void	NextBySec(DWORD dwTermSec)
	{
		NextTime( (BYTE)(dwTermSec / 60));
	}

	BYTE	byHour;
	BYTE	byMinute;
};



//-----------------------------------------------------------------------------
// Protocol ������ ����Ѵ�

//-------------------------------------
// GU_TIMEQUEST_ROOM_LIST_RES ���� ���
struct sTIMEQUEST_ROOM_TMQ_INFO
{
	TBLIDX				tmqTblidx;				// tmq tblidx
	BYTE				byDifficult;			// ���̵� - eTIMEQUEST_DIFFICULTY
	sTIMEQUEST_TIME		sCurTime;				// ���� �ð�
	sTIMEQUEST_TIME		sNextEnterTime;			// ���� ��� �ð�
	WORD				wWaitPartyCount;		// ��������ǽ�û ��Ƽ ��
	WORD				wWaitIndividualCount;	// ��û PC ��
};


//-------------------------------------
// GU_TIMEQUEST_ROOM_JOIN_RES, GU_TIMEQUEST_ROOM_JOIN_NFY ���� ���
struct sTIMEQUEST_ROOM_JOIN_INFO
{
	TBLIDX					tmqTblidx;
	ROOMID					roomId;
	BYTE					byRoomState;			// eTIMEQUEST_ROOM_STATE
	BYTE					byTimeQuestMode;		// eTIMEQUEST_MODEz
	DWORD					dwRemainTime;			// [��÷|����]���� ���� �ð�
	BYTE					byDifficult;			// ���̵�
	WORD					wWaitPartyCount;		// ��û ��Ƽ ��
	WORD					wWaitIndividualCount;	// ��û PC ��
};


//-------------------------------------
// GU_TIMEQUEST_ROOM_INFO_RES ���� ���
// TMQ ��û �� ȭ�� ���� �ϴܿ� ������ TMQ Info Icon�� ������Ʈ �ϱ� ���� ����
struct sTIMEQUEST_ROOM_REGISTRATION_ICON_INFO
{
	WORD					wWaitPartyCount;		// ��û ��Ƽ ��
	WORD					wWaitIndividualCount;	// ��û PC ��
};

struct sTIMEQUEST_ROOM_WAITENTRY_ICON_INFO
{
	BYTE					bHaveItem;				// �������� ������ �ֳ�?
};

union uTIMEQUEST_ROOM_ICON_INFO
{
	sTIMEQUEST_ROOM_REGISTRATION_ICON_INFO	sRegistrationInfo;	// eTIMEQUEST_ROOM_STATE == TIMEQUEST_ROOM_STATE_REGISTRAITION
	sTIMEQUEST_ROOM_WAITENTRY_ICON_INFO		sWaitEntryInfo;		// eTIMEQUEST_ROOM_STATE == TIMEQUEST_ROOM_STATE_WAITENTRY
};



//-------------------------------------
// GU_TIMEQUEST_SELECTION_NFY ���� ���
struct sTIMEQUEST_ROOM_ENTRY_INFO
{
	DWORD					dwReaminEntryTime;		// ���Ա��� ���� �ð�
	bool					bHaveItem;				// �ʿ� �������� ������ �ִ°�?
};

struct sTIMEQUEST_ROOM_NEXT_TMQ_INFO
{
	TBLIDX					tmqTblidx;
	sTIMEQUEST_TIME			sNextTMQTime;			// ���� ���� �ð�
};

union uTIMEQUEST_ROOM_SELECTION_INFO
{
	sTIMEQUEST_ROOM_ENTRY_INFO		sEntryInfo;
	sTIMEQUEST_ROOM_NEXT_TMQ_INFO	sNextTmqInfo;
};




struct sTIMEQUEST_DAYRECORD_DATA
{
	BYTE		byDifficult;
	DWORD		dwClearTime;
	BYTE		byMemberCount;
	CHARACTERID	aMemberCharId[NTL_MAX_MEMBER_IN_PARTY];
};


//--------------------------------------------
// Query Server <-> Game Server
struct sTIMEQUEST_TEAM_DATA
{
	DWORD				dwClearTime;	// clear time
	BYTE				byMode;			// eTIMEQUEST_MODE
	WCHAR				wszPartyName[NTL_MAX_SIZE_PARTY_NAME_IN_UNICODE];
	BYTE				byMemberCount;
	WCHAR				awszMember[NTL_MAX_MEMBER_IN_PARTY][NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
};

struct sTIMEQUEST_MEMBER_DATA
{
	CHARACTERID			charId;
	WCHAR				wszName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
};

//------------------------------------------------------------------
struct sTIMEQUEST_PARTY_MEMBER_DATA
{
	BYTE				byLevel;
	BYTE				byClass;
	WCHAR				wszName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
};
	
struct sTIMEQUEST_TEAM_RANK_DATA
{
	DWORD				dwClearTime;	// clear time
	BYTE				byMode;			// eTIMEQUEST_MODE
	WCHAR				wszPartyName[NTL_MAX_SIZE_PARTY_NAME_IN_UNICODE];
};

struct sTIMEQUEST_TEAM_MEMBER_DATA
{
	BYTE							byMemberCount;
	sTIMEQUEST_PARTY_MEMBER_DATA	asMember[NTL_MAX_MEMBER_IN_PARTY];
};


//----------------------------------------------
// Game Server <-> Client

struct sTIMEQUEST_MEMBER_VAR
{
	WORD		wName;		// WCHAR[NTL_MAX_SIZE_CHAR_NAME_UNICODE]
	CHARACTERID	charId;
};

struct sTIMEQUEST_TEAM_VAR
{
	DWORD				dwClearTime;	// clear time
	WORD				wPartyName;		// WCHAR [NTL_MAX_SIZE_PARTY_NAME_IN_UNICODE];
	BYTE				byMemberCount;
	WORD				wMember;		// sTIMEQUEST_MEMBER [NTL_MAX_MEMBER_IN_PARTY];
};




//-----------------------------------------------------------------------------
//	index - data�� ��ġ
//	[ 1byte | .... ] [ 2byte | .... ] [ 2byte | .... ] [ 1byte | .... ]
//  [ size  | data ] [ size  | data ] [ size  | data ] [ size  | data ]
//  size : 1~2byte  ù��° byte�� ù��° bit�� ũ�Ⱑ 127�� �Ѿ������ üũ�ϴ� ��Ʈ

struct sVARIABLE_DATA
{
protected:
	WORD	wReserveSize;
	WORD	wOffset;			// ���ο� �����Ͱ� �� ��ġ���� �������� ũ���̴�
	BYTE	abyData[1];

public:
	sVARIABLE_DATA() : wOffset(0), wReserveSize(1){}						// �������ݿ����� ����ϵ��� �Ѵ�.
	sVARIABLE_DATA(WORD wReserve) : wOffset(0)
	{
		Init( wReserve );
	}

	void Init( WORD wReserve )
	{
		wOffset = 0;

		if( wReserve >= 4096/*PACKET_MAX_SIZE*/ )
		{
			_ASSERT(0);

			wReserveSize = 0;
			return;
		}

		wReserveSize = wReserve;

		::memset( abyData, 0xff, sizeof(BYTE) * wReserve );
	}


	// ��Ŷ ���� �ʱ�ȭ�� ���� �ϱ� ���� �Լ�(��Ŷ ��뿡 Ưȭ�� �Լ�)
	void InitPacketSize( WORD wDefaultPacketSize )
	{
		wOffset = 0;

		wReserveSize = 4096/*PACKET_MAX_SIZE*/ - wDefaultPacketSize + sizeof(BYTE);

		if( wReserveSize >= 4096/*PACKET_MAX_SIZE*/ )
		{
			_ASSERT(0);

			wReserveSize = 0;
			return;
		}

		::memset( abyData, 0xff, sizeof(BYTE) * wReserveSize );
	}


	// ��Ŷ ���� ��Ŷ�� ũ�⸦ ���� ����ϱ� ���� �Լ�.(��Ŷ ��뿡 Ưȭ�� �Լ�)
	WORD GetPacketSize( WORD wDefaultPacketSize ) { return wDefaultPacketSize - sizeof(BYTE) + GetDataSize(); }


	// sVARIABLE_DAT�� �� ũ�� : offset + sizeof(sVARIABLE_DATA) - abyData[1] ũ��
	WORD GetTotalSize() { return wOffset + sizeof(sVARIABLE_DATA) - sizeof(BYTE);}
	// Data�� ũ��
	WORD GetDataSize() { return wOffset;}

	// ���� ũ�⸦ ����(���� �޸��� ũ�⸦ ��ȯ��Ű���� �ʴ´�. �� ���� �����Ҷ� Ȥ�� ���� ���� �ܺο��� �˷��ش�.)
//	void SetReserveSize(WORD wReserve) { wReserveSize = wReserve; }
//	WORD GetReserveSize() { return wReserveSize;}

	void WriteLock() { wReserveSize = GetDataSize(); }


	// Data�� �����Ѵ�.
	void __SetData( WORD wOff, BYTE * pData)
	{
		wOffset = wOff;
		::memcpy( abyData, pData, wOff);
	}

	// pData : ������ ��ġ, wReserverSize : ���� ������ ���� ������ ũ��(���� ����)
	bool CopyTo( sVARIABLE_DATA * pData, WORD wReserve)
	{
		if(NULL == pData)
		{
			return false;
		}

		if(wReserve < GetDataSize())
		{
			return false;
		}

		pData->__SetData( wOffset, abyData);
		pData->WriteLock();

		return true;
	}


	//-----------------------------------------------------------------------------------
	//	Purpose	: 127 ���� ���� ���� 127 ���� ũ�ų� ���� ��츦 �и��Ͽ� ����
	//			  ũ���� ù��° bit�� data�� ũ�Ⱑ 127�� �Ѵ��� ���� �ʴ����� ǥ���Ѵ�
	//			  ��ü ũ��� 2�� 15���� ���� ���Ѵ�.
	//	Return	: 
	//-----------------------------------------------------------------------------------
	WORD Write( WORD wSize, void * pData)
	{
		WORD wTemp = wOffset;

		if( 127 >= wSize)	// ���̰� 127���� �۰ų� ���� ���
		{
			// ���� ������ ������� üũ
			if( wOffset + wSize + 1 > wReserveSize)
			{
				return INVALID_WORD;
			}


			// write
			abyData[wOffset] = (BYTE)wSize;
			::memcpy( &(abyData[wOffset + 1]), pData, wSize);

			// offset ����
			wOffset += wSize + 1;
		}
		else				// ���̰� 127���� ū ��� WORD ������ ũ�� ����
		{
			// ���� ������ ������� üũ
			if( wOffset + wSize + 2 > wReserveSize)
			{
				return INVALID_WORD;
			}

			// write
			abyData[wOffset] = (BYTE)((wSize % 0x80) | 0x80);	// ù��° byte
			abyData[wOffset+1] = (BYTE)(wSize >> 7);			// �ι�° byte

			::memcpy( &(abyData[wOffset + 2]), pData, wSize);

			// offset ����
			wOffset += wSize + 2;
		}

		return wTemp;
	}


	//-----------------------------------------------------------------------------------
	//	Purpose	: 127 ���� ���� ���� 127 ���� ũ�ų� ���� ��츦 �и��Ͽ� ����
	//			  ũ���� ù��° bit�� data�� ũ�Ⱑ 127�� �Ѵ��� ���� �ʴ����� ǥ���Ѵ�
	//			  ��ü ũ��� 2�� 15���� ���� ���Ѵ�.
	//	Return	: wSize ũ�⸸ŭ�� �޸𸮸� �Ҵ��ϰ� �ش� �������� ��ȯ�Ѵ�.
	//			  (�޸��Ҵ��� Write()�� ���������� �Ҵ��� �޸𸮿� ��� ���� ������ �ʴ´�.)
	//-----------------------------------------------------------------------------------
	WORD Malloc( WORD wSize)
	{
		WORD wTemp = wOffset;

		if( 127 >= wSize)	// ���̰� 127���� �۰ų� ���� ���
		{
			// ���� ������ ������� üũ
			if( wOffset + wSize + 1 > wReserveSize)
			{
				return INVALID_WORD;
			}


			// write
			abyData[wOffset] = (BYTE)wSize;

			// offset ����
			wOffset += wSize + 1;
		}
		else				// ���̰� 127���� ū ��� WORD ������ ũ�� ����
		{
			// ���� ������ ������� üũ
			if( wOffset + wSize + 2 > wReserveSize)
			{
				return INVALID_WORD;
			}

			// write
			abyData[wOffset] = (BYTE)((wSize % 0x80) | 0x80);	// ù��° byte
			abyData[wOffset+1] = (BYTE)(wSize >> 7);			// �ι�° byte

			// offset ����
			wOffset += wSize + 2;
		}

		return wTemp;
	}


	//-----------------------------------------------------------------------------------
	//	Purpose	: wReadLoc�� ��ġ�� Data�� ũ�⸦ ��ȯ
	//	Return	: 
	//-----------------------------------------------------------------------------------
	WORD GetSize( WORD wReadLoc)
	{
		if( wReadLoc >= wOffset)
		{
			return 0;
		}

		// ũ�Ⱑ 127�� �Ѵ� ���
		if( 0x80 & abyData[wReadLoc])
		{
			// ũ�Ⱑ ����� ��ġ�� ��ȿ���� üũ(2byte �� ����ϹǷ�)
			if(wReadLoc + 1 >= wOffset)
			{
				return 0;
			}

			// get size
			WORD wSize = (abyData[wReadLoc] & 0x7f) + (abyData[wReadLoc + 1] << 7);

			// ����� ũ��� ����� �������� ũ�Ⱑ ��ȿ���� üũ
			if(wReadLoc + wSize + 2 > wOffset)
			{
				return 0;
			}

			return wSize;
		}
		// ũ�Ⱑ 127�� ���� �ʴ� ���
		else								
		{
			// ����� ũ��� ����� �������� ũ�Ⱑ ��ȿ���� üũ
			if(wReadLoc + abyData[wReadLoc] + 1 > wOffset)
			{
				return 0;
			}

			return abyData[wReadLoc];
		}
	}


	//-----------------------------------------------------------------------------------
	//	Purpose	: wReadLoc�� ��ġ�� Data�� pData�� �����Ѵ�.
	//	Return	: 
	//-----------------------------------------------------------------------------------
	bool Read( WORD wReadLoc, void * pData)
	{
		// ũ�⸦ �����ϴ� ������ ��ȿ���� üũ
		if( wReadLoc >= wOffset)
		{
			return false;
		}

		// ũ�Ⱑ 127�� �Ѵ� ���
		if( 0x80 & abyData[wReadLoc])
		{
			// ũ�⸦ �����ϴ� ������ ��ȿ���� üũ(2byte �� ����ϹǷ�)
			if(wReadLoc + 1 >= wOffset)
			{
				return false;
			}

			// get size
			WORD wSize = (abyData[wReadLoc] & 0x7f) + (abyData[wReadLoc + 1] << 7);

			// �����͸� �����ϴ� ������ ��ȿ���� üũ
			if(wReadLoc + wSize + 2 > wOffset )
			{
				return false;
			}

			// copy
			::memcpy( pData, &(abyData[wReadLoc + 2]), wSize);
		}
		// ũ�Ⱑ 127�� ���� �ʴ� ���
		else
		{
			// �����͸� �����ϴ� ������ ��ȿ���� üũ
			if(wReadLoc + abyData[wReadLoc] + 1 > wOffset)
			{
				return false;
			}

			// copy
			::memcpy( pData, &(abyData[wReadLoc + 1]), abyData[wReadLoc]);
		}

		return true;
	}


	//-----------------------------------------------------------------------------------
	//	Purpose	: wReadLoc�� ��ġ�� Data�� ��ȯ�Ѵ�.
	//	Return	: 
	//-----------------------------------------------------------------------------------
	void * Read( WORD wReadLoc)
	{
		// ũ�⸦ �����ϴ� ������ ��ȿ���� üũ
		if( wReadLoc >= wOffset)
		{
			return NULL;
		}


		// ũ�Ⱑ 127�� �Ѵ� ���
		if( 0x80 & abyData[wReadLoc])
		{
			// ũ�⸦ �����ϴ� ������ ��ȿ���� üũ(2byte �� ����ϹǷ�)
			if(wReadLoc + 1 >= wOffset)
			{
				return NULL;
			}

			// get size
			WORD wSize = (abyData[wReadLoc] & 0x7f) + (abyData[wReadLoc + 1] << 7);

			// �����͸� �����ϴ� ������ ��ȿ������ üũ
			if(wReadLoc + wSize + 2 > wOffset)
			{
				return NULL;
			}

			return &(abyData[wReadLoc + 2]);
		}
		// ũ�Ⱑ 127�� ���� �ʴ� ���
		else
		{
			// �����͸� �����ϴ� ������ ��ȿ������ üũ
			if(wReadLoc + abyData[wReadLoc] + 1 > wOffset)
			{
				return NULL;
			}

			return &(abyData[wReadLoc + 1]);
		} // end if
	} // end void * Read() func
};


#pragma pack()



