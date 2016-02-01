#include "stdafx.h"
#include "NtlItem.h"
#include "Battle.h"
#include "Object.h"
#include "NtlStringHandler.h"
#include "NtlHex.h"

WORD Dbo_GetFinalOffence(WORD wBaseOffence, BYTE byGrade)
{
	if (ITEM_GRADE_LEVEL_0 == byGrade)
	{
		return wBaseOffence;
	}
	else
	{
		return (WORD)(wBaseOffence * (1.0f + (0.03f * byGrade)) + (byGrade * byGrade + 1));
	}
}

WORD Dbo_GetFinalDefence(WORD wBaseDefence, BYTE byGrade)
{
	if (ITEM_GRADE_LEVEL_0 == byGrade)
	{
		return wBaseDefence;
	}
	else
	{
		return (WORD)(wBaseDefence * (1.0f + (0.03f * byGrade)) + (byGrade * byGrade * 0.6 + 1));
	}
}

float Dbo_UpgradeSuccessRate( BYTE byGrade, BYTE byStoneType )
{
	if ( byGrade > NTL_ITEM_MAX_GRADE || byGrade < 0 ) // �⺻üũ
		return 0.0f;
	if ( byStoneType != ITEM_TYPE_STONE && byStoneType != ITEM_TYPE_PURE_STONE && byStoneType != ITEM_TYPE_BLACK_STONE )
		return 0.0f;
	
	// �� ȣ������ ������ ��� ������ 100%�� Ȯ���� ����.
	if ( byStoneType == ITEM_TYPE_BLACK_STONE )
	{
		if ( 0 == byGrade ) return 0.0f;
		else return 100.0f;
	}

	// ���߿� ǻ��� �Ϲ��̶� Ȯ���޶����� ���� ���� ����.
	const static float successRateTable[NTL_ITEM_MAX_GRADE+1] = {
		 100.0f // 0
		,100.0f // 1
		,80.0f  // 2 
		,30.0f  // 3
		,60.0f  // 4
		,30.0f  // 5
		,20.0f  // 6
		,0.0f   // 7
		,20.0f  // 8
		,10.0f  // 9
		,5.0f   // 10
		,0.0f   // 11
		,2.0f   // 12
		,0.0f   // 13
		,0.0f   // 14
		,0.0f }; // 15

	return successRateTable[byGrade];
}

float Dbo_GetAttributeRate( BYTE byItemBattleAttribute, BYTE byPosNum )
{
	if( byItemBattleAttribute >= BATTLE_ATTRIBUTE_COUNT ||
		byPosNum >= BATTLE_ATTRIBUTE_COUNT )
		return ITEM_UPGRADE_RATE_2;

	BYTE byRet = Dbo_GetUpgradeRate(byItemBattleAttribute,byPosNum);

	static float fRate[BATTLE_ATTRIBUTE_COUNT] ={ -10.0f , -5.0f, 0.0f, 5.0f, 10.0f, 20.0f, };
	return fRate[byRet];
}

