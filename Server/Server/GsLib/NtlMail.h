//***********************************************************************************
//
//	File		:	NtlMail.h
//
//	Begin		:	2007-08-6
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	john@ntl-inc.com
//
//	Desc		:	
//
//***********************************************************************************

#pragma once
#include "NtlItem.h"
#include "SharedType.h"

const DWORD		NTL_MAX_BASIC_MAIL_SEND_ZENNY	= 10;		// ������
const DWORD		NTL_MAX_ATTACH_MAIL_SEND_ZENNY	= 10;		// ������
const DWORD		NTL_MAX_MAIL_SEND_ZENNY_AMOUNTS	= 100000;	// ÷�� �ִ밡�� �ݾ�
const DWORD		NTL_MAX_MAIL_SLOT_COUNT	= 30;				// �ִ� ���� ������ ����
const DWORD		NTL_MAIL_RELOAD_TIME    = 1 * 60 * 1000;    // DB ����� ����ȭ �ð� ���� �ʿ�
const DWORD		NTL_MAIL_DISTANCE_CHECK_TIME = 3 * 1000;	// ���Ϲڽ����� �Ÿ� üũ �ð� 
const BYTE		NTL_DEFAULT_MAIL_KEEPING_PERIOD = 10;		// �⺻ ���� ���� �Ⱓ. ��(day) ����
const DWORD		NTL_MAX_COUNT_OF_MULTI_DEL		= 6;		// ��Ƽ������ �ִ��
const BYTE		NTL_MAX_COUNT_MULTI_MAIL		= 50;		// GM-TOOL ��Ƽ���� �ִ�ġ
//-----------------------------------------------------------------------------------
// ���� Ÿ�� 
//-----------------------------------------------------------------------------------
enum eMAIL_TYPE
{
	eMAIL_TYPE_NONE,			// ������ ���
	eMAIL_TYPE_BASIC,			// TEXT ONLY
	eMAIL_TYPE_ITEM,			// ITEM PLUS
	eMAIL_TYPE_ZENNY,			// ZENNY PLUS
	eMAIL_TYPE_ITEM_ZENNY,		// ITEM + ZENNY
	eMAIL_TYPE_ITEM_ZENNY_REQ,  // ITEM + ZENNY REQUEST
	eMAIL_TYPE_ZENNY_REQ,		// ZENNY REQUEST
	eMAIL_COUNT,				// GMTool���� eMAIL_TYPE�� ���� ��Ʈ���� ����Ѵ�. �׷��� Count�� �ʿ���[10/8/2007 SGpro]
};

//-----------------------------------------------------------------------------------
// sender Ÿ�� 
//-----------------------------------------------------------------------------------
enum eMAIL_SENDER_TYPE
{
	eMAIL_SENDER_TYPE_BASIC,		// �Ϲ�����
	eMAIL_SENDER_TYPE_REPLY,		// �������
	eMAIL_SENDER_TYPE_RETURN,		// ���ϸ���
	eMAIL_SENDER_TYPE_SYSTEM,		// System
	eMAIL_SENDER_TYPE_GM,			// GM

};

struct sMAIL_SLOT
{
	MAILID aMailID[NTL_MAX_MAIL_SLOT_COUNT];
};

struct sMAIL_BRIEF
{
	BYTE byMailType;
	DWORD dwZenny;
	bool bIsRead;
	bool bIsAccept;
	bool bIsLock;
	BYTE bySenderType;
	DBOTIME	endTime;
};

struct sMAIL_DATA
{
	MAILID				mailID;			// ���� ���̵�
	bool 				bIsRead;
	bool 				bIsAccept;
	bool 				bIsLock;
	BYTE 				byMailType;		// eMAIL_TYPE
	BYTE 				bySenderType;	// eMAIL_SENDER_TYPE
	DWORD				dwZenny;		// Req or Give Zenny
	BYTE				byExpired;		// ��ȿ���ᳯ¥ �ִ� 10��
	sITEM_DATA			sItemData;		// �����۳���	
	sDBO_TIME			tCreateTime;	// ������¥
	WCHAR				wszFromName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];		// ���� ĳ�� �̸�
	BYTE				byTextSize;
	WCHAR				wszText[NTL_MAX_LENGTH_OF_MAIL_MESSAGE_IN_UNICODE + 1];	// ���ϳ���
	DBOTIME				endTime;
};

