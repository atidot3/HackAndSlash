#include "HackAndSlash.h"
#include "UdpSocketSender.h"

MyUdpSocketSender::MyUdpSocketSender()
{
	connected = false;
}
MyUdpSocketSender::~MyUdpSocketSender()
{
	m_recvQueue.Clear();
	m_recvQueue.Destroy();
	runnable = false;
	closesocket(sock);
	WSACleanup();
}
int MyUdpSocketSender::getPacketLen(BYTE* pHeaderPointer)
{
	PACKETHEADER* pHeader = (PACKETHEADER*)pHeaderPointer;
	return pHeader->wPacketLen;
}
void MyUdpSocketSender::popPacket(CNtlPacket * pPacket, BYTE * buffer)
{
	int nPacketLen = getPacketLen(buffer);

	pPacket->AttachData(buffer, (WORD)(PACKET_HEADSIZE + nPacketLen));
}
void MyUdpSocketSender::Tick()
{
}
bool MyUdpSocketSender::Init()
{
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
	{
		UE_LOG(LogInit, Log, TEXT("WSAStartup init error"));
		return false;
	}
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		UE_LOG(LogInit, Log, TEXT("sock init error"));
		return false;
	}
	sin.sin_addr.s_addr = inet_addr("88.190.215.114");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(12345);

	m_pNetwork = new CNtlClientNet();
	m_NetSender = new CNtlNetSender();

	if (!m_pNetwork->Create())
	{
		UE_LOG(LogInit, Log, TEXT("Fail create client network"));
		return false;
	}
	return true;
}
void MyUdpSocketSender::RecvData(MyUdpSocketSender* sess)
{
	while (sess->runnable != false)
	{
		CNtlPacket* ptr = (CNtlPacket*)m_pNetwork->PeekPacket(sess->sock);
		if (ptr != NULL)
		{
			m_recvQueue.PushPacket(new CNtlPacket(ptr->GetPacketData(), ptr->GetUsedSize()));
			FGraphEventRef Task = FFunctionGraphTask::CreateAndDispatchWhenReady([&]()
			{
				ParsePacket(m_recvQueue.PopPacket());
			}, TStatId(), NULL, ENamedThreads::GameThread);
			FGraphEventRef Task1 = FFunctionGraphTask::CreateAndDispatchWhenReady([&]()
			{
				HackAndSlash::instance->MyTick();
			}, TStatId(), NULL, ENamedThreads::GameThread);
			m_pNetwork->PopPacket(sess->sock);
		}
	}
}
void MyUdpSocketSender::ParsePacket(CNtlPacket* pPacket)
{
	HackAndSlash::instance->QueuePacket(pPacket);
	//ThePC->parseMyPacket(pPacket);
}
unsigned long MyUdpSocketSender::PreUpdate(MyUdpSocketSender* sess)
{
	RecvData(sess);
	return 0;
}
bool MyUdpSocketSender::Connect()
{
	if (connected == false)
	{
		if ((m_pNetwork->Connect("88.190.215.114", 12345, &sock, false, eNETCLIENT_ENCODE_TYPE::NETCLIENT_ENCODE_NONE)) == false)
		{
			UE_LOG(LogInit, Log, TEXT("Fail to connect"));
			connected = false;
		}
		else
		{
			m_NetSender->SetData(sock, m_pNetwork);
			runnable = true;
			hProcessThread = CreateThread(NULL, 0, &MyUdpSocketSender::StaticThreadStart, this, 0, 0);
			connected = true;
		}
	}
	return connected;
}
bool MyUdpSocketSender::SendClient(CNtlPacket * pPacket)
{
	if (m_pNetwork != NULL && m_pNetwork != nullptr)
	{
		bool pushPacket = m_pNetwork->PushPacket(m_NetSender->GetSocketHandle(), pPacket->GetPacketData(), pPacket->GetPacketLen());
		if (pushPacket == true)
			return m_pNetwork->NetMsgProc(0, FD_WRITE);
	}
	return false;
}