BYTE Dbo_GetUpgradeRate( BYTE byItemBattleAttribute, BYTE byPosNum )
{
	static BYTE aByBattleAttributeBonusRate[BATTLE_ATTRIBUTE_COUNT][BATTLE_ATTRIBUTE_COUNT] = 
	{
		// BATTLE_ATTRIBUTE_NONE
		{ ITEM_UPGRADE_RATE_2, ITEM_UPGRADE_RATE_2, ITEM_UPGRADE_RATE_2, ITEM_UPGRADE_RATE_2, ITEM_UPGRADE_RATE_2, ITEM_UPGRADE_RATE_2 },

		// BATTLE_ATTRIBUTE_HONEST
		{ ITEM_UPGRADE_RATE_2, ITEM_UPGRADE_RATE_5, ITEM_UPGRADE_RATE_1, ITEM_UPGRADE_RATE_0, ITEM_UPGRADE_RATE_4, ITEM_UPGRADE_RATE_3 },

		// BATTLE_ATTRIBUTE_STRANGE
		{ ITEM_UPGRADE_RATE_2, ITEM_UPGRADE_RATE_3, ITEM_UPGRADE_RATE_5, ITEM_UPGRADE_RATE_1, ITEM_UPGRADE_RATE_0, ITEM_UPGRADE_RATE_4 },

		// BATTLE_ATTRIBUTE_WILD
		{ ITEM_UPGRADE_RATE_2, ITEM_UPGRADE_RATE_4, ITEM_UPGRADE_RATE_3, ITEM_UPGRADE_RATE_5, ITEM_UPGRADE_RATE_1, ITEM_UPGRADE_RATE_0 },

		// BATTLE_ATTRIBUTE_ELEGANCE
		{ ITEM_UPGRADE_RATE_2, ITEM_UPGRADE_RATE_0, ITEM_UPGRADE_RATE_4, ITEM_UPGRADE_RATE_3, ITEM_UPGRADE_RATE_5, ITEM_UPGRADE_RATE_1 },

		// BATTLE_ATTRIBUTE_FUNNY
		{ ITEM_UPGRADE_RATE_2, ITEM_UPGRADE_RATE_1, ITEM_UPGRADE_RATE_0, ITEM_UPGRADE_RATE_4, ITEM_UPGRADE_RATE_3, ITEM_UPGRADE_RATE_5 },

	};

	return aByBattleAttributeBonusRate[byItemBattleAttribute][byPosNum];
}
BYTE Dbo_GetHoipoiStoneCount( const BYTE byStoneType, const BYTE byItemType, BYTE byGrade )
{
	// �Ϲ� ȣ������ ����
	const static BYTE byNeedCountBasicWeapon[NTL_ITEM_MAX_GRADE]	= {2,2,2,4,4,4,6,6,6,8,8,8,10,10,10};
	const static BYTE byNeedCountBasicArmor[NTL_ITEM_MAX_GRADE]		= {1,1,1,2,2,2,3,3,3,4,4,4,5, 5, 5};
	// ǻ�� ȣ������ ����
	const static BYTE byNeedCountPureWeapon[NTL_ITEM_MAX_GRADE]		= {2,2,2,4,4,4,6,6,6,8,8,8,10,10,10};
	const static BYTE byNeedCountPureArmor[NTL_ITEM_MAX_GRADE]		= {1,1,1,2,2,2,3,3,3,4,4,4,5, 5, 5};
	// �� ȣ������ ����
	const static BYTE byNeedCountBlackWeapon[NTL_ITEM_MAX_GRADE]	= {2,2,2,2,2,4,4,4,4,4,6,6,6, 6, 6};
	const static BYTE byNeedCountBlackArmor[NTL_ITEM_MAX_GRADE]		= {1,1,1,1,1,2,2,2,2,2,3,3,3, 3, 3};

	// �� ȣ������ ���濡 ���� ó��
	if ( ITEM_TYPE_BLACK_STONE == byStoneType )
	{
		--byGrade;
	}

	// �׷��̵尡 �߸��� ��� �ι븮��.
	if ( byGrade < 0 || byGrade >= NTL_ITEM_MAX_GRADE )
		return INVALID_BYTE;

	if ( ITEM_TYPE_WEAPON_FIRST <= byItemType && ITEM_TYPE_WEAPON_LAST >= byItemType )
	{
		if ( ITEM_TYPE_STONE == byStoneType )		return byNeedCountBasicWeapon[byGrade];
		if ( ITEM_TYPE_PURE_STONE == byStoneType )	return byNeedCountPureWeapon[byGrade];
		if ( ITEM_TYPE_BLACK_STONE == byStoneType ) return byNeedCountBlackWeapon[byGrade];
	}
	else if ( ITEM_TYPE_ARMOR_FIRST <= byItemType && ITEM_TYPE_ARMOR_LAST >= byItemType )
	{
		if ( ITEM_TYPE_STONE == byStoneType )		return byNeedCountBasicArmor[byGrade];
		if ( ITEM_TYPE_PURE_STONE == byStoneType )	return byNeedCountPureArmor[byGrade];
		if ( ITEM_TYPE_BLACK_STONE == byStoneType ) return byNeedCountBlackArmor[byGrade];
	}
	
	// ������� �Դٸ� ������ Ÿ���� �߸��Ǿ��� ������.
	return INVALID_BYTE;
}

DWORD Dbo_GetRepairPay( DWORD dwCost, BYTE byDur, BYTE byCurDur)
{
	float fRate = (float)byCurDur / (float)byDur;
	if ( fRate >= 1.0f )
		return 0;

	DWORD dwRepairCost = (DWORD)( (dwCost - ( dwCost *  fRate)) * 0.9f );

	if( dwRepairCost == 0 )
	{
		dwRepairCost = 1;
	}

	return dwRepairCost;
}

DWORD Dbo_GetHoipoiMixEXP( bool bIsNormalSuccess, bool bIsGreatSuccess, BYTE byMadeLevel, BYTE byNeedMixLevel )
{
	DWORD dwBasic = (10 - ( byMadeLevel - byNeedMixLevel ));
	if ( false == bIsNormalSuccess )
	{
		return dwBasic;
	}
	else
	{
		if ( false == bIsGreatSuccess )
		{
			return dwBasic * 2;
		}
		else
		{
			return dwBasic * 4;
		}
	}
}

DWORD Dbo_GetHoipoiMixNeedLevelExp( BYTE byCurLevel )
{
	return (DWORD)( DBO_HOIPOIMIX_BASIC_EXP + ( byCurLevel * ( DBO_HOIPOIMIX_BASIC_EXP * 0.3 ) ) );
}