struct sMAIL_GM_DATA
{
	MAILID				mailID;			// ���� ���̵�
	bool 				bIsRead;
	bool 				bIsAccept;
	bool 				bIsLock;
	BYTE 				byMailType;		// eMAIL_TYPE
	BYTE 				bySenderType;	// eMAIL_SENDER_TYPE
	DWORD				dwZenny;		// Req or Give Zenny
	BYTE				byExpired;		// ��ȿ���ᳯ¥ �ִ� 10��
	sITEM_DATA			sItemData;		// �����۳���	
	sDBO_TIME			tCreateTime;	// ������¥
	CHARACTERID			FromCharID;
	WCHAR				wszFromName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];		// ���� ĳ�� �̸�
	BYTE				byTextSize;
	WCHAR				wszText[NTL_MAX_LENGTH_OF_MAIL_MESSAGE_IN_UNICODE + 1];	// ���ϳ���
	bool				bIsTemp;	// tempMail ? True
};

struct sMAIL_PROFILE
{
	MAILID				mailID;			// ���� ���̵�
	bool 				bIsRead;
	bool 				bIsAccept;
	bool 				bIsLock;
	BYTE 				byMailType;		// eMAIL_TYPE
	BYTE 				bySenderType;	// eMAIL_SENDER_TYPE
	DWORD				dwZenny;		// Req or Give Zenny
	BYTE				byExpired;		// ��ȿ���ᳯ¥ �ִ� 10��
	sITEM_PROFILE		sItemProfile;	// �����۳���	
	sDBO_TIME			tCreateTime;	// ������¥
	WCHAR				wszFromName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];		// ���� ĳ�� �̸�
	WCHAR				wszText[NTL_MAX_LENGTH_OF_MAIL_MESSAGE_IN_UNICODE + 1];	// ���ϳ���
	DBOTIME				endTime;
};
struct sMAIL_NEW_PROFILE
{
	MAILID				mailID;			// ���� ���̵�
	bool 				bIsRead;
	bool 				bIsAccept;
	bool 				bIsLock;
	BYTE 				byMailType;		// eMAIL_TYPE
	BYTE 				bySenderType;	// eMAIL_SENDER_TYPE
	DWORD				dwZenny;		// Req or Give Zenny
	BYTE				byExpired;		// ��ȿ���ᳯ¥ �ִ� 10��
	sITEM_PROFILE		sItemProfile;	// �����۳���	
	sDBO_TIME			tCreateTime;	// ������¥
	WCHAR				wszFromName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];		// ���� ĳ�� �̸�
	DBOTIME				endTime;
};

struct sMAIL_NEW_GM_PROFILE
{
	MAILID				mailID;			// ���� ���̵�
	bool 				bIsRead;
	bool 				bIsAccept;
	bool 				bIsLock;
	BYTE 				byMailType;		// eMAIL_TYPE
	BYTE 				bySenderType;	// eMAIL_SENDER_TYPE
	DWORD				dwZenny;		// Req or Give Zenny
	BYTE				byExpired;		// ��ȿ���ᳯ¥ �ִ� 10��
	sITEM_PROFILE		sItemProfile;	// �����۳���	
	sDBO_TIME			tCreateTime;	// ������¥
	CHARACTERID			FromCharID;
	WCHAR				wszFromName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];		// ���� ĳ�� �̸�
	bool				bIsTemp;	// tempMail ? True
};

struct sMAIL_NEW_BREIF
{
	BYTE				byMailCount; // Total
	BYTE				byUnReadManager;
	BYTE				byUnReadNormal;
};