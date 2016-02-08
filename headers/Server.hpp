// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 18:15:09 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:15:10 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

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
	int					nbPlayers;
	S_Client			**clients;
	struct sockaddr_in  sockserver;
	bool				_wall;
	int					_width;
	int					_height;
	int					_maxPlayer;
	Player				*_me1;
	Player				*_me2;

	Server(void);
	Server(const Server & src);
	Server	&	operator=(const Server & src);
	
	public:
	Server(int port, bool wall, int width, int height, int maxPlayer, int nbPlayers);
	~Server(void);
	int			run_serv(bool co);
	void		connection(S_Client **clients);
	void		init_fd(S_Client **clients);
	void		check_actions(S_Client **clients, int cs, char *msg);
	void		do_cmd(S_Client **clients, int cs, char *msg);
	void		name_client(S_Client **clients, int cs, char *msg);
	void		create_snake(S_Client **clients, int cs, char *msg);
	void		send_msg_to_all(S_Client **clients,int cs, const char *msg);
	void		check_fd(S_Client **clients);
	void		check_fd_noCo(S_Client **clients);
	void		init_clt(void);
	void		init_clt(S_Client **clients);
	void		init_srv(int port);
	void		stop_serv(void);
	S_Client	**getClients(void);
	int			disconnection(void);
	int			getMaxFD(void);
	int			getNbPlayers(void);
	void		setPlayers(Player *me1, Player *me2);
	void		VerifySnakes(char *tmp);
	void		Snake_Eat(char *tmp);
	void		Snake_Take(char *tmp);
	void		Snake_Death(char *tmp);

};

#endif