BYTE Dbo_GetHoipoiMixNeedLevelForJobSet( const BYTE byRecipeType )
{
	if ( eRECIPE_NORMAL == byRecipeType ) return 10;
	if ( eRECIPE_MAINWEAPON == byRecipeType ) return 15;
	if ( eRECIPE_ARMOR == byRecipeType ) return 15;
	if ( eRECIPE_ACCESSORY == byRecipeType ) return 15;
	if ( eRECIPE_SCOUTER == byRecipeType ) return 15;
	if ( eRECIPE_SUBWEAPON == byRecipeType ) return 15;

	return INVALID_BYTE;
}

DWORD Dbo_GetHoipoiMixNeedZennyForJobSet( const BYTE byRecipeType )
{
	if ( eRECIPE_NORMAL == byRecipeType ) return 1000;
	if ( eRECIPE_MAINWEAPON == byRecipeType ) return 1500;
	if ( eRECIPE_SUBWEAPON == byRecipeType ) return 1500;
	if ( eRECIPE_ARMOR == byRecipeType ) return 2000;
	if ( eRECIPE_ACCESSORY == byRecipeType ) return 2500;
	if ( eRECIPE_SCOUTER == byRecipeType ) return 3000;

	return INVALID_DWORD;
}

// ������ �ͽ� ����
DWORD Dbo_GetHoipoiMixFare( DWORD dwCost, BYTE byDiscountRate /*=0*/ )
{
	return static_cast<DWORD>( dwCost * (1.0f- static_cast<float>(byDiscountRate)/100) );
}

//-----------------------------------------------------------------------------------
// �Ʒ� �Լ��� 
// bool Dbo_SetItemData( sITEM_DATA* const pItemData_Output, sITEM_DATA* const pItemData_Input )
// �� ���� ����: 
// sITEM_DATA�� ����Ÿ�� ����ǰų� �߰��� ���, �۾��ڿ� �Ǽ��� ������ �������� ��� �����̴�. 
// ����붧 �������, �ڵ��� �������~
// �׷���, ����ó�� ���� �������� ����.
//-----------------------------------------------------------------------------------
bool Dbo_SetItemData( sITEM_DATA* const pItemData
					 , ITEMID itemId
					 , TBLIDX itemNo
					 , CHARACTERID charId
					 , BYTE byPlace
					 , BYTE byPosition
					 , BYTE byStackcount
					 , BYTE byRank
					 , BYTE byCurrentDurability
					 , bool bNeedToIdentify
					 , BYTE byGrade
					 , BYTE byBattleAttribute
					 , BYTE byRestrictType
					 , const WCHAR* const awchMaker
					 , TBLIDX* const aOptionTblidx
					 , BYTE byDurationType
					 , DBOTIME nUseStartTime
					 , DBOTIME nUseEndTime )
{
	if( NULL == pItemData )
	{
		return false;
	}

	pItemData->itemId = itemId;
	pItemData->itemNo = itemNo; 
	pItemData->charId = charId;
	pItemData->byPlace = byPlace;
	pItemData->byPosition = byPosition;
	pItemData->byStackcount = byStackcount;
	pItemData->byRank = byRank;
	pItemData->byCurrentDurability = byCurrentDurability;
	pItemData->bNeedToIdentify = bNeedToIdentify;
	pItemData->byGrade = byGrade;
	pItemData->byBattleAttribute = byBattleAttribute;
	pItemData->byRestrictType = byRestrictType;
	pItemData->byDurationType = byDurationType;
	pItemData->nUseStartTime = nUseStartTime;
	pItemData->nUseEndTime = nUseEndTime;

	if( NULL == awchMaker )
	{
		memset( pItemData->awchMaker, 0x00, sizeof(pItemData->awchMaker) );
	}
	else
	{
		memcpy( pItemData->awchMaker, awchMaker, sizeof( pItemData->awchMaker ) );
		(pItemData->awchMaker)[NTL_MAX_SIZE_CHAR_NAME_UNICODE] = L'\0';
	}

	if( NULL == aOptionTblidx )
	{
		memset( pItemData->aOptionTblidx, INVALID_TBLIDX, sizeof( pItemData->aOptionTblidx ) );
	}
	else
	{
		memcpy( pItemData->aOptionTblidx, aOptionTblidx, sizeof( pItemData->aOptionTblidx ) );
	}

	return true;
}

