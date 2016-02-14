#include "stdafx.h"
#include "../../Server/GameServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>

//--------------------------------------------------------------------------------------//
//		Send Friend List From Database
//--------------------------------------------------------------------------------------//
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
//--------------------------------------------------------------------------------------//
//		Send Friend Notification On Logging And Logout
//--------------------------------------------------------------------------------------//
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
//--------------------------------------------------------------------------------------//
//		REQUEST PLAYER TO JOIN GROUP
//--------------------------------------------------------------------------------------//
void	CClientSession::SendFriendToAddToGroupeRequest(CNtlPacket *pPacket, CAuthServer * app)
{
	sUF_GROUP_FRIEND_REQ * req = (sUF_GROUP_FRIEND_REQ *)pPacket->GetPacketData();
	CClientSession *other = app->GetCharacterManager()->GetPlayerByAccount(req->friendAccountID);

	CNtlPacket packet(sizeof(sFU_GROUP_FRIEND_REFUSE_RES));
	sFU_GROUP_FRIEND_REFUSE_RES * res = (sFU_GROUP_FRIEND_REFUSE_RES*)packet.GetPacketData();
	if (other != NULL)
	{
		bool caninvite = false;
		if (other->me->getIsGrouped() == false && other->me->getIPendingInvitation() == false)// other player is not grouped
		{
			if (me->getIsLead() == true && me->getIsGrouped() == true) // i'm a leader and i'm already in a group
			{
				if (me->getGroup() != NULL) // sure the group is valid
				{
					if (me->getGroup()->IsFull() == false) // GROUPE IS NOT FULL
					{
						caninvite = true;
					}
					else // GROUPE IS FULL
					{
						res->wResultCode = GAME_PARTY_IS_FULL;
						caninvite = false;
					}
				}
			}
			else if (me->getIsLead() == false && me->getIsGrouped() == true) // i'm in a group but not the leader
			{
				res->wResultCode = GAME_PARTY_NOT_LEADER;
				caninvite = false;
			}
			else if (me->getIsGrouped() == false && me->getIPendingInvitation() == false) // everything is ok
			{
				caninvite = true;
			}
		}
		else if (other->me->getIsGrouped() == true || other->me->getIPendingInvitation() == true) // other is grouped or already pending for a group
		{
			res->wResultCode = GAME_PARTY_ALREADY_IN_PARTY;
			caninvite = false;
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
		else
		{
			res->wOpCode = FU_GROUP_FRIEND_REFUSE_RES;
			packet.SetPacketLen(sizeof(sFU_GROUP_FRIEND_REFUSE_RES));
			SendPacket(&packet);
		}
	}
}
//--------------------------------------------------------------------------------------//
//		Populate The Group With User
//--------------------------------------------------------------------------------------//
void	CClientSession::SendFriendGroupe(CNtlPacket *pPacket, CAuthServer * app)//SOMEONE RESPONCE FOR THE GROUPE REQUEST
{
	sUF_GROUP_FRIEND_AWSER_REQ * req = (sUF_GROUP_FRIEND_AWSER_REQ *)pPacket->GetPacketData();
	CClientSession *sender = app->GetCharacterManager()->GetPlayerByAccount(req->friendAccountID);

	if (sender == NULL)
	{
		me->setIPendingInvitation(false);
		return;
	}
	if (req->accept == true) // i accept the group invitation
	{
		if (sender->me->getIsGrouped() == true) // Player who send invit is grouped so add the current player to the other group
		{
			sender->me->setIPendingInvitation(false);
			me->setIPendingInvitation(false);
			me->setIsGrouped(true);
			sender->me->getGroup()->AddMember(me);
			// need to change it
			if (sender->me->getStatut() == ClientStatut::GAME) // assign the session to the group
			{
				me->getGroup()->setSession(sender->me->getGameSession());
			}
			else
				me->getGroup()->setSession(NULL);
			//until here
		}
		else if (sender->me->getIsGrouped() == false) // sender is not grouped at all create new party
		{
			sender->me->setIsLead(true);
			sender->me->setIsGrouped(true);
			sender->me->setIPendingInvitation(false);
			me->setIPendingInvitation(false);
			me->setIsGrouped(true);
			sender->me->setGroup(new Group());
			sender->me->getGroup()->Create(sender->me); // Create the group with other in param as he is the leader
			sender->me->getGroup()->AddMember(me);
			if (me->getStatut() == ClientStatut::GAME && sender->me->getStatut() != ClientStatut::GAME) // receiver is already in a party ! and sender is not
			{
				sender->me->getGroup()->setSession(me->getGameSession()); // force game to receiver party
				me->getGroup()->setSession(me->getGameSession());
			}
			else if (me->getStatut() == ClientStatut::GAME && sender->me->getStatut() == ClientStatut::GAME) // sender is the leader so his game take possesion
			{
				Session* oldSession = me->getGameSession();
				sender->me->getGroup()->setSession(sender->me->getGameSession()); // force the groupe to use the leader session
				/*
					must force the other player to refresh his game
					send him on the main map (town)
				*/

				/*
					once the player is sended to the other map delete old session ?
				*/
				SAFE_DELETE(oldSession);
				me->setGameSession(NULL);
			}
			else // no game actually
			{
				me->getGroup()->setSession(NULL);
			}
		}
	}
	else
	{
		me->setIPendingInvitation(false);
		sender->me->setIPendingInvitation(false);
		
		CNtlPacket packet(sizeof(sFU_GROUP_FRIEND_REFUSE_RES));
		sFU_GROUP_FRIEND_REFUSE_RES * res = (sFU_GROUP_FRIEND_REFUSE_RES*)packet.GetPacketData();
		res->wOpCode = FU_GROUP_FRIEND_REFUSE_RES;
		res->wResultCode = GAME_PARTY_TARGET_REFUSE_INVITATION;
		packet.SetPacketLen(sizeof(sFU_GROUP_FRIEND_REFUSE_RES));
		sender->SendPacket(&packet);
	}
}
//--------------------------------------------------------------------------------------//
//		Request to add a new friend
//--------------------------------------------------------------------------------------//
void		CClientSession::SendFriendRequest(CNtlPacket *pPacket, CAuthServer * app)
{
	sUF_REQUEST_NEW_FRIEND_REQ * req = (sUF_REQUEST_NEW_FRIEND_REQ *)pPacket->GetPacketData();

	app->db->prepare("SELECT * FROM accounts where username = ?");
	app->db->setString(1, req->toWho);
	app->db->execute();

	if ((app->db->rowsCount()) != 0) // account exist
	{
		std::cout << "The account exist" << std::endl;
		app->db->fetch();
		app->db->closeStatm();
		app->db->prepare("SELECT * FROM friendlist where account = ? AND friend = ?");
		app->db->setString(1, me->getAccountName().c_str());
		app->db->setString(2, req->toWho);
		app->db->execute();

		if (app->db->rowsCount() != 0) // already friend with
		{
			std::cout << "already friend !" << std::endl;
			app->db->fetch();
			app->db->closeStatm();
			CNtlPacket packet(sizeof(sFU_FRIEND_REQUEST_RES));
			sFU_FRIEND_REQUEST_RES * res = (sFU_FRIEND_REQUEST_RES*)packet.GetPacketData();

			res->wOpCode = FU_FRIEND_REQUEST_RES;
			res->wResultCode = COMMUNITY_FRIEND_CHAR_ARLEADY_ADDED;

			packet.SetPacketLen(sizeof(sFU_FRIEND_REQUEST_RES));
			SendPacket(&packet);
		}
		else // can add this friend
		{
			std::cout << "supposed to be added" << std::endl;
			app->db->fetch();
			app->db->closeStatm();
			CNtlPacket packet(sizeof(sFU_FRIEND_REQUEST_RES));
			sFU_FRIEND_REQUEST_RES * res = (sFU_FRIEND_REQUEST_RES*)packet.GetPacketData();

			res->wOpCode = FU_FRIEND_REQUEST_RES;
			res->wResultCode = COMMUNITY_FRIEND_ADDED;

			app->db->prepare("INSERT INTO pendingrequest (fromWho, toWho) VALUES(?,?)");
			app->db->setString(1, me->getAccountName().c_str());
			app->db->setString(2, req->toWho);
			app->db->execute();

			packet.SetPacketLen(sizeof(sFU_FRIEND_REQUEST_RES));
			SendPacket(&packet);

			if (app->GetCharacterManager()->FindUser(req->toWho))
			{
				CNtlPacket packet2(sizeof(sFU_FRIEND_REQUEST_RECV_RES));
				sFU_FRIEND_REQUEST_RECV_RES * res2 = (sFU_FRIEND_REQUEST_RECV_RES*)packet2.GetPacketData();

				strcpy_s(res2->from, strlen(me->getAccountName().c_str()), me->getAccountName().c_str());
				res2->wOpCode = FU_FRIEND_REQUEST_RECV_RES;

				packet2.SetPacketLen(sizeof(sFU_FRIEND_REQUEST_RECV_RES));
				app->GetCharacterManager()->GetPlayerByName(req->toWho)->SendPacket(&packet2);
				app->GetCharacterManager()->GetPlayerByName(req->toWho)->SendFriendPendingRequest();
			}
		}
	}
	else
	{
		app->db->fetch();
		app->db->closeStatm();
		CNtlPacket packet(sizeof(sFU_FRIEND_REQUEST_RES));
		sFU_FRIEND_REQUEST_RES * res = (sFU_FRIEND_REQUEST_RES*)packet.GetPacketData();

		res->wOpCode = FU_FRIEND_REQUEST_RES;
		res->wResultCode = COMMUNITY_FRIEND_CHAR_NOT_FOUND;

		packet.SetPacketLen(sizeof(sFU_FRIEND_REQUEST_RES));
		SendPacket(&packet);
	}
}
void	CClientSession::SendFriendPendingRequest()
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();

	app->db->prepare("SELECT * FROM pendingrequest where toWho = ?");
	app->db->setString(1, me->getAccountName().c_str());
	app->db->execute();

	list<string> nameList;
	std::list<string>::iterator it = nameList.begin();
	if (app->db->rowsCount() != 0) // i got some pending invitation
	{
		CNtlPacket packet(sizeof(sFU_FRIEND_PENDING_RECV_LIST_RES));
		sFU_FRIEND_PENDING_RECV_LIST_RES * res = (sFU_FRIEND_PENDING_RECV_LIST_RES*)packet.GetPacketData();
		res->wOpCode = FU_FRIEND_PENDING_RECV_LIST_RES;
		int i = 0;
		res->lenght = i;
		while (app->db->fetch())
		{
			nameList.push_back(app->db->getString("fromWho"));
			//std::cout << friendNameRequestMe << std::endl;
			i++;
			res->lenght = i;
		}
		app->db->closeStatm();
		i = 0;
		if (res->lenght > 0)
		{
			for (it = nameList.begin(); it != nameList.end(); ++it)
			{
				app->db->prepare("SELECT * FROM accounts where userName = ?");
				string name = *it;
				std::cout << name << std::endl;
				app->db->setString(1, name);
				app->db->execute();
				app->db->fetch();

				res->resquests[i].accountID = app->db->getInt("AccountID");
				memcpy(res->resquests[i].name, name.c_str(), strlen(name.c_str()));

				app->db->closeStatm();
				i++;
			}
			packet.SetPacketLen(sizeof(sFU_FRIEND_PENDING_RECV_LIST_RES));
			SendPacket(&packet);
		}
	}
}