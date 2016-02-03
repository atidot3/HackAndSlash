#include "HackAndSlash.h"
//#include "NtlGeneralInclude.h"
#include "NtlNetSender.h"
#include "NtlClientNet.h"

NotifyNetSendPacketFunc CNtlNetSender::m_fnSendPacket = NULL;

CNtlNetSender::CNtlNetSender()
{
	m_hSocketId = INVALID_HSERVER;
	m_pNet = NULL;
}

void CNtlNetSender::CallNotifySendPacket(void *pData)
{
	if(m_fnSendPacket)
		(*m_fnSendPacket)(pData);
}

void CNtlNetSender::SetData(HSERVER hSocketId, CNtlClientNet *pNet)
{
	m_hSocketId = hSocketId;
	m_pNet = pNet;
}

bool CNtlNetSender::SendPacket(RwInt32 iDataLen, void *pData)
{
	if (m_pNet == NULL || m_hSocketId == INVALID_HSERVER)
	{
		std::cout << "m_pNet == NULL || m_hSocketId == INVALID_HSERVER" << std::endl;
		return 0;
	}
    bool bError = m_pNet->PushPacket(m_hSocketId, pData, iDataLen); 

	if(!bError)
	{
		std::cout << "!bError" << std::endl;
		m_pNet = NULL;
		m_hSocketId = INVALID_HSERVER;
	}

	return bError;
}

HSERVER CNtlNetSender::GetSocketHandle()
{
	return m_hSocketId;
}

void CNtlNetSender::LinkNotifySendPacketFunc(NotifyNetSendPacketFunc fnSendPacket)
{
	m_fnSendPacket = fnSendPacket;
}

void CNtlNetSender::UnLinkNotifySendPacket(void)
{
	m_fnSendPacket = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

NtlVirtualNetSenderFunc CNtlVirtualNetSender::m_fnNetCallback;

CNtlVirtualNetSender::CNtlVirtualNetSender()
{
}

void CNtlVirtualNetSender::SetVirtualNetSenderFunction(NtlVirtualNetSenderFunc fnNetCallback)
{
	m_fnNetCallback = fnNetCallback;
}

bool CNtlVirtualNetSender::SendPacket(RwInt32 iDataLen, void *pData)
{
	CallNotifySendPacket(pData);

	if(m_fnNetCallback)
	{
		return (*m_fnNetCallback)(iDataLen, pData);
	}

	return true;
}