//-----------------------------------------------------------------------------------
// �Ʒ� �Լ��� 
// bool Dbo_SetItemData_NeedToIdentify( sITEM_DATA* const pItemData_Output, sITEM_DATA* const pItemData_Input )
// �� ���� ����: 
// sITEM_DATA�� ����Ÿ�� ����ǰų� �߰��� ���, �۾��ڿ� �Ǽ��� ������ �������� ��� �����̴�. 
// ����붧 �������, �ڵ��� �������~
// �׷���, ����ó�� ���� �������� ����.
//-----------------------------------------------------------------------------------
bool Dbo_SetItemData_CheckNeedToIdentify( sITEM_DATA* const pItemData
					 , ITEMID itemId
					 , TBLIDX itemNo
					 , CHARACTERID charId
					 , BYTE byPlace
					 , BYTE byPosition
					 , BYTE byStackcount
					 , BYTE byRank
					 , BYTE byCurrentDurability
					 , bool bNeedToIdentify
					 , BYTE byGrade
					 , BYTE byBattleAttribute
					 , BYTE byRestrictType
					 , WCHAR* const awchMaker
					 , TBLIDX* const aOptionTblidx
					 , BYTE byDurationType
					 , DBOTIME nUseStartTime
					 , DBOTIME nUseEndTime )
{
	if( NULL == pItemData )
	{
		return false;
	}

	pItemData->itemId = itemId;
	pItemData->charId = charId;
	pItemData->byPlace = byPlace;
	pItemData->byPosition = byPosition;
	pItemData->bNeedToIdentify = bNeedToIdentify;

	if ( true == pItemData->bNeedToIdentify )
	{
		//��Ȯ�� �������� ���
		return true;
	}

	//Ȯ�� �������� ���
	pItemData->itemNo = itemNo; 
	pItemData->byStackcount = byStackcount;
	pItemData->byRank = byRank;
	pItemData->byCurrentDurability = byCurrentDurability;
	pItemData->byGrade = byGrade;
	pItemData->byBattleAttribute = byBattleAttribute;
	pItemData->byRestrictType = byRestrictType;
	pItemData->byDurationType = byDurationType;
	pItemData->nUseStartTime = nUseStartTime;
	pItemData->nUseEndTime = nUseEndTime;

	if( NULL == awchMaker )
	{
		memset( pItemData->awchMaker, 0x00, sizeof(pItemData->awchMaker) );
	}
	else
	{
		memcpy( pItemData->awchMaker, awchMaker, sizeof( pItemData->awchMaker ) );
		(pItemData->awchMaker)[NTL_MAX_SIZE_CHAR_NAME_UNICODE] = L'\0';
	}

	if( NULL == aOptionTblidx )
	{
		memset( pItemData->aOptionTblidx, INVALID_TBLIDX, sizeof( pItemData->aOptionTblidx ) );
	}
	else
	{
		memcpy( pItemData->aOptionTblidx, aOptionTblidx, sizeof( pItemData->aOptionTblidx ) );
	}

	return true;
}


//-----------------------------------------------------------------------------------
// �Ʒ� �Լ��� 
// bool Dbo_SetItemProfile( sITEM_PROFILE* const pItemData_Output, sITEM_PROFILE* const pItemData_Input )
// �� ���� ����: 
// sITEM_PROFILE�� ����Ÿ�� ����ǰų� �߰��� ���, �۾��ڿ� �Ǽ��� ������ �������� ��� �����̴�. 
// ����붧 �������, �ڵ��� �������~
// �׷���, ����ó�� ���� �������� ����.
//-----------------------------------------------------------------------------------
bool Dbo_SetItemProfile( sITEM_PROFILE* const pItemProfile
						, HOBJECT handle
						, TBLIDX tblidx
						, BYTE byPlace
						, BYTE byPos
						, BYTE byStackcount
						, BYTE byRank
						, BYTE byCurDur
						, bool bNeedToIdentify
						, BYTE byGrade
						, BYTE byBattleAttribute
						, BYTE byRestrictType
						, WCHAR* const awchMaker
						, TBLIDX* const aOptionTblidx
						, BYTE byDurationType
						, DBOTIME nUseStartTime
						, DBOTIME nUseEndTime )
{

	if( NULL == pItemProfile )
	{
		return false;
	}

	pItemProfile->handle = handle;
	pItemProfile->byPlace = byPlace;
	pItemProfile->byPos = byPos;
	pItemProfile->bNeedToIdentify = bNeedToIdentify;

	if( true == bNeedToIdentify )
	{
		//��Ȯ�� �������� ���
		return true;
	}

	//Ȯ�� �������� ���
	pItemProfile->tblidx = tblidx;
	pItemProfile->byStackcount = byStackcount;
	pItemProfile->byRank = byRank;
	pItemProfile->byCurDur = byCurDur;
	pItemProfile->byGrade = byGrade;
	pItemProfile->byBattleAttribute = byBattleAttribute;
	pItemProfile->byRestrictType = byRestrictType;
	pItemProfile->byDurationType = byDurationType; 
	pItemProfile->nUseStartTime = nUseStartTime;
	pItemProfile->nUseEndTime = nUseEndTime;

	if( NULL == awchMaker )
	{
		memset( pItemProfile->awchMaker, 0x00, sizeof(pItemProfile->awchMaker) );
	}
	else
	{
		memcpy( pItemProfile->awchMaker, awchMaker, sizeof( pItemProfile->awchMaker ) );
		(pItemProfile->awchMaker)[NTL_MAX_SIZE_CHAR_NAME_UNICODE] = L'\0';
	}

	if( NULL == aOptionTblidx )
	{
		memset( pItemProfile->aOptionTblidx, INVALID_TBLIDX, sizeof( pItemProfile->aOptionTblidx ) );
	}
	else
	{
		memcpy( pItemProfile->aOptionTblidx, aOptionTblidx, sizeof( pItemProfile->aOptionTblidx ) );
	}

	return true;
}

