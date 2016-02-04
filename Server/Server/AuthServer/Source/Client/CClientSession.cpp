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
	NTL_PRINT(PRINT_APP, FOREGROUND_GREEN, "CClientSession Destructor Called");
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
void						CClientSession::Update(DWORD diff)
{
	if (!isInWorld())
		return;
	//std::cout << "client: " << me->getAccountID() << " with name: " << me->getAccountName() << " Updating" << std::endl;
	//std::cout << diff << std::endl;
}
bool						CClientSession::isInWorld()
{
	if (me != NULL)
	{
		if (me->getPlayer() != NULL)
		{
			if (ClientStatut::GAME == me->getStatut())
			{
				return true;
			}
		}
	}
	return false;
}
void						CClientSession::sendToAllPacket(CNtlPacket * pPacket, int accid)
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();

	app->GetCharacterManager()->sendToAll(pPacket, accid);
}
CharacterManager			*CAuthServer::GetCharacterManager()
{
	return Charmanager;
}
int							CClientSession::OnDispatch(CNtlPacket * pPacket)
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();
	if (pHeader->wOpCode >= UA_OPCODE_BEGIN && pHeader->wOpCode <= UA_OPCODE_END)
	{
		ParseAuthPacket(pPacket);
	}
	else if (pHeader->wOpCode >= UF_OPCODE_BEGIN && pHeader->wOpCode <= UF_OPCODE_END)
	{
		ParseFriendPacket(pPacket);
	}
	else if (pHeader->wOpCode >= UG_OPCODE_BEGIN && pHeader->wOpCode <= UG_OPCODE_END || pHeader->wOpCode == GU_PARTY_MEMBER_MOVE)
	{
		ParseGamePacket(pPacket);
	}
	else if (pHeader->wOpCode >= UGR_OPCODE_BEGIN && pHeader->wOpCode <= UGR_OPCODE_END)
	{
		ParseGroupePacket(pPacket);
	}
	else if (pHeader->wOpCode >= UCH_OPCODE_BEGIN && pHeader->wOpCode <= UCH_OPCODE_END)
	{
		ParseChatPacket(pPacket);
	}
	return NTL_SUCCESS;
}
