/*
	Select.hpp for project Server_Library
	Created on 8/2/2016
	Update on 8/2/2016 11:12 AM

	Copyright (c) 2016 Christian Chaumery
*/

#ifndef		SELECT_HPP_
# define	SELECT_HPP_

# include	"Socket.hpp"

class SERVER_LIBRARY_API Select
{
public:
	enum Type
	{
		READ = 0,
		WRITE = 1,
		EXCEPT = 2
	};

private:
	SOCKET	_nfds;
	fd_set	_rdfs, _wrfs, _exfs;
	struct timeval	_timeout;

public:
	Select();
	~Select();

	void	zero();
	void	set(Socket &sock, Type type);
	int		isset(Socket &sock, Type type);

	int		start();

	void	setNdfs(Socket &sock);
	void	setTimeout(long tv_sec, long tv_usec);

private:

};

#endif // !SELECT_HPP_

