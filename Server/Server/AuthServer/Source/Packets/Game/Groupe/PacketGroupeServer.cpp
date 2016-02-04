#include "stdafx.h"
#include "../../../Server/AuthServer.h"

#include "NtlSfx.h"
#include "NtlFile.h"

#include "../../../Packets/AllPackets.h"
#include "ResultCode.h"

#include <iostream>
#include <map>
#include <list>

//--------------------------------------------------------------------------------------//
//		Player Is Kick From The Current Group
//--------------------------------------------------------------------------------------//
void		CClientSession::SendPlayerOnKick(CNtlPacket *pPacket, CAuthServer * app)
{
	sUGR_GROUPE_KICK * req = (sUGR_GROUPE_KICK *)pPacket->GetPacketData();

	if (me->getIsGrouped() == true)
	{
		if (me->getIsLead() == true)
		{
			if (me->getGroup()->GetMembersCount() <= 2)
			{
				CClientSession *plr = app->GetCharacterManager()->GetPlayerByAccount(req->friendAccountID);
				if (plr)
				{
					me->getGroup()->Disband(true);
					plr->me->setStatut(ClientStatut::MENU);
					plr->me->setGameSession(NULL);
					Player* tmp = plr->me->getPlayer();
					SAFE_DELETE(tmp);
					plr->me->setPlayer(NULL);
					CNtlPacket packet2(sizeof(sGRU_PLAYER_KICK_RES));
					sGRU_PLAYER_KICK_RES * res2 = (sGRU_PLAYER_KICK_RES *)packet2.GetPacketData();
					res2->wOpCode = GRU_PLAYER_KICK_RES;
					packet2.SetPacketLen(sizeof(sGRU_PLAYER_KICK_RES));
					plr->SendPacket(&packet2);
				}
			}
			else
			{
				CClientSession *plr = app->GetCharacterManager()->GetPlayerByAccount(req->friendAccountID);
				if (plr)
				{
					plr->me->setStatut(ClientStatut::MENU);
					plr->me->setIPendingInvitation(false);
					plr->me->setIsGrouped(false);

					me->getGroup()->RemoveMember(plr->me);
					Session *sess = me->getGameSession();
					if (sess)
					{
						sess->RemovePlayer(plr->me);
						plr->me->setGameSession(NULL);
						plr->me->setGroup(NULL);
						Player* tmp = plr->me->getPlayer();
						SAFE_DELETE(tmp);
						plr->me->setPlayer(NULL);
						CNtlPacket packet2(sizeof(sGRU_PLAYER_KICK_RES));
						sGRU_PLAYER_KICK_RES * res2 = (sGRU_PLAYER_KICK_RES *)packet2.GetPacketData();
						res2->wOpCode = GRU_PLAYER_KICK_RES;
						packet2.SetPacketLen(sizeof(sGRU_PLAYER_KICK_RES));
						plr->SendPacket(&packet2);
					}
				}
			}
		}
	}
}