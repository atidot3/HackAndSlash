#pragma once

#include "SharedType.h"
#include "TSCoreDefine.h"
#include "NtlBitFlag.h"


//===================================================================================
//	����Ʈ ���̵�
//===================================================================================

// ����Ʈ ���̵� ��� �뵵 ����
//	����) �Ʒ��� ���� �߰� �ʿ伺 �߻� �� �ݵ��
//		  ����Ʈ ����� ( lleo52@ntl-inc.com )���� ���� �ٶ�
enum eQUEST_ID_RANGE
{
	// General quest�� �Ϲ����� ����Ʈ�� �Ʒ��� ���� ���̵� ���ֳ����� ���Ǿ�� ��.
	// ���� Ȯ�� ��û�� Reserve quest range�� �̿��Ͽ� Ȯ���ϸ� ��.
	eQUEST_ID_RANGE_GENERAL_QUEST_MIN		= 0,
	eQUEST_ID_RANGE_GENERAL_QUEST_MAX		= 7000,
	eQUEST_ID_RANGE_GENERAL_QUEST_COUNT		= eQUEST_ID_RANGE_GENERAL_QUEST_MAX - eQUEST_ID_RANGE_GENERAL_QUEST_MIN,

	// Reserve quest�� ���� General quest�� Ȯ���� ��ȹ���� �䱸�� �� �ִٴ� �����Ͽ�
	// �Ʒ��� ���� ���� �� ����.
	eQUEST_ID_RANGE_RESERVE_QUEST_MIN		= 7000,
	eQUEST_ID_RANGE_RESERVE_QUEST_MAX		= 11000,
	eQUEST_ID_RANGE_RESERVE_QUEST_COUNT		= eQUEST_ID_RANGE_RESERVE_QUEST_MAX - eQUEST_ID_RANGE_RESERVE_QUEST_MIN,

	// Special quest�� Tutorial, TMQ �� ���� Ư�� �ý��ۿ��� ����ϴ� ����Ʈ ���̵�ν�
	// Ư�� �ý����� ���� �Ǵ� ������ �ڵ� �����Ǿ�� �ϴ� ����Ʈ�� ���ؼ� ����.
	eQUEST_ID_RANGE_SPECIAL_QUEST_MIN		= 11000,
	eQUEST_ID_RANGE_SPECIAL_QUEST_MAX		= 14000,
	eQUEST_ID_RANGE_SPECIAL_QUEST_COUNT		= eQUEST_ID_RANGE_SPECIAL_QUEST_MAX - eQUEST_ID_RANGE_SPECIAL_QUEST_MIN,

	eQUEST_ID_RANGE_QUEST_MAX				= 14000,
};


//===================================================================================
//	�Ϸ�� ����Ʈ ����
//===================================================================================

//	����Ʈ �Ϸ� ����
//	����) �Ʒ��� ���� �߰� �ʿ伺 �߻� �� �ݵ��
//		  ����Ʈ ����� ( lleo52@ntl-inc.com )���� ���� �ٶ�
enum eCOMPLETE_QUEST_STATE
{
	eCOMPLETE_QUEST_STATE_CLEAR				= 0x1,

	eCOMPLETE_QUEST_STATE_MAX				= 1
};

enum
{
	eCOMPLETE_QUEST_QUEST_PER_BYTE			= 8 / eCOMPLETE_QUEST_STATE_MAX
};

enum
{
	eCOMPLETE_QUEST_QUEST_PER_STRUCT		= 1000
};

enum
{
	eCOMPLETE_QUEST_QUEST_STRUCT_COUNT		= eQUEST_ID_RANGE_QUEST_MAX / eCOMPLETE_QUEST_QUEST_PER_STRUCT
};

#pragma pack( 1 )
struct sCOMPLETE_QUEST_INFO
{
	unsigned char							abyQCInfo[eQUEST_ID_RANGE_QUEST_MAX/eCOMPLETE_QUEST_QUEST_PER_BYTE];
};


struct sCOMPLETE_QUEST_BIT_INFO
{
	unsigned char							abyQCBitInfo[eCOMPLETE_QUEST_QUEST_PER_STRUCT/eCOMPLETE_QUEST_QUEST_PER_BYTE];//125
};

struct sCOMPLETE_QUEST_TOTAL_BIT_INFO
{
	sCOMPLETE_QUEST_BIT_INFO				asQCBitInfo[eCOMPLETE_QUEST_QUEST_STRUCT_COUNT];	//14 
};

#pragma pack()


//===================================================================================
//	���� ���� ����Ʈ ����
//===================================================================================

