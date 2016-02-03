#ifndef __UDPSOCKETSENDER_H__
#define __UDPSOCKETSENDER_H__

#pragma once

#include "HackAndSlash.h"
#include "Networking.h"
#include "../../NetLib/NetworkLibrary.h"
#include "AllowWindowsPlatformTypes.h"
#include <windows.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <thread>
#include <mutex>
#include <iostream>
#include "HideWindowsPlatformTypes.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS

class MyUdpSocketSender
{
public:
	MyUdpSocketSender();
	~MyUdpSocketSender();
	bool Connect();
	void Logout();
	bool SendClient(CNtlPacket * pPacket);
	void popPacket(CNtlPacket * pPacket, BYTE * buffer);
	int getPacketLen(BYTE* pHeaderPointer);
	TArray< TSharedRef<FInternetAddr> > addr;
	bool Init();
	void Tick();
	void RecvData(MyUdpSocketSender *sess);
	void ParsePacket(CNtlPacket* pPacket);
	void setController(AHackAndSlashPlayerController *PC){ ThePC = PC; }
	// AUTH FUNCTION
	bool Login(const char* user, const char* password);
	// GAME FUNCTION
	void SendEnterWorldReq(int32 mapID, int32 charID, Difficulty diff);
	void SendEnterGameComplete(NtlVector location, int32 mapID);
	void SendMovement(NtlVector location, int32 mapID);
	void SendMapID(int mapID);
	void SwitchMap(int charID);
	void BackToMenu();
	void MenuLoaded();
	// OTHER NETWORK THING
	void SendGroupInvit(int AccountIDToAdd);
	void AcceptGroupInvit(int AccountIDToAdd, bool accept);
	void KickPlayer(int32 charID);
	// CHAT
	void SendWorldMessage(const char* message, int accountID);
private:
	AHackAndSlashPlayerController *ThePC;
	bool							connected;
	CNtlNetQueue					m_recvQueue;
	CNtlClientNet					*m_pNetwork;
	CNtlNetSender					*m_NetSender;
public:
	CNtlPacket						packet;
	WSADATA							WSAData;
	SOCKET							sock;
	SOCKADDR_IN						sin;
	HANDLE							hProcessThread;
	bool							runnable;
	unsigned long					PreUpdate(MyUdpSocketSender* sess);
	static unsigned long WINAPI		StaticThreadStart(void* Param)
	{
		MyUdpSocketSender* This = (MyUdpSocketSender*)Param;
		return This->PreUpdate(This);
	}
};

#endif