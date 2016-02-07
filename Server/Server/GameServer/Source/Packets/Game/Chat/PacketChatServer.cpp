#include "stdafx.h"
#include "../../../Server/GameServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../../../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>
//--------------------------------------------------------------------------------------//
//		Send Chat World Message
//--------------------------------------------------------------------------------------//
void			CClientSession::SendWorldMessage(CNtlPacket *pPacket, CAuthServer * app)
{
	CNtlPacket packet(sizeof(sCHU_SEND_WORLD_MESSAGE_RES));
	sCHU_SEND_WORLD_MESSAGE_RES * res = (sCHU_SEND_WORLD_MESSAGE_RES *)packet.GetPacketData();
	sUCH_SEND_WORLD_MESSAGE * req = (sUCH_SEND_WORLD_MESSAGE *)pPacket->GetPacketData();
	
	if (req->Sender == me->getAccountID())
	{
		memcpy(res->Message, req->Message, NTL_MAX_LENGTH_OF_CHAT_MESSAGE);
		memcpy(res->Sender, me->getAccountName().c_str(), NTL_MAX_SIZE_USERID);
		
		res->wOpCode = CHU_SEND_WORLD_MESSAGE_RES;

		packet.SetPacketLen(sizeof(sCHU_SEND_WORLD_MESSAGE_RES));
		sendToAllPacket(&packet, me->getAccountID());
	}
}