//-----------------------------------------------------------------------------------
// �Ʒ� �Լ��� 
// bool Dbo_SetBankItemProfile( sBANK_PROFILE* const pItemData_Output, sBANK_PROFILE* const pItemData_Input )
// �� ���� ����: 
// sBANK_PROFILE�� ����Ÿ�� ����ǰų� �߰��� ���, �۾��ڿ� �Ǽ��� ������ �������� ��� �����̴�. 
// ����붧 �������, �ڵ��� �������~
// �׷���, ����ó�� ���� �������� ����.
//-----------------------------------------------------------------------------------
/*bool Dbo_SetBankItemProfile( sBANK_PROFILE* const pItemProfile
							, HOBJECT handle
							, TBLIDX tblidx
							, BYTE byPos
							, BYTE byStackcount
							, BYTE byRank
							, BYTE byCurDur
							, bool bNeedToIdentify
							, BYTE byGrade
							, BYTE byBattleAttribute
							, BYTE byRestrictType
							, WCHAR* const awchMaker
							, TBLIDX* const aOptionTblidx
							, BYTE byDurationType
							, DBOTIME nUseStartTime
							, DBOTIME nUseEndTime )
{

	if( NULL == pItemProfile )
	{
		return false;
	}

	pItemProfile->handle = handle;
	pItemProfile->tblidx = tblidx;
	pItemProfile->byPos = byPos;
	pItemProfile->byStackcount = byStackcount;
	pItemProfile->byRank = byRank;
	pItemProfile->byCurDur = byCurDur;
	pItemProfile->bNeedToIdentify = bNeedToIdentify;
	pItemProfile->byGrade = byGrade;
	pItemProfile->byBattleAttribute = byBattleAttribute;
	pItemProfile->byRestrictType = byRestrictType;
	pItemProfile->byDurationType = byDurationType;
	pItemProfile->nUseStartTime = nUseStartTime;
	pItemProfile->nUseEndTime = nUseEndTime;

	if( NULL == awchMaker )
	{
		memset( pItemProfile->awchMaker, 0x00, sizeof(pItemProfile->awchMaker) );
	}
	else
	{
		memcpy( pItemProfile->awchMaker, awchMaker, sizeof( pItemProfile->awchMaker ) );
		(pItemProfile->awchMaker)[NTL_MAX_SIZE_CHAR_NAME_UNICODE] = L'\0';
	}

	if( NULL == aOptionTblidx )
	{
		memset( pItemProfile->aOptionTblidx, INVALID_TBLIDX, sizeof( pItemProfile->aOptionTblidx ) );
	}
	else
	{
		memcpy( pItemProfile->aOptionTblidx, aOptionTblidx, sizeof( pItemProfile->aOptionTblidx ) );
	}

	return true;
}*/

//-----------------------------------------------------------------------------------
// �̳��� ���� �� �������� ������... ( ���̴µ��� �����ϱ� �ٷ���~ )
// �Ʒ� �Լ��� 
// bool Dbo_SetItemBrief( sITEM_BRIEF* const pItemData_Output, sITEM_BRIEF* const pItemData_Input )
// �� ���� ����: 
// sITEM_BRIEF�� ����Ÿ�� ����ǰų� �߰��� ���, �۾��ڿ� �Ǽ��� ������ �������� ��� �����̴�. 
// ����붧 �������, �ڵ��� �������~
// �׷���, ����ó�� ���� �������� ����.
//-----------------------------------------------------------------------------------
bool Dbo_SetItemBrief( sITEM_BRIEF* const pItemBrief
							, TBLIDX tblidx
							, BYTE byRank
							, BYTE byGrade
							, BYTE byBattleAttribute
							, TBLIDX* const aOptionTblidx )
{
	if( NULL == pItemBrief )
	{
		return false;
	}

	pItemBrief->tblidx = tblidx;
	pItemBrief->byRank = byRank;
	pItemBrief->byGrade = byGrade;
	pItemBrief->byBattleAttribute = byBattleAttribute;

	if( NULL == aOptionTblidx )
	{
		memset( pItemBrief->aOptionTblidx, INVALID_TBLIDX, sizeof( pItemBrief->aOptionTblidx ) );
	}
	else
	{
		memcpy( pItemBrief->aOptionTblidx, aOptionTblidx, sizeof( pItemBrief->aOptionTblidx ) );
	}

	return true;
}