// ���� ������ �ִ� ����Ʈ ����
enum
{
	eMAX_CAN_PROGRESS_QUEST_NUM				= 20,

	eMAX_CAN_PROGRESS_GENERAL_QUEST_NUM		= 10,	// �Ϲ����� ����Ʈ
	eMAX_CAN_PROGRESS_SPECIAL_QUEST_NUM		= 10,	// TMQ, Tutorial... �� ����Ʈ
};

// ���� ������ �ִ� Ʈ���� ����
enum
{
	eMAX_CAN_PROGRESS_TRIGGER_NUM			= 20
};

// ���� ���� ����Ʈ�� ����
// ��) ���� ���¸� �����ϱ� ���� ������ 2 Byte�� ���� �Ǿ� ����.
//	   �Ʒ� ���� �߰��� 2Byte�� ���� �ʵ��� ���� �ʿ�.
enum eTS_SVR_STATE
{
	eTS_SVR_STATE_ERROR						= 0x0001,		// ���� ����
	eTS_SVR_STATE_FAILED					= 0x0002,		// ����Ʈ ���� ���� ����
	eTS_SVR_STATE_ESCORT					= 0x0004,		// ȣ�� ����
	eTS_SVR_STATE_SVR_EVT_WORLD_RANGE		= 0x0008,		// �����̺�Ʈ(��ų...)�� ���� ����� ���� ( �� �÷��װ� ���� ���� ������ ��Ƽ �������� ó���� )
	eTS_SVR_STATE_WPS_MODE					= 0x0010,		// World play script �׼��� ������
	eTS_SVR_STATE_USER_OUT_FAILED_WPS		= 0x0020,		// World play script ������ ������ �α� �ƿ� �� ��� Failed ó�� �Ǿ�� �ϴ� ��츦 �����ϴ� �÷���
};

#pragma pack( 1 )
struct sMAIN_TSP
{
	NTL_TS_TC_ID							tcCurId;
	NTL_TS_TC_ID							tcPreId;
};
#pragma pack()

#pragma pack( 1 )
struct sEXCEPT_TIMER
{
	NTL_TS_TC_ID							tcId;
	NTL_TS_TA_ID							taId;

	unsigned int							uiRemainTime;
};
#pragma pack()


#pragma pack( 1 )
struct sEXCEPT_TIMER_SLOT
{
	enum { eTIMER_SLOT_MAX = 4 };

	sEXCEPT_TIMER							asExceptTimer[eTIMER_SLOT_MAX];
};
#pragma pack()

#pragma pack( 1 )
struct sSTORAGE_SLOT_MEMORY
{
	enum { eSTORAGE_SLOT_MEMORY_MAX = 8 };

	// �迭�� �ε����� SSM �� ���̵�� ����
	unsigned int							auiSSM[eSTORAGE_SLOT_MEMORY_MAX];
};
#pragma pack()

#pragma pack( 1 )
struct sSTOC_EVT_DB_DATA
{
	enum { eSTOC_EVT_DB_DATA_USER_DATA_MAX = 4 };

	NTL_TS_TC_ID							tcId;
	NTL_TS_TA_ID							taId;
	unsigned int							m_aUserData[eSTOC_EVT_DB_DATA_USER_DATA_MAX];		// tcId, taId�� ���� ����޴� ����� ���� ������

	void Init( void )
	{
		tcId = NTL_TS_TC_ID_INVALID;
		taId = NTL_TS_TA_ID_INVALID;
		memset( m_aUserData, 0, sizeof( m_aUserData ) );
	}
};
#pragma pack()

#pragma pack( 1 )
struct sPROGRESS_QUEST_INFO
{
	enum { ePROGRESS_QUEST_INFO_MAX_SIZE = 256 };
	enum { eCUR_VERSION = 0 };

	sPROGRESS_QUEST_INFO( void )
	{
		byVer = eCUR_VERSION;
		tId = NTL_TS_T_ID_INVALID;

		memset( &uData.sQInfoV0, 0xff, sizeof( uData.sQInfoV0 ) );
		uData.sQInfoV0.wQState = 0;
		uData.sQInfoV0.tcQuestInfo = NTL_TS_TC_ID_INVALID;
		uData.sQInfoV0.taQuestInfo = NTL_TS_TA_ID_INVALID;
	}

	unsigned char							byVer;				// ����
	NTL_TS_T_ID								tId;				// ����Ʈ ���̵�

