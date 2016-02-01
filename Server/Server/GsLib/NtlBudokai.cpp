//***********************************************************************************
//
//	File		:	NtlBudokai.cpp
//
//	Begin		:	2009-07-28
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Lee Ju-hyeong
//
//	Desc		:	
//
//***********************************************************************************

#include "stdafx.h"
#include "NtlBudokai.h"
#include "time.h"

eBUDOKAI_TYPE GetBudokaiType( BYTE byState )
{
	if( byState >= BUDOKAI_STATE_JUNIOR_FIRST && byState <= BUDOKAI_STATE_JUNIOR_LAST )
	{
		return BUDOKAI_TYPE_JUNIOR;
	}

	if( byState >= BUDOKAI_STATE_ADULT_FIRST && byState <= BUDOKAI_STATE_ADULT_LAST )
	{
		return BUDOKAI_TYPE_ADULT;
	}

	return INVALID_BUDOKAI_TYPE;
}


// is open
bool IsBudokaiOpen( BYTE byState )
{
	switch(byState)
	{
	case BUDOKAI_STATE_JUNIOR_OPEN:
	case BUDOKAI_STATE_OPEN:
		return true;
	}

	return false;
}


//-----------------------------------------------------------------------------------
//		Purpose	: õ�����Ϲ���ȸ�� �����ֱ⸦ �˾Ƴ���.
//		Return	:
//-----------------------------------------------------------------------------------
BUDOKAITIME CalcBudokaiNextStartTime( BUDOKAITIME tmDefaultTime, BYTE byOpenTerm, BYTE byOpenDayOfWeek, BYTE byOpenHour, BYTE byOpenMinute )
{
	__time32_t tmPrevOpenTime = tmDefaultTime;

	tm sPrevOpenTime;

	// 64bit
	errno_t errid = _localtime32_s( &sPrevOpenTime, &tmPrevOpenTime );
	if( 0 != errid)
	{
		return 0;
	}

	// �����ֱ� ù��° �Ͽ��� ���� �ð�
	time_t tmSunday = tmPrevOpenTime
		- ( sPrevOpenTime.tm_wday * 24 * 60 * 60
		+ sPrevOpenTime.tm_hour * 60 * 60
		+ sPrevOpenTime.tm_min * 60
		+ sPrevOpenTime.tm_sec )
		+ 7 * 24 * 60 * 60;


	// ���� õ������ ����ȸ �ð�
	time_t tmNextBudokaiTime = tmSunday
		+ ( byOpenTerm * 7 * 24 * 60 * 60			// term
		+ byOpenDayOfWeek * 24 * 60 * 60			// day
		+ byOpenHour * 60 * 60						// Hour
		+ byOpenMinute * 60 );						// minute

	return (BUDOKAITIME)tmNextBudokaiTime;
}
