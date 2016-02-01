//***********************************************************************************
//
//	File		:	NtlHlsItem.h
//
//	Begin		:	2009-8-14
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	chung,DooSup ( john@ntl-inc.com )
//
//	Desc		: HLS�� ȣ������ ���Ÿ� ���� ���ڷ� Cash�� ���� �����ϴ� ������ ���Ѵ�.	
//
//***********************************************************************************
#pragma once
#include "SharedType.h"


//-----------------------------------------------------------------------------------
// ĳ�� ������ Ÿ��
//-----------------------------------------------------------------------------------
enum eCASHITEM_TYPE
{
	CASHITEM_TYPE_ITEM_CREATE,			// ĸ��Ŷ���� �̵�
	CASHITEM_TYPE_PACKAGE,				// ��Ű��
	CASHITEM_TYPE_GMT,					// ���ӸŴϾ�Ÿ���缳��Ƚ������
	CASHITEM_TYPE_ACCOUNT_USE,			// ����â�� ���Ⱓ ������
	CASHITEM_TYPE_EXP_ZENNY,			// ����ġ ���� �߰� ȹ��Ⱓ ������Ʈ

	CASHITEM_TYPE_COUNT,

	CASHITEM_TYPE_INVALID = 0xff,
};
struct sCASHITEM_BRIEF
{
	DWORD			dwProductId;
	TBLIDX			HLSitemTblidx; // item table index
	BYTE			byStackCount;
};

//-----------------------------------------------------------------------------------
// ĳ�� ������ �������� ��� Ÿ�� �÷���
//----------------------------------------------------------------------------------
enum eHLS_TAB_TYPE
{
	HLS_TAB_TYPE_NORMAL,
	HLS_TAB_TYPE_ALL,
	HLS_TAB_TYPE_NEW,
	HLS_TAB_TYPE_HOT,
	HLS_TAB_TYPE_LIMITED,

	HLS_TAB_TYPE_COUNT,

	HLS_TAB_TYPE_FIRST = HLS_TAB_TYPE_NORMAL,
	HLS_TAB_TYPE_LAST = HLS_TAB_TYPE_COUNT - 1,
};

enum eHLS_SELL_TYPE
{
	HLS_SELL_TYPE_NORMAL,
	HLS_SELL_TYPE_PERIOD,	// �Ⱓ
	HLS_SELL_TYPE_TOTAL_COUNT,	// ����
	
	HLS_SELL_TYPE_COUNT,

	HLS_SELL_TYPE_FIRST = HLS_SELL_TYPE_NORMAL,
	HLS_SELL_TYPE_LAST = HLS_SELL_TYPE_COUNT - 1,
};

enum eHLS_DISPLAY_ITEM_FUNC
{
	HLS_DISPLAY_ITEM_FUNC_NORMAL,
	HLS_DISPLAY_ITEM_FUNC_NEW,
	HLS_DISPLAY_ITEM_FUNC_HOT,
	HLS_DISPLAY_ITEM_FUNC_LIMITED,
};

enum eHLS_DISPLAY_ITEM_FUNC_BIT_FLAG
{
	HLS_DISPLAY_ITEM_FUNC_BIT_FLAG_NORMAL	= 0x01 << HLS_DISPLAY_ITEM_FUNC_NORMAL,
	HLS_DISPLAY_ITEM_FUNC_BIT_FLAG_NEW		= 0x01 << HLS_DISPLAY_ITEM_FUNC_NEW,
	HLS_DISPLAY_ITEM_FUNC_BIT_FLAG_HOT		= 0x01 << HLS_DISPLAY_ITEM_FUNC_HOT,
	HLS_DISPLAY_ITEM_FUNC_BIT_FLAG_LIMITED  = 0x01 << HLS_DISPLAY_ITEM_FUNC_LIMITED,
};

const DWORD		NTL_CASHITEM_RELOAD_TIME    = 1 * 60 * 1000;    // DB ����� ����ȭ �ð� ���� �ʿ�
const DWORD		NTL_MAX_CASHITEM_COUNT		= 255;				// ǥ���ϰų� �ѹ��� �ε��Ҽ� �ִ� �ִ� ĳ��������// ���Ѿ����� �ε����� �����ؾ���
const DWORD		DBO_MAX_COUNT_HLSITEM_SUB_ITEM = 5;