	union uDATA
	{
		struct sEXTENDED_POSSIBLE_V0
		{
			unsigned short					wQState;			// ����Ʈ ����
			sMAIN_TSP						sMainTSP;			// ����Ʈ ���� ������
			sEXCEPT_TIMER_SLOT				sETSlot;			// ���� Ÿ�̸��� ���� ����
			sSTORAGE_SLOT_MEMORY			sSSM;				// ���� ���� �޸�
			sSTOC_EVT_DB_DATA				sSToCEvtData;		// ���� �̺�Ʈ ������
			NTL_TS_TG_ID					tgExcCGroup;		// ������ Ŭ���̾�Ʈ �׷�

			NTL_TS_TC_ID					tcQuestInfo;		// ����Ʈ ���� �����̳� ���̵�
			NTL_TS_TA_ID					taQuestInfo;		// ����Ʈ ���� �׼� ���̵�
		};
		sEXTENDED_POSSIBLE_V0				sQInfoV0;
	};
	uDATA									uData;
};
#pragma pack()

//===================================================================================
//
//===================================================================================
typedef NTL_TS_T_ID		QUESTID;
const	QUESTID			INVALID_QUESTID = NTL_TS_T_ID_INVALID;
//===================================================================================


//-----------------------------------------------------------------------------------
// Ʈ���� ������Ʈ�� ����
//-----------------------------------------------------------------------------------
typedef BYTE TOBJECT_STATE;

typedef BYTE TOBJECT_SUBSTATE;


enum eTOBJECT_STATE
{
	TOBJECT_STATE_NONE = 0xFF, // ���� ����

	MAX_TOBJECT_STATE = 10
};


enum eTOBJECT_STATE_TYPE
{
	TOBJECT_STATE_TYPE_A,
	TOBJECT_STATE_TYPE_B,
	TOBJECT_STATE_TYPE_C,

	MAX_TOBJECT_STATE_TYPE,

	INVALID_TOBJECT_STATE_TYPE = 0xFF
};


enum eTOBJECT_STATE_TYPE_A
{
	TOBJECT_STATE_TYPE_A_CLOSED,
	TOBJECT_STATE_TYPE_A_OPEND,
	TOBJECT_STATE_TYPE_A_DESTROYED,

	MAX_TOBJECT_STATETYPE_A
};


enum eTOBJECT_STATE_TYPE_B
{
	TOBJECT_STATE_TYPE_B_CLOSING,
	TOBJECT_STATE_TYPE_B_CLOSED,
	TOBJECT_STATE_TYPE_B_OPENING,
	TOBJECT_STATE_TYPE_B_OPEND,
	TOBJECT_STATE_TYPE_B_DESTROYING,
	TOBJECT_STATE_TYPE_B_DESTROYED,

	MAX_TOBJECT_STATE_TYPE_B
};


enum eTOBJECT_STATE_TYPE_C
{
	TOBJECT_STATE_TYPE_C_NO_TEAM,
	TOBJECT_STATE_TYPE_C_ATTACK_TEAM,
	TOBJECT_STATE_TYPE_C_DEFENCE_TEAM,

	MAX_TOBJECT_STATE_TYPE_C
};


enum eTOBJECT_SUBSTATE
{
	TOBJECT_SUBSTATE_SHOW,
	TOBJECT_SUBSTATE_UNSELECT,

	MAX_TOBJECT_SUBSTATE,
};


enum eTOBJECT_SUBSTATE_FLAG
{
	TOBJECT_SUBSTATE_FLAG_SHOW = MAKE_BIT_FLAG( TOBJECT_SUBSTATE_SHOW ),
	TOBJECT_SUBSTATE_FLAG_UNSELECT = MAKE_BIT_FLAG( TOBJECT_SUBSTATE_UNSELECT ),
};


enum eTRIGGER_SERVER_EVENT_TYPE
{
	TRIGGER_SERVER_EVENT_TYPE_SPS,
	TRIGGER_SERVER_EVENT_TYPE_TQS,

	TRIGGER_SERVER_EVENT_TYPE_TMQ_START,
	TRIGGER_SERVER_EVENT_TYPE_TMQ_ARRIVE,
	TRIGGER_SERVER_EVENT_TYPE_TMQ_LEAVE,

	TRIGGER_SERVER_EVENT_TYPE_TS,

	TRIGGER_SERVER_EVENT_TYPE_WPS,

	TRIGGER_SERVER_EVENT_TYPE_INVALID = 0xffffffff
};


