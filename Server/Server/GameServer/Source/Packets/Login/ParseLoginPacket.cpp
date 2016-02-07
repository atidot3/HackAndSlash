#include "stdafx.h"
#include "../../Server/GameServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>

int CClientSession::ParseAuthPacket(CNtlPacket * pPacket)
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();

	switch (pHeader->wOpCode)
	{
		case UA_LOGIN_REQ:
		{
			if (CClientSession::SendCharLogInReq(pPacket, app) == true)
			{
				SendMapList();
				app->GetCharacterManager()->UpdateFriendList();
				sock = g_pApp->GetNetwork()->FindSocket(this->GetHandle());
				SendPopupMessage("Welcome onto the server, have fun by all the team :)");
				SendFriendLogin(app, true);
			}
		}
		break;
		case UA_LOGIN_DISCONNECT_REQ:
		{
			SendFriendLogin(app, false);
			CClientSession::SendLoginDcReq(pPacket);
		}
		break;	
		default:
			return CNtlSession::OnDispatch(pPacket);
	}
	return NTL_SUCCESS;
}
