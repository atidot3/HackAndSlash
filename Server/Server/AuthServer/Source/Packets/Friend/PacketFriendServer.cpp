#include "stdafx.h"
#include "../../Server/AuthServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>

void	CClientSession::SendFriendList()
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	CNtlPacket packet(sizeof(sFU_FRIENDLIST_RES));
	sFU_FRIENDLIST_RES * res = (sFU_FRIENDLIST_RES *)packet.GetPacketData();

	res->wOpCode = FU_FRIENDLIST_RES;
	res->totalFriend = 0;
	app->db->prepare("SELECT * FROM friendlist where account = ?");
	app->db->setString(1, this->me->getAccountName().c_str());
	app->db->execute();
	if ((app->db->rowsCount()) != 0)
	{
		int yolo = app->db->rowsCount();
		int i = 0;
		while (i < yolo)
		{
			app->db->fetch();
			std::string name = app->db->getString("friend");
			strcpy(res->friends[i].name, name.c_str());
			res->totalFriend++;
			res->friends[i].online = false;
			if (app->GetCharacterManager()->FindUser(name.c_str()) == true)
			{
				res->friends[i].online = true;
				CClientSession *other = app->GetCharacterManager()->GetPlayerByName(name.c_str());
				if (other != NULL)
				{
					if (other->me != NULL)
					{
						res->friends[i].accountID = other->me->getAccountID();
					}
				}
			}
			i++;
		}
	}
	packet.SetPacketLen(sizeof(sFU_FRIENDLIST_RES));
	SendPacket(&packet);
	app->db->closeStatm();
}
void	CClientSession::SendFriendLogin(CAuthServer * app, bool online)
{
	if (me == NULL)
		return;
	CNtlPacket packet(sizeof(sFU_FRIEND_NOTIFICATION_RES));
	sFU_FRIEND_NOTIFICATION_RES * res = (sFU_FRIEND_NOTIFICATION_RES *)packet.GetPacketData();

	res->wOpCode = FU_FRIEND_NOTIFICATION_RES;
	res->friends.accountID = me->getAccountID();
	strcpy(res->friends.name, me->getAccountName().c_str());
	res->friends.online = online;
	res->wResultCode = GAME_SUCCESS;

	packet.SetPacketLen(sizeof(sFU_FRIEND_NOTIFICATION_RES));

	app->db->prepare("SELECT * FROM friendlist where account = ?");
	app->db->setString(1, this->me->getAccountName().c_str());
	app->db->execute();
	if ((app->db->rowsCount()) != 0)
	{
		int yolo = app->db->rowsCount();
		int i = 0;
		while (i < yolo)
		{
			if (app->db->fetch() == true)
			{
				std::string name = app->db->getString("friend");
				CClientSession * plr = app->GetCharacterManager()->GetPlayerByName(name.c_str());
				if (plr != NULL)
				{
					app->GetCharacterManager()->SendToPlayerIfExist(name.c_str(), &packet);
					if (online == true)
						plr->SendFriendList();
				}
			}
			i++;
		}
	}
}
void	CClientSession::SendFriendToAddToGroupeRequest(CNtlPacket *pPacket, CAuthServer * app)
{
	sUF_GROUP_FRIEND_REQ * req = (sUF_GROUP_FRIEND_REQ *)pPacket->GetPacketData();
	CClientSession *other = app->GetCharacterManager()->GetPlayerByAccount(req->friendAccountID);
	if (other != NULL)
	{
		bool caninvite = false;
		if (other->me->getIsGrouped() == false && other->me->getIPendingInvitation() == false)
		{
			if ((me->getIsLead() == true && me->getIsGrouped() == true) || (me->getIsGrouped() == false && me->getIPendingInvitation() == false))
			{
				caninvite = true;
			}
			else
			{
				caninvite = false;
			}
		}
		if (caninvite == true)
		{
			other->me->setIPendingInvitation(true);
			me->setIPendingInvitation(true);
			CNtlPacket packet(sizeof(sFU_ADD_FRIEND_GROUPE_RES));
			sFU_ADD_FRIEND_GROUPE_RES * res = (sFU_ADD_FRIEND_GROUPE_RES *)packet.GetPacketData();
			res->friendAccountID = me->getAccountID();
			strcpy(res->name, me->getAccountName().c_str());
			res->wOpCode = FU_ADD_FRIEND_GROUPE_RES;
			packet.SetPacketLen(sizeof(sFU_ADD_FRIEND_GROUPE_RES));
			other->SendPacket(&packet); // SEND TO THE PLAYER THE GROUPE REQUEST
		}
	}
}
void	CClientSession::SendFriendGroupe(CNtlPacket *pPacket, CAuthServer * app)//SOMEONE RESPONCE FOR THE GROUPE REQUEST
{
	sUF_GROUP_FRIEND_AWSER_REQ * req = (sUF_GROUP_FRIEND_AWSER_REQ *)pPacket->GetPacketData();
	CClientSession *other = app->GetCharacterManager()->GetPlayerByAccount(req->friendAccountID);

	if (other == NULL)
	{
		me->setIPendingInvitation(false);
		return;
	}
	if (req->accept == true)
	{
		if (other->me->getIsGrouped() == true) // Player who send invit is grouped so add the current player to the other group
		{
			other->me->setIPendingInvitation(false);
			me->setIPendingInvitation(false);
			me->setIsGrouped(true);
			other->me->getGroup()->AddMember(me);
		}
		else if (other->me->getIsGrouped() == false) // not grouped at all create new party
		{
			other->me->setIsLead(true);
			other->me->setIsGrouped(true);
			other->me->setIPendingInvitation(false);
			me->setIPendingInvitation(false);
			me->setIsGrouped(true);
			other->me->setGroup(new Group());
			other->me->getGroup()->Create(other->me);
			other->me->getGroup()->AddMember(me);
			me->getGroup()->setSession(NULL);
		}
	}
	else
	{
		me->setIPendingInvitation(false);
		other->me->setIPendingInvitation(false);
		/*
		PACKET FOR PLAYER REFUSED TO GROUPE
		*/
	}
}