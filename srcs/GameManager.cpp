// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/08 17:19:46 by rduclos           #+#    #+#             //
//   Updated: 2015/12/04 17:32:26 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "GameManager.hpp"
#include "AEntity.hpp"
#include "Player.hpp"

GameManager::GameManager(void)
{
	std::cout << "Creating GameManager !" << std::endl;
	this->_master = true;
	this->_multi = false;
	this->_massif = false;
	this->_leave = false;
	this->_pl2 = false;
	this->_me = new Player();
	this->_curPL = 1;
}

GameManager::GameManager(bool pl2, bool multi, bool massif, bool master)
{
	std::cout << "Creating GameManager !" << std::endl;
	this->_multi = multi;
	this->_massif = massif;
	this->_master = master;
	this->_leave = false;
	this->_me = new Player(false, master);
	this->_curPL = 1;
	this->_pl2 = pl2;
	if (pl2 == true)
	{
		this->_curPL++;
		this->_me2 = new Player(true, master);
	}
	else
		this->_me2 = NULL;
}

GameManager::GameManager(const GameManager & copy)
{
	*this = copy;
}

GameManager::~GameManager(void)
{
	std::list<Player *>::iterator		pl = this->_players.begin();
	std::list<Player *>::iterator		end = this->_players.end();

	while (pl != end)
	{
		Player *del = *pl;
		this->_players.erase(pl);
		pl = this->_players.begin();
		delete del;
	}
	if (this->_me != NULL)
		delete this->_me;
	if (this->_me2 != NULL)
		delete this->_me2;

	std::cout << "Destroying GameManager !" << std::endl;
}

GameManager	&	GameManager::operator=(const GameManager & ass)
{
	this->_nbPlayer = ass._nbPlayer;
	this->_width = ass._width;
	this->_height = ass._height;
	this->_players = ass._players;
	this->_multi = ass._multi;
	this->_me = ass._me;
	this->_me2 = ass._me2;
	return (*this);
}

double			GameManager::deltaTime(void)
{
	static auto             last = Clock::now();
	auto                    time = Clock::now();
	float                   tmp;

	tmp = std::chrono::duration_cast<std::chrono::microseconds>(time - last).count() / 1000000.f;
	last = time;
	return (tmp);
}

void		GameManager::init(int nbplayer, int width, int height)
{
	this->_nbPlayer = nbplayer;
	this->_width = width;
	this->_height = height;
}

void		GameManager::init(int nbplayer, int width, int height, int port)
{
	this->_nbPlayer = nbplayer;
	this->_width = width;
	this->_height = height;
	if (this->_multi == true && this->_master == false && this->_massif == false)
	{
		//Version Client
		;
	}
	else if (this->_multi == true && this->_master == true && this->_massif == true)
	{
		//Version Client Massif
		;
	}
	else if (this->_multi == true && this->_master == true && this->_massif == false)
	{
		//Version Server
		this->_serv = new Server(port);
		this->_serv->init_clt(this->_clients);
	}
	else if (this->_multi == true && this->_master == true && this->_massif == true)
	{
		//Version Server Massif
		;
	}
	
}

bool		GameManager::IsAlive(void)
{
	bool	test = false;

	if (this->_me != NULL)
	{
		if (this->_me->IsAlive() == true)
			test = true;
		else
		{
			std::cout << "Player1 " << std ::endl;
			delete this->_me;
			this->_me = NULL;
		}
	}
	if (this->_me2 != NULL)
	{
		if (this->_me2->IsAlive() == true)
			test = true;
		else
		{
			std::cout << "Player2 " << std::endl;
			delete this->_me2;
			this->_me2 = NULL;
		}
	}
	if (this->_leave == true)
		test = false;
	return (test);
}

void		GameManager::update(double time)
{
	e_Input								input = I_Nope;
	std::list<e_Input>					inputs;
	std::list<Player *>::iterator		pl = this->_players.begin();
	std::list<Player *>::iterator		end = this->_players.end();
	bool								player1;

	inputs = GraphicsManager::Instance().getInput();
	GraphicsManager::Instance().clear();
	for (auto it = inputs.begin(); it != inputs.end(); it++)
	{
		if ((*it & I_Close) != 0)
			this->_leave = true;
		if ((*it & I_Restart) != 0)
		{
			if (this->_master == true)
			{
				this->restart();
				for (int i = 0; i < this->_nbPlayer; i++)
					MapManager::Instance().foodpop(true);
			}
		}
		if ((*it & I_Dir) != 0)
		{
			input = (e_Input)(*it & I_Dir);
			player1 = (*it & I_Player1);
			if (this->_me != NULL && player1)
			{
				if (this->_me->getSizeTouch() < 3)
					this->_me->add_touch((e_Cardinal)input);
			}
			else if (this->_me2 != NULL && !player1)
			{
				if (this->_me2->getSizeTouch() < 3)
					this->_me2->add_touch((e_Cardinal)input);
			}
		}
	}
	if (this->_me != NULL)
		this->_me->update(time);
	if (this->_me2 != NULL)
		this->_me2->update(time);
	if (this->_multi == true)
	{
		if (this->_master == true)
		{
			const char *tmp = MapManager::Instance().takeToSend().c_str();
			this->_serv->send_msg_to_all(this->_clients, -1, tmp);
			for (int i = 0; i < this->_serv->getMaxFD(); i++)
			{
				if (this->_clients[i]->get_type() == CLT_FD)
				{
					Player *tmp1;
					Player *tmp2;
					if ((tmp1 = this->_clients[i]->getPlayer1()) != NULL)
						tmp1->update(time);
					if ((tmp2 = this->_clients[i]->getPlayer2()) != NULL)
						tmp2->update(time);
				}
			}
		}
		else
		{
			while (pl != end)
			{
				(*pl)->update(time);
				pl++;
			}
		}
	}
}

bool			GameManager::leaving(void)
{
	return (this->_leave);
}

void			GameManager::restart(void)
{
	if (this->_me != NULL)
		delete this->_me;
	if (this->_pl2 == true && this->_me2 != NULL)
		delete this->_me2;
	MapManager::Instance().restart();
	this->_me = new Player();
	if (this->_pl2 == true)
		this->_me2 = new Player(true, true);
}

int				GameManager::getCurPL(void)
{
	return (this->_curPL);
}

void			GameManager::Server_Check(bool co)
{
	this->_serv->run_serv(co);
}

int				GameManager::getServPL(void)
{
	return (this->_serv->getNbPlayers());
}
