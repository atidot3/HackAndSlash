#include "stdafx.h"
#include "../../Server/GameServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>

int CClientSession::ParseGamePacket(CNtlPacket * pPacket)
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();
	switch (pHeader->wOpCode)
	{
		case UG_GAME_ENTER_REQ:
		{
			SendGameEnterReq(pPacket, app);
		}
		break;
		case UG_GAME_ENTER_COMPLETE_REQ:
		{
			SendGameEnterCompleteReq(pPacket, app);
			RefreshMyGroupHUD();
		}
		break;
		case GU_PARTY_MEMBER_MOVE:
		{
			SendCharacterMoveOnMap(pPacket, app);
		}
		break;
		case UG_BACK_TO_MENU_REQ:
		{
			SendBackToMenu(pPacket, app);
		}
		break;
		case UG_MENU_LOADED_REQ:
		{
			SendMapList();
			app->GetCharacterManager()->UpdateFriendList();
			RefreshMyGroupHUD();
		}
		break;
		default:
			return CNtlSession::OnDispatch(pPacket);
	}
	return NTL_SUCCESS;
}
