#include "HackAndSlash.h"
#include "HackAndSlashPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"

void AHackAndSlashPlayerController::RecvInvitForGroup(CNtlPacket * pPacket)
{
	sFU_ADD_FRIEND_GROUPE_RES * res = (sFU_ADD_FRIEND_GROUPE_RES *)pPacket->GetPacketData();
	
	FString name = FString(ANSI_TO_TCHAR(res->name));
	this->OnGroupeInviteRecv((int32)res->friendAccountID, name);
}
void AHackAndSlashPlayerController::RecvFriendList(CNtlPacket * pPacket)
{
	sFU_FRIENDLIST_RES * res = (sFU_FRIENDLIST_RES *)pPacket->GetPacketData();
	TArray<FFriend> TheList;
	int i = res->totalFriend;
	int j = 0;
	while (j < i && res != NULL)
	{
		FFriend fr;
		fr.Class = 0;
		fr.Level = 0;
		fr.Online = res->friends[j].online;
		fr.name = FString(ANSI_TO_TCHAR(res->friends[j].name));
		fr.AccountID = res->friends[j].accountID;
		TheList.Add(fr);
		j++;
	}
	if (TheList.Num() > 0)
	{
		HackAndSlash::instance->TheList = TheList;
		FriendListResult(TheList);
	}
}
void AHackAndSlashPlayerController::RecvRefreshGroup(CNtlPacket * pPacket)
{
	sGRU_REFRESH_GROUPE_RES * res = (sGRU_REFRESH_GROUPE_RES *)pPacket->GetPacketData();
	
	TArray<FRefreshFriend> TheList;
	int i = res->size;
	if (i > 1)
	{
		int j = 0;
		while (j < i && i > 0)
		{
			if (res->groupePlayers[j].accountID == HackAndSlash::instance->AccountID)
			{
				FRefreshFriend fr;
				fr.charID = res->groupePlayers[j].charID;
				fr.leader = res->groupePlayers[j].leader;
				isLeader = fr.leader;
				isGrouped = true;
				fr.classe = res->groupePlayers[j].classe;
				fr.level = res->groupePlayers[j].level;
				fr.life = res->groupePlayers[j].life;
				fr.disconnected = res->groupePlayers[j].disconnected;
				fr.name = FString(ANSI_TO_TCHAR(res->groupePlayers[j].name));
				TheList.Add(fr);
			}
			j++;
		}
		j = 0;
		while (j < i && i > 0)
		{
			if (res->groupePlayers[j].accountID != HackAndSlash::instance->AccountID)
			{
				FRefreshFriend fr;
				fr.charID = res->groupePlayers[j].charID;
				fr.leader = res->groupePlayers[j].leader;
				fr.classe = res->groupePlayers[j].classe;
				fr.level = res->groupePlayers[j].level;
				fr.life = res->groupePlayers[j].life;
				fr.disconnected = res->groupePlayers[j].disconnected;
				fr.name = FString(ANSI_TO_TCHAR(res->groupePlayers[j].name));
				TheList.Add(fr);
			}
			j++;
		}
		if (TheList.Num() > 1)
		{
			OnRefreshGroupRecv(TheList);
			return;
		}
	}
	isGrouped = false;
	isLeader = false;
}
void AHackAndSlashPlayerController::RecvFriendNotification(CNtlPacket * pPacket)
{
	sFU_FRIEND_NOTIFICATION_RES * res = (sFU_FRIEND_NOTIFICATION_RES *)pPacket->GetPacketData();

	if (res->wResultCode == GAME_SUCCESS)
	{
		FString name = FString(ANSI_TO_TCHAR(res->friends.name));
		FriendNotificationResult(res->friends.online, name);
		if (res->friends.online == false)
		{
			int len = HackAndSlash::instance->TheList.Num();
			if (len > 0)
			{
				for (int i = 0; i < len; i++)
				{
					if (HackAndSlash::instance->TheList[i].AccountID == res->friends.accountID)
					{
						HackAndSlash::instance->TheList[i].Online = false;
						FriendListResult(HackAndSlash::instance->TheList);
						break;
					}
				}
			}
		}
	}
}