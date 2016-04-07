/*
	Select.hpp for project Server_Library
	Created on 8/2/2016
	Update on 8/2/2016 11:12 AM

	Copyright (c) 2016 Christian Chaumery
*/

#ifndef		SELECT_HPP_
# define	SELECT_HPP_

# include	"Network/Socket.hpp"

// Class that encapsulate the select() call and its properties
class Select
{
public:
	// Type of the fd_set
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
	// Constructor
	Select();
	// Destructor
	~Select();

	// Set all the fd_set to zero
	void	zero();
	/*
		Set a socket in a 'type' fd_set
		@param &sock:	socket to be set
		@param &type:	type of the fd_set
	*/
	void	set(Socket &sock, Type type);
	/*
		Check if a socket is ready in the 'type' fd_set
		@param &sock:	socket to check
		@param &type:	type of the fd_set
	*/
	int		isset(Socket &sock, Type type);

	/* Call to select() */
	int		start();

	/*
		Set the greater value of socket
		@param &sock:	socket to be set as ndfs if possible
	*/
	void	setNdfs(Socket &sock); // Should be private
	/*
		Set the timeout for select()
		@param tv_sec:	time in seconds
		@param tv_usec:	time in microseconds
	*/
	void	setTimeout(long tv_sec, long tv_usec);

	// clean the fucking loop
	int		UpdateLoop(Socket &server, Socket& cpy);
private:

};

#endif // !SELECT_HPP_

