#include "Client.h"

Client::Client()
{
	player = NULL;
	gameSession = NULL;
	group = NULL;
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
	player = NULL;
	gameSession = NULL;
	group = NULL;
}
Client::~Client()
{
	if (player != 0 && player && player != NULL)
		SAFE_DELETE(player);
}
