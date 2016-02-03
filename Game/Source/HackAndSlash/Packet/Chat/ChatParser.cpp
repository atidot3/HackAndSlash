#include "HackAndSlash.h"
#include "HackAndSlashPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"

void AHackAndSlashPlayerController::RecvWorldMessage(CNtlPacket * pPacket)
{
	sCHU_SEND_WORLD_MESSAGE_RES * res = (sCHU_SEND_WORLD_MESSAGE_RES*)pPacket->GetPacketData();

	char MESSAGE[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE] = "";
	char SENDER[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE] = "";
	strcpy_s(MESSAGE, NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE, (char*)res->Message);
	strcpy_s(SENDER, NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE, (char*)res->Sender);


	FString messageStr = FString(ANSI_TO_TCHAR(MESSAGE));
	FString senderStr = FString(ANSI_TO_TCHAR(SENDER));

	WorldMessageRecv(senderStr, messageStr);
}
