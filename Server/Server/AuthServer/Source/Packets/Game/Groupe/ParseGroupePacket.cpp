#include "stdafx.h"
#include "../../../Server/AuthServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../../../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>

int CClientSession::ParseGroupePacket(CNtlPacket * pPacket)
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();
	switch (pHeader->wOpCode)
	{
		case 0:
		{

		}
		break;
		default:
			return CNtlSession::OnDispatch(pPacket);
	}
	return NTL_SUCCESS;
}
