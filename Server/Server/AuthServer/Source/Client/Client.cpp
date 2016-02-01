#include "Client.h"

Client::Client()
{
	player = NULL;
	gameSession = NULL;
}
Client::Client(char *_AccountName, int _AccountID)
{
	AccountName = _AccountName;
	accountID = _AccountID;
	isGrouped = false;
	isPendingInvitation = false;
	isLead = false;
	statut = ClientStatut::MENU;
	lastPing = ::GetTickCount();
}
Client::~Client()
{
	delete player;
}
