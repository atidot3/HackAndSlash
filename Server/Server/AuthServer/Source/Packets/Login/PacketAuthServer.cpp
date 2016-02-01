#include "stdafx.h"
#include "NtlSfx.h"
#include "NtlPacketUA.h"
#include "NtlPacketAU.h"
#include "ResultCode.h"

#include "../../Server/AuthServer.h"
//--------------------------------------------------------------------------------------//
//		Get the account ID and log in to Char Server									//
//--------------------------------------------------------------------------------------//
bool CClientSession::SendCharLogInReq(CNtlPacket * pPacket, CAuthServer * app) 
{
	sUA_LOGIN_REQ * req = (sUA_LOGIN_REQ *)pPacket->GetPacketData();
	CNtlPacket packet(sizeof(sAU_LOGIN_RES));
	sAU_LOGIN_RES * res = (sAU_LOGIN_RES *)packet.GetPacketData();
	bool theReturn = false;

	res->wOpCode = AU_LOGIN_RES;
	strcpy_s((char*)res->abyAuthKey, NTL_MAX_SIZE_AUTH_KEY, "Dbo");
	char user[NTL_MAX_SIZE_USERID] = "";
	char pass[NTL_MAX_SIZE_USERPW] = "";
	strcpy_s(user, NTL_MAX_SIZE_USERID, (char*)req->awchUserId);
	strcpy_s(pass, NTL_MAX_SIZE_USERPW, (char*)req->awchPasswd);

	app->db->prepare("SELECT * FROM accounts where username = ? AND acc_status = \"active\"");
	app->db->setString(1, user);
	app->db->execute();
	if ((app->db->rowsCount()) != 0)
	{
		app->db->fetch();
		if (app->db->getString("username") == user && app->db->getString("AccountPW") == pass & app->db->getString("acc_status") == "active")
		{
			res->accountId = app->db->getInt("AccountID");
			res->wResultCode = AUTH_SUCCESS;
			this->me = new Client(user, res->accountId);
			this->me->setSession(this);
			app->AddUser(me->getAccountName().c_str(), this);
			this->me->setPlayer(new Player());
			this->me->getPlayer()->setClient(this->me);
			me->setMoney(app->db->getInt("money"));
			me->getPlayer()->setGroup(NULL);
			me->setGameSession(NULL);
			me->setStatut(ClientStatut::MENU);
			theReturn = true;
		}
		else
		{
			if (app->db->getString("AccountPW") != pass)
				res->wResultCode = AUTH_WRONG_PASSWORD;
			else if (app->db->getString("acc_status") != "active")
				res->wResultCode = AUTH_USER_BLOCK;
			else
				res->wResultCode  = AUTH_USER_NOT_FOUND;
		}
	}
	else
	{
		res->wResultCode = AUTH_USER_NOT_FOUND;
		me = NULL;
	}
	packet.SetPacketLen(sizeof(sAU_LOGIN_RES));
	int rc = SendPacket(&packet);
	app->db->closeStatm();
	return theReturn;
}
//--------------------------------------------------------------------------------------//
//		REFRESH GROUP WHEN BACK TO MENU
//--------------------------------------------------------------------------------------//
void CClientSession::RefreshMyGroupHUD()
{
	if (me != NULL)
	{
		if (me->getIsGrouped() == true)
		{
			if (me->getPlayer()->getGroup() != NULL)
			{
				me->getPlayer()->getGroup()->RefreshAllGroup();
			}
		}
	}
}
//--------------------------------------------------------------------------------------//
//		Disconnect from Auth Server
//--------------------------------------------------------------------------------------//
void CClientSession::SendLoginDcReq(CNtlPacket * pPacket) 
{
	CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	if (me != NULL)
	{
		if (me->getIsGrouped() == true)
		{
			if (me->getPlayer()->getGroup() != NULL)
			{
				if (me->getPlayer()->getGroup()->GetMembersCount() <= 1)
				{
					if (me->getGameSession() != NULL)
					{
						me->getGameSession()->PreDestruct();
						delete me->getGameSession();
					}
					delete me->getPlayer()->getGroup();
				}
				else
				{
					if (me->getGameSession() != NULL)
					{
						me->getGameSession()->RemovePlayerFromMap(me->getPlayer(), true);
					}
					me->getPlayer()->getGroup()->RemoveMember(me->getPlayer());
				}
			}
		}
		else if (me->getIsGrouped() == false)
		{
			if (me->getGameSession() != NULL)
			{
				me->getGameSession()->PreDestruct();
				delete me->getGameSession();
			}
		}
		app->RemoveUser(me->getAccountName().c_str());
		delete me;
	}
	this->Disconnect(true);
}
