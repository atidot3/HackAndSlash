#include "stdafx.h"
#include "../../Server/GameServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>

int CClientSession::ParseFriendPacket(CNtlPacket * pPacket)
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();
	switch (pHeader->wOpCode)
	{
		case UF_GROUP_FRIEND_REQ: // REQUEST SOMEONE TO GROUPE WITH YOU
		{
			SendFriendToAddToGroupeRequest(pPacket, app);
		}
		break;
		case UF_GROUP_FRIEND_AWSER_REQ: //SOMEONE RESPONCE FOR THE GROUPE REQUEST
		{
			SendFriendGroupe(pPacket, app);
		}
		break;
		case UF_REQUEST_NEW_FRIEND_REQ:
		{
			SendFriendRequest(pPacket, app);
		}
		break;
		default:
			return CNtlSession::OnDispatch(pPacket);
	}
	return NTL_SUCCESS;
}