enum eTS_EVENT_SEND_TYPE
{
	TS_EVENT_SEND_TYPE_WORLD,				// ���忡 ��ε�ĳ��Ʈ
	TS_EVENT_SEND_TYPE_WORLD_AREA,			// ������ Ư�� ������������ �����Ÿ����� ��ε�ĳ��Ʈ
	TS_EVENT_SEND_TYPE_PARTY,				// ��� ��Ƽ�� : ��Ƽ�� ���� ��� ����
	TS_EVENT_SEND_TYPE_PARTY_AREA,			// ���� �Ÿ� �ȿ� �ִ� ��Ƽ�� : ��Ƽ�� ���� ��� ����.
	TS_EVENT_SEND_TYPE_PC,					// ����
	TS_EVENT_SEND_TYPE_INVALID = 0xffffffff
};



//-----------------------------------------------------------------------------------
const BYTE		DBO_MAX_OBJECT_STATE = MAX_TOBJECT_STATE;
const BYTE		DBO_MAX_OBJECT_STATE_ANIMATION = 10;
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------


//===================================================================================
//
//===================================================================================
const unsigned int			NTL_QUEST_INVENTORY_WIDTH = 4;
const unsigned int			NTL_QUEST_TIMER_SLOT_MAX = 4;
const unsigned int			NTL_QUEST_INVENTORY_HEIGHT = 8;
const unsigned int			NTL_QUEST_EVENT_PARAM_MAX = 12;
const unsigned int			NTL_QUEST_INVENTORY_SLOT_COUNT = NTL_QUEST_INVENTORY_WIDTH * NTL_QUEST_INVENTORY_HEIGHT;
//===================================================================================



// �ѹ��� ������ �� �ִ� ����Ʈ �������� �ִ� ����
const int NTL_QUEST_ITEM_CREATE_MAX_COUNT = 5;

enum eQUEST_ITEM_UPDATE_TYPE
{
	eQUEST_ITEM_UPDATE_TYPE_CREATE = 0,	// ����
	eQUEST_ITEM_UPDATE_TYPE_UPDATE,		// ������Ʈ
	eQUEST_ITEM_UPDATE_TYPE_DELETE		// ����
};


// Query Server �� ����Ʈ ������ ���� �� ���� ��û �� ������.
// res�� �޾��� �� ó���� ���ؿ� ���
enum eQUEST_ITEM_REQUEST_TYPE
{
	eQUEST_ITEM_REQUEST_TYPE_TS_CREATE,		// TS ���� ���� ��û	-> callback
	eQUEST_ITEM_REQUEST_TYPE_TS_DELETE,		// TS ���� ���� ��û	-> callback
	eQUEST_ITEM_REQUEST_TYPE_MOB_DROP,		// ���� ���			-> ����
	eQUEST_ITEM_REQUEST_TYPE_USER_DELETE,	// ����� ���� ��û
	eQUEST_ITEM_REQUEST_TYPE_SERVER_EVENT,	// Server Event���� have quest item ����Ʈ ����� ���
	eQUEST_ITEM_REQUEST_TYPE_VISIT_EVENT,	// Visit event���� ���

	eQUEST_ITEM_REQUEST_TYPE_INVALID = 0xFF
};


// 
enum eQUEST_DROP_PERMISSION_TYPE
{
	eQUEST_DROP_PERMISSION_TYPE_PERSONAL,
	eQUEST_DROP_PERMISSION_TYPE_PARTY,

	eQUEST_DROP_PERMISSION_TYPE_INVALID = 0xFF
};


// ������Ʈ Ÿ��
enum eESCORT_TYPE
{
	ESCORT_TYPE_UNDER_ESCORT, // ȣ�����ϰ� ����
	ESCORT_TYPE_TARGET_FOLLOW, // �������� ���󰡰� ����

	MAX_ESCORT_TYPE,
	INVALID_ESCORT_TYPE,
};


// Select reward type
#define INVALID_SELECT_REWARD_SLOT_INDEX	(0xffffffff)


//===================================================================================
//
//===================================================================================
#pragma pack(1)


struct sQUESTITEM_DATA
{
	TBLIDX			tblidx;
	BYTE			byCurStackCount;
	BYTE			byPos;				// �κ��丮������ �������� ��ġ by ju-hyeong
};


// Quesy Server �� Game Server ���� ���
typedef sCOMPLETE_QUEST_INFO		sQUEST_COMPLETE_DATA;		// ����Ʈ �Ϸ� ����
typedef sPROGRESS_QUEST_INFO		sQUEST_PROGRESS_DATA;		// ����Ʈ ���� ����
typedef sQUESTITEM_DATA				sQUEST_INVENTORY_DATA;		// ����Ʈ �κ��丮 

