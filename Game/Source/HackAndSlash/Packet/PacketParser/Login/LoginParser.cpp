#include "HackAndSlash.h"
#include "HackAndSlashPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"

void AHackAndSlashPlayerController::Login(CNtlPacket * pPacket)
{
	sAU_LOGIN_RES * res = (sAU_LOGIN_RES *)pPacket->GetPacketData();
	LoginResultEnum result = LoginResultEnum::Unknow;

	if (res->wResultCode == AUTH_SUCCESS)
	{
		//HackAndSlash::instance->token = res->abyAuthKey;
		HackAndSlash::instance->AccountID = res->accountId;
		//HackAndSlash::instance->money = res->wOpCode;
		result = LoginResultEnum::OK;
	}
	else if (res->wResultCode == AUTH_FAIL)
		result = LoginResultEnum::Unknow;
	else if (res->wResultCode == AUTH_WRONG_PASSWORD)
		result = LoginResultEnum::BadPassword;
	else if (res->wResultCode == AUTH_USER_BLOCK)
		result = LoginResultEnum::Banned;
	else if (res->wResultCode == AUTH_USER_NOT_FOUND)
		result = LoginResultEnum::BadUsername;
	this->LoginResult(result);
}
