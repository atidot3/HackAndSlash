#include "CClientSession.h"
#include "../Server/AuthServer.h"

CClientSession::CClientSession(bool bAliveCheck, bool bOpcodeCheck) : CNtlSession(SESSION_CLIENT)
{
	SetControlFlag(CONTROL_FLAG_USE_SEND_QUEUE);
	if (bAliveCheck)
	{
		SetControlFlag(CONTROL_FLAG_CHECK_ALIVE);
	}
	if (bOpcodeCheck)
	{
		SetControlFlag(CONTROL_FLAG_CHECK_OPCODE);
	}
	SetPacketEncoder(&m_packetEncoder);
}
CClientSession::~CClientSession()
{
	//NTL_PRINT(PRINT_APP, FOREGROUND_GREEN, "CClientSession Destructor Called");
}
int							CClientSession::OnAccept()
{
	//NTL_PRINT( PRINT_APP, "%s", __FUNCTION__ );
	return NTL_SUCCESS;
}
void						CClientSession::OnClose()
{
	//NTL_PRINT( PRINT_APP, "%s", __FUNCTION__ );
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
}
int							CClientSession::SendPacket(CNtlPacket * pPacket, int sleepTime)
{
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();
	int header = pHeader->wOpCode;
	int rc = g_pApp->Send(this->GetHandle(), pPacket);
	//std::cout << "Packet sended " << i++ << " size packet: " << pPacket->GetUsedSize() << " Opcode: " << header << endl;
	return rc;
}

int							CClientSession::OnDispatch(CNtlPacket * pPacket)
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();
	if (pHeader->wOpCode >= UA_OPCODE_BEGIN && pHeader->wOpCode <= UA_OPCODE_END)
	{
		ParseAuthPacket(pPacket);
	}
	return NTL_SUCCESS;
}