//-----------------------------------------------------------------------------------
// �Ʒ� �Լ��� 
// bool Dbo_SetItemBrief( sITEM_BRIEF* const pItemData_Output, sITEM_BRIEF* const pItemData_Input )
// �� ���� ����: 
// sITEM_BRIEF�� ����Ÿ�� ����ǰų� �߰��� ���, �۾��ڿ� �Ǽ��� ������ �������� ��� �����̴�. 
// ����붧 �������, �ڵ��� �������~
// �׷���, ����ó�� ���� �������� ����.
//-----------------------------------------------------------------------------------
bool Dbo_SetShopBuyInven( sSHOP_BUY_INVEN* const pShopBuyInven
						 , BYTE byPlace
						 , BYTE byPos
						 , BYTE byStack
						 , TBLIDX tblItem
						 , BYTE byRank
						 , BYTE byCurrentDurability
						 , BYTE byGrade
						 , BYTE byRestrictType
						 , WCHAR* const awchMaker
						 , TBLIDX* const aOptionTblidx
						 , BYTE byDurationType
						 , DBOTIME nUseStartTime
						 , DBOTIME nUseEndTime )
{
	if( NULL == pShopBuyInven )
	{
		return false;
	}

	pShopBuyInven->byPlace = byPlace;
	pShopBuyInven->byPos = byPos;
	pShopBuyInven->byStack = byStack;
	pShopBuyInven->tblItem = tblItem;
	pShopBuyInven->byRank = byRank;
	pShopBuyInven->byCurrentDurability = byCurrentDurability;
	pShopBuyInven->byGrade = byGrade;
	pShopBuyInven->byRestrictType = byRestrictType;
	pShopBuyInven->byDurationType = byDurationType;
	pShopBuyInven->nUseStartTime = nUseStartTime;
	pShopBuyInven->nUseEndTime = nUseEndTime;

	if( NULL == awchMaker )
	{
		memset( pShopBuyInven->awchMaker, 0x00, sizeof(pShopBuyInven->awchMaker) );
	}
	else
	{
		memcpy( pShopBuyInven->awchMaker, awchMaker, sizeof( pShopBuyInven->awchMaker ) );
		(pShopBuyInven->awchMaker)[NTL_MAX_SIZE_CHAR_NAME_UNICODE] = L'\0';
	}

	if( NULL == aOptionTblidx )
	{
		memset( pShopBuyInven->aOptionTblidx, INVALID_TBLIDX, sizeof( pShopBuyInven->aOptionTblidx ) );
	}
	else
	{
		memcpy( pShopBuyInven->aOptionTblidx, aOptionTblidx, sizeof( pShopBuyInven->aOptionTblidx ) );
	}

	return true;
}

//-----------------------------------------------------------------------------------
// �Ʒ� �Լ��� 
// bool Dbo_SetItemDataToQryData( const sITEM_DATA* const pItemData_Output, const sITEM_DATA* const pItemData_Input )
// �� ���� ����: 
// sITEM_DATA�� ����Ÿ�� ����ǰų� �߰��� ���, �۾��ڿ� �Ǽ��� ������ �������� ��� �����̴�. 
// ����붧 �������, �ڵ��� �������~
// �׷���, ����ó�� ���� �������� ����.
//-----------------------------------------------------------------------------------
bool Dbo_SetItemDataToQryData( const sITEM_DATA& rItemDataOrg
						   , int& itemNo
						   , int& charId
						   , BYTE& byPlace
						   , BYTE& byPosition
						   , BYTE& byStackcount
						   , BYTE& byRank
						   , BYTE& byCurrentDurability
						   , BYTE& byNeedToIdentify
						   , BYTE& byGrade
						   , BYTE& byBattleAttribute
						   , BYTE& byRestrictType
						   , char* pMakerInHex
						   , size_t nMakerInHex_Size
						   , int* aOptionTblidx
						   , size_t nOptionTblidx_Size
						   , BYTE& byDurationType
						   , __int64& nUseStartTime
						   , __int64& nUseEndTime )
{
	//itemId = pItemDataOrg->itemId;
	itemNo = rItemDataOrg.itemNo;
	charId = rItemDataOrg.charId;
	byPlace = rItemDataOrg.byPlace;
	byPosition = rItemDataOrg.byPosition;
	byStackcount = rItemDataOrg.byStackcount;
	byRank = rItemDataOrg.byRank;
	byCurrentDurability = rItemDataOrg.byCurrentDurability;
	byGrade = rItemDataOrg.byGrade;
	byBattleAttribute = rItemDataOrg.byBattleAttribute;
	byRestrictType = rItemDataOrg.byRestrictType;
	byDurationType = rItemDataOrg.byDurationType;
	nUseStartTime = rItemDataOrg.nUseStartTime;
	nUseEndTime = rItemDataOrg.nUseEndTime;
	byNeedToIdentify = ( true == rItemDataOrg.bNeedToIdentify ) ? 1 : 0;

	char achMakerInHex[(NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1) * sizeof(WCHAR) * 2 + 2 + 1];
	WideCharToHex( const_cast< WCHAR* >( rItemDataOrg.awchMaker ), _countof(achMakerInHex), achMakerInHex);
	NTL_SAFE_STRCPY_SIZEINPUT(pMakerInHex, nMakerInHex_Size, achMakerInHex);

	memcpy( aOptionTblidx, rItemDataOrg.aOptionTblidx, nOptionTblidx_Size );

	return true;
}

