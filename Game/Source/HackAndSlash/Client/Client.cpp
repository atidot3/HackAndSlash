#include "HackAndSlash.h"
#include "Client.h"

AClient::AClient()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AClient::BeginPlay()
{
	Super::BeginPlay();
}
void AClient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HackAndSlash::instance->MyTick();
}
bool AClient::Connect()
{
	return HackAndSlash::instance->Connect();
}
void AClient::Init(AHackAndSlashPlayerController* PC)
{
	HackAndSlash::instance->InitPlayer(PC);
}
bool AClient::Login(FString username, FString password)
{
	return HackAndSlash::instance->Login(username, password);
}
void AClient::SendEnterWorldComplete(AHackAndSlashPlayerController *PC, FVector position, int32 mapID)
{
	HackAndSlash::instance->InitPlayerGame(PC);
	HackAndSlash::instance->SendEnterWorldComplete(position, mapID);
}
void AClient::SendEnterWorldReq(int32 mapID, int32 charID, int32 diff)
{
	// NEED TO CHANGE FOR THE CHARACTER ID SELECTED !!!!!!!!!!!
	int ccid = HackAndSlash::instance->AccountID;
	Difficulty dif = (Difficulty)diff;
	HackAndSlash::instance->SendEnterWorldReq(mapID, ccid, dif);
}
void AClient::SendMapID(int32 mapID)
{
	HackAndSlash::instance->SendMapID(mapID);
}
bool AClient::IsAlreadyInitialized()
{
	return HackAndSlash::instance->Inited;
}
void AClient::SwitchMap()
{
	HackAndSlash::instance->SwitchMap();
}
void AClient::SendGroupInvit(int32 AccountID)
{
	HackAndSlash::instance->SendGroupInvit(AccountID);
}
void AClient::AcceptGroupInvit(bool accept, int32 accountID)
{
	HackAndSlash::instance->AcceptGroupInvit(accountID, accept);
}
bool AClient::isConnected()
{
	return HackAndSlash::instance->isConnectedToServer();
}
void AClient::Logout()
{
	HackAndSlash::instance->Logout();
}
void AClient::ReturnToMenu()
{
	HackAndSlash::instance->BackToMenu();
}
void AClient::MenuLoaded(AHackAndSlashPlayerController* PC)
{
	HackAndSlash::instance->InitPlayerGame(PC);
	HackAndSlash::instance->MenuLoaded();
}