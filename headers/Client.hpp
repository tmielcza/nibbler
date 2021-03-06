// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Client.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 18:13:41 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:13:42 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <cstdlib>
# include <unistd.h>
# include <strings.h>
# include <cstring>
# include <netdb.h>
# include <sys/types.h>//pour les sockets
# include <sys/socket.h>//pour les sockets
# include <netinet/in.h>//pour les sockets
# include <arpa/inet.h>//pour les sockets
# include <sys/select.h>

# include "Buff_Circle.hpp"
# include "Player.hpp"

class Client
{
	private:

	int						sock;
	int						r;
	fd_set					fd_read;
	fd_set					fd_write;
	Buff_Circle				b_read;
	Buff_Circle				b_write;
	char					tmp_read[BC_SIZE + 1];
	char					tmp_write[BC_SIZE + 1];
	Player					*_me1;
	Player					*_me2;
	std::list<Player*>		_players;
	bool					_pl2;
	bool					_init;
	bool					_wall;
	bool					_null1;
	bool					_null2;
	int						_width;
	int						_height;
	int						_maxPlayer;
	int						_nbPlayer;

	Client(const Client & src);
	Client	&	operator=(const Client & src);

	public:

	Client(void);
	Client(bool pl2);
	~Client(void);
	void				init(char *adr, int port);
	void				check_actions(void);
	void				do_select(void);
	void				run_clt(void);
	void				send_data(void);
	void				receive_data(void);
	void				set_write(char *tmp);
	char				*get_read(void);
	void				receive_entrance(void);
	void				Snake_direc(char *tmp);
	void				popFood(char *tmp);
	void				popBonus(char *tmp);
	void				init_Game(char *tmp);
	void				init_Others(char *tmp);
	std::list<Player*>	*getClients(void);
	void				make_cmd(char *tmp);
	Player				*getPlayer1(void);
	Player				*getPlayer2(void);
	bool				getInit(void);
	bool				getWall(void);
	int					getWidth(void);
	int					getHeight(void);
	int					getMaxPlayer(void);
	int					getNBPlayers(void);
	void				VerifySnakes(char *tmp);
	void				Snake_Eat(char *tmp);
	void				Snake_Take(char *tmp);
	void				Snake_Death(char *tmp);
	bool				getNull1(void);
	void				setNull1(bool null1);
	bool				getNull2(void);
	void				setNull2(bool null2);

};

char				**ft_strtab(char *str);

#endif