//-----------------------------------------------------------------------------------
// �Ʒ� �Լ��� 
// bool Dbo_SetItemDataToData( const sITEM_DATA* const pItemData_Output, const sITEM_DATA* const pItemData_Input )
// �� ���� ����: 
// sITEM_DATA�� ����Ÿ�� ����ǰų� �߰��� ���, �۾��ڿ� �Ǽ��� ������ �������� ��� �����̴�. 
// ����붧 �������, �ڵ��� �������~
// �׷���, ����ó�� ���� �������� ����.
//-----------------------------------------------------------------------------------
bool Dbo_SetItemDataToData( const sITEM_DATA& rItemDataOrg
						   , ITEMID& itemId
						   , TBLIDX& itemNo
						   , CHARACTERID& charId
						   , BYTE& byPlace
						   , BYTE& byPosition
						   , BYTE& byStackcount
						   , BYTE& byRank
						   , BYTE& byCurrentDurability
						   , bool& bNeedToIdentify
						   , BYTE& byGrade
						   , BYTE& byBattleAttribute
						   , BYTE& byRestrictType
						   , WCHAR* pMakerInHex
						   , size_t nMakerInHex_Size
						   , TBLIDX* pOptionTblidx
						   , size_t nOptionTblidx_Size
						   , eDURATIONTYPE& eDurationType
						   , DBOTIME& nUseStartTime
						   , DBOTIME& nUseEndTime )
{
	itemId = rItemDataOrg.itemId;
	itemNo = rItemDataOrg.itemNo;
	charId = rItemDataOrg.charId;
	byPlace = rItemDataOrg.byPlace;
	byPosition = rItemDataOrg.byPosition;
	byStackcount = rItemDataOrg.byStackcount;
	byRank = rItemDataOrg.byRank;
	byCurrentDurability = rItemDataOrg.byCurrentDurability;
	byGrade = rItemDataOrg.byGrade;
	byBattleAttribute = rItemDataOrg.byBattleAttribute;
	byRestrictType = rItemDataOrg.byRestrictType;
	eDurationType = eDURATIONTYPE( rItemDataOrg.byDurationType );
	nUseStartTime = rItemDataOrg.nUseStartTime;
	nUseEndTime = rItemDataOrg.nUseEndTime;
	bNeedToIdentify = ( true == rItemDataOrg.bNeedToIdentify ) ? 1 : 0;

	NTL_SAFE_WCSNCPY_SIZEINPUT( pMakerInHex, nMakerInHex_Size, rItemDataOrg.awchMaker, NTL_MAX_SIZE_CHAR_NAME_UNICODE );

	memcpy( pOptionTblidx, rItemDataOrg.aOptionTblidx, nOptionTblidx_Size );

	return true;
}

