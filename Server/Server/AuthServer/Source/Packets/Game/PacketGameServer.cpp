#include "stdafx.h"
#include "../../Server/AuthServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>
//--------------------------------------------------------------------------------------//
//		Send Map List From Database
//--------------------------------------------------------------------------------------//
void CClientSession::SendMapList()
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	app->db->prepare("SELECT * FROM maps");
	app->db->execute();

	CNtlPacket packet(sizeof(sGU_LOAD_MAPS));
	sGU_LOAD_MAPS * res = (sGU_LOAD_MAPS *)packet.GetPacketData();
	
	res->wOpCode = GU_LOAD_MAPS;
	if ((app->db->rowsCount()) != 0)
	{
		int yolo = app->db->rowsCount();
		int i = 0;
		while (i < yolo)
		{
			app->db->fetch();
			std::string name = app->db->getString("name");
			strcpy(res->map[i].name, name.c_str());
			res->map[i].id = app->db->getInt("id");
			i++;
			res->byCount = i;
		}
	}
	app->db->closeStatm();
	packet.SetPacketLen(sizeof(sGU_LOAD_MAPS));
	SendPacket(&packet, 300);
}
//--------------------------------------------------------------------------------------//
//		Player Request To Join The Game
//--------------------------------------------------------------------------------------//
void CClientSession::SendGameEnterReq(CNtlPacket *pPacket, CAuthServer * app)
{
	me->setPlayer(new Player());
	me->getPlayer()->setClient(me);
	/*
	*
	*
	!!!!!!!!!!! NEED TO GET THE CHARACTER AND FILL STRUCT ETC !!!!!!!!!!!!!
	*
	*
	*/
	CNtlPacket packet(sizeof(sGU_ENTER_GAME_RES));
	sGU_ENTER_GAME_RES * res = (sGU_ENTER_GAME_RES *)packet.GetPacketData();
	sUG_GAME_ENTER_REQ * req = (sUG_GAME_ENTER_REQ *)pPacket->GetPacketData();
	Session *sess;
	//req->charID;

	app->db->prepare("SELECT * FROM maps where id = ?");
	app->db->setInt(1, req->mapID);
	app->db->execute();
	if (app->db->rowsCount() != 0)
	{
		app->db->fetch();
		if (me->getIsGrouped() == true)
		{
			if (me->getIsLead() == true)
			{
				if (me->getGroup()->getSession() == NULL)
				{
					sess = new Session();
					me->getGroup()->setSession(sess);
					me->getGroup()->getSession()->AddPlayerToSession(me);
					sess->UpdateDifficulty(req->difficu);
					res->wResultCode = GAME_SUCCESS;
				}
				else
				{
					sess = me->getGroup()->getSession();
					me->getGroup()->getSession()->AddPlayerToSession(me);
					res->wResultCode = GAME_SUCCESS;
				}
			}
			else
			{
				sess = me->getGroup()->getSession();
				if (sess != NULL)
				{
					me->getGroup()->getSession()->AddPlayerToSession(me);
					res->wResultCode = GAME_SUCCESS;
				}
				else
					res->wResultCode = GAME_FAIL;
			}
		}
		else
		{
			Session* tmp = me->getGameSession();
			if (tmp)
				SAFE_DELETE(tmp);
			sess = new Session();
			sess->AddPlayerToSession(me);
			res->wResultCode = GAME_SUCCESS;
		}
		//sess->AddPlayerToMap(req->mapID, me->getPlayer()); // SET AFTER ON GAME ENTER DONE
		strcpy(res->mapName, app->db->getString("Name").c_str());
		me->setGameSession(sess);
	}
	else
	{
		Player* tmp = me->getPlayer();
		SAFE_DELETE(tmp);
		me->setPlayer(0);
		me->setStatut(ClientStatut::MENU);
		res->wResultCode = GAME_FAIL;
		std::cout << "false" << std::endl;
	}
	app->db->closeStatm();
	res->wOpCode = GU_ENTER_GAME_RES;
	packet.SetPacketLen(sizeof(sGU_ENTER_GAME_RES));
	SendPacket(&packet);
}
//--------------------------------------------------------------------------------------//
//		The Server Responce For The Enter In Game Resquest
//--------------------------------------------------------------------------------------//
void CClientSession::SendGameEnterCompleteReq(CNtlPacket *pPacket, CAuthServer * app)
{
	sUG_GAME_ENTER_COMPLETE_REQ * req = (sUG_GAME_ENTER_COMPLETE_REQ *)pPacket->GetPacketData();

	if (me->getGameSession() != NULL)
	{
		me->setStatut(ClientStatut::GAME);
		me->getPlayer()->setLocation(req->postion);
		// need to fill players class with models etc
		if (me->getIsGrouped() == true)
			me->getGroup()->UpdatePlayerOnline(me);
		//
		me->getGameSession()->AddPlayerToMap(req->mapID, me->getPlayer());
	}
}
//--------------------------------------------------------------------------------------//
//		Send Player Movement
//--------------------------------------------------------------------------------------//
void CClientSession::SendCharacterMoveOnMap(CNtlPacket *pPacket, CAuthServer * app)
{
	sGU_PARTY_MEMBER_MOVE * req = (sGU_PARTY_MEMBER_MOVE *)pPacket->GetPacketData();
	
	if (me->getPlayer() == NULL)
		return;
	me->getPlayer()->setLocation(req->location);
	if (me->getIsGrouped() == true)
	{
		if (me->getGameSession() != NULL)
		{
			me->getGameSession()->SendMovementPlayer(me->getPlayer(), req->mapID, pPacket);
		}
	}
}
//--------------------------------------------------------------------------------------//
//		Player Go Back To Menu
//--------------------------------------------------------------------------------------//
void CClientSession::SendBackToMenu(CNtlPacket *pPacket, CAuthServer * app)
{
	if (me != NULL)
	{
		me->setStatut(ClientStatut::MENU);
		if (me->getIsGrouped() == true)
		{
			if (me->getGroup() != NULL)
			{
				if (me->getGroup()->GetMembersCount() <= 1)
				{
					if (me->getGameSession() != NULL)
					{
						me->getGameSession()->PreDestruct();
						Group* grp = me->getGroup();
						SAFE_DELETE(grp);
						Session* tmp = me->getGameSession();
						SAFE_DELETE(tmp);
						me->setGroup(NULL);
						me->setGameSession(NULL);
						Player *plr = me->getPlayer();
						SAFE_DELETE(plr);
						me->setPlayer(NULL);
					}
				}
				else
				{
					Player *plr = me->getPlayer();
					me->getGameSession()->RemovePlayerFromMap(plr, true);
					SAFE_DELETE(plr);
					me->setPlayer(NULL);
					me->getGroup()->UpdatePlayerOnline(me);
				}
			}
		}
		else if (me->getIsGrouped() == false)
		{
			if (me->getGameSession() != NULL)
			{
				me->getGameSession()->PreDestruct();
				Session* tmp = me->getGameSession();
				SAFE_DELETE(tmp);
				me->setGameSession(NULL);
				Player *plr = me->getPlayer();
				SAFE_DELETE(plr);
				me->setPlayer(NULL);
			}
		}
	}
}
//--------------------------------------------------------------------------------------//
//		Server Important Message
//--------------------------------------------------------------------------------------//
void CClientSession::SendPopupMessage(const char* theString)
{
	CNtlPacket packet(sizeof(sGU_POPUP_MESSAGE));
	sGU_POPUP_MESSAGE * res = (sGU_POPUP_MESSAGE *)packet.GetPacketData();
	
	memcpy(res->theMessage, theString, strlen(theString));
	res->wOpCode = GU_POPUP_MESSAGE;

	packet.SetPacketLen(sizeof(sGU_POPUP_MESSAGE));
	SendPacket(&packet);
}