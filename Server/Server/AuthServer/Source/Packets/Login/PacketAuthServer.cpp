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
			for (int i = 0; i <= app->serverNmb; i++)
			{
				res->serverList[i].id = app->serverList[i].id;
				memcpy(res->serverList[i].ip, app->serverList[i].ip, 16);
				memcpy(res->serverList[i].servername, app->serverList[i].servername, 16);
				res->serverList[i].len = app->serverList[i].len;
				res->serverList[i].port = app->serverList[i].port;
				res->serverList[i].len = i;
			}
			res->serverList[0].len = app->serverNmb;
			std::cout << res->serverList[0].len;
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
			theReturn = false;
		}
	}
	else
	{
		res->wResultCode = AUTH_USER_NOT_FOUND;
		theReturn = false;
	}
	packet.SetPacketLen(sizeof(sAU_LOGIN_RES));
	int rc = SendPacket(&packet);
	app->db->closeStatm();
	return theReturn;
	this->Disconnect(true);
}
//--------------------------------------------------------------------------------------//
//		REFRESH GROUP WHEN BACK TO MENU
//--------------------------------------------------------------------------------------//
void CClientSession::RefreshMyGroupHUD()
{
	/*if (me != NULL)
	{
		if (me->getIsGrouped() == true)
		{
			if (me->getGroup() != NULL)
			{
				me->getGroup()->RefreshAllGroup();
			}
		}
	}*/
}
//--------------------------------------------------------------------------------------//
//		Disconnect from Auth Server
//--------------------------------------------------------------------------------------//
void CClientSession::SendLoginDcReq(CNtlPacket * pPacket) 
{
	/*CAuthServer * app = (CAuthServer*)NtlSfxGetApp();
	if (me != NULL)
	{
		if (me->getIsGrouped() == true)
		{
			if (me->getGroup() != NULL)
			{
				if (me->getGroup()->GetMembersCount() <= 1)
				{
					if (me->getGameSession())
					{
						me->getGameSession()->PreDestruct();
						Session* sess = me->getGameSession();
						SAFE_DELETE(sess);
						Group* grp = me->getGroup();
						SAFE_DELETE(grp);
					}
				}
				else
				{
					if (me->getGameSession() != NULL)
					{
						me->getGameSession()->RemovePlayer(me);
						me->getGameSession()->RemovePlayerFromMap(me->getPlayer(), true);
					}
					me->getGroup()->RemoveMember(me);
				}
			}
		}
		else if (me->getIsGrouped() == false)
		{
			if (me->getGameSession() != NULL)
			{
				me->getGameSession()->PreDestruct();
				Session* sess = me->getGameSession();
				SAFE_DELETE(sess);
			}
		}
		app->GetCharacterManager()->RemoveUser(me->getAccountName().c_str());
		SAFE_DELETE(me);
	}
	this->Disconnect(true);*/
}
