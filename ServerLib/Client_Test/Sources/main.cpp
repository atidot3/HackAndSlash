/*
	main.cpp for project Client_Test
	Created on 6/2/2016
	Update on 6/2/2016 1:34 PM

	Copyright (c) 2016 Christian Chaumery
*/

#include	<Socket.hpp>
#include	<Select.hpp>
#include	<iostream>

int		main()
{
	WSADATA		WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	bool			isRunning = true;
	unsigned int	port = 12345;
	int				ret = 0;
	std::string		str = "", cmd = "Hello Server";
	Socket	client("127.0.0.1", port);
	Select	select;

	client.Connect();
	select.setNdfs(client);
	
	while (isRunning)
	{
		select.zero();
		select.set(client, Select::READ);
		select.set(client, Select::WRITE);
		if (select.start() < 0)
		{
			std::cerr << "Select Error: " << WSAGetLastError() << std::endl;
			isRunning = false;
		}
		else if (select.isset(client, Select::READ))
		{
			ret = client.Recv(client, str);
			if (ret < 0)
				isRunning = false;
			else if (ret == 0)
			{
				std::cerr << "Server Disconnected" << std::endl;
				isRunning = false;
			}
			else
			{
				std::cout << str << std::endl;
				if (str == "quit")
					isRunning = false;
			}
		}
		else if (select.isset(client, Select::WRITE))
		{
			//client.Send(client, cmd);
		}
	}

	client.Close();
	WSACleanup();

	std::cerr << "Client Closed" << std::endl;

	while (42);

	return 0;
}