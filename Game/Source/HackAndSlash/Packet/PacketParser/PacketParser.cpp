#include "HackAndSlash.h"
#include "HackAndSlashPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"

void AHackAndSlashPlayerController::parseMyPacket(CNtlPacket *pPacket)
{
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();
	switch (pHeader->wOpCode)
	{
	case GU_PARTY_MEMBER_MOVE:
	{
		RecvSpawnPartyMemberMovement(pPacket);
		break;
	}
	case AU_LOGIN_RES:
	{
		this->Login(pPacket);
		break;
	}
	case FU_FRIENDLIST_RES:
	{
		RecvFriendList(pPacket);
		break;
	}
	case FU_ADD_FRIEND_GROUPE_RES:
	{
		RecvInvitForGroup(pPacket);
		break;
	}
	case GRU_REFRESH_GROUPE_RES:
	{
		RecvRefreshGroup(pPacket);
		break;
	}
	case GRU_DISBAND_GROUPE_RES:
	{
		isLeader = false;
		isGrouped = false;
		OnRemoveGroupRecv();
		break;
	}
	case GU_LOAD_MAPS:
	{
		RecvMapsList(pPacket);
		break;
	}
	case GU_ENTER_GAME_RES:
	{
		RecvEnterGameRes(pPacket);
		break;
	}
	case GU_PARTY_MEMBER_SPAWN:
	{
		RecvSpawnPartyMember(pPacket);
		break;
	}
	case GU_PARTY_MEMBER_LOGOUT:
	{
		RecvPartyMemberLogout(pPacket);
		break;
	}
	case GU_POPUP_MESSAGE:
	{
		RecvPopupMessage(pPacket);
		break;
	}
	case FU_FRIEND_NOTIFICATION_RES:
	{
		RecvFriendNotification(pPacket);
		break;
	}
	/*case CU_CHARACTER_LOAD_RES:
	{
	RecvCharacterLoad(pk);
	break;
	}
	case GU_PARTY_SWITCH_MAP:
	{
	RecvPartySwitchMap(pk);
	break;
	}
	case AU_GROUP_FRIEND_REFUSE_RES:
	{
	break;
	}*/
	}
}