#ifndef _CLIENT_H_
# define _CLIENT_H_

#pragma once

#include "../Server/AuthServer.h"
#include "../Game/Groupe/Groupe.h"

class CClientSession;
class Player;
class Session;

enum ClientStatut
{
	MENU,
	GAME
};

class Client
{
public:
	Client();
	Client(char *_AccountName, int _AccountID);
	~Client();
	std::string		getAccountName(){ return AccountName; }
	int				getAccountID(){ return accountID; }
	bool			getIsGrouped(){ return isGrouped; }
	bool			getIPendingInvitation(){ return isPendingInvitation; }
	bool			getIsLead(){ return isLead; }
	void			setIsGrouped(bool val){ isGrouped = val; }
	void			setIPendingInvitation(bool val){ isPendingInvitation = val; }
	void			setIsLead(bool val){ isLead = val; }
	void			setPlayer(Player* plr){ player = plr; }
	Player			*getPlayer(){ return player; }
	void			setSession(CClientSession *ss){ session = ss; }
	CClientSession	*getSession(){ return session; }
	void			setGameSession(Session* session){ gameSession = session; }
	Session			*getGameSession(){ return gameSession; }
	void			setStatut(ClientStatut state){ statut = state; }
	ClientStatut	getStatut(){ return statut; }
	void			setMoney(int val){ money = val; }
	int				getMoney(){ return money; }
	DWORD			lastPing;
private:
	//DATA
	CClientSession	*session;
	Session			*gameSession;
	// ACCOUNT
	std::string		AccountName;
	int				accountID;
	ClientStatut	statut;
	int				money;
	// GROUPE
	bool			isGrouped;
	bool			isPendingInvitation;
	bool			isLead;
	Player			*player;
	
};

#endif