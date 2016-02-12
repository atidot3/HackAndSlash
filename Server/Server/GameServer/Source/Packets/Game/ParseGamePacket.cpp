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
		case UG_GAME_LOGIN_REQ:
		{
			if (OnGameLogin(pPacket) == true)
			{
				Sleep(100);
				SendMapList();
				Sleep(100);
				app->GetCharacterManager()->UpdateFriendList();
				Sleep(100);
				sock = g_pApp->GetNetwork()->FindSocket(this->GetHandle());
				Sleep(100);
				SendPopupMessage("Welcome onto the server, have fun by all the team :)");
				Sleep(100);
				SendFriendLogin(app, true);
			}
		}
		break;
		case UG_GAME_ENTER_REQ:
		{
			SendGameEnterReq(pPacket, app);
		}
		break;
		case UG_GAME_ENTER_COMPLETE_REQ:
		{
			SendGameEnterCompleteReq(pPacket, app);
			RefreshMyGroupHUD();
			
			CNtlPacket packet(sizeof(sGU_ENTER_GAME_COMPLETE_RES));
			sGU_ENTER_GAME_COMPLETE_RES * res = (sGU_ENTER_GAME_COMPLETE_RES *)packet.GetPacketData();
			res->GUID = me->getPlayer()->getGUID();
			res->wOpCode = GU_ENTER_GAME_COMPLETE_RES;
			packet.SetPacketLen(sizeof(sGU_ENTER_GAME_COMPLETE_RES));
			SendPacket(&packet);
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
