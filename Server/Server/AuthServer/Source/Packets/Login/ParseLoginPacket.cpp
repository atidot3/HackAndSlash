#include "stdafx.h"
#include "../../Server/AuthServer.h"

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
			std::cout << "UA_LOGIN_REQ" << std::endl;
			CClientSession::SendCharLogInReq(pPacket, app);
		}
		break;
		case UA_LOGIN_DISCONNECT_REQ:
		{
			std::cout << "UA_LOGIN_DISCONNECT_REQ" << std::endl;
			CClientSession::SendLoginDcReq(pPacket);
		}
		break;	
		default:
			return CNtlSession::OnDispatch(pPacket);
	}
	return NTL_SUCCESS;
}
