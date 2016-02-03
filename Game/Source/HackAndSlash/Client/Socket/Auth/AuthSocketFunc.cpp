#include "HackAndSlash.h"
#include "../UdpSocketSender.h"

bool MyUdpSocketSender::Login(const char* user, const char* password)
{
	CNtlPacket packet(sizeof(sUA_LOGIN_REQ));
	sUA_LOGIN_REQ * res = (sUA_LOGIN_REQ *)packet.GetPacketData();

	res->wOpCode = UA_LOGIN_REQ;
	memcpy(res->awchUserId, user, strlen(user));
	memcpy(res->awchPasswd, password, strlen(password));
	packet.SetPacketLen(sizeof(sUA_LOGIN_REQ));
	
	return SendClient(&packet);
}
void MyUdpSocketSender::Logout()
{
	if (connected == true)
	{
		CNtlPacket packet(sizeof(sUA_LOGIN_DISCONNECT_REQ));
		sUA_LOGIN_DISCONNECT_REQ * req = (sUA_LOGIN_DISCONNECT_REQ *)packet.GetPacketData();

		req->wOpCode = UA_LOGIN_DISCONNECT_REQ;

		packet.SetPacketLen(sizeof(sUA_LOGIN_DISCONNECT_REQ));
		SendClient(&packet);
		runnable = false;
		connected = false;
		m_pNetwork->Disconnect(sock);
	}
	//client->Close();
	//ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(client);
}
void MyUdpSocketSender::SendGroupInvit(int AccountIDToAdd)
{
	CNtlPacket packet(sizeof(sUF_GROUP_FRIEND_REQ));
	sUF_GROUP_FRIEND_REQ * req = (sUF_GROUP_FRIEND_REQ *)packet.GetPacketData();

	req->friendAccountID = AccountIDToAdd;
	req->wOpCode = UF_GROUP_FRIEND_REQ;

	packet.SetPacketLen(sizeof(sUF_GROUP_FRIEND_REQ));
	SendClient(&packet);
}
void MyUdpSocketSender::AcceptGroupInvit(int AccountIDToAdd, bool accept)
{
	CNtlPacket packet(sizeof(sUF_GROUP_FRIEND_AWSER_REQ));
	sUF_GROUP_FRIEND_AWSER_REQ * req = (sUF_GROUP_FRIEND_AWSER_REQ *)packet.GetPacketData();

	req->accept = accept;
	req->wOpCode = UF_GROUP_FRIEND_AWSER_REQ;
	req->friendAccountID = AccountIDToAdd;

	packet.SetPacketLen(sizeof(sUF_GROUP_FRIEND_AWSER_REQ));
	SendClient(&packet);
}