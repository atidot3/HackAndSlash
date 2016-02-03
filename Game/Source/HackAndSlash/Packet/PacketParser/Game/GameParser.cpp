#include "HackAndSlash.h"
#include "HackAndSlashPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"

void AHackAndSlashPlayerController::RecvSpawnPartyMember(CNtlPacket *pPacket)
{
	sGU_PARTY_MEMBER_SPAWN * res = (sGU_PARTY_MEMBER_SPAWN*)pPacket->GetPacketData();
	FSpawnFriendParty partyMember;

	if (res->count > 0)
	{
		for (int i = 0; i < res->count; i++)
		{
			partyMember.location.X = res->group[i].location.x;
			partyMember.location.Y = res->group[i].location.y;
			partyMember.location.Z = res->group[i].location.z;
			partyMember.charID = res->group[i].charId;
			partyMember.level = res->group[i].level;
			partyMember.name = FString(ANSI_TO_TCHAR(res->group[i].name));
			SpawnPlayerParty(partyMember);
		}
	}
}
void AHackAndSlashPlayerController::RefreshMaps()
{
	OnMapsListRecv(HackAndSlash::instance->maps);
}
void AHackAndSlashPlayerController::RecvMapsList(CNtlPacket *pPacket)
{
	sGU_LOAD_MAPS * res = (sGU_LOAD_MAPS *)pPacket->GetPacketData();
	
	for (int i = 0; i < res->byCount && res != NULL; i++)
	{
		FMaps map;
		map.id = res->map[i].id;
		map.name = FString(ANSI_TO_TCHAR(res->map[i].name));
		HackAndSlash::instance->maps.Add(map);
	}
	OnMapsListRecv(HackAndSlash::instance->maps);
}
void AHackAndSlashPlayerController::RecvSpawnPartyMemberMovement(CNtlPacket *pPacket)
{
	sGU_PARTY_MEMBER_MOVE * res = (sGU_PARTY_MEMBER_MOVE *)pPacket->GetPacketData();

	FVector location;

	location.X = res->location.x;
	location.Y = res->location.y;
	location.Z = res->location.z;
	int32 charID = res->charID;
	MovePlayerParty(location, charID);
}
void AHackAndSlashPlayerController::RecvPartyMemberLogout(CNtlPacket *pPacket)
{
	sGU_PARTY_MEMBER_LOGOUT * res = (sGU_PARTY_MEMBER_LOGOUT *)pPacket->GetPacketData();

	RemovePlayerParty(res->charID);
}
void AHackAndSlashPlayerController::RecvPartySwitchMap(CNtlPacket *pPacket)
{
	/*if (pk == nullptr)
		return;
	GU_PARTY_SWITCH_MAP_RES *res = new GU_PARTY_SWITCH_MAP_RES;
	memcpy(res, pk->pk, sizeof(GU_PARTY_SWITCH_MAP_RES));

	RemovePlayerParty(res->charID);*/
}
void AHackAndSlashPlayerController::RecvEnterGameRes(CNtlPacket *pPacket)
{
	sGU_ENTER_GAME_RES * res = (sGU_ENTER_GAME_RES *)pPacket->GetPacketData();
	if (res->wResultCode == GAME_SUCCESS)
	{
		isSessionRunning = true;
		FString name = FString(ANSI_TO_TCHAR(res->mapName));
		OnEnterGameRes(true, name);
	}
	else
	{
		OnPopupMessageRes(FString(ANSI_TO_TCHAR("Leader groupe didn't start the game yet.")));
	}
}
void AHackAndSlashPlayerController::RecvPopupMessage(CNtlPacket *pPacket)
{
	sGU_POPUP_MESSAGE * res = (sGU_POPUP_MESSAGE *)pPacket->GetPacketData();

	char msg[256] = "";
	strcpy_s(msg, 256, (char*)res->theMessage);
	FString message = FString(ANSI_TO_TCHAR(msg));
	OnPopupMessageRes(message);
}