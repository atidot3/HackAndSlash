#include "Groupe.h"

Group::Group() : m_dungeonDifficulty(DIFFICULTY_NORMAL)
{
	sess = NULL;
}

Group::~Group()
{
}
bool Group::Create(Player* leader)
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
		res->groupePlayers[i].accountID = witr->me->getClient()->getAccountID();
		res->groupePlayers[i].charID = res->groupePlayers[i].accountID; // TEMP VALUE
		res->groupePlayers[i].classe = witr->_class;
		res->groupePlayers[i].leader = witr->me->getClient()->getIsLead();
		res->groupePlayers[i].level = witr->me->getLevel();
		res->groupePlayers[i].life = witr->me->getLife();
		res->groupePlayers[i].disconnected = witr->disconnected;
		strcpy(res->groupePlayers[i].name, witr->me->getClient()->getAccountName().c_str());
		i++;
	}
	packet.SetPacketLen(sizeof(sGRU_REFRESH_GROUPE_RES));
	SendAll(&packet);
}
bool Group::AddMember(Player* player)
{
	if (GetMembersCount() < MAX_GROUP_SIZE)	// If the leader can't be added to a new group because it appears full, something is clearly wrong.
	{
		if (player->getDisconnedted() == true)
		{
			MemberSlot member;
			member.guid = player->getClient()->getAccountID();
			member.name = "";
			member._class = 0;
			member.group = 0;
			member.flags = 0;
			member.roles = 0;
			member.readyChecked = false;
			member.disconnected = player->getDisconnedted();
			member.me = player;
			m_memberSlots.push_back(member);
		}
		player->setGroup(this);
		RefreshAllGroup();
		return true;
	}
	return false;
}
bool Group::RemoveMember(Player* player)
{
	// remove member and change leader (if need) only if strong more 2 members _before_ member remove (BG/BF allow 1 member group)
	if (GetMembersCount() > 2 && player->getClient()->getIsLead() == true) // IF TOTAL PLAYER > 2 CHANGE LEAD
	{
		for (member_witerator itr = m_memberSlots.begin(); itr != m_memberSlots.end(); ++itr)
		{
			Client* cl;
			if (player != NULL)
				cl = player->getClient();
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
		if (witr->guid == player->getClient()->getAccountID())
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
		itr->me->getClient()->getSession()->SendPacket(&packet); // SEND DISBAND TO LAST PLAYERS
		itr->me->getClient()->setIPendingInvitation(false);
		itr->me->getClient()->setIsGrouped(false);
		itr->me->getClient()->setIsLead(false);
		itr->me->setGroup(NULL);
	}
	delete this;
}
void Group::ChangeLeader(Player* player)
{
	player->getClient()->setIsLead(true);
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
			Player *plr = witr->me;
			if (plr->getClient() != NULL)
			{
				Client *cur = plr->getClient();
				cur->getSession()->SendPacket(pPacket);
			}
		}
	}
}