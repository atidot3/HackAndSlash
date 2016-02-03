#pragma once

#include "HackAndSlash.H"
#include "../Packet/Define.h"
#include "GameFramework/Actor.h"
#include "Client.generated.h"

UCLASS()
class HACKANDSLASH_API AClient : public AActor
{
	GENERATED_BODY()
public:
	AClient();
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable, Category = Connection)
	bool IsAlreadyInitialized();
	UFUNCTION(BlueprintCallable, Category = Connection)
	bool Connect();
	UFUNCTION(BlueprintCallable, Category = Connection)
	void Init(AHackAndSlashPlayerController* PC);
	UFUNCTION(BlueprintCallable, Category = Connection)
	bool Login(FString username, FString password);
	UFUNCTION(BlueprintCallable, Category = Connection)
	void Logout();
	UFUNCTION(BlueprintCallable, Category = Game)
	void ReturnToMenu();
	UFUNCTION(BlueprintCallable, Category = Game)
	void MenuLoaded(AHackAndSlashPlayerController* PC);
	UFUNCTION(BlueprintCallable, Category = Game)
	void SendEnterWorldComplete(AHackAndSlashPlayerController *PC, FVector position, int32 mapID);
	UFUNCTION(BlueprintCallable, Category = Game)
	void SendMapID(int32 mapID);
	UFUNCTION(BlueprintCallable, Category = Game)
	void SwitchMap();
	UFUNCTION(BlueprintCallable, Category = Game)
	void SendGroupInvit(int32 AccountID);
	UFUNCTION(BlueprintCallable, Category = Game)
	void AcceptGroupInvit(bool accept, int32 accountID);
	UFUNCTION(BlueprintCallable, Category = Game)
	bool isConnected();
	UFUNCTION(BlueprintCallable, Category = Game)
	void SendEnterWorldReq(int32 mapID, int32 charID, int32 difficu);
	UFUNCTION(BlueprintCallable, Category = Groupe)
	void DoIamLeader(const bool &value);
	UFUNCTION(BlueprintCallable, Category = Groupe)
	void KickPlayerFromGroup(int32 charID);
	UFUNCTION(BlueprintCallable, Category = Chat)
	void SendWorldMessage(FString message);
};
