#include "HackAndSlash.h"
#include "../UdpSocketSender.h"

void MyUdpSocketSender::SendWorldMessage(const char* message, int accountID)
{
	CNtlPacket packet(sizeof(sUCH_SEND_WORLD_MESSAGE));
	sUCH_SEND_WORLD_MESSAGE * req = (sUCH_SEND_WORLD_MESSAGE *)packet.GetPacketData();
	
	memcpy(req->Message, message, strlen(message));
	req->Sender = accountID;
	req->wOpCode = UCH_SEND_WORLD_MESSAGE;
	packet.SetPacketLen(sizeof(sUCH_SEND_WORLD_MESSAGE));

	SendClient(&packet);
}