// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/08 17:04:14 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 21:39:07 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

# include <chrono>

# include "MapManager.hpp"
# include "GraphicsManager.hpp"
# include "Player.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "S_Client.hpp"

typedef std::chrono::high_resolution_clock Clock;

class GameManager
{
	private:

	int						_nbPlayer;
	int						_width;
	int						_height;
	bool					_pl2;
	bool					_master;
	bool					_multi;
	bool					_massif;
	bool					_leave;
	bool					_wall;
	int						_curPL;
	Client					*_client;
	std::list<Player*>		*_players;
	Server					*_serv;
	S_Client				**_clients;
	Player					*_me;
	Player					*_me2;

	public:

	GameManager(void);
	GameManager(bool pl2, bool multi, bool massif, bool master);
	GameManager(const GameManager & copy);
	~GameManager(void);

	GameManager	&	operator=(const GameManager & ass);

	double			deltaTime(void);
	void			init(int nbplayer, int width, int height, bool wall);
	void			init_tcp(char *addr, int port);
	bool			IsAlive(void);
	bool			leaving(void);
	void			update(double time);
	void			restart(void);
	int				getCurPL(void);
	int				getServPL(void);
	int				getCltPL(void);
	int				getMaxPlayer(void);
	void			Server_Check(bool co);
	void			Client_Check(void);
	bool			Client_init(void);
	void			init_from_clt(void);
	void			Bring_Serv_Clients(void);
	void			Bring_Client_Serv(void);
	void			setPlayertoServ(void);

};

#endif
