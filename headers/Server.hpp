#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <cstdlib>
# include <unistd.h>
# include <strings.h>
# include <cstring>
# include <sys/types.h>//pour les sockets
# include <sys/socket.h>//pour les sockets
# include <netinet/in.h>//pour les sockets
# include <arpa/inet.h>//pour les sockets
# include "S_Client.hpp"

class Server
{

	private:
	int                 ssock;
	fd_set              fd_read;
	fd_set              fd_write;
	int                 max_fd; //maximum fd available
	int					fd_max; //maximum fd set
	int					r;
	S_Client			**clients;
	struct sockaddr_in  sockserver;

	Server(void);
	Server(const Server & src);
	Server	&	operator=(const Server & src);
	
	public:
	Server(int port);
	~Server(void);
	int			run_serv(void);
	void		connection(S_Client **clients);
	void		init_fd(S_Client **clients);
	void		check_actions(S_Client **clients, int cs, char *msg);
	void		name_client(S_Client **clients, int cs, char *msg);
	void		send_msg_to_all(S_Client **clients,int cs, char *msg);
	void		check_fd(S_Client **clients);
	void		init_clt(void);
	void		init_clt(S_Client **clients);
	void		init_srv(int port);
	void		stop_serv(void);
	S_Client	**getClients(void);
	int			disconnection(void);
	int			getLimit(void);

};

#endif
