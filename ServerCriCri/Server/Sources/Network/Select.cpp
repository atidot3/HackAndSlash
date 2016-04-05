/*
	Select.cpp for project Server_Library
	Created on 8/2/2016
	Update on 8/2/2016 11:12 AM

	Copyright (c) 2016 Christian Chaumery
*/

#include	"Network/Select.hpp"

Select::Select()
{
	_nfds = 0;
	_timeout.tv_sec = 0;
	_timeout.tv_usec = 10000;
}

Select::~Select()
{
}

void Select::zero()
{
	FD_ZERO(&_rdfs);
	FD_ZERO(&_wrfs);
	FD_ZERO(&_exfs);
}

void Select::set(Socket &sock, Type type)
{
	if (type == READ)
		FD_SET(sock.getRawSocket(), &_rdfs);
	else if (type == WRITE)
		FD_SET(sock.getRawSocket(), &_wrfs);
	else if (type == EXCEPT)
		FD_SET(sock.getRawSocket(), &_exfs);
}

int Select::isset(Socket &sock, Type type)
{
	if (type == READ)
		return FD_ISSET(sock.getRawSocket(), &_rdfs);
	else if (type == WRITE)
		return FD_ISSET(sock.getRawSocket(), &_wrfs);
	else if (type == EXCEPT)
		return FD_ISSET(sock.getRawSocket(), &_exfs);
	return false;
}

int Select::start()
{
	return select((int)_nfds + 1, &_rdfs, &_wrfs, &_exfs, &_timeout);
}

void Select::setNdfs(Socket &sock)
{
	_nfds = sock.getRawSocket() > _nfds ? sock.getRawSocket() : _nfds;
}

void Select::setTimeout(long tv_sec, long tv_usec)
{
	_timeout.tv_sec = tv_sec;
	_timeout.tv_usec = tv_usec;
}
