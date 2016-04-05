// AuthServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AuthServer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	AuthServer server;
	server.Start();
//	sAuth->Start();
	system("PAUSE");
	return 0;
}

