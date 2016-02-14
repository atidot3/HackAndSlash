#include "Groupe.h"

Group::Group() : m_dungeonDifficulty(DIFFICULTY_NORMAL)
{
	sess = NULL;
}
Group::~Group()
{
}
bool Group::Create(Client* leader)
{
	m_dungeonDifficulty = DIFFICULTY_NORMAL;

	return AddMember(leader);
}
void Group::RefreshAllGroup()
{
	CNtlPacket packet(sizeof(sGRU_REFRESH_GROUPE_RES));
	sGRU_REFRESH_GROUPE_RES * res = (sGRU_REFRESH_GROUPE_RES *)packet.GetPacketData();
	res->size = GetMembersCount();
	res->wOpCode = GRU_REFRESH_GROUPE_RES;
	int i = 0;
	for (member_witerator witr = m_memberSlots.begin(); witr != m_memberSlots.end(); ++witr)
	{
		res->groupePlayers[i].accountID = witr->me->getAccountID();
		res->groupePlayers[i].charID = res->groupePlayers[i].accountID; // TEMP VALUE
		res->groupePlayers[i].leader = witr->me->getIsLead();
		strcpy(res->groupePlayers[i].name, witr->me->getAccountName().c_str());
		if (witr->me->getPlayer() != NULL)
		{
			res->groupePlayers[i].disconnected = witr->disconnected;
			res->groupePlayers[i].classe = witr->_class;
			res->groupePlayers[i].level = witr->level;
			res->groupePlayers[i].life = witr->life;
		}
		else
		{
			res->groupePlayers[i].disconnected = true;
			res->groupePlayers[i].classe = 0;
			res->groupePlayers[i].level = 0;
			res->groupePlayers[i].life = 0;
		}
		i++;
	}
	packet.SetPacketLen(sizeof(sGRU_REFRESH_GROUPE_RES));
	SendAll(&packet);
}
void Group::UpdatePlayerOnline(Client *cl)
{
	if (cl->getPlayer())
	{
		for (member_witerator witr = m_memberSlots.begin(); witr != m_memberSlots.end(); ++witr)
		{
			if (witr->guid == cl->getAccountID())
			{
				witr->disconnected = false;
				witr->level = cl->getPlayer()->getLevel();
				witr->life = cl->getPlayer()->getLife();
				witr->_class = cl->getPlayer()->getClass();
			}
		}
	}
	else
	{
		for (member_witerator witr = m_memberSlots.begin(); witr != m_memberSlots.end(); ++witr)
		{
			if (witr->guid == cl->getAccountID())
			{
				witr->disconnected = true;
				witr->level = 0;
				witr->life = 0;
				witr->_class = 0;
			}
		}
	}
	RefreshAllGroup();
}
bool Group::AddMember(Client* client)
{
	if (GetMembersCount() < MAX_GROUP_SIZE)	// If the leader can't be added to a new group because it appears full, something is clearly wrong.
	{
		MemberSlot member;
		if (client->getStatut() == ClientStatut::MENU)
		{
			member.guid = client->getAccountID();
			member.name = "";
			member._class = 0;
			member.level = 0;
			member.life = 0;
			member.disconnected = true;
			member.me = client;
		}
		else
		{
			member.guid = client->getAccountID();
			member.name = client->getAccountName();
			member._class = client->getPlayer()->getClass();
			member.level = client->getPlayer()->getLevel();
			member.life = client->getPlayer()->getLife();
			member.disconnected = false;
			member.me = client;
		}
		m_memberSlots.push_back(member);
		client->setGroup(this);
		RefreshAllGroup();
		return true;
	}
	return false;
}
bool Group::RemoveMember(Client* client)
{
	// remove member and change leader (if need) only if strong more 2 members _before_ member remove (BG/BF allow 1 member group)
	if (GetMembersCount() > 2 && client->getIsLead() == true) // IF TOTAL PLAYER > 2 CHANGE LEAD
	{
		for (member_witerator itr = m_memberSlots.begin(); itr != m_memberSlots.end(); ++itr)
		{
			Client* cl;
			if (client != NULL)
				cl = client;
			if (cl != NULL)
			{
				if (itr->guid != cl->getAccountID())
				{
					ChangeLeader(itr->me);
					break;
				}
			}
		}
	}
	bool found = false; // REMOVE THE LOGGOUT PLAYER
	member_witerator witr = m_memberSlots.begin();
	while (witr != m_memberSlots.end())
	{
		if (witr->guid == client->getAccountID())
		{
			found = true;
			break;
		}
		++witr;
	}
	if (found == true)
	{
		m_memberSlots.erase(witr);
	}
	// If group size before player removal <= 2 then disband it
	if (GetMembersCount() < 2)
	{
		Disband(false);
	}
	else
	{
		RefreshAllGroup();
	}
	return true;
}
void Group::Disband(bool hideDestroy /* = false */)
{
	for (member_witerator itr = m_memberSlots.begin(); itr != m_memberSlots.end(); ++itr)
	{
		CNtlPacket packet(sizeof(sGRU_DISBAND_GROUPE_RES));
		sGRU_DISBAND_GROUPE_RES * res = (sGRU_DISBAND_GROUPE_RES *)packet.GetPacketData();
		res->wOpCode = GRU_DISBAND_GROUPE_RES;
		packet.SetPacketLen(sizeof(sGRU_DISBAND_GROUPE_RES));
		itr->me->getSession()->SendPacket(&packet); // SEND DISBAND TO LAST PLAYERS
		itr->me->setIPendingInvitation(false);
		itr->me->setIsGrouped(false);
		itr->me->setIsLead(false);
		itr->me->setGroup(NULL);
	}
	delete this;
}
void Group::ChangeLeader(Client* client)
{
	client->setIsLead(true);
}
void Group::Update(int diff)
{
}
// properties accessories
bool Group::IsFull()
{
	if (GetMembersCount() == MAX_GROUP_SIZE)
		return true;
	return false;
}
void Group::SetDungeonDifficultyID(Difficulty difficulty)
{
	m_dungeonDifficulty = difficulty;
}
Difficulty Group::GetDifficultyID()
{
	return m_dungeonDifficulty;
}
void Group::SendUpdate(CNtlPacket *pPacket)
{
	for (member_witerator witr = m_memberSlots.begin(); witr != m_memberSlots.end(); ++witr)
	{
	}
}
void Group::SendAll(CNtlPacket *pPacket)
{
	for (member_witerator witr = m_memberSlots.begin(); witr != m_memberSlots.end(); ++witr)
	{
		if (witr->me != NULL)
		{
			Client *plr = witr->me;
			if (plr != NULL)
			{
				Client *cur = plr;
				cur->getSession()->SendPacket(pPacket);
			}
		}
	}
}