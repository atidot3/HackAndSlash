#include "HackAndSlash.h"
#include "../UdpSocketSender.h"

void MyUdpSocketSender::SendEnterWorldReq(int32 mapID, int32 charID, Difficulty diff)
{
	CNtlPacket packet(sizeof(sUG_GAME_ENTER_REQ));
	sUG_GAME_ENTER_REQ * req = (sUG_GAME_ENTER_REQ *)packet.GetPacketData();
	
	req->charID = charID;
	req->d = diff;
	req->mapID = mapID;
	req->wOpCode = UG_GAME_ENTER_REQ;

	packet.SetPacketLen(sizeof(sUG_GAME_ENTER_REQ));
	SendClient(&packet);
}
void MyUdpSocketSender::SendEnterGameComplete(NtlVector location, int32 mapID)
{
	CNtlPacket packet(sizeof(sUG_GAME_ENTER_COMPLETE_REQ));
	sUG_GAME_ENTER_COMPLETE_REQ * req = (sUG_GAME_ENTER_COMPLETE_REQ *)packet.GetPacketData();
	
	req->mapID = mapID;
	req->postion = location;
	req->wOpCode = UG_GAME_ENTER_COMPLETE_REQ;

	packet.SetPacketLen(sizeof(sUG_GAME_ENTER_COMPLETE_REQ));
	SendClient(&packet);
}

void MyUdpSocketSender::SendMovement(NtlVector location, int32 mapID)
{
	CNtlPacket packet(sizeof(sGU_PARTY_MEMBER_MOVE));
	sGU_PARTY_MEMBER_MOVE * req = (sGU_PARTY_MEMBER_MOVE *)packet.GetPacketData();
	
	req->charID = HackAndSlash::instance->AccountID;
	req->location = location;
	req->mapID = mapID;
	req->wOpCode = GU_PARTY_MEMBER_MOVE;
	packet.SetPacketLen(sizeof(sGU_PARTY_MEMBER_MOVE));
	SendClient(&packet);
}
void MyUdpSocketSender::BackToMenu()
{
	CNtlPacket packet(sizeof(sUG_BACK_TO_MENU_REQ));
	sUG_BACK_TO_MENU_REQ * req = (sUG_BACK_TO_MENU_REQ *)packet.GetPacketData();

	req->wOpCode = UG_BACK_TO_MENU_REQ;

	packet.SetPacketLen(sizeof(sUG_BACK_TO_MENU_REQ));
	SendClient(&packet);
}
void MyUdpSocketSender::MenuLoaded()
{
	CNtlPacket packet(sizeof(sUG_MENU_LOADED_REQ));
	sUG_MENU_LOADED_REQ * req = (sUG_MENU_LOADED_REQ *)packet.GetPacketData();

	req->wOpCode = UG_MENU_LOADED_REQ;

	packet.SetPacketLen(sizeof(sUG_MENU_LOADED_REQ));
	SendClient(&packet);
}
void MyUdpSocketSender::SendMapID(int mapID)
{
/*	NtlPAcket *pk = new NtlPAcket;
	UG_GAME_SET_MAP_ID req;
	pk->enume = UG_GAME_MAP_SET_ID_REQ;

	req.accid = accid;
	strcpy(req.AUTH_KEY, token);
	req.mapID = mapID;

	memcpy((char*)pk->pk, (char*)&req, sizeof(NtlPAcket));
	//uint8 *Data = (uint8*)pk;
	SendClient(pk, sizeof(NtlPAcket));*/
}
void MyUdpSocketSender::SwitchMap(int charID)
{
	/*NtlPAcket *pk = new NtlPAcket;
	UG_SWITCH_MAP req;
	pk->enume = UG_SWITCH_MAP_REQ;

	req.accid = accid;
	strcpy(req.AUTH_KEY, token);
	req.charID = charID;
	memcpy((char*)pk->pk, (char*)&req, sizeof(NtlPAcket));
	//uint8 *Data = (uint8*)pk;
	SendClient(pk, sizeof(NtlPAcket));*/
}