typedef sCOMPLETE_QUEST_TOTAL_BIT_INFO		sCOMPLETE_QUEST_TOTAL_BIT_DATA;		// ����Ʈ �Ϸ� ����

// ����Ʈ �κ��丮 - Ŭ���̾�Ʈ���� ��� ����Ʈ �����۵��� �����ϴ� �� ���
struct sQUEST_INVENTORY_FULLDATA
{
	BYTE				byQuestItemCount;	// ������ ����
	sQUESTITEM_DATA		aQuestItemData[NTL_QUEST_INVENTORY_SLOT_COUNT];	// ������
};


// �������� ����ü�� ���� �� Ŭ���̾�Ʈ�� ����ü�� ���� ����ϹǷ� ������ ���� typedef
typedef sCOMPLETE_QUEST_INFO	sQUEST_COMPLETE_INFO;
typedef sPROGRESS_QUEST_INFO	sQUEST_PROGRESS_INFO;
typedef sQUESTITEM_DATA			sQUEST_INVENTORY_INFO;



struct sTOBJECT_BRIEF
{
	TBLIDX		objectID; // = trigger object table index
};


struct sTOBJECT_STATE
{
	BYTE		byState; // Main State
	BYTE		bySubStateFlag; // Sub State Flag
	DWORD		dwStateTime; // �ش� State�� ���ͼ� ������ �ð�	
};


#pragma pack()


#pragma pack( 1 )


// ����Ʈ �������� ������Ʈ[����,����,����] �� ����Ʈ ������ �ϳ��� ����
struct sQUEST_ITEM_UPDATE_DATA
{
	BYTE		byUpdateType;	// eQUEST_ITEM_UPDATE_TYPE
	TBLIDX		itemTblidx;		// ����Ʈ ������ index
	BYTE		byPos;			// ����Ʈ �������� ��ġ
	BYTE		byCurCount;		// ����Ʈ �������� ����
};


// Trigger System Middle Serial
struct sTSM_SERIAL
{
	DWORD		dwKey;				// TSMiddle Serial
	DWORD		dwSub;				// TSMiddle SubSerial
};

//---------------------------------------------------------------------------------------
// Sub Data

//
struct sQUEST_ITEM_TS_SUB_DATA
{
	BYTE		byTSType;				// eTSM_MANAGER_TYPE
	HOBJECT		hObject;				// Trigger Object Handle : ObjectTrigger������ ���δ�.
	sTSM_SERIAL	sSerial;
};


// ����Ʈ �������� ������Ʈ[����,����,����]�� ���������� ���굥����
// enum eQUEST_ITEM_REQUEST_TYPE �� ��ġ�ȴ�.
union uQUEST_ITEM_UPDATE_SUB_DATA
{
	sQUEST_ITEM_TS_SUB_DATA	sTSCreate;	// ����Ʈ ������ ����
	sQUEST_ITEM_TS_SUB_DATA	sTSDelete;	// ����Ʈ ������ ����
	DWORD					dwReserve;	// ������� ���� - �� ������� ���� ������ ����
};


//---------------------------------------------------------------------------------------


// Quest Server Event Update �� ����ϴ� ����
union uSTOC_EVT_UPDATE_DATA
{
	// �� ���̱�
	struct sMOB_KILL_CNT
	{
		int											nCurMobCnt;
	};

	// �� ������ ���� �ϱ�
	struct sMOB_KILL_ITEM_CNT
	{
		int											nCurMobLICnt;
	};

	// ������ ����ϱ�
	struct sDELIVERY_ITEM
	{
		int											nCurItemCnt;
	};

	// ������Ʈ ������
	struct sOBJECT_ITEM
	{
		int											nCurItemCnt;
	};

	// public �� ������ ���� - �� ���� ��� �̺�Ʈ
	struct sPUBLIC_MOB_ITEM_CNT
	{
		int											nCurItemCnt;
	};

	// Custom event counter
	struct sCUSTOM_EVT_CNT
	{
		int											nCurCnt;
	};

	struct sVISIT_EVT
	{
		bool										bCompleted;
	};


	sMOB_KILL_CNT				sMobKillCnt;
	sMOB_KILL_ITEM_CNT			sMobKillItemCnt;
	sDELIVERY_ITEM				sDeliveryItemCnt;
	sOBJECT_ITEM				sObjectItemCnt;
	sPUBLIC_MOB_ITEM_CNT		sPublicMobItemCnt;
	sCUSTOM_EVT_CNT				sCustomEvtCnt;
	sVISIT_EVT					sVisitEvt;
};

#pragma pack()