//-----------------------------------------------------------------------------------
// �Ʒ� �Լ��� 
// bool Dbo_SetAutoEquipItemDataToQryData( const sITEM_AUTO_EQUIP_DATA* const pItemData_Output, const sITEM_AUTO_EQUIP_DATA* const pItemData_Input )
// �� ���� ����: 
// sITEM_AUTO_EQUIP_DATA�� ����Ÿ�� ����ǰų� �߰��� ���, �۾��ڿ� �Ǽ��� ������ �������� ��� �����̴�. 
// ����붧 �������, �ڵ��� �������~
// �׷���, ����ó�� ���� �������� ����.
//-----------------------------------------------------------------------------------
bool Dbo_SetAutoEquipItemDataToQryData( const sITEM_AUTO_EQUIP_DATA& rItemAutoEquipData
						   , int& srcItemId
						   , HOBJECT& hSrcItem
						   , BYTE& bySrcEquipPlace
						   , BYTE& bySrcEquipPos
						   , BYTE& byDestPlace
						   , BYTE& byDestPos
						   , int& itemNo
						   , int& charId
						   , BYTE& byPlace
						   , BYTE& byPosition
						   , BYTE& byStackcount
						   , BYTE& byRank
						   , BYTE& byCurrentDurability
						   , BYTE& byNeedToIdentify
						   , BYTE& byGrade
						   , BYTE& byBattleAttribute
						   , BYTE& byRestrictType
						   , char* pMakerInHex
						   , size_t nMakerInHex_Size
						   , int* aOptionTblidx
						   , size_t nOptionTblidx_Size
						   , BYTE& byDurationType
						   , __int64& nUseStartTime
						   , __int64& nUseEndTime )
{
	srcItemId = rItemAutoEquipData.srcItemId;
	hSrcItem = rItemAutoEquipData.hSrcItem;
	bySrcEquipPlace = rItemAutoEquipData.bySrcEquipPlace;
	bySrcEquipPos = rItemAutoEquipData.bySrcEquipPos;
	byDestPlace = rItemAutoEquipData.byDestPlace;
	byDestPos = rItemAutoEquipData.byDestPos;

	return Dbo_SetItemDataToQryData( rItemAutoEquipData.sEquipItem
		, itemNo
		, charId
		, byPlace
		, byPosition
		, byStackcount
		, byRank
		, byCurrentDurability
		, byNeedToIdentify
		, byGrade
		, byBattleAttribute
		, byRestrictType
		, pMakerInHex
		, nMakerInHex_Size
		, aOptionTblidx
		, nOptionTblidx_Size
		, byDurationType
		, nUseStartTime
		, nUseEndTime );
}

//-----------------------------------------------------------------------------------
// �Ʒ� �Լ��� 
// bool Dbo_SetItemDataToQryData( const sITEM_DATA* const pItemData_Output, const sITEM_DATA* const pItemData_Input )
// �� ���� ����: 
// sITEM_DATA�� ����Ÿ�� ����ǰų� �߰��� ���, �۾��ڿ� �Ǽ��� ������ �������� ��� �����̴�. 
// ����붧 �������, �ڵ��� �������~
// �׷���, ����ó�� ���� �������� ����.
//-----------------------------------------------------------------------------------
bool Dbo_SetShopBuyInvenToQryData( const sSHOP_BUY_INVEN& rShopBuyInven
								  , BYTE& byPlace
								  , BYTE& byPos
								  , BYTE& byStack
								  , int& tblItem
								  , BYTE& byRank
								  , BYTE& byCurrentDurability
								  , BYTE& byGrade
								  , BYTE& byRestrictType
								  , char* pMakerInHex
								  , size_t nMakerInHex_Size
								  , int* aOptionTblidx
								  , size_t nOptionTblidx_Size
								  , BYTE& byDurationType
								  , __int64& nUseStartTime
								  , __int64& nUseEndTime )
{
	byPlace = rShopBuyInven.byPlace;
	byPos = rShopBuyInven.byPos;
	byStack = rShopBuyInven.byStack;
	tblItem = rShopBuyInven.tblItem;
	byRank = rShopBuyInven.byRank;
	byCurrentDurability = rShopBuyInven.byCurrentDurability;
	byGrade = rShopBuyInven.byGrade;
	byRestrictType = rShopBuyInven.byRestrictType;
	byDurationType = rShopBuyInven.byDurationType;
	nUseStartTime = rShopBuyInven.nUseStartTime;
	nUseEndTime = rShopBuyInven.nUseEndTime;

	char achMakerInHex[(NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1) * sizeof(WCHAR) * 2 + 2 + 1];
	WideCharToHex( const_cast< WCHAR* >( rShopBuyInven.awchMaker ), _countof(achMakerInHex), achMakerInHex);
	NTL_SAFE_STRCPY_SIZEINPUT(pMakerInHex, nMakerInHex_Size, achMakerInHex);

	memcpy( aOptionTblidx, rShopBuyInven.aOptionTblidx, nOptionTblidx_Size );
	return true;
}

float Dbo_ItemDestroyRateByUpgradeFail( const BYTE byRank, const BYTE byItemBattleAttribute, const BYTE byStoneBattleAttribute, const float fAddRateByScouter )
{
	// ����ó��
	if ( ITEM_RANK_FIRST >= byRank || ITEM_RANK_LAST < byRank )
	{
		return 0.0f; 
	}
	static const float fRate[NTL_ITEM_MAX_RANK] ={  50.0f, 60.0f, 70.0f, 80.0f, 90.0f, };

	const float retRate = fRate[byRank-1];
	const float fbonus1 = ( 100-Dbo_GetAttributeRate(byItemBattleAttribute, byStoneBattleAttribute) ) * 0.01f;
	const float fbonus2 = ( 100-fAddRateByScouter ) * 0.01f;

	return (retRate * fbonus1 * fbonus2);
}