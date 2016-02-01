#pragma once

#include "SharedType.h"
#include "Vector.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#define NTL_MAX_BIND_RADIUS		(8.0f)
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

// �ڷ���Ʈ ����
enum eTELEPORT_TYPE
{
	TELEPORT_TYPE_DEFAULT,				// �Ϲ����� ��Ȳ
	TELEPORT_TYPE_GAME_IN,				// ���ӿ� ó������ ���� ���
	TELEPORT_TYPE_GAME_OUT,				// ���ӿ��� ������ ���
	TELEPORT_TYPE_TELEPOPO,				// �ڷ����� �������� ����� ���
	TELEPORT_TYPE_SKILL,				// ���� �̵� ���� ��ų�� ����� ���
	TELEPORT_TYPE_NPC_PORTAL,			// NPC ��Ż ���񽺸� �̿��� ���
	TELEPORT_TYPE_POPOSTONE,			// ��Ȱ�Ͽ� ������ ���� ��ȯ�� ���
	TELEPORT_TYPE_WORLD_MOVE,			// ���尣 �̵��� �� ���
	TELEPORT_TYPE_TMQ_WORLD_MOVE,		// TMQ �������� �����ϰų� TMQ �������� ������ ���
	TELEPORT_TYPE_TMQ_PORTAL,			// TMQ ���� ������ �ڷ���Ʈ�� ���

	TELEPORT_TYPE_RANKBATTLE,
	TELEPORT_TYPE_TIMEQUEST,
	TELEPORT_TYPE_TUTORIAL,
	TELEPORT_TYPE_BUDOKAI,				// õ�����Ϲ���ȸ �Ϲ� �÷ο� ����
	TELEPORT_TYPE_MATCH,				// õ�����Ϲ���ȸ ���
	TELEPORT_TYPE_MINORMATCH,			// õ�����Ϲ���ȸ ������ �ڷ���Ʈ
	TELEPORT_TYPE_MAJORMATCH,			// õ�����Ϲ���ȸ ���� �ڷ���Ʈ
	TELEPORT_TYPE_FINALMATCH,			// õ�����Ϲ���ȸ �ἱ �ڷ���Ʈ

	TELEPORT_TYPE_COMMAND,
	TELEPORT_TYPE_GM,
	TELEPORT_TYPE_DUNGEON,
	TELEPORT_TYPE_DOJO,

	TELEPORT_TYPE_COUNT,

	TELEPORT_TYPE_INVALID = 0xFFui8,

	TELEPORT_TYPE_FIRST = TELEPORT_TYPE_GAME_IN,
	TELEPORT_TYPE_LAST = TELEPORT_TYPE_DUNGEON,
};

enum eDBO_REVIVAL_REQUEST_TYPE
{
	DBO_REVIVAL_REQUEST_TYPE_TELEPORT_SOMEWHERE = 0,
	DBO_REVIVAL_REQUEST_TYPE_CURRENT_POSITION,

	DBO_REVIVAL_REQUEST_TYPE_COUNT,

	DBO_REVIVAL_REQUEST_TYPE_FIRST = DBO_REVIVAL_REQUEST_TYPE_TELEPORT_SOMEWHERE,
	DBO_REVIVAL_REQUEST_TYPE_LAST = DBO_REVIVAL_REQUEST_TYPE_COUNT - 1,
};

// ��Ȱ ����
enum eREVIVAL_TYPE
{
	REVIVAL_TYPE_CURRENT_POSITION = 0, // ���� ��ġ���� �ٷ� ��Ȱ
	REVIVAL_TYPE_BIND_POINT, // ���ε� ��ġ�� �̵��ؼ� ��Ȱ
	REVIVAL_TYPE_RESCUED, // ��ų�̳� ��Ÿ gm ��ɿ� ���� �ٷ� ��Ȱ
	REVIVAL_TYPE_SPECIFIED_POSITION, // ������ ��ġ���� ��Ȱ

	REVIVAL_TYPE_FIRST = REVIVAL_TYPE_CURRENT_POSITION,
	REVIVAL_TYPE_LAST = REVIVAL_TYPE_RESCUED,
	INVALID_REVIVAL_TYPE = 0xFF
};

// Bind ����
enum eDBO_BIND_TYPE
{
	DBO_BIND_TYPE_INITIAL_LOCATION = 0,		// ĳ���Ͱ� ������ �� �� ���� bind�� ���� ���� ����
	DBO_BIND_TYPE_POPO_STONE,				// ������������ bind ��ġ�� ������ ����
	DBO_BIND_TYPE_GM_TOOL,					// GM tool�� ���� bind ��ġ�� ������ ����
	DBO_BIND_TYPE_SKILL,					// ��ų�� ���� bind ��ġ�� ������ ����

	DBO_BIND_TYPE_FIRST = DBO_BIND_TYPE_INITIAL_LOCATION,
	DBO_BIND_TYPE_LAST = DBO_BIND_TYPE_SKILL,
	DBO_BIND_TYPE_INVALID = 0xFF
};

//-----------------------------------------------------------------------------------
// ��Ż���� �ִ밳��
//-----------------------------------------------------------------------------------
const int		NTL_PORTAL_MAX_COUNT	= 100;


const DWORD		DBO_TELEPORT_PROPOSAL_WAIT_TIME		= 120;		// �ڷ���Ʈ ����â �ִ� ���ð�



//-----------------------------------------------------------------------------------
#pragma pack(1)

// �����̵� ����
struct sSERVERTELEPORT_INFO
{
	BYTE			byTeleportType;	// eTELEPORT_TYPE
	WORLDID			worldId;
	TBLIDX			worldTblidx;
	sVECTOR3		vLoc;
	sVECTOR3		vDir;
	SERVERCHANNELID	serverChannelId;
	SERVERINDEX		serverIndex;
};

#pragma pack()
